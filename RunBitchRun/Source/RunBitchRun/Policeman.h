// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Policeman.generated.h"

UCLASS()
class RUNBITCHRUN_API APoliceman : public ACharacter
{
	GENERATED_BODY()

public:
	APoliceman();

	void StartChasing();

	void StopChasing();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FTransform SpawnPoint{ };

	bool bIsChasing = false;

	UPROPERTY(EditAnywhere, Category = "Speed");
	float Speed{ 700.0f };

	UPROPERTY(EditAnywhere, Category = Spawner);
	TObjectPtr<class AActor> WheelchairPtr{ nullptr };
};
