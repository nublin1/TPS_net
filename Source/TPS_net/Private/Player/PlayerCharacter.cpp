// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "StateMachine/StateMachineComponent.h"

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

void APlayerCharacter::ShortCollisionOff(UBoxComponent* TargetCollision)
{
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

