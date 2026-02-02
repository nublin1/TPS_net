// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "AI/Al_Helper.h"
#include "Components/StateTreeComponent.h"

#include "Interfaces/IHealthInterface.h"
#include "NPC/Inrfaces/AIAttackInterface.h"
#include "Player/Interfaces/WeaponSystemInterface.h"

#include "NPCZombie.generated.h"

class UWeaponSystemComponent;
class UNPCSenseComponent;

UCLASS()
class TPS_NET_API ANPCZombie : public ABaseCharacter, public IIHealthInterface, public IWeaponSystemInterface, public IAIAttackInterface
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetChanged, AActor*, Target);
	
public:
	ANPCZombie();

protected:
	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;
	
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTargetChanged OnTargetChanged;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	virtual void InitCharacterData() override;
	
	UFUNCTION(BlueprintCallable)
	virtual class UHealthComponent* GetHealthComponent() const override;
	UFUNCTION()
	virtual UWeaponSystemComponent* GetWeaponSystemComponent() const override {return WeaponSystemComponent;}

	UFUNCTION(BlueprintCallable)
	virtual AActor* GetCurrentTarget_Implementation() const ;

	UFUNCTION()
	virtual void SetTargetActor(AActor* NewTarget);

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> HealthComponent;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNPCSenseComponent> SenseComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UStateTreeComponent> StateTreeComponent;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWeaponSystemComponent> WeaponSystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<AActor> TargetActor;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Transformation")
	float SprintSpeed = 600.0f;
	
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	void OnActorSensed(AActor* SensedActor);

};
