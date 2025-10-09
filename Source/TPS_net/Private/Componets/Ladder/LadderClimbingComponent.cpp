// Fill out your copyright notice in the Description page of Project Settings.


#include "Componets/Ladder/LadderClimbingComponent.h"

ULadderClimbingComponent::ULadderClimbingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void ULadderClimbingComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void ULadderClimbingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

