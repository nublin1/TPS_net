// Nublin Studio 2025 All Rights Reserved.


#include "Characters/BaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "StateMachine/StateMachineComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	StateMachine_Movement = CreateDefaultSubobject<UStateMachineComponent>(TEXT("StateMachine_Movement"));
	StateMachine_Movement->OnComponentCreated();
	StateMachine_Movement->SetIsReplicated(true);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMeshComponent = FindComponentByClass<USkeletalMeshComponent>();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ABaseCharacter, StateMachine_Movement);
}

void ABaseCharacter::ChangeMaxMoveSpeed(float NewMaxSpeed)
{
	if (!Controller)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Controller is Null"));
		return;
	}

	if (Controller->IsPlayerController())
	{
		if (HasAuthority())
		{
			MulticastSetSpeed(NewMaxSpeed);
		}
		else
		{
			ServerSetSpeed(NewMaxSpeed);
		}
	}
	else
	{
		MulticastSetSpeed(NewMaxSpeed);
	}
	
}

void ABaseCharacter::ServerSetSpeed_Implementation(float NewMaxSpeed)
{
	MulticastSetSpeed(NewMaxSpeed);
}

void ABaseCharacter::MulticastSetSpeed_Implementation(float NewMaxSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewMaxSpeed;
}

