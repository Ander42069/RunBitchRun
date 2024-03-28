

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class RUNBITCHRUN_API AObstacle : public AActor 
{
	GENERATED_BODY()

public:
	AObstacle() noexcept;

private:
	virtual void BeginPlay() override;
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	bool bIsPolicemanActivated = false ;

	UFUNCTION(BlueprintCallable, Category = "Components")
	UStaticMesh* GetRandomMesh(const TArray<UStaticMesh*>& Array);

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class USceneComponent> ObstacleScene{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class UStaticMeshComponent> ObstacleMesh{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TObjectPtr<class UBoxComponent> ObstacleBox{ nullptr };

	UPROPERTY(EditAnywhere, Category = "Components");
	TArray<UStaticMesh*> ObstacleMeshes;

	UPROPERTY(EditAnywhere, Category = Spawner);
	TObjectPtr<class APoliceman> PolicemanPtr{ nullptr };

	/*UPROPERTY(EditAnywhere, Category = Police);
	TObjectPtr<class APoliceman> pPoliceman{ nullptr };*/
};