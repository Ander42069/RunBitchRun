// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWheeledVehiclePawn.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"

AMyWheeledVehiclePawn::AMyWheeledVehiclePawn() noexcept
	: CollisionCapsule{ CreateDefaultSubobject<UCapsuleComponent>("CollisionCapsule") }
	, CameraArm{ CreateDefaultSubobject<USpringArmComponent>("CameraArm") }
	, Camera{ CreateDefaultSubobject<UCameraComponent>("Camera") }
{
	SetRootComponent(CollisionCapsule);
	CameraArm->SetupAttachment(GetRootComponent());
	CameraArm->TargetArmLength = 550.0f;
	CameraArm->bUsePawnControlRotation = true;

	Camera->SetupAttachment(CameraArm);
	Camera->FieldOfView = 90.0f;
}

void AMyWheeledVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Get ControlRotation from Wheelchair Actor
	FRotator ControlRotation = GetControlRotation();//Aqui esta el eje z (Yaw) y su valor se queda igual

	//Break Rotator      |  Make Rotator
	ControlRotation.Roll = 0.0f; //Se rompe el ejes X (Roll) y se asigna el valor de 0 float
	ControlRotation.Pitch = 0.0f; //Se rompe el eje Y (Pitch) y se asigna el valor de 0 float

	AddMovementInput(ControlRotation.Vector());
}

void AMyWheeledVehiclePawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMyWheeledVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyWheeledVehiclePawn::MoveForward);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyWheeledVehiclePawn::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AMyWheeledVehiclePawn::Turn);

	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AWheelchair::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &AWheelchair::StopJumping);
}

void AMyWheeledVehiclePawn::MoveForward(float Value) noexcept
{
	if (Value != 0.0f)
	{
		//FVector Forward = GetActorForwardVector();
		//AddActorLocalOffset(Forward * Value);
	};
}

void AMyWheeledVehiclePawn::LookUp(float Value) noexcept
{
	if (Value != 0.0f)
	{
		AddControllerPitchInput(Value);
	}
}

void AMyWheeledVehiclePawn::Turn(float Value) noexcept
{
	if (Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}