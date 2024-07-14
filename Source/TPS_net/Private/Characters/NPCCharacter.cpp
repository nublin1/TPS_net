// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPCCharacter.h"

#include "Components/CapsuleComponent.h"

// Sets default values
ANPCCharacter::ANPCCharacter(): IIHealthInterface(100.0f, 100.0f)
{	
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANPCCharacter::TakeDamage(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health < 0.0f)
	{
		Health = 0.0f;
	}

	auto result = FindComponentByClass<USkeletalMeshComponent>();
	if (result)
	{
		UE_LOG(LogTemp, Error, TEXT("HIT"));
		result->SetSimulatePhysics(true);

		FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}



// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

