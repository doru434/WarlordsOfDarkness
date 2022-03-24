	// Fill out your copyright notice in the Description page of Project Settings.


#include "WOD/Player/CorePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "WOD/Player/PlayerPawn.h"

#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "GameFramework/SpringArmComponent.h"
#include "WOD/Systems/Selection/SelectionInterface.h"

ACorePlayerController::ACorePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
// PlayerController interface
void ACorePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// -- Camera movement and rotattion 
	if (!bCameraMovementMouseButtonPressed)
	{
		MoveCameraByMouse();
	}

	if (bCameraMovementMouseButtonPressed)
	{
		FVector2D NewMousePosition;
		GetMousePosition(NewMousePosition.X, NewMousePosition.Y);
		DeltaMousePosition.X = BaseMousePosition.X - NewMousePosition.X;
		DeltaMousePosition.Y = BaseMousePosition.Y - NewMousePosition.Y;

		ZoomCameraByMouse();
		RotateCameraByMouse();

		BaseMousePosition = NewMousePosition;
	}
}
void ACorePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	//Action
	InputComponent->BindAction("MouseCameraMovementKey", IE_Pressed, this, &ACorePlayerController::MouseCameraMovementActivation);
	InputComponent->BindAction("MouseCameraMovementKey", IE_Released, this, &ACorePlayerController::MouseCameraMovementDeactivation);
	InputComponent->BindAction("ResetRotation", IE_Pressed, this, &ACorePlayerController::ResetRotation);
	InputComponent->BindAction("MouseAction", IE_Pressed, this, &ACorePlayerController::MouseAction);

	//Axis
	InputComponent->BindAxis("MoveForward", this, &ACorePlayerController::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &ACorePlayerController::MoveRight);
	InputComponent->BindAxis("ZoomCamera", this, &ACorePlayerController::ZoomCamera);
}
void ACorePlayerController::BeginPlay()
{
	Super::BeginPlay();
	if(IsValid(CameraData))
	{
		CameraParamsData = FCameraParamsData(CameraData);
	}
	else
	{
		CameraParamsData = FCameraParamsData();
	}
	APlayerPawn* PlayerPawn = Cast<APlayerPawn>(GetPawn());
	if (PlayerPawn)
	{
		PlayerPawn->SpringArmComponent->TargetArmLength =  CameraParamsData.MinCameraHeight+ ((CameraParamsData.MaxCameraHeight - CameraParamsData.MinCameraHeight)/2);
		PlayerPawn->SpringArmComponent->SetRelativeRotation(
			FMath::Lerp(CameraParamsData.MinCameraRotation,
				CameraParamsData.MaxCameraRotation,
				(PlayerPawn->SpringArmComponent->TargetArmLength - CameraParamsData.MinCameraHeight) / (CameraParamsData.MaxCameraHeight - CameraParamsData.MinCameraHeight)
				));
	}
}
// End PlayerController interface

// General Functions
FVector2D ACorePlayerController::GetGameViewportSize()
{
	FVector2D Result = FVector2D(1, 1);

	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize( /*out*/Result);
	}

	return Result;
}

FVector2D ACorePlayerController::GetGameResolution()
{
	FVector2D Result = FVector2D(1, 1);

	Result.X = GSystemResolution.ResX;
	Result.Y = GSystemResolution.ResY;

	return Result;
}


// Camera movement functions
void ACorePlayerController::MoveUp(float Amount)
{
	if (Amount)
	{
		FVector Forward = GetPawn()->GetActorForwardVector();
		//GetPawn()->AddMovementInput(Forward, Amount * CameraParamsData.CameraSpeed);
		GetPawn()->AddActorWorldOffset(Forward*(Amount * CameraParamsData.CameraSpeed));
	}
}
void ACorePlayerController::MoveRight(float Amount)
{
	if (Amount)
	{
		FVector Right = GetPawn()->GetActorRightVector();
		GetPawn()->AddActorWorldOffset(Right*(Amount * CameraParamsData.CameraSpeed));
	}
}
void ACorePlayerController::MouseCameraMovementActivation()
{
	bCameraMovementMouseButtonPressed = true;
	GetMousePosition(BaseMousePosition.X, BaseMousePosition.Y);
}
void ACorePlayerController::MouseCameraMovementDeactivation()
{
	bCameraMovementMouseButtonPressed = false;
	BaseMousePosition.X = 0;
	BaseMousePosition.Y = 0;
}
void ACorePlayerController::MouseAction()
{

}

void ACorePlayerController::MoveCameraByMouse()
{
	float MouseLocationX;
	float MouseLocationY;
	GetMousePosition(MouseLocationX, MouseLocationY);

	FVector2D GameViewportSize = GetGameViewportSize();
	FVector Forward = GetPawn()->GetActorForwardVector();
	FVector Right = GetPawn()->GetActorRightVector();

	if (MouseLocationX < CameraParamsData.ScreenMargin)
	{
		GetPawn()->AddMovementInput(Right, -1 * CameraParamsData.CameraSpeed);
	}
	if (MouseLocationX > GameViewportSize.X - CameraParamsData.ScreenMargin)
	{
		GetPawn()->AddMovementInput(Right, 1 * CameraParamsData.CameraSpeed);
	}

	if (MouseLocationY > GameViewportSize.Y - CameraParamsData.ScreenMargin)
	{
		GetPawn()->AddMovementInput(Forward, -1 * CameraParamsData.CameraSpeed);
	}

	if (MouseLocationY < CameraParamsData.ScreenMargin)
	{
		GetPawn()->AddMovementInput(Forward, 1 * CameraParamsData.CameraSpeed);
	}
}
// End camera movement functions


// Camera rotation functions
void ACorePlayerController::ZoomCamera(float Amount)
{
	
	APlayerPawn* PlayerPawn;
	if (Amount)
	{
		PlayerPawn = Cast<APlayerPawn>(GetPawn());
		if (PlayerPawn)
		{
			if (Amount > 0)
			{
				if (PlayerPawn->SpringArmComponent->TargetArmLength + (Amount * CameraParamsData.CameraZoomingSpeed) <= CameraParamsData.MaxCameraHeight)
				{
					PlayerPawn->SpringArmComponent->TargetArmLength = PlayerPawn->SpringArmComponent->TargetArmLength + (Amount * CameraParamsData.CameraZoomingSpeed);
				}
			}
			else
			{
				if (PlayerPawn->SpringArmComponent->TargetArmLength - (Amount * CameraParamsData.CameraZoomingSpeed) >= CameraParamsData.MinCameraHeight)
				{
					PlayerPawn->SpringArmComponent->TargetArmLength = PlayerPawn->SpringArmComponent->TargetArmLength + (Amount * CameraParamsData.CameraZoomingSpeed);
				}
			}
			if(CameraParamsData.AllowRotation)
			{
				PlayerPawn->SpringArmComponent->SetRelativeRotation(
				FMath::Lerp(CameraParamsData.MinCameraRotation,
					CameraParamsData.MaxCameraRotation,
					(PlayerPawn->SpringArmComponent->TargetArmLength - CameraParamsData.MinCameraHeight) / (CameraParamsData.MaxCameraHeight - CameraParamsData.MinCameraHeight)
					)
					);
			}
		}
	}
}
void ACorePlayerController::ZoomCameraByMouse()
{
	UE_LOG(LogTemp, Warning, TEXT("Zoom Amount: %f"), DeltaMousePosition.X * (-0.05));
	ZoomCamera(DeltaMousePosition.Y * (-0.05));
}
void ACorePlayerController::RotateCamera(float Amount)
{
	if(CameraParamsData.AllowRotation)
	{
		APlayerPawn* PlayerPawn;
		if (Amount != 0)
		{
			PlayerPawn = Cast<APlayerPawn>(GetPawn());
			if (PlayerPawn)
			{
				FRotator Rotation = PlayerPawn->GetActorRotation();
				Rotation.Yaw = Rotation.Yaw + Amount;
				PlayerPawn->SetActorRotation(Rotation);
			}
		}
	}
}
void ACorePlayerController::RotateCameraByMouse()
{
	//UE_LOG(LogTemp, Warning, TEXT("Rotate Amount: %f"), DeltaMousePosition.X * (-0.05));
	RotateCamera(DeltaMousePosition.X * (CameraParamsData.RotationSpeed));
}
void ACorePlayerController::ResetRotation()
{
	if (!bCameraMovementMouseButtonPressed)
	{
		APlayerPawn* PlayerPawn = Cast<APlayerPawn>(GetPawn());
		if (PlayerPawn)
		{
			FRotator Rotation = FRotator(0.f, 0.f, 0.f);
			PlayerPawn->SetActorRotation(Rotation);
		}
	}
}
// End rotation functions


// Selection functions
FHitResult ACorePlayerController::GetTraceUnderCursor(ETraceTypeQuery TraceChannel)
{
	FHitResult Hit;
	GetHitResultUnderCursorByChannel(TraceChannel, false, Hit);
	
	return Hit;
}
