// Copyright Epic Games, Inc. All Rights Reserved.


#include "RunBitchRunGameModeBase.h"
#include "GroundTiles.h"
#include "Wheelchair.h"
#include "Policeman.h"
#include <Kismet/GameplayStatics.h>

ARunBitchRunGameModeBase::ARunBitchRunGameModeBase() noexcept
{
	// El GameModeBase hace de Wheelchair el jugador por defecto
	DefaultPawnClass = AWheelchair::StaticClass();

}

void ARunBitchRunGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	AddLaneLocation();
	
	// Creamos las primeras tiras de suelo al comenzar el juego
	CreateInitialGroundTiles();

	RespawnPoliceman();
}

// Funcion void CreateInitialGroundTiles que se ejecutara una unica vez al iniciar el juego
void ARunBitchRunGameModeBase::CreateInitialGroundTiles() noexcept
{
	//funcion que respawnea las primeras 15 tiras de suelo
	for (int32 i = 0; i < NumInitialGroundTiles; i++)
	{
		RespawnGroundTiles(true);
	}
}

// Funcion que obtiene y guarda en un Array los valores de las locaciones en Y de los ArrowComponent de los carriles de la tiras de suelo
void ARunBitchRunGameModeBase::AddLaneLocation() noexcept
{
	// Se mete el Actor a GroundTiles spawneado con su locacion y false = no items
	GroundTilesPtr = RespawnGroundTiles(false);

	// Checar si GroundTilesPtr no es nulo, si contiene el actor AGroundTiles spawneado
	if (GroundTilesPtr)
	{
		// Agregamos los locations de Y en el array LaneSwitchValues
		LaneSwitchValues.Add(GroundTilesPtr->GetLeftLaneLocation().Y);
		LaneSwitchValues.Add(GroundTilesPtr->GetCenterLaneLocation().Y);
		LaneSwitchValues.Add(GroundTilesPtr->GetRightLaneLocation().Y);
	}

	// Imprimir valores del arreglo 
	for (float Value : LaneSwitchValues)
	{
		UE_LOG(LogTemp, Warning, TEXT("LANE VALUE: %f"), Value);
	}
}

// Funcion RespawnGroundTiles que regresa un puntero a AGroundTiles
FORCEINLINE AGroundTiles* ARunBitchRunGameModeBase::RespawnGroundTiles(const bool bSpawnItem) noexcept
{	
	// Declaración puntero WorldPtr e inicializacion  
	TObjectPtr<class UWorld> WorldPtr{ GetWorld() };//Obtiene el mundo del Actor (AGroundTiles)

	// Verificar si puntero a UWorld es valido
	if (WorldPtr)
	{
		// Si es valido llamamos la función SpawnActor de la clase UWorld desde el puntero a UWorld
		GroundTilesPtr = WorldPtr->SpawnActor<AGroundTiles>(GroundTilesClass, NextSpawnPoint);

		if (GroundTilesPtr)
		{
			// Spawnear Items
			if (bSpawnItem)
			{
				// Spawnear Items
				GroundTilesPtr->SpawnItem();
			}

			// Lugar donde queremos spawnear el GroundTile
			NextSpawnPoint = GroundTilesPtr->GetAttachPointTransform();
			const FVector NextSpawnLocation = NextSpawnPoint.GetLocation();
			NextSpawnPoint.SetLocation({ NextSpawnLocation.X, NextSpawnLocation.Y, NextSpawnLocation.Z });
		}

		return GroundTilesPtr;
	}

	return nullptr;
}

void ARunBitchRunGameModeBase::RespawnPoliceman()
{
	TObjectPtr<class UWorld> WorldPtr{ GetWorld() };

	if (WorldPtr)
	{
		FVector WheelchairLocation{ FVector::ZeroVector };
		TObjectPtr<class AActor> WheelchairPtr{ UGameplayStatics::GetPlayerPawn(this, 0) };
		
		if (WheelchairPtr)
		{
			WheelchairLocation = WheelchairPtr->GetActorLocation();
		}

		FVector PolicemanSpawnLocation{ WheelchairLocation - FVector(20.0f, 0.0f, 0.0f) };  // Posición de spawn detrás del Wheelchair
		FRotator PolicemanSpawnRotation{ FRotator::ZeroRotator };  // Sin rotación inicial
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		PolicemanPtr = WorldPtr->SpawnActor<APoliceman>(PolicemanClass, PolicemanSpawnLocation, PolicemanSpawnRotation, SpawnParams);
	}
}

/*void ARunBitchRunGameModeBase::RespawnPoliceman()
{
	if (PolicemanClass)
	{
		TObjectPtr<class UWorld> WorldPtr{ GetWorld() };
		if (WorldPtr)
		{
			FVector PolicemanSpawnLocation = FVector(-500.0f, 0.0f, 100.0f);  // Ajusta la posición según tus necesidades
			FRotator PolicemanSpawnRotation = FRotator::ZeroRotator;

			TObjectPtr<UClass> PolicemanClassPtr = PolicemanClass.Get();
			if (PolicemanClassPtr)
			{
				PolicemanPtr = WorldPtr->SpawnActor<APoliceman>(PolicemanClassPtr, PolicemanSpawnLocation, PolicemanSpawnRotation);
			}
			else
			{
				// PolicemanClass no es una clase válida.
				UE_LOG(LogTemp, Warning, TEXT("PolicemanClass no es una clase válida."));
			}
		}
	}
	else
	{
		// PolicemanClass no está asignada.
		UE_LOG(LogTemp, Warning, TEXT("PolicemanClass no está asignada."));
	}
}*/