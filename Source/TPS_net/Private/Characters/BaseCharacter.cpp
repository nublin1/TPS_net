// Nublin Studio 2025 All Rights Reserved.


#include "Characters/BaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Data/Characters/CharacterDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayAbilitySystem/BaseAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "StateMachine/StateMachineComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	StateMachine_Movement = CreateDefaultSubobject<UStateMachineComponent>(TEXT("StateMachine_Movement"));
	StateMachine_Movement->OnComponentCreated();
	StateMachine_Movement->SetIsReplicated(true);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(ASCReplicationMode);

	BaseAttributes = CreateDefaultSubobject<UBaseAttributeSet>(TEXT("BaseAttributes"));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	SkeletalMeshComponent = FindComponentByClass<USkeletalMeshComponent>();

	InitCharacterData();
}

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ABaseCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
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

void ABaseCharacter::InitCharacterData()
{
	if (!CharacterData)
		return;

	FactionName = CharacterData->FactionName;
	
	InitSetBaseCharacterStats();
}

void ABaseCharacter::InitSetBaseCharacterStats_Implementation()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	//if (!ASC || !GE_InitStats) return;
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

void ABaseCharacter::NPCDead(AActor* KilledActor, AController* EventInstigator)
{
	Server_NPCDead(KilledActor);
}

void ABaseCharacter::Server_NPCDead_Implementation(AActor* KilledActor)
{
	if(HasAuthority())
		NetMulticast_NPCDead(KilledActor);
}

void ABaseCharacter::NetMulticast_NPCDead_Implementation(AActor* KilledActor)
{
	if (KilledActor == this)
	{
		if (SkeletalMeshComponent)
		{
			SkeletalMeshComponent->SetSimulatePhysics(true);
			SkeletalMeshComponent->SetCollisionProfileName(TEXT("Ragdoll"), true);
			FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		
		GetWorldTimerManager().SetTimer(DeadHandle, [this]()
		{
			//SkeletalMeshComponent->SetSimulatePhysics(false);
			SkeletalMeshComponent->Stop();
			SkeletalMeshComponent->bPauseAnims = true;
			SkeletalMeshComponent->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
			SkeletalMeshComponent->SetAllPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
		}, 3.0f, false);

		if (DyingSound)
			UGameplayStatics::PlaySoundAtLocation(this, DyingSound, GetActorLocation());
	}
}

