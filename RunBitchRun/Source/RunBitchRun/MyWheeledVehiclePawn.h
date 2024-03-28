// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "MyWheeledVehiclePawn.generated.h"

/**
 * 
 */
UCLASS()
class RUNBITCHRUN_API AMyWheeledVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	AMyWheeledVehiclePawn() noexcept;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value) noexcept;

	void LookUp(float Value) noexcept;

	void Turn(float Value) noexcept;

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class USpringArmComponent> CameraArm{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class UCameraComponent> Camera{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class UCapsuleComponent> CollisionCapsule{ nullptr };
};
