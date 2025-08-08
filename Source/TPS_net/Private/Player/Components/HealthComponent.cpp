// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Components/HealthComponent.h"

#include "Components/CapsuleComponent.h"
#include "Interfaces/IHealthInterface.h"
#include "Net/UnrealNetwork.h"

class UCapsuleComponent;
// Sets default values for this component's properties
UHealthComponent::UHealthComponent(): MaxHealth(100)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ComponentTags.Add("HealthComponent");

	Health = MaxHealth;

	ArmBoneNames = { "upperarm_l", "lowerarm_l", "hand_l", "upperarm_r", "lowerarm_r", "hand_r" };
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, bIsGodMode);
	DOREPLIFETIME(UHealthComponent, Health);
	DOREPLIFETIME(UHealthComponent, MaxHealth);
}

void UHealthComponent::TakeDamage(float DamageAmount, AController* EventInstigator )
{
	/*if (!GetOwner()-> GetInstigatorController())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Controller is Null"));
		return;
	}*/

	if (!GetOwner()->HasAuthority())
	{
		ServerTakeDamage(DamageAmount);
		return;
	}

	ApplyDamage(DamageAmount, EventInstigator);
}

void UHealthComponent::ServerTakeDamage_Implementation(float DamageAmount)
{
	NetMulticastTakeDamage(DamageAmount);
}

void UHealthComponent::NetMulticastTakeDamage_Implementation(float DamageAmount)
{
	if (!bIsGodMode)
	{
		Health -= DamageAmount;
	}
}

void UHealthComponent::ApplyDamage(float DamageAmount, AController* EventInstigator)
{
	if (bIsGodMode)
	{
		return;
	}
	
	float OldHealth = Health;
	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);
	if (OnHealthChangedDelegate.IsBound())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Здоровье изменилось на сервере: %f"), Health);
		OnHealthChangedDelegate.Broadcast(Health);
	}
	
	if (Health <= 0.0f && OldHealth > 0.0f)
	{
		if (OnKilledDelegate.IsBound())
		{
			OnKilledDelegate.Broadcast(GetOwner(), EventInstigator? EventInstigator: nullptr);
		}
	}
}

void UHealthComponent::OnRep_Health() const
{
	//UE_LOG(LogTemp, Warning, TEXT("Здоровье изменилось на клиенте: %f"), Health);
	if (OnHealthChangedDelegate.IsBound())
	{
		OnHealthChangedDelegate.Broadcast(Health);
	}
	
}
