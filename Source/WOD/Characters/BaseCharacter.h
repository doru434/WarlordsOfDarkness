// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WOD/Systems/Selection/SelectionInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

 UENUM(BlueprintType)
 enum class EFriendOrFoe : uint8 {
      Friend = 0 UMETA(DisplayName = "Friend"),
      Foe = 1  UMETA(DisplayName = "Foe"),
 };
 
UCLASS()
class WOD_API ABaseCharacter : public ACharacter, public ISelectionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Code Variables")
	class UDecalComponent* SelectionDecalComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Code Variables")
	EFriendOrFoe E_FriendOrFoe;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SelectActor_Implementation() override;
	virtual void UnselectActor_Implementation() override;
};
