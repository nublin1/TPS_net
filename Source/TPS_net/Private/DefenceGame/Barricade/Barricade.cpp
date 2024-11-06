// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenceGame/Barricade/Barricade.h"

#include "Componets/AIPointGeneratorComponent.h"
#include "Player/Components/HealthComponent.h"

// Sets default values
ABarricade::ABarricade()
{
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnComponentCreated();
	HealthComponent->SetIsReplicated(true);
	HealthComponent->OnKilledDelegate.AddDynamic(this, &ABarricade::ActorDestroyed);

	PointGeneratorComponent = CreateDefaultSubobject<UAIPointGeneratorComponent>(TEXT("UAIPointGeneratorComponent"));
	
	Tags.Add("Obstacle");
	
	PrimaryActorTick.bCanEverTick = true;

}

class UHealthComponent* ABarricade::GetHealthComponent() const
{
	return FindComponentByClass<UHealthComponent>();
}

void ABarricade::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABarricade::ActorDestroyed(AActor* DestroyedActor, AController* EventInstigator)
{
	if (DestroyedActor != this)
		return;

	Server_ActorDestroyed(DestroyedActor);
}

void ABarricade::Server_ActorDestroyed_Implementation(AActor* DestroyedActor)
{
	NetMulticast_ActorDestroyed(DestroyedActor);
}

void ABarricade::NetMulticast_ActorDestroyed_Implementation(AActor* DestroyedActor)
{
	if (DestroyedActor == this)
	{
		Destroy();
	}
}

void ABarricade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

