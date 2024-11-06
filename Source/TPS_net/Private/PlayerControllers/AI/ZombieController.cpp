// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/AI/ZombieController.h"

#include "EngineUtils.h"
#include "Landscape.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Navigation/CrowdFollowingComponent.h"

AZombieController::AZombieController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent"))),
	  NavSystem(nullptr)
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

			CheckObstacles(Path->PathPoints.Last(), Path->PathPoints.Last(), 75.0f);
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

void AZombieController::CheckObstacles(FVector Start, FVector End, float Radius)
{
	TArray<FHitResult> OutHits;

	//UE_LOG(LogTemp, Warning, TEXT("Start = %s"), *Start.ToString());

	// Define the types of objects to trace for
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));

	// Trace parameters
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	QueryParams.AddIgnoredActor(this->GetOwner()); // Ignore self

	// 
	TArray<AActor*> ActorsToIgnore;
	for (TActorIterator<ALandscapeProxy> It(GetWorld()); It; ++It)
	{
		ActorsToIgnore.Add(*It);
	}


	// Multi-Sphere Trace
	bool bHit = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),         
		Start,              
		End,              
		Radius,             
		ObjectTypes,        
		false,             
		ActorsToIgnore,
		EDrawDebugTrace::None, 
		OutHits,           
		true                // Return only blocking hits
	);

	if (bHit && OutHits.Num() > 0)
	{
		ObstaclesHitResult.Empty();
		
		ObstaclesHitResult = OutHits;
		
		for (const FHitResult& Hit : OutHits)
		{
			if (!Hit.GetActor()->IsA(ALandscape::StaticClass()))
			{
				ObstaclesHitResult.Add(Hit);

				if (IsDebug)
				{
					FVector ActorLocation = Hit.GetActor()->GetActorLocation();
					DrawDebugPoint(
						GetWorld(), 
						ActorLocation,  
						60.0f,          
						FColor::Magenta, 
						false,          
						1000.0f          
					);
				}
			}
		}
	}
}

void AZombieController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	//UE_LOG(LogTemp, Warning, TEXT("MoveCompleted. IsTargetIsReachable = %s"), bIsTargetIsReachable ? TEXT("true") : TEXT("false"));
	
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

void AZombieController::TargetDestoyed(AActor* DestroyedActor)
{
	ObstaclesHitResult.Empty();
}


