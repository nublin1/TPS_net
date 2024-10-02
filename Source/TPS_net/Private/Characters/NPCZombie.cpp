// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPCZombie.h"

#include "Animation/AnimInstance.h"
#include "Characters/NPC/Components/ZombieCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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
		HealthComponent->OnKilledDelegate.AddDynamic(this, &ANPCZombie::NPCDead);
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

void ANPCZombie::ChangeMaxMoveSpeed(float NewMaxSpeed)
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

void ANPCZombie::ServerSetSpeed_Implementation(float NewMaxSpeed)
{
	MulticastSetSpeed(NewMaxSpeed);
}

void ANPCZombie::MulticastSetSpeed_Implementation(float NewMaxSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewMaxSpeed;
}

void ANPCZombie::SimpleAttack(UAnimMontage* MontageToPlay)
{
	UAnimInstance* AnimInstance = FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance();
	if (AnimInstance && MontageToPlay)
	{
		FOnMontageEnded EndDelegate;
		EndDelegate.BindUObject(this, &ANPCZombie::SimpleAttackCompleted);

		AnimInstance->Montage_Play(MontageToPlay, 1.0f);
		AnimInstance->Montage_SetEndDelegate(EndDelegate, MontageToPlay);
	}
}

void ANPCZombie::SimpleAttackCompleted(UAnimMontage* Montage, bool bInterrupted)
{
	ReadyToAttack = true;
	ChangeMaxMoveSpeed(100.0f);
}

void ANPCZombie::NPCDead(AActor* KilledActor)
{
	if (KilledActor == this)
	{
		auto result = FindComponentByClass<USkeletalMeshComponent>();
		if (result)
		{
			result->SetSimulatePhysics(true);
			result->SetCollisionProfileName(TEXT("Ragdoll"), true);
			FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, [this]()
		{
			Destroy();
		}, 5.0f, false);
	}
}

void ANPCZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ANPCZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
