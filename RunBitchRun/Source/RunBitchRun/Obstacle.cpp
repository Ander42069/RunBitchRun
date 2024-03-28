


#include "Obstacle.h"
#include "Wheelchair.h"
#include "Components/BoxComponent.h"
#include "Policeman.h"

AObstacle::AObstacle() noexcept 
	: ObstacleScene{ CreateDefaultSubobject<USceneComponent>("Obstacle Scene") }
	, ObstacleMesh{ CreateDefaultSubobject<UStaticMeshComponent>("Obstacle Mesh") }
	, ObstacleBox{ CreateDefaultSubobject<UBoxComponent>("Obstacle Box") }
{
	SetRootComponent(ObstacleScene);
	
	ObstacleMesh->SetupAttachment(GetRootComponent());
	ObstacleBox->SetupAttachment(GetRootComponent());
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	ObstacleMesh->SetStaticMesh(GetRandomMesh(ObstacleMeshes));
}

void AObstacle::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor && OtherActor->ActorHasTag("Wheelchair"))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, "El Wheelchair ha chocado el Obstacle" );
		
		/*pPoliceman = PolicemanPtr->GetPoliceman();
		
		if (pPoliceman && !bIsPolicemanActivated)
		{
			bIsPolicemanActivated = true;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Funcion StartPatrol Activated");
			pPoliceman->StartChasing();
		}*/
	}
}

UStaticMesh* AObstacle::GetRandomMesh(const TArray<UStaticMesh*>& Array)
{
	if (Array.Num() > 0)
	{
		const int32 RandValue = FMath::RandRange(0, Array.Num() - 1);
		return Array[RandValue];
	}
	return nullptr;
}

