// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Bodyparts/BodyPart.h"

#include "Components/PoseableMeshComponent.h"

ABodyPart::ABodyPart()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABodyPart::BeginPlay()
{
	Super::BeginPlay();
	
}