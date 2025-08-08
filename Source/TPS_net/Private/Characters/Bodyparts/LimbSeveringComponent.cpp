// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Bodyparts/LimbSeveringComponent.h"

#include "Animations/AnimInstances/SeveredLimbAnimInstance.h"
#include "Engine/SkeletalMeshSocket.h"
#include "PhysicsEngine/PhysicsAsset.h"

ULimbSeveringComponent::ULimbSeveringComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void ULimbSeveringComponent::BeginPlay()
{
	Super::BeginPlay();

	if(PelvisBoneName == NAME_None)
	{
		UE_LOG(LogTemp, Display, TEXT("Component has an invalid Pelvis Bone Name"));
	}

	if(!SeveringMesh)
		FindSkeletalMeshComponent();

	if (!SeveredLimbClass)
		UE_LOG(LogTemp, Display, TEXT("Component has an invalid SeveredLimbClass"));

	if (!SeveredLimbAnimClass)
		UE_LOG(LogTemp, Display, TEXT("Component has an invalid SeveredLimbAnimClass"));
	
}

void ULimbSeveringComponent::SeverLimbByBone(FName BoneName, FVector Impulse)
{
	if(IsVirtualBone(BoneName))
	{
		UE_LOG(LogTemp, Display, TEXT("Bone %s is Virtual"), *BoneName.ToString());
	}
	
	if(!GetIsReplicated())
	{
		LimbSevering_Internal(BoneName, Impulse);
		return;
	}

	if(GetOwner()->HasAuthority())
	{
		LimbSevering_Multi(BoneName, Impulse);
	}
	else
	{
		LimbSevering_Server(BoneName, Impulse);
	}
}

void ULimbSeveringComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ULimbSeveringComponent::LimbSevering_Server_Implementation(FName BoneName, const FVector& Impulse)
{
	LimbSevering_Multi(BoneName, Impulse);
}

void ULimbSeveringComponent::LimbSevering_Multi_Implementation(FName BoneName, const FVector& Impulse)
{
	if(GetOwner()->HasAuthority()) return;

	LimbSevering_Internal(BoneName, Impulse);
}

void ULimbSeveringComponent::LimbSevering_Internal(FName BoneName, const FVector& Impulse)
{
	if (!SeveredLimbClass) return;
	if (!CheckBoneFilter(BoneName)) return;
	if(SeveredLimbs.Contains(BoneName)) return;

	PreSevering(BoneName, Impulse);

	const FTransform CachedBoneTransform = SeveringMesh->GetSocketTransform(BoneName, RTS_World);

	SeveringMesh->HideBoneByName(BoneName, EPhysBodyOp::PBO_Term);
	SeveringMesh->BreakConstraint(FVector(0), FVector(0), BoneName);

	TArray<USkeletalMeshSocket*> UsedSockets;
	GetSocketsOnBoneAndChildren(SeveringMesh, BoneName, UsedSockets);
	TSet<FName> SocketNames;
	for (USkeletalMeshSocket* Socket : UsedSockets)
	{
		SocketNames.Add(Socket->SocketName);
	}
	
	auto LimbSpawnedActor = CreateSeveredLimb(BoneName, CachedBoneTransform, SocketNames);
	USkeletalMeshComponent* TargetMeshComp = LimbSpawnedActor->FindComponentByClass<USkeletalMeshComponent>();
	
	SeveredLimbs.Add(BoneName);
	FrameDelayedSevering(TargetMeshComp, BoneName, Impulse, CachedBoneTransform);
}

void ULimbSeveringComponent::PreSevering(const FName BoneName, FVector Impulse)
{
	if (OnPreSevering.IsBound())
		OnPreSevering.Broadcast(BoneName, Impulse);
}

void ULimbSeveringComponent::PostSevering(const FName BoneName, USkeletalMeshComponent* DismemberMesh)
{
	if (OnPostSevering.IsBound())
		OnPostSevering.Broadcast(BoneName, DismemberMesh);
}

bool ULimbSeveringComponent::CheckBoneFilter(const FName BoneName)
{
	if(BlacklistBones.Contains(BoneName)) return false;
	if(WhitelistBones.Num() > 0 && !WhitelistBones.Contains(BoneName)) return false;
	return true;
}

bool ULimbSeveringComponent::IsVirtualBone(FName BoneName)
{
	FString BoneString = BoneName.ToString();
	
	if(BoneString.Len() < 2) return false;
	
	return BoneString[0] == *"V" && BoneString[1] == *"B";
}

void ULimbSeveringComponent::FindSkeletalMeshComponent()
{
	TArray<TObjectPtr<USkeletalMeshComponent>> OwnersMeshComponents;
	GetOwner()->GetComponents(OwnersMeshComponents);

	if(OwnersMeshComponents.IsEmpty())
	{
		UE_LOG(LogTemp, Display, TEXT(" Owner %s has no Skeletal Mesh Components."), *GetOwner()->GetName());
		return;
	}

	SeveringMesh = OwnersMeshComponents[0];
}

AActor* ULimbSeveringComponent::CreateSeveredLimb(const FName BoneName, const FTransform& Transform, TSet<FName> Sockets)
{
	FVector SpawnLocation = Transform.GetLocation();
	FRotator SpawnRotation = Transform.Rotator();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	
	auto LimbSpawnedActor = GetWorld()->SpawnActor<AActor>(SeveredLimbClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (!LimbSpawnedActor)
	{
		return nullptr;
	}

	USkeletalMeshComponent* TargetMeshComp = LimbSpawnedActor->FindComponentByClass<USkeletalMeshComponent>();
	if (!TargetMeshComp)
	{
		TargetMeshComp =  NewObject<USkeletalMeshComponent>(LimbSpawnedActor->GetRootComponent());
		TargetMeshComp->RegisterComponent();
	}
	
	ApplyAnimInstanceToSeveredLimb(TargetMeshComp, BoneName);
	CopyLimbProperties(SeveringMesh, TargetMeshComp);

	LimbSpawnedActor->Tags.Add("Severed Limb");
	if(bSupportAttachedChildMeshes)
	{
		for (auto Mesh : GetAllAttachedMeshes(SeveringMesh, Sockets))
		{
			if(Mesh->ComponentTags.Contains(Tag_NoSevering)) continue;
			//if(Mesh->GetAttachSocketName() != NAME_None && !LimbMap->GetLimb(BoneName).Get().Contains(Mesh->GetAttachSocketName())) continue;

			if(Mesh->ComponentTags.Contains(Tag_TransferSevering))
			{				
				Mesh->AttachToComponent(TargetMeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, Mesh->GetAttachSocketName());
				continue;
			}
		}
	}
	
	return LimbSpawnedActor;
}

void ULimbSeveringComponent::FrameDelayedSevering(USkeletalMeshComponent* Component, const FName BoneName,
                                                  const FVector& Impulse, const FTransform& Transform)
{
	FSeveredLimbFrame SeveredLimbFrame (BoneName, Component);
	SeveredLimbFrame.Impulse = Impulse;
	SeveredLimbFrame.Transform = Transform;
	DelayedSeveredLimbs.Add(SeveredLimbFrame);

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ULimbSeveringComponent::SeveringLimbFrameDelayed);
}

void ULimbSeveringComponent::SeveringLimbFrameDelayed()
{
	for (auto SeveredLimbData : DelayedSeveredLimbs)
	{
		USkeletalMeshComponent* CachedSeveredLimb = SeveredLimbData.SkeletalMeshComponent;

		if (bUseSpecificCollisionObjectType && !CollisionProfileName.IsNone())
		{
			CachedSeveredLimb->SetCollisionProfileName(CollisionProfileName);
		}
		else
		{
			CachedSeveredLimb->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			CachedSeveredLimb->SetCollisionObjectType(ECC_PhysicsBody);
			CachedSeveredLimb->SetCollisionResponseToAllChannels(ECR_Ignore);
			CachedSeveredLimb->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
			CachedSeveredLimb->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
		}
		

		//CreateDismemberLimbPhysicsAsset(CachedDismemberedLimb, Data.BoneName);
		
		CachedSeveredLimb->SetSimulatePhysics(true);
		
		CachedSeveredLimb->AddImpulse(SeveredLimbData.Impulse, SeveredLimbData.BoneName, true);
		
		//UpdateMissingLimbs(CachedDismemberedLimb, Data.BoneName);
		
		PostSevering(SeveredLimbData.BoneName, CachedSeveredLimb);
	}

	DelayedSeveredLimbs.Reset();
}

void ULimbSeveringComponent::CopyLimbProperties(USkeletalMeshComponent* Mesh, USkeletalMeshComponent* Limb)
{
	// Copy Mesh
	Limb->SetSkeletalMesh(Mesh->GetSkeletalMeshAsset());

	// Copy Materials
	for(int32 i = 0; i < Mesh->GetNumMaterials(); i++)
	{
		Limb->SetMaterial(i, Mesh->GetMaterial(i));
	}
}

void ULimbSeveringComponent::GetSocketsOnBoneAndChildren(USkeletalMeshComponent* MeshComp, FName RootBone,
	TArray<USkeletalMeshSocket*>& OutSockets)
{
	auto MeshAsset =  MeshComp->GetSkeletalMeshAsset();
	const int32 RootBoneIndex = MeshComp->GetBoneIndex(RootBone);
	if (RootBoneIndex == INDEX_NONE)
		return;

	const FReferenceSkeleton& RefSkeleton = MeshAsset->GetRefSkeleton();
	const int32 NumBones = RefSkeleton.GetNum();
	TSet<FName> BoneAndChildren;
	for (int32 i = 0; i < NumBones; ++i)
	{
		if (MeshComp->BoneIsChildOf(MeshComp->GetBoneName(i), MeshComp->GetBoneName(RootBoneIndex)))
		{
			BoneAndChildren.Add(MeshComp->GetBoneName(i));
			//UE_LOG(LogTemp, Display, TEXT("bone %s is child of %s"), *MeshComp->GetBoneName(i).ToString(), *MeshComp->GetBoneName(RootBoneIndex).ToString());
		}
	}

	auto SocketsArray = MeshAsset->GetActiveSocketList();
	for (auto Socket : SocketsArray)
	{
		if (Socket && BoneAndChildren.Contains(Socket->BoneName))
			OutSockets.Add(Socket);
	}
}

TArray<USkeletalMeshComponent*> ULimbSeveringComponent::GetAllAttachedMeshes(
	USkeletalMeshComponent* SkeletalMeshComponent, TSet<FName> UsedSockets)
{
	TArray<USceneComponent*> Children;
	TArray<USkeletalMeshComponent*> ChildMeshes;

	SkeletalMeshComponent->GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		if(!Child->IsA(USkeletalMeshComponent::StaticClass())) continue;
	
		USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(Child);
		if(Mesh)
		{
			FName SocketName = Child->GetAttachSocketName();
			if (UsedSockets.Contains(SocketName))
			{
				ChildMeshes.Add(Mesh);
			}
		}
	}

	return ChildMeshes;
}

void ULimbSeveringComponent::GenerateSeveredLimbPhysicsAsset(FName InLimb)
{
	UPhysicsAsset* NewPhysicsAsset = DuplicateObject<UPhysicsAsset>(SeveringMesh->GetPhysicsAsset(), SeveringMesh);
	
	TArray<FName> BoneNames;
	SeveringMesh->GetBoneNames(BoneNames);
	
	for(const FName Bone : BoneNames)
	{
		const int32 Index = NewPhysicsAsset->FindBodyIndex(Bone);

		if(Index == INDEX_NONE) continue;
		//if(LimbMap->GetLimb(InLimb).Get().Contains(Bone))
		{
			//TerminatePhysicsBodies(NewPhysicsAsset, Index); // <--- From: FPhysicsAssetUtils::DestroyBody(NewPhysicsAsset, Index);
		}
	}
}

void ULimbSeveringComponent::ApplyAnimInstanceToSeveredLimb(USkeletalMeshComponent* Component, FName BoneName)
{
	Component->SetAnimInstanceClass(SeveredLimbAnimClass);
	USeveredLimbAnimInstance* AnimInstance = Cast<USeveredLimbAnimInstance>(Component->GetAnimInstance());
	if (!AnimInstance)
		return;

	AnimInstance->PelvisBoneName = PelvisBoneName;
	AnimInstance->LimbBoneName = BoneName;
}

