// Nublin Studio 2025 All Rights Reserved.


#include "Characters/BaseCharacter.h"

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

