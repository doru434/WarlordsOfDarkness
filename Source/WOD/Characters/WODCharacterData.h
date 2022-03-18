// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WODCharacterData.generated.h"

UENUM(BlueprintType)
enum class Race : uint8
{
	HUMAN = 0 UMETA(DisplayName = "Human"),
	STRYGAN = 1 UMETA(DisplayName = "Strygan"),
	WARG = 2 UMETA(DisplayName = "Warg"),
	KARGOT = 3 UMETA(DisplayName = "Kargot")
};

USTRUCT(Blueprintable)
struct FWODCharacterData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	FName CharacterName;

	UPROPERTY(EditDefaultsOnly)
	Race ERace;

	UPROPERTY(EditDefaultsOnly)
	float MaxHP;
};
