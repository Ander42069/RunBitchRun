// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunBitchRunGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RUNBITCHRUN_API ARunBitchRunGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ARunBitchRunGameModeBase() noexcept;

	class AGroundTiles* RespawnGroundTiles(const bool bSpawnItem) noexcept;

	const TArray<float> GetLaneSwitchValues() const
	{
		return LaneSwitchValues;
	};

private:
	virtual void BeginPlay() override;

	// Funci�n miembro local
	void CreateInitialGroundTiles() noexcept;

	// Funci�n para obtener las locaciones en Y de los Lanes de AGroundTiles
	void AddLaneLocation() noexcept;

	void RespawnPoliceman();

	int32 NumInitialGroundTiles = 15;

	FTransform NextSpawnPoint{ };

	// Arreglo tipo float
	UPROPERTY();
	TArray<float> LaneSwitchValues;
	
	// Clase AGroundTiles
	UPROPERTY(EditAnywhere, Category = Spawner);
	TSubclassOf<class AGroundTiles> GroundTilesClass{ nullptr };
	
	// Declaraci�n e inicializaci�n a nullptr del puntero a AGroundTiles
	// Esta clase es responsable de crear el recurso y liberar el recurso, si quiero liberar el recurso debo ver donde esta en memoria, por eso creo un puntero miembro de clase para usarlo de forma mas sencilla dentro de la clase
	UPROPERTY(EditAnywhere, Category = Spawner);
	TObjectPtr<class AGroundTiles> GroundTilesPtr{ nullptr };

	UPROPERTY(EditAnywhere, Category = Spawner);
	TSubclassOf<class APoliceman> PolicemanClass{ nullptr };

	UPROPERTY(EditAnywhere, Category = Spawner);
	TObjectPtr<class APoliceman> PolicemanPtr{ nullptr };

};
