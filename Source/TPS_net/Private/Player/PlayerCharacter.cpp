// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "StateMachine/StateMachineComponent.h"
#include "World/Ladders/ProceduralLadder.h"

#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter(): IsAiming(false), CameraInterpolationSpeed(5)
{
	PrimaryActorTick.bCanEverTick = true;

	CurrentCameraLocation= FVector(250, 20, 30);
	DesiredCameraLocation = FVector(250, 20, 30);	
	DefaultCameraLocation = FVector(250, 20, 30);
	AimingCameraPosition = FVector(100,60,60);

	StateMachine_Movemant = CreateDefaultSubobject<UStateMachineComponent>(TEXT("StateMachine_Movemant"));
	//StateMachine_Movemant->RegisterComponent();
	//this->AddInstanceComponent(StateMachine_Movemant);
	StateMachine_Movemant->OnComponentCreated();

	StateMachine_Aiming = CreateDefaultSubobject<UStateMachineComponent>(TEXT("StateMachine_Aiming"));
	//StateMachine_Aiming->RegisterComponent();
	//this->AddInstanceComponent(StateMachine_Aiming);
	StateMachine_Aiming->OnComponentCreated();	
	
	
}

void APlayerCharacter::PostInitProperties()
{
	Super::PostInitProperties();
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::StartClimbing()
{
	if (IsUpLadderEntry)
	{
		
	}
	else
	{
		AProceduralLadder* Ladder = Cast<AProceduralLadder>(LadderTarget);
		ShortCollisionOff(Cast<UBoxComponent>(Ladder->GetDefaultSubobjectByName(TEXT("EnterBox"))));
		ShortCollisionOff(Cast<UBoxComponent>(Ladder->GetDefaultSubobjectByName(TEXT("SlideExitBox"))));
		//ServerStartClimbing_Implementation(Cast<USceneComponent>(Ladder->GetDefaultSubobjectByName(TEXT("LadderBeginningDownPosition"))));
	}
}

void APlayerCharacter::ServerStartClimbing_Implementation(USceneComponent* TargetMoveToComponent )
{
	
}

bool APlayerCharacter::ServerStartClimbing_Validate(USceneComponent* TargetMoveToComponent)
{
	//if (!LadderTarget)
	//	return false;
	
	return true;
}

void APlayerCharacter::MulticastStartClimbing_Implementation(USceneComponent* TargetMoveToComponent)
{
	StateMachine_Movemant->SwitchState(FGameplayTag::RequestGameplayTag(TEXT("PlayerStates.Ladder.EnteringLadder")));
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	GetCharacterMovement()->MaxFlySpeed = 0.0f;
	GetCharacterMovement()->BrakingDecelerationFlying = 3000.0f;

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo(
		RootComponent,
		TargetMoveToComponent->GetComponentLocation(),
		TargetMoveToComponent->GetComponentRotation(),
		false, false, 0.2f,false, EMoveComponentAction::Type::Move, LatentInfo);

	StateMachine_Movemant->SwitchState(FGameplayTag::RequestGameplayTag(TEXT("PlayerStates.Ladder.OnLadder")));
}

void APlayerCharacter::ShortCollisionOff(UBoxComponent* TargetCollision)
{
	if (!TargetCollision)
		return;
	
	UBoxComponent* TempCollision = TargetCollision;
	TempCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	GetWorld()->GetTimerManager().SetTimer(CollisionOffTimerHandle, [TempCollision]()
	{
		TempCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	},  1.0f , false);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& LifetimeProperties) const
{
	Super::GetLifetimeReplicatedProps(LifetimeProperties);

	TArray<FLifetimeProperty> OutLifetimeProps;
	
	DOREPLIFETIME(APlayerCharacter, IsAiming);
	DOREPLIFETIME(APlayerCharacter, CurrentCameraLocation);
	DOREPLIFETIME(APlayerCharacter, DesiredCameraLocation);
}

