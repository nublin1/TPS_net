// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Components/HealthComponent.h"

#include "Components/CapsuleComponent.h"
#include "Interfaces/IHealthInterface.h"

class UCapsuleComponent;
// Sets default values for this component's properties
UHealthComponent::UHealthComponent(): MaxHealth(100)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Health = MaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::TakeDamage(float DamageAmount)
{
	if (bIsGodMode)
	{
		return;
	}
	
	Health -= DamageAmount;
	if (Health < 0.0f)
	{
		Health = 0.0f;

		auto result = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
		if (result)
		{
			result->SetSimulatePhysics(true);
			result->SetCollisionProfileName(TEXT("Ragdoll"), true);
			GetOwner()->FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		

		if (OnKilledDelegate.IsBound())
			OnKilledDelegate.Broadcast(GetOwner());

		FTimerHandle UnusedHandle;
		GetOwner()->GetWorldTimerManager().SetTimer(UnusedHandle, [this]()
		{
			GetOwner()->Destroy();
		}, 5.0f, false);
	}
}
