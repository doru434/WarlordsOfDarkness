// Fill out your copyright notice in the Description page of Project Settings.


#include "WOD/Characters/BaseCharacter.h"
#include "WOD/Characters/WODCharacterData.h"
#include "Components/DecalComponent.h"
#include "WOD/Characters/PatrolPoint.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SelectionDecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	SelectionDecalComponent->SetupAttachment(RootComponent);
	SelectionDecalComponent->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	SelectionDecalComponent->SetRelativeLocation(FVector(0.f,0.f,-90.f));
	E_FriendOrFoe = EFriendOrFoe::Foe;
	SelectionDecalComponent->SetVisibility(false);
	this->GetMesh()->SetReceivesDecals(false);
	AttackRange = 150.f;
	ChaseRange = 1000.f;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(IsValid(CharacterData))
	{
		WODCharacterDataStruct = FWODCharacterDataStruct(CharacterData);
	}
	else
	{
		WODCharacterDataStruct = FWODCharacterDataStruct();
	}
	Health = WODCharacterDataStruct.MaxHP;
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseCharacter::SelectActor_Implementation()
{
	ISelectionInterface::SelectActor_Implementation();
	UE_LOG(LogTemp, Warning, TEXT("SelectActor ABaseCharacter override"));
	if(SelectionDecalComponent->IsVisible())
	{
		
	}
	else
	{
		SelectionDecalComponent->SetVisibility(true);
	}
}

void ABaseCharacter::UnselectActor_Implementation()
{
	ISelectionInterface::UnselectActor_Implementation();
	UE_LOG(LogTemp, Warning, TEXT("UnselectActor ABaseCharacter override"));
	if(SelectionDecalComponent->IsVisible())
	{
		SelectionDecalComponent->SetVisibility(false);
	}
}


