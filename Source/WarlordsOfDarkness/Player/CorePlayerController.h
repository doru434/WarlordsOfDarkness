// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CanvasPanelSlot.h"
#include "GameFramework/PlayerController.h"
#include "CorePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WARLORDSOFDARKNESS_API ACorePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ACorePlayerController();

protected:
	// Camera properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ScreenMargin = 40.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CameraSpeed = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RotationSpeed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CameraZoomingSpeed = 40;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxCameraHeight = 2400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MinCameraHeight = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator MinCameraRotation = FRotator(-35.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator MaxCameraRotation = FRotator(-70.f, 0.f, 0.f);

	UPROPERTY()
		bool bCameraMovementMouseButtonPressed = false;
	UPROPERTY()
		FVector2D BaseMousePosition = FVector2D(0.f, 0.f);
	UPROPERTY()
		FVector2D DeltaMousePosition = FVector2D(0.f, 0.f);
	UPROPERTY()
	class ASelectionVolumeBox*  SelectionVolumeBox;

	// End camera properties

	// === Functions ===

	// PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	// End PlayerController interface

	// General Functions
	UFUNCTION()
		FVector2D GetGameViewportSize();
	UFUNCTION()
		FVector2D GetGameResolution();

	// Camera movement functions
	UFUNCTION()
		void MoveUp(float Amount);
	UFUNCTION()
		void MoveRight(float Amount);
	UFUNCTION()
		void MouseCameraMovementActivation();
	UFUNCTION()
		void MouseCameraMovementDeactivation();
	UFUNCTION()
	void MouseSelection();
	UFUNCTION()
	void MouseAction();

	UFUNCTION()
		void MoveCameraByMouse();
	// End camera movement functions

	// Camera rotation functions
	UFUNCTION()
		void ZoomCamera(float Amount);
	UFUNCTION()
		void ZoomCameraByMouse();
	UFUNCTION()
		void RotateCamera(float Amount);
	UFUNCTION()
		void RotateCameraByMouse();
	UFUNCTION()
		void ResetRotation();
	// End rotation functions

	// Selection functions
	UFUNCTION(BlueprintCallable)
	FVector GetTraceUnderCursor();


	UFUNCTION(BlueprintCallable)
	FVector2D CalculateSelectionBoxSize(UCanvasPanelSlot* Slot, float BaseX, float BaseY);
	void SpawnVolumeSelectionBox(FVector2D Size, FVector2D MouseLocation);
	
	UFUNCTION(BlueprintCallable)
	void CreateVolumeSelectionBox(FVector Start, FVector End);

	UFUNCTION(BlueprintCallable)
	void SelectActorsWithBox();
};
