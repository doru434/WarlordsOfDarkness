// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CameraData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class WOD_API UCameraData : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly)
	bool AllowRotation;
	
	UPROPERTY(EditDefaultsOnly)
	float ScreenMargin;

	UPROPERTY(EditDefaultsOnly)
	float CameraSpeed;

	UPROPERTY(EditDefaultsOnly)
	float RotationSpeed;

	UPROPERTY(EditDefaultsOnly)
	float CameraZoomingSpeed;

	UPROPERTY(EditDefaultsOnly)
	float MaxCameraHeight;

	UPROPERTY(EditDefaultsOnly)
	float MinCameraHeight;

	UPROPERTY(EditDefaultsOnly)
	FRotator MinCameraRotation;

	UPROPERTY(EditDefaultsOnly)
	FRotator MaxCameraRotation;
};
