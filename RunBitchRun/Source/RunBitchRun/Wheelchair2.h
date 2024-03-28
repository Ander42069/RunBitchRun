// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Wheelchair2.generated.h"

UCLASS()
class RUNBITCHRUN_API AWheelchair2 : public ACharacter
{
	GENERATED_BODY()

public:
	AWheelchair2() noexcept;

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
};
