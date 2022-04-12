// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/UObjectGlobals.h"
#include "AIController.h"
#include "BaseDetourCrowdAIController.generated.h"

/**
 * 
 */
UCLASS()
class WOD_API ABaseDetourCrowdAIController : public AAIController
{
	GENERATED_BODY()
	public:
	ABaseDetourCrowdAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;


};
