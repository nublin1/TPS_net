// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPC/Components/ZombieCombatComponent.h"

#include "Engine/Engine.h"
#include "AITypes.h"
#include "Components/BoxComponent.h"
#include "Interfaces/IHealthInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "PlayerControllers/TPS/PlayerController_TPS.h"

// Sets default values for this component's properties
UZombieCombatComponent::UZombieCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ComponentTags.Add(FName("ZombieCombatComponentTag"));
}

void UZombieCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	auto OwnerSkeletalMeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	if (OwnerSkeletalMeshComponent)
		SkeletalMeshComponent = OwnerSkeletalMeshComponent;
}


bool UZombieCombatComponent::RequestHitDetect()
{
	AActor* Owner = GetOwner();
	if (!Owner) return false;

	if (Owner->HasAuthority())
	{
		return HitDetect();
	}
	
	auto PC = Cast<APlayerController_TPS>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (PC)
	{
		// Клиент посылает запрос на сервер через свой PlayerController
		PC->RequestHitDetectOnServer(Owner);
	}

	return false;
}

bool UZombieCombatComponent::HitDetect()
{
	AActor* Owner = GetOwner();
	if (!Owner) return false;

	USkeletalMeshComponent* SkeletalMesh = Owner->FindComponentByClass<USkeletalMeshComponent>();
	if (!SkeletalMesh) return false;

	FVector SocketLocation = SkeletalMesh->GetSocketLocation(FName("hand_r"));
	FVector Start = SocketLocation;
	FVector End = Start;
	float Radius = 45.0f;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());

	TArray<FHitResult> OutHits;

	// Multi Sphere Trace
	bool bHit = GetWorld()->SweepMultiByObjectType(
		OutHits,
		Start,
		End,
		FQuat::Identity,
		FCollisionObjectQueryParams(ObjectTypes),
		FCollisionShape::MakeSphere(Radius),
		Params
	);

	if (IsDebug)
	{
		DrawDebugSphere(GetWorld(), Start, Radius, 12, FColor::Red, false, 1.0f);
		if (bHit)
		{
			DrawDebugSphere(GetWorld(), Start, Radius, 12, FColor::Green, false, 1.0f);
		}
	}

	for (FHitResult Hit : OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		auto OwnerClass = GetOwner()->GetClass();

		if (HitActor && !AlreadyHitTargets.Contains(HitActor) && !HitActor->IsA(OwnerClass))
		{
			AlreadyHitTargets.Add(HitActor, false);
			//UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *Hit.GetActor()->GetName());
		}
	}

	if (AlreadyHitTargets.Num() <= 0)
	{
		return false;
	}
	for (auto& Hit : AlreadyHitTargets)
	{
		if (Hit.Key->Implements<UIHealthInterface>() && Hit.Value == false)
		{
			ServerApplyDamage(Hit.Key);
			Hit.Value = true;
		}
	}

	return true;
}

void UZombieCombatComponent::Server_HitDetect_Implementation()
{
	HitDetect();
}

void UZombieCombatComponent::ServerApplyDamage_Implementation(AActor* HitActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("ApplyDamage on Server"));
	UGameplayStatics::ApplyDamage(HitActor, 10.0f, HitActor->GetInstigatorController(), nullptr, nullptr);
}


void UZombieCombatComponent::ClearAlreadyHitTargets()
{
	if (GetOwner()->HasAuthority())
	{
		AlreadyHitTargets.Empty();
		return;
	}

	auto PC = Cast<APlayerController_TPS>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	if (PC)
	{
		// Клиент посылает запрос на сервер через свой PlayerController
		PC->RequestClearAlreadyHitTargetsOnServer(GetOwner());
	}
}

void UZombieCombatComponent::ServerClearAlreadyHitTargets_Implementation()
{
	AlreadyHitTargets.Empty();
}

void UZombieCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
