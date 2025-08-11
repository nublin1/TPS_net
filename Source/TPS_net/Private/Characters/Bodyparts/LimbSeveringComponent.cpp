// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Bodyparts/LimbSeveringComponent.h"

#include "Animations/AnimInstances/SeveredLimbAnimInstance.h"
#include "Engine/SkeletalMeshSocket.h"
#include "FX/EffectFXManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "Rendering/SkeletalMeshRenderData.h"

ULimbSeveringComponent::ULimbSeveringComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ULimbSeveringComponent::InitializeVertexColors);
}

void ULimbSeveringComponent::InitializeVertexColors()
{
	if(IsRunningDedicatedServer()) return;
		
	for (int32 i = 0; i < SeveringMesh->GetNumLODs(); i++)
	{
		TArray<FLinearColor> Colors = UVertexColorUtility::GetCurrentVertexColors(SeveringMesh, i);
		UVertexColorUtility::SetLinearColorChannel(Colors, 0.f, BloodVertexChannel);
		SeveringMesh->SetVertexColorOverride_LinearColor(i, Colors);
	}
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
	if (bDisableSevering) return;
	if (!SeveredLimbClass) return;
	if (!CheckBoneFilter(BoneName)) return;
	if(SeveredLimbs.Contains(BoneName)) return;

	PreSevering(BoneName, Impulse);

	const FTransform CachedBoneTransform = SeveringMesh->GetSocketTransform(BoneName, RTS_World);

	SeveringMesh->HideBoneByName(BoneName, EPhysBodyOp::PBO_Term);
	SeveringMesh->BreakConstraint(FVector(0), FVector(0), BoneName);
	
	auto LimbSpawnedActor = CreateSeveredLimb(BoneName, CachedBoneTransform);
	
	SeveredLimbs.Add(BoneName, LimbSpawnedActor);
	FrameDelayedSevering(LimbSpawnedActor, BoneName, Impulse, CachedBoneTransform);
}

void ULimbSeveringComponent::PreSevering(const FName BoneName, FVector Impulse)
{
	if (OnPreSevering.IsBound())
		OnPreSevering.Broadcast(BoneName, Impulse);

	if (!FX_BloodBurst) return;
	
	FVector HitLocation = SeveringMesh->GetSocketLocation(BoneName);	
	UEffectFXManager::SpawnFXEffect(FX_BloodBurst, nullptr, NAME_None, HitLocation, Impulse.Rotation(), FVector(BloodParticleScale));

	LineTraceForBloodPool(HitLocation, Impulse.GetSafeNormal());

	if(BoneName != NAME_None) ApplyBlood(BoneName);
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

void ULimbSeveringComponent::LineTraceForBloodPool(FVector HitLocation, FVector Direction)
{
	FVector End = Direction;
	End.Z = -0.7;
	End *= FVector(2000.f);
	End += HitLocation;
	
	FHitResult HitResult;
	
	UKismetSystemLibrary::LineTraceSingleForObjects(GetOwner(),
		HitLocation, End,
		{EObjectTypeQuery::ObjectTypeQuery1}, true, {},
		EDrawDebugTrace::None, HitResult, true);
	
	if(!HitResult.bBlockingHit) return;
	
	SpawnBloodPool(HitResult.ImpactPoint, HitResult.ImpactNormal, Direction, HitResult.GetComponent());
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

AActor* ULimbSeveringComponent::CreateSeveredLimb(const FName BoneName, const FTransform& Transform)
{
	FVector SpawnLocation = Transform.GetLocation();
	FRotator SpawnRotation = Transform.Rotator();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	
	auto SpawnedSeveredLimbActor = GetWorld()->SpawnActor<AActor>(SeveredLimbClass, SpawnLocation, SpawnRotation, SpawnParams);
	if (!SpawnedSeveredLimbActor)
	{
		return nullptr;
	}

	if (bBlockFurtherSevering)
	{
		ULimbSeveringComponent* SpawnedLimbSeveringComponent = SpawnedSeveredLimbActor->FindComponentByClass<ULimbSeveringComponent>();
		if (SpawnedLimbSeveringComponent)
		{
			SpawnedLimbSeveringComponent->bDisableSevering = true;
			SpawnedLimbSeveringComponent->bBlockFurtherSevering = true;
		}
	}
	else
	{
		ULimbSeveringComponent* TargetLimbSeveringComp = SpawnedSeveredLimbActor->FindComponentByClass<ULimbSeveringComponent>();
		if (!TargetLimbSeveringComp)
		{
			TargetLimbSeveringComp = NewObject<ULimbSeveringComponent>(SpawnedSeveredLimbActor->GetRootComponent());
		}

		TargetLimbSeveringComp->bDisableSevering = false;
		TargetLimbSeveringComp->bBlockFurtherSevering = false;
		TargetLimbSeveringComp->AddBoneToBlackList(BoneName);
	}
	
	USkeletalMeshComponent* SpawnedLimbMeshComponent = SpawnedSeveredLimbActor->FindComponentByClass<USkeletalMeshComponent>();
	if (!SpawnedLimbMeshComponent)
	{
		SpawnedLimbMeshComponent = NewObject<USkeletalMeshComponent>(SpawnedSeveredLimbActor->GetRootComponent());
		SpawnedLimbMeshComponent->RegisterComponent();
	}
	
	ApplyAnimInstanceToSeveredLimb(SpawnedLimbMeshComponent, BoneName);
	CopyLimbProperties(SeveringMesh, SpawnedLimbMeshComponent);

	SpawnedSeveredLimbActor->Tags.Add("Severed Limb");
	if(bSupportAttachedChildMeshes)
	{
		TArray<USkeletalMeshSocket*> UsedSockets;
		GetSocketsOnBoneAndChildren(SeveringMesh, BoneName, UsedSockets);
		TSet<FName> SocketNames;
		for (USkeletalMeshSocket* Socket : UsedSockets)
		{
			SocketNames.Add(Socket->SocketName);
		}
		
		for (auto Comp : GetAllAttachedMeshes(SeveringMesh, SocketNames))
		{
			//UE_LOG(LogTemp, Display, TEXT(" Owner %s has ."), *Comp->GetName());
			
			if(Comp->ComponentTags.Contains(Tag_KeepAttached))
			{
				Comp->SetHiddenInGame(true);
				continue;
			}

			if(Comp->ComponentTags.Contains(Tag_MoveToSeveredLimb))
			{				
				Comp->AttachToComponent(SpawnedLimbMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Comp->GetAttachSocketName());
				continue;
			}
			
			if(Comp->ComponentTags.Contains(Tag_DetachOnSever))
			{
				auto& AttachedComps = BoneAttachedComponents.FindOrAdd(BoneName);
				if (!AttachedComps.Contains(Comp))
				{
					AttachedComps.Add(Comp );
				}
				
				Comp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			}
			
			/*if(Comp->ComponentTags.Contains(Tag_SeveredLimb))
			{
				// Copy the Mesh
				USkeletalMeshComponent* Child = NewObject<USkeletalMeshComponent>(GetOwner());
				Child->AttachToComponent(SpawnedLimbMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, Comp->GetAttachSocketName());
				Child->RegisterComponent();
				CopyLimbProperties(Mesh, Child);
				Child->SetLeaderPoseComponent(SpawnedLimbMeshComponent);
			}*/
		}
	}
	
	return SpawnedSeveredLimbActor;
}

void ULimbSeveringComponent::FrameDelayedSevering(AActor* Component, const FName BoneName,
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
		USkeletalMeshComponent* SpawnedLimbMeshComponent = SeveredLimbData.TargetActor->FindComponentByClass<USkeletalMeshComponent>();
		USeveredLimbAnimInstance* AnimInstance = Cast<USeveredLimbAnimInstance>(SpawnedLimbMeshComponent->GetAnimInstance());
		AnimInstance->bIsSynced = true;
		
		if (bUseSpecificCollisionObjectType && !CollisionProfileName.IsNone())
		{
			SpawnedLimbMeshComponent->SetCollisionProfileName(CollisionProfileName);
		}
		else
		{
			SpawnedLimbMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			SpawnedLimbMeshComponent->SetCollisionObjectType(ECC_PhysicsBody);
			SpawnedLimbMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
			SpawnedLimbMeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
			SpawnedLimbMeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
		}
		
		//CreateDismemberLimbPhysicsAsset(CachedDismemberedLimb, Data.BoneName);
		
		SpawnedLimbMeshComponent->SetSimulatePhysics(true);
		
		SpawnedLimbMeshComponent->AddImpulse(SeveredLimbData.Impulse, SeveredLimbData.BoneName, true);
		
		//UpdateMissingLimbs(CachedDismemberedLimb, Data.BoneName);

		if (!BoneAttachedComponents.IsEmpty())
		{
			for (auto& Pair : BoneAttachedComponents)
			{
				FName Key = Pair.Key;
				auto& AttachedComp = Pair.Value;

				for (int32 i = AttachedComp.Num() - 1; i >= 0; --i)
				{
					if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(AttachedComp[i]))
					{
						PrimComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
						PrimComp->SetCollisionObjectType(ECC_PhysicsBody);
						PrimComp->SetCollisionResponseToAllChannels(ECR_Ignore);
						PrimComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
						PrimComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
						PrimComp->SetSimulatePhysics(true);
						PrimComp->AddImpulse(SeveredLimbData.Impulse);
					}

					AttachedComp.RemoveAt(i);
				}

				BoneAttachedComponents.Remove(Key);
			}
		}
		
		PostSevering(SeveredLimbData.BoneName, SpawnedLimbMeshComponent);
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

TArray<USceneComponent*> ULimbSeveringComponent::GetAllAttachedMeshes(
	USkeletalMeshComponent* SkeletalMeshComponent, TSet<FName> UsedSockets)
{
	TArray<USceneComponent*> Children;
	TArray<USceneComponent*> Result;

	SkeletalMeshComponent->GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		if (!Child) continue;
	
		if (Child->GetAttachParent() == SkeletalMeshComponent)
		{
			FName SocketName = Child->GetAttachSocketName();
			if (UsedSockets.Contains(SocketName))
			{
				Result.Add(Child);
			}
		}
	}

	return Result;
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

void ULimbSeveringComponent::ApplyBlood(FName BoneName, float Radius, float Hardness)
{
	if(IsRunningDedicatedServer()) return;

	if(SeveringMesh->ComponentTags.Contains("Ignore Blood")) return;

	ApplyBloodToMesh(Mesh, BoneName, Radius, Hardness);
}

void ULimbSeveringComponent::ApplyAnimInstanceToSeveredLimb(USkeletalMeshComponent* Component, FName BoneName)
{
	Component->SetAnimInstanceClass(SeveredLimbAnimClass);
	USeveredLimbAnimInstance* AnimInstance = Cast<USeveredLimbAnimInstance>(Component->GetAnimInstance());
	if (!AnimInstance)
		return;

	AnimInstance->PelvisBoneName = PelvisBoneName;
	AnimInstance->LimbBoneName = BoneName;

	AnimInstance->SourceMeshForPose = Component;
}

