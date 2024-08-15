// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/Components/WeaponSystemComponent.h"
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
	StateMachine_Movemant->OnComponentCreated();
	StateMachine_Movemant->SetIsReplicated(true);

	StateMachine_Aiming = CreateDefaultSubobject<UStateMachineComponent>(TEXT("StateMachine_Aiming"));
	StateMachine_Aiming->OnComponentCreated();
}

void APlayerCharacter::PostInitProperties()
{
	Super::PostInitProperties();
	if (WeaponSystemComponentClass)
	{
		WeaponSystemComponent = NewObject<UWeaponSystemComponent>(this, WeaponSystemComponentClass);
		WeaponSystemComponent->OnComponentCreated();
		WeaponSystemComponent->SetIsReplicated(true);
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::ChangeMaxMoveSpeed(float NewMaxSpeed)
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

void APlayerCharacter::ServerSetSpeed_Implementation(float NewMaxSpeed)
{
	MulticastSetSpeed(NewMaxSpeed);
}

void APlayerCharacter::MulticastSetSpeed_Implementation(float NewMaxSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewMaxSpeed;
}

void APlayerCharacter::StartClimbing()
{
	if (IsUpLadderEntry)
	{
		AProceduralLadder* Ladder = Cast<AProceduralLadder>(LadderTarget);
		
		
		if (HasAuthority())
		{
			ShortCollisionOff(Cast<UBoxComponent>(Ladder->GetDefaultSubobjectByName(TEXT("ExitBox"))));
			ShortCollisionOff(Cast<UBoxComponent>(Ladder->GetDefaultSubobjectByName(TEXT("ClimbTriggerUp"))));
			MulticastStartClimbing(Cast<USceneComponent>(Ladder->GetDefaultSubobjectByName(TEXT("LadderBeginningUpPosition"))));
		}
		else
		{
			ServerStartClimbing(Cast<USceneComponent>(Ladder->GetDefaultSubobjectByName(TEXT("LadderBeginningUpPosition"))));
		}
	}
	else
	{
		AProceduralLadder* Ladder = Cast<AProceduralLadder>(LadderTarget);
		
		
		if (HasAuthority())
		{
			//ShortCollisionOff(Cast<UBoxComponent>(Ladder->GetDefaultSubobjectByName(TEXT("EnterBox"))));
			//ShortCollisionOff(Cast<UBoxComponent>(Ladder->GetDefaultSubobjectByName(TEXT("SlideExitBox"))));
			MulticastStartClimbing(Cast<USceneComponent>(Ladder->GetDefaultSubobjectByName(TEXT("LadderBeginningDownPosition"))));
		}
		else
		{
			ServerStartClimbing(Cast<USceneComponent>(Ladder->GetDefaultSubobjectByName(TEXT("LadderBeginningDownPosition"))));
		}
	}
}

void APlayerCharacter::ServerStartClimbing_Implementation(USceneComponent* TargetMoveToComponent)
{
	
	MulticastStartClimbing_Implementation(TargetMoveToComponent);
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
		false, false, 0.5f,true, EMoveComponentAction::Type::Move, LatentInfo);

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

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APlayerCharacter, IsAiming);
	DOREPLIFETIME(APlayerCharacter, CurrentCameraLocation);
	DOREPLIFETIME(APlayerCharacter, DesiredCameraLocation);

	DOREPLIFETIME(APlayerCharacter, StateMachine_Movemant);
	DOREPLIFETIME(APlayerCharacter, WeaponSystemComponent);
}

