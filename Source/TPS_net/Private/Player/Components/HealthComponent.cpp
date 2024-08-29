// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Components/HealthComponent.h"

#include "Components/CapsuleComponent.h"

class UCapsuleComponent;
// Sets default values for this component's properties
UHealthComponent::UHealthComponent(): Health(100), MaxHealth(100)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UHealthComponent::UHealthComponent(float Health, float MaxHealth): Health(Health),
																	 MaxHealth(MaxHealth)
{
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UHealthComponent::TakeDamage(float DamageAmount)
{
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

		//auto AControlller = this->GetController();
		//AAIController* myAIEnemyController;

		if (OnKilledDelegate.IsBound())
			OnKilledDelegate.Broadcast(GetOwner());

		FTimerHandle UnusedHandle;
		GetOwner()->GetWorldTimerManager().SetTimer(UnusedHandle, [this]()
		{
			GetOwner()->Destroy();
		}, 5.0f, false);
	}
}
