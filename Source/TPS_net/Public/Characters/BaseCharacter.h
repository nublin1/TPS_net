// Nublin Studio 2025 All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/FactionSystem/FactionOwnerInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UStateMachineComponent;

UCLASS()
class TPS_NET_API ABaseCharacter : public ACharacter, public IFactionOwnerInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&) const override;

	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	//====================================================================
	// FUNCTIONS
	//====================================================================
	UFUNCTION()
	virtual UStateMachineComponent* GetStateMachine_Movement() {return StateMachine_Movement;}
	UFUNCTION()
	virtual FName GetFactionName_Implementation() const override { return FactionName; }

protected:
	//====================================================================
	// PROPERTIES AND VARIABLES
	//====================================================================
	// Components
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadWrite)
	UStateMachineComponent* StateMachine_Movement;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Faction")
	FName FactionName = "Neutral";

	//Dying
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USoundBase> DyingSound;
	UPROPERTY()
	FTimerHandle DeadHandle;

	//====================================================================
	// FUNCTIONS
	//====================================================================
	// MovementSpeed
	UFUNCTION(BlueprintCallable)
	virtual void ChangeMaxMoveSpeed(float NewMaxSpeed);
	UFUNCTION(Server, Unreliable, BlueprintCallable)
	virtual void ServerSetSpeed(float NewMaxSpeed);
	UFUNCTION(NetMulticast, Unreliable)
	virtual void MulticastSetSpeed(float NewMaxSpeed);

	//
	UFUNCTION(BlueprintCallable)
	void NPCDead(AActor* KilledActor, AController* EventInstigator);
	UFUNCTION(Server, Unreliable, BlueprintCallable)
	void Server_NPCDead(AActor* KilledActor);
	UFUNCTION(NetMulticast, Unreliable)
	void NetMulticast_NPCDead(AActor* KilledActor);
	
};
