// Nublin Studio 2025 All Rights Reserved.


#include "Characters/NPCZombie.h"

#include "Animation/AnimInstance.h"
#include "Characters/NPC/Components/AIAttackComponent.h"
#include "Components/CapsuleComponent.h"
#include "Componets/Sense/NPCSenseComponent.h"
#include "Componets/Weapon/WeaponSystemComponent.h"
#include "Data/Characters/CharacterDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/Components/HealthComponent.h"
#include "StateMachine/StateMachineComponent.h"
#include "Subsystems/FactionSubsystem/FactionSubsystem.h"

// Sets default values
ANPCZombie::ANPCZombie()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnComponentCreated();
	HealthComponent->SetIsReplicated(true);

	SenseComponent = CreateDefaultSubobject<UNPCSenseComponent>(TEXT("SenseComponent"));
	SenseComponent->OnComponentCreated();
	SenseComponent->SetIsReplicated(true);

	StateTreeComponent = CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComponentAI"));

	HealthComponent->OnKilledDelegate.AddDynamic(this, &ANPCZombie::NPCDead);
}

void ANPCZombie::PreInitializeComponents()
{
	Super::PreInitializeComponents();
}

void ANPCZombie::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SenseComponent->OnActorSensed.AddDynamic(this, &ANPCZombie::OnActorSensed);
}

void ANPCZombie::BeginPlay()
{
	Super::BeginPlay();
}

void ANPCZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPCZombie::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ANPCZombie, SprintSpeed);
	DOREPLIFETIME(ANPCZombie, SenseComponent);
}

void ANPCZombie::InitCharacterData()
{
	if (!CharacterData)
		return;
	
	Super::InitCharacterData();

	if (SenseComponent)
		SenseComponent->InitSense(CharacterData->SenseData);
}

UHealthComponent* ANPCZombie::GetHealthComponent() const
{
	return FindComponentByClass<UHealthComponent>();
}

void ANPCZombie::SetTargetActor(AActor* NewTarget)
{
	TargetActor = NewTarget;
	if (OnTargetChanged.IsBound())
		OnTargetChanged.Broadcast(TargetActor);
}

void ANPCZombie::OnActorSensed(AActor* SensedActor)
{
	ABaseCharacter* SensedCharacter = Cast<ABaseCharacter>(SensedActor);
	if (!SensedCharacter)
		return;

	auto AnotherFactionName = SensedCharacter->GetFactionName_Implementation();
	UFactionSubsystem* FactionSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UFactionSubsystem>();
	
	auto Result = FactionSubsystem->GetAttitudeBetween(FactionName, AnotherFactionName);
	if (Result == EFactionAttitude::Hostile)
	{
		if (SensedCharacter != TargetActor)
			SetTargetActor(SensedActor);
		//BehavorState->SwitchState(FGameplayTag::RequestGameplayTag(FName("NPCBehavorState.ChasingTarget")));
		
	}
}
