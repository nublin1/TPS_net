// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Bodyparts/LimbSeveringComponent.h"

#include "Animations/AnimInstances/SeveredLimbAnimInstance.h"
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
	if(SeveredLimbs.Contains(BoneName)) return;

	PreSevering(BoneName, Impulse);

	const FTransform CachedBoneTransform = SeveringMesh->GetSocketTransform(BoneName, RTS_World);

	SeveringMesh->HideBoneByName(BoneName, EPhysBodyOp::PBO_Term);
	SeveringMesh->BreakConstraint(FVector(0), FVector(0), BoneName);

	FVector SpawnLocation = CachedBoneTransform.GetLocation();
	FRotator SpawnRotation = CachedBoneTransform.Rotator();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	
	auto LimbSpawnedActor = GetWorld()->SpawnActor<AActor>(SeveredLimbClass, SpawnLocation, SpawnRotation, SpawnParams);

	if (USkeletalMeshComponent* TargetMeshComp = LimbSpawnedActor->FindComponentByClass<USkeletalMeshComponent>())
	{
		ApplyAnimInstanceToSeveredLimb(TargetMeshComp, BoneName);
		CopyLimbProperties(SeveringMesh, TargetMeshComp);
	}

	SeveredLimbs.Add(BoneName);
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

