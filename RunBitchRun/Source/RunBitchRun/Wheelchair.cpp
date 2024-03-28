// Fill out your copyright notice in the Description page of Project Settings.


#include "Wheelchair.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GroundTiles.h"
#include "RunBitchRunGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"


AWheelchair::AWheelchair() noexcept
	: CameraArm{ CreateDefaultSubobject<USpringArmComponent>("CameraArm") }
	, Camera{ CreateDefaultSubobject<UCameraComponent>("Camera") }
{
	CameraArm->SetupAttachment(GetRootComponent());
	CameraArm->TargetArmLength = 550.0f;
	CameraArm->bUsePawnControlRotation = true;

	Camera->SetupAttachment(CameraArm);
	Camera->bUsePawnControlRotation = true;

	GetCharacterMovement()->JumpZVelocity = 500.0f;
}

void AWheelchair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Get ControlRotation from Wheelchair Actor
	FRotator ControlRotation = GetControlRotation();//Aqui esta el eje Z (Yaw) y su valor se queda igual

	//Break Rotator     |  Make Rotator
	ControlRotation.Roll = 0.0f; //Se rompe el eje X (Roll) y se asigna el valor de 0 float
	ControlRotation.Pitch = 0.0f; //Se rompe el eje Y (Pitch) y se asigna el valor de 0 float

	AddMovementInput(ControlRotation.Vector());

}

void AWheelchair::ChangeLaneUpdate(const float LaneValue) noexcept
{
	FVector Location = GetCapsuleComponent()->GetComponentLocation();
	Location.Y = FMath::Lerp(pRunBitchRunGameModeBase->GetLaneSwitchValues()[CurrentLaneIndex], pRunBitchRunGameModeBase->GetLaneSwitchValues()[NewLaneIndex], LaneValue);
	SetActorLocation(Location);
}

void AWheelchair::ChangeLaneFinished() noexcept
{
	CurrentLaneIndex = NewLaneIndex;
}

void AWheelchair::BeginPlay()
{
	Super::BeginPlay();

	pRunBitchRunGameModeBase = Cast<ARunBitchRunGameModeBase>(GetWorld()->GetAuthGameMode());

	check(pRunBitchRunGameModeBase);
}

void AWheelchair::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &AWheelchair::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &AWheelchair::MoveRight);
	PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &AWheelchair::MoveDown);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AWheelchair::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AWheelchair::StopJumping);
}

void AWheelchair::MoveLeft() noexcept
{
	NewLaneIndex = FMath::Clamp(CurrentLaneIndex + (-1), 0, MaxLanes - 1);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("LANE VALUE: %d"), NewLaneIndex));

	ChangeLane();
}

void AWheelchair::MoveRight() noexcept
{
	NewLaneIndex = FMath::Clamp(CurrentLaneIndex + (1), 0, MaxLanes - 1);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("LANE VALUE: %d"), NewLaneIndex));

	ChangeLane();
}

void AWheelchair::MoveDown() noexcept
{
	GetCharacterMovement()->AddImpulse(FVector(0.0f, 0.0f, MoveDownImpulse), true);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("IMPULSE VALUE: %d"), MoveDownImpulse));
}
