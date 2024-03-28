// Fill out your copyright notice in the Description page of Project Settings.


#include "Wheelchair2.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

AWheelchair2::AWheelchair2() noexcept
	: CameraArm{ CreateDefaultSubobject<USpringArmComponent>("CameraArm") }
	, Camera{ CreateDefaultSubobject<UCameraComponent>("Camera") }
{
	CameraArm->SetupAttachment(GetRootComponent());
	CameraArm->TargetArmLength = 550.0f;
	CameraArm->bUsePawnControlRotation = true;

	Camera->SetupAttachment(CameraArm);
	Camera->FieldOfView = 90.0f;
}

void AWheelchair2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Get ControlRotation from Wheelchair Actor
	FRotator ControlRotation = GetControlRotation();//Aqui esta el eje z (Yaw) y su valor se queda igual

	//Break Rotator      |  Make Rotator
	ControlRotation.Roll = 0.0f; //Se rompe el ejes X (Roll) y se asigna el valor de 0 float
	ControlRotation.Pitch = 0.0f; //Se rompe el eje Y (Pitch) y se asigna el valor de 0 float

	AddMovementInput(ControlRotation.Vector());
}

void AWheelchair2::BeginPlay()
{
	Super::BeginPlay();
}

void AWheelchair2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AWheelchair2::MoveForward);
	PlayerInputComponent->BindAxis("LookUp", this, &AWheelchair2::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AWheelchair2::Turn);

	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AWheelchair::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &AWheelchair::StopJumping);
}

void AWheelchair2::MoveForward(float Value) noexcept
{
	if (Value != 0.0f)
	{

	};
}

void AWheelchair2::LookUp(float Value) noexcept
{
	if (Value != 0.0f)
	{
		AddControllerPitchInput(Value);
	}
}

void AWheelchair2::Turn(float Value) noexcept
{
	if (Value != 0.0f)
	{
		AddControllerYawInput(Value);
	}
}

/*void AWheelchair::Jump() noexcept
{

}*/

