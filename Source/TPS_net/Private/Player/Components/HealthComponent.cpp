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

	Health = MaxHealth;
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

void UHealthComponent::TakeDamage(float DamageAmount)
{
	const auto Controller = GetOwner()-> GetInstigatorController();
	if (!GetOwner()-> GetInstigatorController())
	{
		//UE_LOG(LogTemp, Warning, TEXT("Controller is Null"));
		return;
	}

	if (Controller->IsPlayerController())
	{
		if (GetOwner()->HasAuthority())
		{
			NetMulticastTakeDamage(DamageAmount);
		}
		else
		{
			ServerTakeDamage(DamageAmount);
		}
	}
	else
	{
		NetMulticastTakeDamage(DamageAmount);
	}
}

void UHealthComponent::ServerTakeDamage_Implementation(float DamageAmount)
{
	NetMulticastTakeDamage(DamageAmount);
}

void UHealthComponent::NetMulticastTakeDamage_Implementation(float DamageAmount)
{
	if (bIsGodMode)
	{
		return;
	}
	
	Health -= DamageAmount;
	if (OnHealthChangedDelegate.IsBound())
	{
		OnHealthChangedDelegate.Broadcast(Health);
	}
	
	if (Health <= 0.0f)
	{
		Health = 0.0f;

		if (OnKilledDelegate.IsBound())
			OnKilledDelegate.Broadcast(GetOwner());
	}
}


void UHealthComponent::OnRep_Health() const
{
	UE_LOG(LogTemp, Warning, TEXT("Здоровье изменилось на клиенте: %f"), Health);
	
}
