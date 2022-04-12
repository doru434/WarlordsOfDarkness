// Fill out your copyright notice in the Description page of Project Settings.


#include "WOD/Characters/AI/BaseDetourCrowdAIController.h"
#include "Navigation/CrowdFollowingComponent.h"

ABaseDetourCrowdAIController::ABaseDetourCrowdAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{

}

ETeamAttitude::Type ABaseDetourCrowdAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const APawn* OtherPawn = Cast<APawn>(&Other)) {

		if (const IGenericTeamAgentInterface* TeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()))
		{
			return Super::GetTeamAttitudeTowards(*OtherPawn->GetController());
		}
	}

	return ETeamAttitude::Neutral;
}
