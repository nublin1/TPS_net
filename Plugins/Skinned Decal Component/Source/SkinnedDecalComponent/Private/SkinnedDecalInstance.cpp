// Copyright Eddie Ataberk 2021 All Rights Reserved.

#include "SkinnedDecalInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/UObjectGlobals.h"
#include "SkinnedDecalSampler.h"
//#include "UObject/UObjectIterator.h"
#include "EngineMinimal.h"

#define PRE5 ENGINE_MAJOR_VERSION < 5

// Sets default values for this component's properties
USkinnedDecalInstance::USkinnedDecalInstance( const FObjectInitializer& ObjectInitializer )
	: Super( ObjectInitializer )
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

// Called when the game starts
void USkinnedDecalInstance::BeginPlay()
{
	Super::BeginPlay();
	// ...
UpdateDecal();
}

void USkinnedDecalInstance::UpdateDecal()
{	
	check(IsInGameThread());

	if (IsTemplate() || !IsInGameThread() || !IsValid(GetOwner()))
	{
		UE_LOG(LogTemp, Warning, TEXT("IsTemplate"));

		return;
	}
	
	USkinnedDecalSampler* SamplerComponent = GetSampler();
	if (!SamplerComponent)	return;
	
	Index = SamplerComponent->SpawnDecal(GetComponentLocation(), GetComponentQuat(), GetAttachSocketName(), Size, SubUV, Index);
	
}

USkinnedDecalSampler* USkinnedDecalInstance::GetSampler()
{			
//	for (TObjectIterator<USkinnedDecalSampler> It; It; ++It)
//	{
//		if(It->GetOwner() == GetOwner())
//		{
//		return *It;
//		}
//	}

	USkinnedDecalSampler* Sampler = Cast<USkinnedDecalSampler>(GetOwner()->GetComponentByClass(USkinnedDecalSampler::StaticClass()));
	if (Sampler)
	{
		return Sampler;
	}
//	return NewObject<USkinnedDecalSampler>(GetOwner());
	return nullptr;
}


void USkinnedDecalInstance::CreateRenderState_Concurrent(FRegisterComponentContext* Context)
{
	Super::CreateRenderState_Concurrent(Context);
	// Mimics UPrimitiveComponent's visibility logic, although without the UPrimitiveCompoent visibility flags
	if (ShouldComponentAddToScene() && ShouldRender())
	{
		//	UpdateDecal();
	}
}


void USkinnedDecalInstance::DestroyComponent(bool bPromoteChildren)
{
	USkinnedDecalSampler* Sampler = GetSampler();
	if (Sampler)
	{
		Sampler->RemoveDecal(Index);
	}
	Super::DestroyComponent(bPromoteChildren);
}

#if WITH_EDITOR
void USkinnedDecalInstance::PostEditComponentMove(bool bFinished)
{
	Super::PostEditComponentMove(bFinished);
	UpdateDecal();
}

void USkinnedDecalInstance::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	UpdateDecal();
}
#endif
