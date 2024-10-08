// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputMappingContext.h" // 追加
#include "InputAction.h" // 追加
#include "InputActionValue.h" // 追加
#include "Tank.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;
class AToonTankPlayerController;

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	AToonTankPlayerController* GetTankPlayerController() const { return ToonTankPlayerController; }

	virtual void ActorDied() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* IMCTank;

	/** Action Input */
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* IA_MoveForwardBackforward;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* IA_MoveLeftRight;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* IA_Fire;

	void EventAction(const FInputActionValue& Value);

	virtual void Fire() override;

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 45.f;

	void Move(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);

	AToonTankPlayerController* ToonTankPlayerController;
};
