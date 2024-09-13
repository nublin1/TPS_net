// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPCCharacter.h"

#include "Characters/NPC/Components/ZombieCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/Components/HealthComponent.h"

// Sets default values
ANPCCharacter::ANPCCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ZombieCombatComponent = CreateDefaultSubobject<UZombieCombatComponent>(TEXT("ZombieCombatComponent"));
	ZombieCombatComponent->OnComponentCreated();
	ZombieCombatComponent->SetIsReplicated(true);

	if (Implements<UIHealthInterface>())
	{
		auto HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
		HealthComponent->OnComponentCreated();
		HealthComponent->SetIsReplicated(true);
	}
	
}

UHealthComponent* ANPCCharacter::GetHealthComponent() const
{
	return FindComponentByClass<UHealthComponent>();
}

void ANPCCharacter::RerunConstructionScripts()
{
	Super::RerunConstructionScripts();
}

void ANPCCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void ANPCCharacter::PostInitProperties()
{
	Super::PostInitProperties();
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ANPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
