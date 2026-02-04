// Nublin Studio 2026 All Rights Reserved.

#include "Player/Anim/PlayerAnimInstance.h"

#include "Componets/Weapon/WeaponSystemComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/PlayerCharacter.h"
#include "StateMachine/StateMachineComponent.h"
#include "World/Weapons/MasterWeaponRanged.h"

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
		CharacterActiveState = Character->GetActiveStateCharacter();
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

	/*UAnimInstance* Anim = Character->GetMesh()->GetAnimInstance();
	if (UAnimBlueprintGeneratedClass* AnimClass = Cast<UAnimBlueprintGeneratedClass>(Anim->GetClass()))
	{
		//FName CurrentState = Anim->GetCurrentStateName("YourStateMachineName");
	}*/
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

	AimingValues = Character->GetAimingValues();
	
	if (WeaponSysComponent)
	{
		if (GEngine)
		{
			/*GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green,
				FString::Printf(TEXT("State: %s "),
					*WeaponSysComponent->GetCurrentStateTagName()));*/
		}
	}
	
	UpdateLayerValues();
	SetIKHands();

	AnimCoverValues = Character->GetCoverValues();

	if (StateWasChanged)
		ChangedState();
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

	LadderClimbingComponent = Character->GetLadderClimbingComponent();
	
	IsInitilize = true;
}

void UPlayerAnimInstance::SetIKHands()
{
	if (!WeaponSysComponent)
		return;
	
	if (WeaponSysComponent->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.Takeup"))
		|| WeaponSysComponent->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.Hide")))
	{
		CurrentLayerBlendingValues.EnableHandIK_R = false;
		return;
	}
}

void UPlayerAnimInstance::UpdateLayerValues()
{
	/*// Set the Base Pose weights
	CurrentLayerBlendingValues.BasePose_N = GetCurveValue(NAME_BasePose_N);
	//CurrentLayerBlendingValues.BasePose_CLF = GetCurveValue(NAME_BasePose_CLF);

	// Set the Additive amount weights for each body part
	CurrentLayerBlendingValues.Pelvis = GetCurveValue(NAME_Pelvis);
	CurrentLayerBlendingValues.Pelvis_Add = GetCurveValue(NAME_Pelvis_Add);
	CurrentLayerBlendingValues.Spine = GetCurveValue(NAME_Spine);
	CurrentLayerBlendingValues.Head = GetCurveValue(NAME_Head);
	CurrentLayerBlendingValues.Arm_L = GetCurveValue(NAME_Arm_L);
	CurrentLayerBlendingValues.Arm_R = GetCurveValue(NAME_Arm_R);
	*/
}

void UPlayerAnimInstance::UpdateAimingValues(float DeltaSeconds)
{
	
}

void UPlayerAnimInstance::WeaponStateChanged(AActor* Actor, const FGameplayTag& NewStateTag)
{
	TObjectPtr<UWeaponDataAsset> WeaponBaseRef = nullptr; 
	if (IsHoldWeapon)
	{
		WeaponBaseRef = WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponDataAssetRef();
	}
	
	if (WeaponSysComponent->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.None")))
	{
		CurrentLayerBlendingValues = WeaponLayerBlendingValues;
	}
	
	else if (WeaponSysComponent->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.Takeup"))
		|| WeaponSysComponent->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.Hide")))
	{
		CurrentLayerBlendingValues.Spine = 0.0f;
		CurrentLayerBlendingValues.Head = 1.0f;
		CurrentLayerBlendingValues.Arm_L = 0.0f;
		CurrentLayerBlendingValues.EnableHandIK_L = 0.0f;
		CurrentLayerBlendingValues.Arm_R = 1.0f;
	}

	else if (WeaponSysComponent->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.StartReload")))
	{
		CurrentLayerBlendingValues.Arm_L = 1.0f;
		CurrentLayerBlendingValues.EnableHandIK_L = 0.0f;
	}
	else if (WeaponSysComponent->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.CompleteReload")))
	{
		CurrentLayerBlendingValues.Arm_L = 1.0f;
		WeaponLayerBlendingValues.EnableHandIK_L = WeaponBaseRef->WeaponGripTypeRelaxed == EWeaponGripType::TwoHanded ? 1.0f : 0.0f;
	}
}

void UPlayerAnimInstance::AimingStateChanged(AActor* Actor, const FGameplayTag& NewStateTag)
{
	TObjectPtr<UWeaponDataAsset> WeaponBaseRef = nullptr; 
	if (IsHoldWeapon)
	{
		WeaponBaseRef = WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponDataAssetRef();
	}
	
	if (NewStateTag == FGameplayTag::RequestGameplayTag(FName("PlayerAimingStates.Aiming"))
		|| NewStateTag == FGameplayTag::RequestGameplayTag(FName("PlayerAimingStates.HipAiming")))
	{
		if (!IsHoldWeapon)
		{
			CurrentLayerBlendingValues.Arm_L = 0.0f;
			return;
		}
		
		CurrentLayerBlendingValues.Arm_L = 1.0f;
		
		bool SecondHandIK = WeaponBaseRef->WeaponGripTypeAiming == EWeaponGripType::TwoHanded ? 1.0f : 0.0f;
		WeaponLayerBlendingValues.EnableHandIK_L = WeaponBaseRef->bIsRightHandDominant? SecondHandIK : 0.0f;
		WeaponLayerBlendingValues.EnableHandIK_R = WeaponBaseRef->bIsRightHandDominant? 0.0f :SecondHandIK;
	}
	else
	{
		if (WeaponSysComponent->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.StartReload"))
			|| WeaponSysComponent->GetCurrentStateTag() == FGameplayTag::RequestGameplayTag(FName("WeaponInteractionStates.CompleteReload")))
		{
			CurrentLayerBlendingValues.EnableHandIK_L = 0.0f;
			return;
		}
		
		CurrentLayerBlendingValues.Arm_L = IsHoldWeapon ? 1.0f : 0.0f;
		
		bool SecondHandIK = WeaponBaseRef->WeaponGripTypeRelaxed == EWeaponGripType::TwoHanded ? 1.0f : 0.0f;
		WeaponLayerBlendingValues.EnableHandIK_L = WeaponBaseRef->bIsRightHandDominant? SecondHandIK : 0.0f;
		WeaponLayerBlendingValues.EnableHandIK_R = WeaponBaseRef->bIsRightHandDominant? 0.0f :SecondHandIK;
		
	}
}

void UPlayerAnimInstance::UpdateWeaponHoldPose()
{
	if (!WeaponSysComponent || !WeaponSysComponent->GetCurrentWeaponInHands())
	{
		return;
	}

	if (WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponDataAssetRef()->WeaponType == EWeaponType::Melee)
		return;

	// Получение позиции для левой руки и перезарядки
	//LeftHandIKLoc = WeaponSysComponent->GetLeftHandSocketTransform().GetLocation();
	ReloadPosition = WeaponSysComponent->GetCurrentWeaponInHands()->GetAmmoMeshReloadPosition();
}

void UPlayerAnimInstance::CleanWeaponData(ABaseWeapon* MasterWeapon)
{
	IsHoldWeapon = false;
}

void UPlayerAnimInstance::UpdateWeaponData(ABaseWeapon* newMasterWeapon)
{
	IsHoldWeapon = WeaponSysComponent->bIsAnyWeaponInHands();
	if (IsHoldWeapon)
	{
		WeaponType = WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponDataAssetRef()->WeaponType;
		BlendSpaceRegular = WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponDataAssetRef()->WeaponPresentationData.BlendSpaceRegular;
		BlendSpaceAiming = WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponDataAssetRef()->WeaponPresentationData.BlendSpaceAiming;
		AimOffset = WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponDataAssetRef()->WeaponPresentationData.AimOffset;
		bAimOffsetIsValid = IsValid(AimOffset);
		UpdateOverrideData();
	}
}

void UPlayerAnimInstance::UpdateOverrideData()
{
	auto WeaponBaseRef = WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponDataAssetRef();

	WeaponLayerBlendingValues.Legs = 0.0f;
	WeaponLayerBlendingValues.Spine = IsHoldWeapon ? 1.0f : 0.0f;
	WeaponLayerBlendingValues.Spine_Add = 0.0f;
	WeaponLayerBlendingValues.Head = IsHoldWeapon ? 1.0f : 0.0f;
	WeaponLayerBlendingValues.Arm_L = IsHoldWeapon ? 1.0f : 0.0f;
	WeaponLayerBlendingValues.Arm_R = IsHoldWeapon ? 1.0f : 0.0f;
	
	if (WeaponType == EWeaponType::Melee)
	{
		switch (WeaponSysComponent->GetCurrentWeaponInHands()->GetWeaponDataAssetRef()->MeleeWeaponType)
		{
		case EMeleeWeaponType::Unarmed:
			break;
		case EMeleeWeaponType::Axe:
			break;
		default:
			break;
		}
	}
	else if (WeaponType == EWeaponType::Ranged)
	{
		bool SecondHandIK = WeaponBaseRef->WeaponGripTypeRelaxed == EWeaponGripType::TwoHanded ? 1.0f : 0.0f;
		WeaponLayerBlendingValues.EnableHandIK_L = WeaponBaseRef->bIsRightHandDominant? SecondHandIK : 0.0f;
		WeaponLayerBlendingValues.EnableHandIK_R = WeaponBaseRef->bIsRightHandDominant? 0.0f :SecondHandIK;
	}
}

void UPlayerAnimInstance::OnJumped()
{
	InAir.bJumped = true;
	InAir.JumpPlayRate = FMath::GetMappedRangeValueClamped<float, float>({0.0f, 600.0f},
		{1.2f, 1.5f}, CharacterInformation.Speed);
}

void UPlayerAnimInstance::ChangedState()
{
	StateWasChanged = false;

	if (NewAnimState.IsBound())
		NewAnimState.Broadcast(PreviousState, CurrentState);
}