// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/AI/ZombieController.h"
#include "Navigation/CrowdFollowingComponent.h"

AZombieController::AZombieController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	
}

void AZombieController::StartFollow(AActor* NewTargetActor,  FVector NewTargetLocation, float AcceptanceRadius)
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(SeekTimerHandle))
		GetWorld()->GetTimerManager().SetTimer(SeekTimerHandle, this, &AZombieController::Seek, 0.25f, true);

	this->TargetActor = NewTargetActor;
	TargetLocation = NewTargetLocation;
}

void AZombieController::StopFollow()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(SeekTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(SeekTimerHandle);
	}
	bIsMoveCompleted = false;
	//StopMovement();
}

void AZombieController::Seek()
{
	FAIMoveRequest MoveRequest;

	if (!TargetActor)
		return;
	
	UE_LOG(LogTemp, Warning, TEXT("TargetActor: %s"), *TargetActor->GetName());
	
	if(TargetActor->GetRootComponent()->Mobility == EComponentMobility::Movable)
	{
		EPathFollowingRequestResult::Type MoveResult = MoveToActor(TargetActor, 50.0f);
	}
	else
	{
		MoveToLocation(TargetLocation, 50.0f);
	}

	if (UPathFollowingComponent* NewPathFollowingComponent = GetPathFollowingComponent())
	{
		NewPathFollowingComponent->OnRequestFinished.AddUObject(this, &AZombieController::OnMoveCompleted);
	}
	
}

void AZombieController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	
	if (Result.IsSuccess())
	{
		bIsMoveCompleted = true;
	}
	else
	{
		bIsMoveCompleted = false;
	}
}

