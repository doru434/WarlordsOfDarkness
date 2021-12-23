// Copyright Epic Games, Inc. All Rights Reserved.

#include "WarlordsOfDarknessGameMode.h"
#include "WarlordsOfDarknessPlayerController.h"
#include "WarlordsOfDarknessCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWarlordsOfDarknessGameMode::AWarlordsOfDarknessGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AWarlordsOfDarknessPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}