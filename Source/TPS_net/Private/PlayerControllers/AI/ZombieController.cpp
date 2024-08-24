// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllers/AI/ZombieController.h"

#include "Navigation/CrowdFollowingComponent.h"

AZombieController::AZombieController(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
	
}
