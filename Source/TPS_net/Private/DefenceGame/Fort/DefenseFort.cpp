// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenceGame/Fort/DefenseFort.h"

#include "Components/BoxComponent.h"
#include "Player/Components/HealthComponent.h"

class UBoxComponent;
// Sets default values
ADefenseFort::ADefenseFort()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (Implements<UIHealthInterface>())
	{
		auto HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
		HealthComponent->OnComponentCreated();
		HealthComponent->SetIsReplicated(true);
	}
}

class UHealthComponent* ADefenseFort::GetHealthComponent() const
{
	auto result = FindComponentByClass<UHealthComponent>();
	return result;
}

void ADefenseFort::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	
}

// Called when the game starts or when spawned
void ADefenseFort::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void ADefenseFort::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

