// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundTiles.h"

#include "Wheelchair.h"
#include "RunBitchRunGameModeBase.h"
#include "Obstacle.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AGroundTiles::AGroundTiles() noexcept
	: GroundTilesScene{ CreateDefaultSubobject<USceneComponent>("GroundTiles Scene") }
	, GroundRoadMesh{ CreateDefaultSubobject<UStaticMeshComponent>("Ground Road") }
	, LeftBuildMesh{ CreateDefaultSubobject<UStaticMeshComponent>("Left Build") }
	, RightBuildMesh{ CreateDefaultSubobject<UStaticMeshComponent>("Right Build") }
	, GroundTriggerBox{ CreateDefaultSubobject<UBoxComponent>("Trigger Box") }
	, AttachPoint{ CreateDefaultSubobject<UArrowComponent>("Attach Point") }
	, CenterLane{ CreateDefaultSubobject<UArrowComponent>("Center Lane") }
	, LeftLane{ CreateDefaultSubobject<UArrowComponent>("Left Lane") }
	, RightLane{ CreateDefaultSubobject<UArrowComponent>("Right Lane") }
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = GroundTilesScene;

	//GroundTilesScene->SetupAttachment(RootComponent);
	GroundRoadMesh->SetupAttachment(RootComponent);
	LeftBuildMesh->SetupAttachment(RootComponent);
	RightBuildMesh->SetupAttachment(RootComponent);
	GroundTriggerBox->SetupAttachment(RootComponent);
	GroundTriggerBox->bHiddenInGame = false;
	AttachPoint->SetupAttachment(RootComponent);
	AttachPoint->bHiddenInGame = false;
	CenterLane->SetupAttachment(RootComponent);
	CenterLane->bHiddenInGame = false;
	LeftLane->SetupAttachment(RootComponent);
	LeftLane->bHiddenInGame = false;
	RightLane->SetupAttachment(RootComponent);
	RightLane->bHiddenInGame = false;
}

// Called when the game starts or when spawned
void AGroundTiles::BeginPlay()
{
	Super::BeginPlay();

	RunBitchRunGameModeBasePtr = Cast<ARunBitchRunGameModeBase>(GetWorld()->GetAuthGameMode());

	check(RunBitchRunGameModeBasePtr);

	LeftBuildMesh->SetStaticMesh(GetRandomMesh(BuildsMeshes));
	RightBuildMesh->SetStaticMesh(GetRandomMesh(BuildsMeshes));
}

// Called every frame
void AGroundTiles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Función para notificar que Wheelchair atraveso el UBoxComponent y spawnea a AGroundTiles
void AGroundTiles::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && OtherActor->ActorHasTag("Wheelchair"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "El Wheelchair ha atravesado el BoxComponent");

		RunBitchRunGameModeBasePtr->RespawnGroundTiles(true);
		
		// Borra actual GroundTile
		SetLifeSpan(2.0f);
		
		DeleteLaneItem();
	}
}

// Función para Destruir Obstacles
void AGroundTiles::DeleteLaneItem() noexcept
{
	if (LeftLaneItemPtr && CenterLaneItemPtr && RightLaneItemPtr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Deleting Lane Items"));

		LeftLaneItemPtr->SetLifeSpan(5.0f);
		CenterLaneItemPtr->SetLifeSpan(5.0f);
		RightLaneItemPtr->SetLifeSpan(5.0f);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Lane Items Pointers are not valid"));
	}
}

// Función para Spawnear Items
void AGroundTiles::SpawnItem() noexcept
{
	if (IsValid(SmallObstaclesStaticClass) && IsValid(BigObstaclesStaticClass) && IsValid(SmallObstaclesMovableClass) && IsValid(BigObstaclesMovableClass))
	{
		LeftLaneItemPtr = SpawnLaneItem(LeftLane);
		CenterLaneItemPtr = SpawnLaneItem(CenterLane);
		RightLaneItemPtr = SpawnLaneItem(RightLane);
	}
}

// Función para Spawnear Items en función de la transformada del Componente Arrow dentro de los parametros
AObstacle* AGroundTiles::SpawnLaneItem(UArrowComponent* Lane) noexcept
{
	// Locación de Spawn del Item
	const FTransform& SpawnPoint = Lane->GetComponentTransform();

	// Porcentaje de Spawn del Item
	const float RandValueItem = FMath::RandRange(0.0f, 1.0f);

	// Parametros de Spawn del Item
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Algoritmo de Spawn del Item
	if (RandValueItem <= 0.25f)
	{
		return GetWorld()->SpawnActor<AObstacle>(SmallObstaclesStaticClass, SpawnPoint, SpawnParams);
	}
	else if (RandValueItem > 0.25f && RandValueItem <= 0.50f)
	{
		return GetWorld()->SpawnActor<AObstacle>(BigObstaclesStaticClass, SpawnPoint, SpawnParams);
	}
	else if (RandValueItem > 0.50f && RandValueItem <= 0.75f)
	{
		return GetWorld()->SpawnActor<AObstacle>(SmallObstaclesMovableClass, SpawnPoint, SpawnParams);
	}
	else if (RandValueItem > 0.75f && RandValueItem <= 1.0f)
	{
		return GetWorld()->SpawnActor<AObstacle>(BigObstaclesMovableClass, SpawnPoint, SpawnParams);
	}
	else
	{
		return nullptr;
	}
}

// Obtener StaticMeshes Random
UStaticMesh* AGroundTiles::GetRandomMesh(const TArray<UStaticMesh*>& Array)
{
	if (Array.Num() >= 0)
	{
		const int32 RandValue = FMath::RandRange(0, Array.Num() - 1);
		return Array[RandValue];
	}
	return nullptr;
}

// Obtener Locacion LeftLane
FORCEINLINE const FVector AGroundTiles::GetLeftLaneLocation() const
{
	return LeftLane->GetComponentLocation();
}

// Obtener Locacion CenterLane
FORCEINLINE const FVector AGroundTiles::GetCenterLaneLocation() const
{
	return CenterLane->GetComponentLocation();
}

// Obtener Locacion RightLane
FORCEINLINE const FVector AGroundTiles::GetRightLaneLocation() const
{
	return RightLane->GetComponentLocation();
}