// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/AI/ZombieController.h"

#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Navigation/CrowdFollowingComponent.h"

AZombieController::AZombieController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	
}

void AZombieController::StartFollow(AActor* NewTargetActor,  FVector NewTargetLocation, float AcceptanceRadius)
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(SeekTimerHandle))
		GetWorld()->GetTimerManager().SetTimer(SeekTimerHandle, this, &AZombieController::Seek, 0.25f, true);

	this->CurrentTargetActor = NewTargetActor;
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

	if (!CurrentTargetActor)
		return;
	
	//UE_LOG(LogTemp, Warning, TEXT("TargetActor: %s"), *CurrentTargetActor->GetName());

	bIsTargetIsReachable = false;
	NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	FVector StartLocation = GetPawn()->GetActorLocation();
	if (NavSystem)
		Path = NavSystem->FindPathToLocationSynchronously(GetWorld(), StartLocation, CurrentTargetActor->GetActorLocation());
	
	if (Path && Path->PathPoints.Num() > 1)
	{
		if (!Path->IsPartial())
		{
			bIsTargetIsReachable = true;
			//UE_LOG(LogTemp, Warning, TEXT("Цель достижима!"));
		}
		else
		{
			bIsTargetIsReachable = false;
			//UE_LOG(LogTemp, Warning, TEXT("Путь частичный, цель недоступна!"));
		}
	}
	
	
	if(CurrentTargetActor->GetRootComponent()->Mobility == EComponentMobility::Movable)
	{
		EPathFollowingRequestResult::Type MoveResult = MoveToActor(CurrentTargetActor, 60, false, true, false);
		
	}
	else
	{
		MoveToLocation(TargetLocation, 5, false, true, false);
		DrawDebugPoint(GetWorld(), TargetLocation, 10,FColor::Blue , false, 5, 0);
	}

	if (UPathFollowingComponent* NewPathFollowingComponent = GetPathFollowingComponent())
	{
		NewPathFollowingComponent->OnRequestFinished.AddUObject(this, &AZombieController::OnMoveCompleted);
	}
	
}

void AZombieController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	UE_LOG(LogTemp, Warning, TEXT("MoveCompleted. IsTargetIsReachable = %s"), bIsTargetIsReachable ? TEXT("true") : TEXT("false"));
	
	
	if (Result.IsSuccess())
	{
		bIsMoveCompleted = true;

		if (UPathFollowingComponent* NewPathFollowingComponent = GetPathFollowingComponent())
		{
			NewPathFollowingComponent->OnRequestFinished.RemoveAll(this);
		}
	}
	else
	{
		bIsMoveCompleted = false;
	}
}

