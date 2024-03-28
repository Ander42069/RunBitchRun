// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Wheelchair.generated.h"

UCLASS()
class RUNBITCHRUN_API AWheelchair : public ACharacter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Lane")
	void ChangeLane();

	UFUNCTION(BlueprintCallable, Category = "Lane")
	void ChangeLaneUpdate(const float LaneValue) noexcept;

	UFUNCTION(BlueprintCallable, Category = "Lane")
	void ChangeLaneFinished() noexcept;

	AWheelchair() noexcept;

private:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveLeft() noexcept;

	void MoveRight() noexcept;

	void MoveDown() noexcept;

	const float MoveDownImpulse = -1000.0f;

	//Valor que tiene el carril actual donde se encuentra el Wheelchair
	int32 CurrentLaneIndex = 1;
	
	//Objeto para guardar el nuevo valor que tendra el carril a donde se cambiara el Wheelchair
	int32 NewLaneIndex = 0;

	//Numero maximo de carriles
	int32 MaxLanes = 3;

	float Speed{};

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class USpringArmComponent> CameraArm{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class UCameraComponent> Camera{ nullptr };
	
	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class ARunBitchRunGameModeBase> pRunBitchRunGameModeBase{ nullptr };
};
