// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NPCZombie.h"

#include "Animation/AnimInstance.h"
#include "Characters/NPC/Components/ZombieCombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/Components/HealthComponent.h"

// Sets default values
ANPCZombie::ANPCZombie()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnComponentCreated();
	HealthComponent->SetIsReplicated(true);
	
	ZombieCombatComponent = CreateDefaultSubobject<UZombieCombatComponent>(TEXT("ZombieCombatComponent"));
	ZombieCombatComponent->OnComponentCreated();
	ZombieCombatComponent->SetIsReplicated(true);

	HealthComponent->OnKilledDelegate.AddDynamic(this, &ANPCZombie::NPCDead);
	
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

void ANPCZombie::PostInitializeComponents()
{
	Super::PostInitializeComponents();
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
	ChangeMaxMoveSpeed(SprintSpeed);
}

void ANPCZombie::NPCDead(AActor* KilledActor, AController* EventInstigator)
{
	Server_NPCDead(KilledActor);
}

void ANPCZombie::Server_NPCDead_Implementation(AActor* KilledActor)
{
	NetMulticast_NPCDead(KilledActor);
}

void ANPCZombie::NetMulticast_NPCDead_Implementation(AActor* KilledActor)
{
	if (KilledActor == this)
	{
		auto SkeletalMeshComponent = FindComponentByClass<USkeletalMeshComponent>();
		if (SkeletalMeshComponent)
		{
			SkeletalMeshComponent->SetSimulatePhysics(true);
			SkeletalMeshComponent->SetCollisionProfileName(TEXT("Ragdoll"), true);
			FindComponentByClass<UCapsuleComponent>()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, [this, SkeletalMeshComponent]()
		{
			//SkeletalMeshComponent->SetSimulatePhysics(false);
			SkeletalMeshComponent->Stop();
			SkeletalMeshComponent->bPauseAnims = true;
			SkeletalMeshComponent->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
			SkeletalMeshComponent->SetAllPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
			//Destroy();
		}, 3.0f, false);

		if (DyingSound)
			UGameplayStatics::PlaySoundAtLocation(this, DyingSound, GetActorLocation());
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

void ANPCZombie::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ANPCZombie, SprintSpeed);
	DOREPLIFETIME(ANPCZombie, ZombieCombatComponent);
}
