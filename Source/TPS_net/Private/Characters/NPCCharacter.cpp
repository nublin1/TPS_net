// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPCCharacter.h"

#include "Characters/NPC/Components/ZombieCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "Player/Components/HealthComponent.h"

// Sets default values
ANPCCharacter::ANPCCharacter(): HealthComponentBlueprint(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	ZombieCombatComponent = CreateDefaultSubobject<UZombieCombatComponent>(TEXT("ZombieCombatComponent"));
	ZombieCombatComponent->OnComponentCreated();
	ZombieCombatComponent->SetIsReplicated(true);
}

void ANPCCharacter::RerunConstructionScripts()
{
	Super::RerunConstructionScripts();
	
}

void ANPCCharacter::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	if (HealthComponentBlueprint)
	{
		HealthComponent =  NewObject<UHealthComponent>(this, HealthComponentBlueprint->GeneratedClass);
		HealthComponent->OnComponentCreated();
		HealthComponent->SetIsReplicated(true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HealthComponentClass is not set! HealthComponent could not be created."));
	}

	
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

