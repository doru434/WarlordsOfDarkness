// Fill out your copyright notice in the Description page of Project Settings.


#include "WarlordsOfDarkness/Player/CorePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "WarlordsOfDarkness/Player/PlayerCamera.h"

#include "Runtime/Engine/Classes/Components/DecalComponent.h"

#include "Components/CanvasPanelSlot.h"
#include "Runtime/Engine/Classes/Engine/UserInterfaceSettings.h"
#include "Engine/World.h"
#include "WarlordsOfDarkness/Systems/Selection/SelectionVolumeBox.h"

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

		//ZoomCameraByMouse();
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
	InputComponent->BindAction("MouseSelection", IE_Pressed, this, &ACorePlayerController::MouseSelection);
	InputComponent->BindAction("MouseAction", IE_Pressed, this, &ACorePlayerController::MouseAction);

	//Axis
	InputComponent->BindAxis("MoveForward", this, &ACorePlayerController::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &ACorePlayerController::MoveRight);
	InputComponent->BindAxis("ZoomCamera", this, &ACorePlayerController::ZoomCamera);
}
void ACorePlayerController::BeginPlay()
{
	Super::BeginPlay();
	APlayerCamera* CameraPawn = Cast<APlayerCamera>(GetPawn());
	if (CameraPawn)
	{
		CameraPawn->SpringArmComponent->SetRelativeRotation(FMath::Lerp(MinCameraRotation, MaxCameraRotation, (CameraPawn->SpringArmComponent->TargetArmLength - MinCameraHeight) / (MaxCameraHeight - MinCameraHeight)));
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
		GetPawn()->AddMovementInput(Forward, Amount * CameraSpeed);
	}
}
void ACorePlayerController::MoveRight(float Amount)
{
	if (Amount)
	{
		FVector Right = GetPawn()->GetActorRightVector();
		GetPawn()->AddMovementInput(Right, Amount * CameraSpeed);
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
void ACorePlayerController::MouseSelection()
{
	FVector TraceLocation = GetTraceUnderCursor();


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

	if (MouseLocationX < ScreenMargin)
	{
		GetPawn()->AddMovementInput(Right, -1 * CameraSpeed);
	}
	if (MouseLocationX > GameViewportSize.X - ScreenMargin)
	{
		GetPawn()->AddMovementInput(Right, 1 * CameraSpeed);
	}

	if (MouseLocationY > GameViewportSize.Y - ScreenMargin)
	{
		GetPawn()->AddMovementInput(Forward, -1 * CameraSpeed);
	}

	if (MouseLocationY < ScreenMargin)
	{
		GetPawn()->AddMovementInput(Forward, 1 * CameraSpeed);
	}
}
// End camera movement functions


// Camera rotation functions
void ACorePlayerController::ZoomCamera(float Amount)
{
	APlayerCamera* CameraPawn;
	if (Amount)
	{
		CameraPawn = Cast<APlayerCamera>(GetPawn());
		if (CameraPawn)
		{
			if (Amount > 0)
			{
				if (CameraPawn->SpringArmComponent->TargetArmLength + (Amount * CameraZoomingSpeed) <= MaxCameraHeight)
				{
					CameraPawn->SpringArmComponent->TargetArmLength = CameraPawn->SpringArmComponent->TargetArmLength + (Amount * CameraZoomingSpeed);
				}
			}
			else
			{
				if (CameraPawn->SpringArmComponent->TargetArmLength - (Amount * CameraZoomingSpeed) >= MinCameraHeight)
				{
					CameraPawn->SpringArmComponent->TargetArmLength = CameraPawn->SpringArmComponent->TargetArmLength + (Amount * CameraZoomingSpeed);
				}
			}
			CameraPawn->SpringArmComponent->SetRelativeRotation(FMath::Lerp(MinCameraRotation, MaxCameraRotation, (CameraPawn->SpringArmComponent->TargetArmLength - MinCameraHeight) / (MaxCameraHeight - MinCameraHeight)));
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
	APlayerCamera* CameraPawn;
	if (Amount != 0)
	{
		CameraPawn = Cast<APlayerCamera>(GetPawn());
		if (CameraPawn)
		{
			FRotator Rotation = CameraPawn->GetActorRotation();
			Rotation.Yaw = Rotation.Yaw + Amount;
			CameraPawn->SetActorRotation(Rotation);
		}
	}
}
void ACorePlayerController::RotateCameraByMouse()
{
	//UE_LOG(LogTemp, Warning, TEXT("Rotate Amount: %f"), DeltaMousePosition.X * (-0.05));
	RotateCamera(DeltaMousePosition.X * (RotationSpeed));
}
void ACorePlayerController::ResetRotation()
{
	if (!bCameraMovementMouseButtonPressed)
	{
		APlayerCamera* CameraPawn = Cast<APlayerCamera>(GetPawn());
		if (CameraPawn)
		{
			FRotator Rotation = FRotator(0.f, 0.f, 0.f);
			CameraPawn->SetActorRotation(Rotation);
		}
	}
}
// End rotation functions


// Selection functions
FVector ACorePlayerController::GetTraceUnderCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);

	if (Hit.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("TraceLocation %f %f %f\t"), Hit.ImpactPoint.X, Hit.ImpactPoint.Y, Hit.ImpactPoint.Z);
		return Hit.ImpactPoint;
	}
	return FVector(0, 0, 0);
}
FVector2D ACorePlayerController::CalculateSelectionBoxSize(UCanvasPanelSlot* Slot, float BaseX, float BaseY)
{
	FVector2D ImageSize = FVector2D(1,1);
	float X;
	float Y;
	this->GetMousePosition(X,Y);
	FVector2D BaseVector = FVector2D(BaseX, BaseY);
	FVector2D ActualVector = FVector2D(X, Y);
	ImageSize = ActualVector - BaseVector;
	const FVector2D viewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const float viewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(viewportSize.X, viewportSize.Y));
	ImageSize = ImageSize / viewportScale;
	//SpawnVolumeSelectionBox(ImageSize, BaseVector);
	return ImageSize;
}

void ACorePlayerController::SpawnVolumeSelectionBox(FVector2D Size, FVector2D MouseLocation)
{
	if(!SelectionVolumeBox)
	{
		FVector WorldLocation;
		FVector WorldDirection;
		DeprojectScreenPositionToWorld(MouseLocation.X, MouseLocation.Y,WorldLocation,WorldDirection);
		WorldLocation.Z = 200;
		FActorSpawnParameters SpawnInfo;
		SelectionVolumeBox = GetWorld()->SpawnActor<ASelectionVolumeBox>(WorldLocation, FRotator(WorldDirection.X,WorldDirection.Y,WorldDirection.Z), SpawnInfo);
	}
	else
	{
		FVector WorldLocation;
		FVector WorldDirection;
		DeprojectScreenPositionToWorld(MouseLocation.X, MouseLocation.Y,WorldLocation,WorldDirection);
		WorldLocation.Z = 200;
		SelectionVolumeBox->SetActorLocation(WorldLocation);
		SelectionVolumeBox->SetActorRotation(FRotator(WorldDirection.X,WorldDirection.Y,WorldDirection.Z));
		
		SelectionVolumeBox->BoxComponent->SetBoxExtent(FVector(Size-MouseLocation,0));
		FVector BoxScale = SelectionVolumeBox->BoxComponent->GetScaledBoxExtent();
		BoxScale= BoxScale/100;
		BoxScale.X = 2*abs(BoxScale.X);
		BoxScale.Y = 2*abs(BoxScale.Y);
		BoxScale.Z = 2*abs(BoxScale.Z);
		SelectionVolumeBox->MeshComponent->SetWorldScale3D(BoxScale);
	}
}

void ACorePlayerController::CreateVolumeSelectionBox(FVector Start, FVector End)
 {
	FVector Bounds = End-Start;
	Bounds = Bounds / 2;
	Bounds.Z = 50;
	if(!SelectionVolumeBox)
	{
		FActorSpawnParameters SpawnInfo;
		SelectionVolumeBox = GetWorld()->SpawnActor<ASelectionVolumeBox>(Start, FRotator(0,0,0), SpawnInfo);
		
	}
	else
	{
		FVector Location = ((End-Start)/2)+Start;
		Location. Z = 150;
		SelectionVolumeBox->SetActorLocation(Location);	
		SelectionVolumeBox->BoxComponent->SetBoxExtent(Bounds);
		FVector BoxScale = SelectionVolumeBox->BoxComponent->GetScaledBoxExtent();
		BoxScale= BoxScale/100;
		BoxScale.X = 2*abs(BoxScale.X);
		BoxScale.Y = 2*abs(BoxScale.Y);
		BoxScale.Z = 2*abs(BoxScale.Z);
		SelectionVolumeBox->MeshComponent->SetWorldScale3D(BoxScale);
	}
}

void ACorePlayerController::SelectActorsWithBox()
{
	SelectionVolumeBox->GetAllSelectableActors();
}