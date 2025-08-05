// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/Components/HealthComponent.h"
#include "StateMachine/StateMachineComponent.h"
#include "World/Ladders/ProceduralLadder.h"

#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter(): CameraInterpolationSpeed(5)
{
	PrimaryActorTick.bCanEverTick = true;

	CurrentCameraLocation= FVector(350, 20, 30);
	DesiredCameraLocation = FVector(350, 20, 30);	
	DefaultCameraLocation = FVector(350, 20, 30);
	AimingCameraPosition = FVector(100,60,60);
	
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnComponentCreated();
	HealthComponent->SetIsReplicated(true);

	StateMachine_Movement = CreateDefaultSubobject<UStateMachineComponent>(TEXT("StateMachine_Movemant"));
	StateMachine_Movement->OnComponentCreated();
	StateMachine_Movement->SetIsReplicated(true);

	StateMachine_Aiming = CreateDefaultSubobject<UStateMachineComponent>(TEXT("StateMachine_Aiming"));
	StateMachine_Aiming->OnComponentCreated();

	ActiveStateCharacter = CreateDefaultSubobject<UStateMachineComponent>(TEXT("ActiveStateCharacter"));
	ActiveStateCharacter->OnComponentCreated();
	ActiveStateCharacter->SetIsReplicated(true);
}

UHealthComponent* APlayerCharacter::GetHealthComponent() const
{
	return FindComponentByClass<UHealthComponent>();
}

void APlayerCharacter::PostInitProperties()
{
	Super::PostInitProperties();
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetOwner(GEngine->GetFirstLocalPlayerController(GetWorld()));

	if (HasAuthority())
	{
		HealthComponent->OnKilledDelegate.AddUniqueDynamic(this, &APlayerCharacter::OnHealthDepleted);
	}
}

void APlayerCharacter::SetEssentialValues(float DeltaTime)
{
	if (GetLocalRole() != ROLE_SimulatedProxy)
	{
		ReplicatedControlRotation = GetControlRotation();
	}
	else
	{
		
	}

	if (GetCharacterMovement()->MaxWalkSpeed != TargetMaxWalkSpeed)
	{
		float CurrentMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
		float InterpSpeed = FMath::FInterpTo(CurrentMaxWalkSpeed, TargetMaxWalkSpeed, DeltaTime, 3.5f);
		GetCharacterMovement()->MaxWalkSpeed = InterpSpeed;

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue,
				FString::Printf(TEXT("Current: %.2f, Target: %.2f, Interp: %.2f"),
								CurrentMaxWalkSpeed, TargetMaxWalkSpeed, InterpSpeed));

			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue,
				FString::Printf(TEXT("Current: %s"),
								*StateMachine_Movement->GetCurrentStateTagName()));
		}
	}

	AimingRotation = FMath::RInterpTo(AimingRotation, ReplicatedControlRotation, DeltaTime, 30);

	const FVector CurrentVel = GetVelocity();
	Speed = CurrentVel.Size2D();
	IsMoving = Speed > 1.0f; 
}

void APlayerCharacter::EventOnJumped()
{
	OnJumpedDelegate.Broadcast();
}

void APlayerCharacter::Multicast_OnJumped_Implementation()
{
	if (!IsLocallyControlled())
	{
		EventOnJumped();
	}
}

void APlayerCharacter::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	if (IsLocallyControlled())
	{
		EventOnJumped();
	}
	if (HasAuthority())
	{
		Multicast_OnJumped();
	}
}

void APlayerCharacter::OnHealthDepleted(AActor* Actor, AController* EventInstigator)
{
	if (!ActiveStateCharacter)
		return;

	if (Actor != this)
		return;
	
	if (HasAuthority())
	{
		ServerOnHealthDepleted();
	}
}

void APlayerCharacter::ServerOnHealthDepleted_Implementation()
{
	ActiveStateCharacter->SwitchState(FGameplayTag::RequestGameplayTag(FName("State.Downed")));
	if (const auto Capsule = FindComponentByClass<UCapsuleComponent>())
	{
		//UE_LOG(LogTemp, Warning, TEXT("State changed on Server"));
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	GetCharacterMovement()->DisableMovement();
	
	NetMulticastOnHealthDepleted();
}

void APlayerCharacter::NetMulticastOnHealthDepleted_Implementation()
{
	if (const auto Capsule = FindComponentByClass<UCapsuleComponent>())
	{
		//UE_LOG(LogTemp, Warning, TEXT("State changed on Client"));
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	GetCharacterMovement()->DisableMovement();
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
	TargetMaxWalkSpeed = NewMaxSpeed;
	
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
	StateMachine_Movement->SwitchState(FGameplayTag::RequestGameplayTag(TEXT("PlayerStates.Ladder.EnteringLadder")));
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

	StateMachine_Movement->SwitchState(FGameplayTag::RequestGameplayTag(TEXT("PlayerStates.Ladder.OnLadder")));
}

bool APlayerCharacter::IsStateTransitionAllowed(FGameplayTag NewState)
{
	if (NewState == FGameplayTag::RequestGameplayTag(TEXT("PlayerStates.Dodge")))
	{
		if (!IsGrounded
			|| StateMachine_Movement->GetCurrentStateTag().MatchesTag(FGameplayTag::RequestGameplayTag(TEXT("PlayerStates.Dodge")))
			|| StateMachine_Movement->GetCurrentStateTag().MatchesTag(FGameplayTag::RequestGameplayTag(TEXT("PlayerStates.Ladder"))))
			return false;
	}
	
	return true;
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

	// Set required values
	SetEssentialValues(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacter, MovementVector);
	DOREPLIFETIME(APlayerCharacter, TargetMaxWalkSpeed);
	
	DOREPLIFETIME(APlayerCharacter, CurrentCameraLocation);
	DOREPLIFETIME(APlayerCharacter, DesiredCameraLocation);

	DOREPLIFETIME(APlayerCharacter, StateMachine_Movement);
	DOREPLIFETIME(APlayerCharacter, StateMachine_Aiming);
	DOREPLIFETIME(APlayerCharacter, ReplicatedControlRotation);
	DOREPLIFETIME(APlayerCharacter, WeaponSystemComponent);
	DOREPLIFETIME(APlayerCharacter, ActiveStateCharacter);
}

