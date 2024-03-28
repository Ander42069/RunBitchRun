// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "GroundTiles.generated.h"

UCLASS()
class RUNBITCHRUN_API AGroundTiles : public AActor
{
	GENERATED_BODY()
	
public:	
	AGroundTiles() noexcept;

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void SpawnItem() noexcept;

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	AObstacle* SpawnLaneItem(UArrowComponent* Lane) noexcept;

	FORCEINLINE const FTransform& GetAttachPointTransform() const
	{
		return AttachPoint->GetComponentTransform();
	};

	FORCEINLINE const FVector GetCenterLaneLocation() const;
	FORCEINLINE const FVector GetRightLaneLocation() const;
	FORCEINLINE const FVector GetLeftLaneLocation() const;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void DeleteLaneItem() noexcept;

	int32 CountObstacles() const;

	UFUNCTION(BlueprintCallable, Category = "Components")
	UStaticMesh* GetRandomMesh(const TArray<UStaticMesh*>& Array);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override final;
	
	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class USceneComponent> GroundTilesScene{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class UStaticMeshComponent> GroundRoadMesh{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class UStaticMeshComponent> LeftBuildMesh{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class UStaticMeshComponent> RightBuildMesh{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class UBoxComponent> GroundTriggerBox{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class UArrowComponent> AttachPoint{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class UArrowComponent> CenterLane{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class UArrowComponent> LeftLane{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class UArrowComponent> RightLane{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TArray<UStaticMesh*> BuildsMeshes;

	// Declaración puntero a ARunBitchRunGameModeBase e inicialización a nullptr
	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class ARunBitchRunGameModeBase> RunBitchRunGameModeBasePtr{ nullptr };

	// Declaración puntero a AObstacle e inicialización a nullptr
	//UPROPERTY(EditAnywhere, Category = Spawner);
	//TObjectPtr<class AObstacle> ObstaclePtr{ nullptr };

	UPROPERTY(EditAnywhere, Category = Spawner);
	TObjectPtr<class AObstacle> LeftLaneItemPtr{ nullptr };

	UPROPERTY(EditAnywhere, Category = Spawner);
	TObjectPtr<class AObstacle> CenterLaneItemPtr{ nullptr };

	UPROPERTY(EditAnywhere, Category = Spawner);
	TObjectPtr<class AObstacle> RightLaneItemPtr{ nullptr };

	// Subclase SmallObstacleStaticClass de la clase AObstacle
	UPROPERTY(EditAnywhere, Category = Spawner);
	TSubclassOf<class AObstacle> SmallObstaclesStaticClass{ nullptr };

	// Subclase BigObstaclesStaticClass de la clase AObstacle
	UPROPERTY(EditAnywhere, Category = Spawner);
	TSubclassOf<class AObstacle> BigObstaclesStaticClass{ nullptr };

	// Subclase SmallObstaclesMovableClass de la clase AObstacle
	UPROPERTY(EditAnywhere, Category = Spawner);
	TSubclassOf<class AObstacle> SmallObstaclesMovableClass{ nullptr };

	// Subclase BigObstaclesMovableClass de la clase AObstacle
	UPROPERTY(EditAnywhere, Category = Spawner);
	TSubclassOf<class AObstacle> BigObstaclesMovableClass{ nullptr };
};
