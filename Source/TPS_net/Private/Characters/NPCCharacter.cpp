// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPCCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Player/Components/HealthComponent.h"

// Sets default values
ANPCCharacter::ANPCCharacter()
{	
	PrimaryActorTick.bCanEverTick = true;
}

void ANPCCharacter::PostInitProperties()
{
	Super::PostInitProperties();
	if (HealthComponentClass)
	{
		HealthComponent = NewObject<UHealthComponent>(this, HealthComponentClass);
		HealthComponent->OnComponentCreated();
		HealthComponent->SetIsReplicated(true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HealthComponentClass is not set! HealthComponent could not be created."));
	}
}

void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

