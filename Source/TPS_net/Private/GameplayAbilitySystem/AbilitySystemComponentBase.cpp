// Nublin Studio 2025 All Rights Reserved.


#include "GameplayAbilitySystem/AbilitySystemComponentBase.h"

#include "Characters/BaseCharacter.h"

UAbilitySystemComponentBase::UAbilitySystemComponentBase()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAbilitySystemComponentBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void UAbilitySystemComponentBase::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAbilitySystemComponentBase::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();

	ABaseCharacter* Character = Cast<ABaseCharacter>(GetOwner());
	if (!Character) return;

	bool bAbilityChanged = false;

	if (LastActivatableAbilities.Num() != ActivatableAbilities.Items.Num())
	{
		bAbilityChanged = true;
	}
	else
	{
		for (int32 i = 0; i < LastActivatableAbilities.Num(); i++)
		{
			if (LastActivatableAbilities[i].Ability != ActivatableAbilities.Items[i].Ability)
			{
				bAbilityChanged = true;
				break;
			}
		}
	}

	if (bAbilityChanged)
	{
		Character->SendAbilitiesChangedEvent();
		LastActivatableAbilities = ActivatableAbilities.Items;
	}
}

