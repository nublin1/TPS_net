// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Anim/PlayerAnimInstance.h"

#include "Net/UnrealNetwork.h"
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

void UPlayerAnimInstance::UpdateHandPositions()
{
	if (!WeaponSysComponent || !IsHoldWeapon)
	{
		IsLeftHandNeeded = false;
		IsUseHoldWeaponPose = false;
		return;
	}
}

void UPlayerAnimInstance::UpdateWeaponHoldPose()
{
	if (!WeaponSysComponent || !WeaponSysComponent->GetCurrentWeaponInHands())
	{
		return;
	}

	// Получение позиции для левой руки и перезарядки
	LeftHandPosition = WeaponSysComponent->GetLeftHandSocketTransform().GetLocation();
	ReloadPosition = WeaponSysComponent->GetCurrentWeaponInHands()->GetSkeletalMeshWeapon()->GetSocketTransform(
		FName("AmmoEject"), RTS_Actor).GetLocation();

	// Установка флага, нужен ли захват левой рукой
	if (WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponBaseRef()->GetWeaponType() != EWeaponType::Pistol
		&& WeaponSysComponent->GetCurrentStateTag() != FGameplayTag::RequestGameplayTag(
			FName("WeaponInteractionStates.StartReload")))
	{
		IsLeftHandNeeded = true;
	}
	else
	{
		IsLeftHandNeeded = false;
	}
	
	if (WeaponSysComponent->GetCurrentStateTag() ==  FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.StartReload"))
		|| (WeaponSysComponent->GetCurrentStateTag() ==  FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.None"))
			&& IsHoldWeapon
			&& (WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponBaseRef()->GetWeaponType() != EWeaponType::Pistol
				|| Character->GetStateMachine_Aiming()->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("PlayerAimingStates.Aiming"))
				|| Character->GetStateMachine_Aiming()->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("PlayerAimingStates.HipAiming")))))
	{
		IsUseHoldWeaponPose = true;
	}
	else
	{
		IsUseHoldWeaponPose = false;
	}
}

void UPlayerAnimInstance::CleanWeaponData(AMasterWeapon* MasterWeapon)
{
	IsHoldWeapon = WeaponSysComponent->bIsAnyWeaponInHands();
	UpdateHandPositions();
}

void UPlayerAnimInstance::UpdateWeaponData(AMasterWeapon* newMasterWeapon)
{
	IsHoldWeapon = WeaponSysComponent->bIsAnyWeaponInHands();
	UpdateHandPositions();
}

void UPlayerAnimInstance::OnRep_Character()
{
	WeaponSysComponent = Character->GetWeaponSystemComponent();
	IsHoldWeapon = WeaponSysComponent->bIsAnyWeaponInHands();
	UpdateHandPositions();
}

void UPlayerAnimInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UPlayerAnimInstance, Character);
	DOREPLIFETIME(UPlayerAnimInstance, IsHoldWeapon);

}
