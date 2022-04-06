// Fill out your copyright notice in the Description page of Project Settings.


#include "WOD/Characters/AI/BaseDetourCrowdAIController.h"
#include "Navigation/CrowdFollowingComponent.h"

ABaseDetourCrowdAIController::ABaseDetourCrowdAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{

}