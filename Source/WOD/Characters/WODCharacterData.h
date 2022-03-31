#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WODCharacterData.generated.h"

/**
* 
*/

UENUM(BlueprintType)
enum class ERace : uint8
{
	HUMAN = 0 UMETA(DisplayName = "Human"),
	STRYGAN = 1 UMETA(DisplayName = "Strygan"),
	WARG = 2 UMETA(DisplayName = "Warg"),
	KARGOT = 3 UMETA(DisplayName = "Kargot")
};

UCLASS(Blueprintable)
class WOD_API UWODCharacterData : public UObject
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditDefaultsOnly)
	FName CharacterName;

	UPROPERTY(EditDefaultsOnly)
	ERace Race;

	UPROPERTY(EditDefaultsOnly)
	float MaxHP;
};
