// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Anim/PlayerAnimInstance.h"

#include "Net/UnrealNetwork.h"
#include "Player/PlayerCharacter.h"
#include "Player/Components/WeaponSystemComponent.h"
#include "StateMachine/StateMachineComponent.h"
#include "World/Weapons/MasterWeapon.h"

static const FName NAME_BasePose_N(TEXT("BasePose_N"));
static const FName NAME_Pelvis(TEXT("Pelvis"));
static const FName NAME_Pelvis_Add(TEXT("Pelvis_Add"));
static const FName NAME_Spine(TEXT("Spine"));
static const FName NAME_Spine_Add(TEXT("Spine_Add"));
static const FName NAME_Head(TEXT("Head"));
static const FName NAME_Head_Add(TEXT("Head_Add"));
static const FName NAME_Arm_L(TEXT("Arm_L"));
static const FName NAME_Arm_L_Add(TEXT("Arm_L_Add"));
static const FName NAME_Arm_R(TEXT("Arm_R"));
static const FName NAME_Arm_R_Add(TEXT("Arm_R_Add"));
static const FName NAME_HandIK_L(TEXT("HandIK_L"));
static const FName NAME_HandIK_R(TEXT("HandIK_R"));

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Character = Cast<APlayerCharacter>(TryGetPawnOwner());
	if (Character)
	{
		ChMovementComponent = Character->GetCharacterMovement();
		StateMachine_Movement = Character->GetStateMachine_Movement();
		StateMachine_Aiming =  Character->GetStateMachine_Aiming();
		WeaponSysComponent = Character->GetWeaponSystemComponent();
		
		Character->OnJumpedDelegate.AddUniqueDynamic(this, &UPlayerAnimInstance::OnJumped);
	}
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Character)
	{
		return;
	}

	CharacterInformation.bShouldMove = Character->GetIsMoving();
	CharacterInformation.MovementVector = Character->GetMovementVector();
	CharacterInformation.Speed = Character ->GetSpeed();

	CharacterInformation.AimingRotation = Character->GetAimingRotation();
	CharacterInformation.CharacterActorRotation = Character->GetActorRotation();
	
	if (WeaponSysComponent)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green,
				FString::Printf(TEXT("State: %s "),
					*WeaponSysComponent->GetCurrentStateTagName()));
		}
	}
	
	UpdateLayerValues();
	UpdateAimingValues(DeltaSeconds);
	SetIKHands();
}

void UPlayerAnimInstance::SighUp()
{
	WeaponSysComponent = Character->GetWeaponSystemComponent();
	if (WeaponSysComponent)
	{
		WeaponSysComponent->OnStateChangedDelegate.AddDynamic(this, &UPlayerAnimInstance::WeaponStateChanged);
		WeaponSysComponent->OnHideArmsDelegate.AddDynamic(this, &UPlayerAnimInstance::CleanWeaponData);
		WeaponSysComponent->OnTakeupArmsDelegate.AddDynamic(this, &UPlayerAnimInstance::UpdateWeaponData);
	}

	if (StateMachine_Aiming)
	{
		StateMachine_Aiming->StateChangedDelegate.AddDynamic(this, &UPlayerAnimInstance::UPlayerAnimInstance::AimingStateChanged);
	}
	
	IsInitilize = true;
}

void UPlayerAnimInstance::SetIKHands()
{
	if (!WeaponSysComponent)
		return;
	
	if (WeaponSysComponent->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.Takeup"))
		|| WeaponSysComponent->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.Hide")))
	{
		LayerBlendingValues.EnableHandIK_R = false;
		return;
	}

	
	if (IsHoldWeapon)
		LayerBlendingValues.EnableHandIK_R = true;
	else
		LayerBlendingValues.EnableHandIK_R = false;
}

void UPlayerAnimInstance::UpdateLayerValues()
{
	/*// Set the Base Pose weights
	LayerBlendingValues.BasePose_N = GetCurveValue(NAME_BasePose_N);
	//LayerBlendingValues.BasePose_CLF = GetCurveValue(NAME_BasePose_CLF);

	// Set the Additive amount weights for each body part
	LayerBlendingValues.Pelvis = GetCurveValue(NAME_Pelvis);
	LayerBlendingValues.Pelvis_Add = GetCurveValue(NAME_Pelvis_Add);
	LayerBlendingValues.Spine = GetCurveValue(NAME_Spine);
	LayerBlendingValues.Head = GetCurveValue(NAME_Head);
	LayerBlendingValues.Arm_L = GetCurveValue(NAME_Arm_L);
	LayerBlendingValues.Arm_R = GetCurveValue(NAME_Arm_R);
	*/
}

void UPlayerAnimInstance::UpdateAimingValues(float DeltaSeconds)
{
	AimingValues.SmoothedAimingRotation = FMath::RInterpTo(AimingValues.SmoothedAimingRotation,
														   CharacterInformation.AimingRotation, DeltaSeconds,
														   Config.SmoothedAimingRotationInterpSpeed);
	
	// Calculate the Aiming angle and Smoothed Aiming Angle by getting
	// the delta between the aiming rotation and the actor rotation.
	FRotator Delta = CharacterInformation.AimingRotation - CharacterInformation.CharacterActorRotation;
	Delta.Normalize();
	AimingValues.AimingAngle.X = Delta.Yaw;
	AimingValues.AimingAngle.Y = Delta.Pitch;

	Delta = AimingValues.SmoothedAimingRotation - CharacterInformation.CharacterActorRotation;
	Delta.Normalize();
	AimingValues.SmoothedAimingAngle.X = Delta.Yaw;
	AimingValues.SmoothedAimingAngle.Y = Delta.Pitch;
}

void UPlayerAnimInstance::WeaponStateChanged(AActor* Actor, const FGameplayTag& NewStateTag)
{
	if (WeaponSysComponent->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.None")))
	{
		LayerBlendingValues.Spine = IsHoldWeapon ? 1.0f : 0.0f;
		LayerBlendingValues.Spine_Add = 0.0f;
		LayerBlendingValues.Head = IsHoldWeapon ? 1.0f : 0.0f;
		LayerBlendingValues.Arm_L = IsHoldWeapon ? 1.0f : 0.0f;
		LayerBlendingValues.Arm_R = IsHoldWeapon ? 1.0f : 0.0f;

		if (WeaponSysComponent->GetCurrentWeaponInHands())
		{
			LayerBlendingValues.EnableHandIK_L =
			WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponBaseRef()->GetWeaponGripType() ==
				EWeaponGripType::TwoHanded ? 1.0f : 0.0f;
			
		}
	}
	
	else if (WeaponSysComponent->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.Takeup"))
		|| WeaponSysComponent->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.Hide")))
	{
		LayerBlendingValues.Spine = 0.0f;
		LayerBlendingValues.Head = 1.0f;
		LayerBlendingValues.Arm_L = 0.0f;
		LayerBlendingValues.EnableHandIK_L = 0.0f;
		LayerBlendingValues.Arm_R = 1.0f;
	}
}

void UPlayerAnimInstance::AimingStateChanged(AActor* Actor, const FGameplayTag& NewStateTag)
{
	if (NewStateTag == FGameplayTag::RequestGameplayTag(FName("PlayerAimingStates.Aiming"))
		|| NewStateTag == FGameplayTag::RequestGameplayTag(FName("PlayerAimingStates.HipAiming")))
	{
		if (!IsHoldWeapon)
			return;
		
		LayerBlendingValues.Arm_L = WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponBaseRef()->GetWeaponGripType() ==
				EWeaponGripType::TwoHanded ? 1.0f : 0.0f;
	}
	else
	{
		LayerBlendingValues.Arm_L = IsHoldWeapon ? 1.0f : 0.0f;
	}
}

void UPlayerAnimInstance::UpdateWeaponHoldPose()
{
	if (!WeaponSysComponent || !WeaponSysComponent->GetCurrentWeaponInHands())
	{
		return;
	}

	// Получение позиции для левой руки и перезарядки
	//LeftHandIKLoc = WeaponSysComponent->GetLeftHandSocketTransform().GetLocation();
	ReloadPosition = WeaponSysComponent->GetCurrentWeaponInHands()->GetSkeletalMeshWeapon()->GetSocketTransform(
		FName("AmmoEject"), RTS_Actor).GetLocation();

	
}

void UPlayerAnimInstance::CleanWeaponData(AMasterWeapon* MasterWeapon)
{
	IsHoldWeapon = false;
}

void UPlayerAnimInstance::UpdateWeaponData(AMasterWeapon* newMasterWeapon)
{
	IsHoldWeapon = WeaponSysComponent->bIsAnyWeaponInHands();
}

void UPlayerAnimInstance::OnRep_Character()
{
	WeaponSysComponent = Character->GetWeaponSystemComponent();
	IsHoldWeapon = WeaponSysComponent->bIsAnyWeaponInHands();
}

void UPlayerAnimInstance::OnJumped()
{
	InAir.bJumped = true;
	InAir.JumpPlayRate = FMath::GetMappedRangeValueClamped<float, float>({0.0f, 600.0f},
		{1.2f, 1.5f}, CharacterInformation.Speed);
}

void UPlayerAnimInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(UPlayerAnimInstance, Character);
	DOREPLIFETIME(UPlayerAnimInstance, IsHoldWeapon);
}
