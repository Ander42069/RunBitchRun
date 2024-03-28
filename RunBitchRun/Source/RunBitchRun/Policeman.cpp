// Fill out your copyright notice in the Description page of Project Settings.


#include "Policeman.h"
#include "Wheelchair.h"
#include <Kismet/GameplayStatics.h>


APoliceman::APoliceman()
{
 	
	PrimaryActorTick.bCanEverTick = true;

}

void APoliceman::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void APoliceman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	/*FRotator ControlRotation = GetControlRotation();//Aqui esta el eje Z (Yaw) y su valor se queda igual

	//Break Rotator     |  Make Rotator
	ControlRotation.Roll = 0.0f; //Se rompe el eje X (Roll) y se asigna el valor de 0 float
	ControlRotation.Pitch = 0.0f; //Se rompe el eje Y (Pitch) y se asigna el valor de 0 float

	AddMovementInput(ControlRotation.Vector());*/
	
	FVector TargetLocation{ FVector::ZeroVector };
	WheelchairPtr = UGameplayStatics::GetPlayerPawn(this, 0);

	if (WheelchairPtr)
	{
		TargetLocation = WheelchairPtr->GetActorLocation();
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("WheelchairLoc: %d"), TargetLocation));
	}

	FVector CurrentLocation{ GetActorLocation() };
	FVector Direction{ (TargetLocation - CurrentLocation).GetSafeNormal() };
	SetActorLocation(CurrentLocation + Direction * Speed * DeltaTime);
}

void APoliceman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APoliceman::StartChasing()
{
	bIsChasing = true;
}

void APoliceman::StopChasing()
{
	bIsChasing = false;
}
