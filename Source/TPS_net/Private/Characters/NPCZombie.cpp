// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPCZombie.h"

#include "Characters/NPC/Components/ZombieCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/Components/HealthComponent.h"

// Sets default values
ANPCZombie::ANPCZombie()
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

UHealthComponent* ANPCZombie::GetHealthComponent() const
{
	return FindComponentByClass<UHealthComponent>();
}

void ANPCZombie::RerunConstructionScripts()
{
	Super::RerunConstructionScripts();
}

void ANPCZombie::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void ANPCZombie::PostInitProperties()
{
	Super::PostInitProperties();
}

void ANPCZombie::BeginPlay()
{
	Super::BeginPlay();
}


void ANPCZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ANPCZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
