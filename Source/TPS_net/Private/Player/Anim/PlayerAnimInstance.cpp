// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Anim/PlayerAnimInstance.h"

#include "Player/PlayerCharacter.h"
#include "Player/Components/WeaponSystemComponent.h"
#include "StateMachine/StateMachineComponent.h"
#include "World/Weapons/MasterWeapon.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UPlayerAnimInstance::SighUp()
{
	WeaponSysComponent = Character->GetWeaponSystemComponent();

	if (WeaponSysComponent)
	{
		WeaponSysComponent->OnHideArmsDelegate.AddDynamic(this, &UPlayerAnimInstance::CleanWeaponData);
		WeaponSysComponent->OnTakeupArmsDelegate.AddDynamic(this, &UPlayerAnimInstance::UpdateWeaponData);
	}

	IsInitilize = true;
}

void UPlayerAnimInstance::HoldWeapon()
{
	if (!WeaponSysComponent)
	{
		return;
	}
	
	LeftHandPosition = WeaponSysComponent->GetLeftHandSocketTransform().GetLocation();

	if (IsHoldWeapon)
	{
		ReloadPosition = WeaponSysComponent->GetCurrentWeaponInHands()->GetSkeletalMeshWeapon()->GetSocketTransform(FName("AmmoEject"), RTS_Actor).GetLocation();

		if (WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponBaseRef()->GetWeaponType() != EWeaponType::Pistol
			&& Character->GetStateMachine_Aiming()->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("PlayerAimingStates.Aiming")))
		{
			IsLeftHandNeeded = true;
		}
		else
		{
			IsLeftHandNeeded = false;
		}		
	}

	

	if (WeaponSysComponent->GetCurrentStateTag() ==  FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.StartReload"))
		|| (WeaponSysComponent->GetCurrentStateTag() ==  FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.None"))
			&& IsHoldWeapon
			&& (WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponBaseRef()->GetWeaponType() != EWeaponType::Pistol
				|| Character->GetStateMachine_Aiming()->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("PlayerAimingStates.Aiming")))))
	{
		IsUseHoldWeaponPose = true;
	}
	else
	{
		IsUseHoldWeaponPose = false;
	}

	//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("GetCurrentStateTag %s"), *WeaponSysComponent->GetCurrentStateTag().ToString() ));
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("IsHoldWeapon %s"), IsHoldWeapon ? TEXT("true") : TEXT("false")));

}

void UPlayerAnimInstance::CleanWeaponData()
{
	IsHoldWeapon = WeaponSysComponent->bIsAnyWeaponInHands();
}

void UPlayerAnimInstance::UpdateWeaponData(AMasterWeapon* newMasterWeapon)
{
	IsHoldWeapon = WeaponSysComponent->bIsAnyWeaponInHands();
	
}
