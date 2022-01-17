// Fill out your copyright notice in the Description page of Project Settings.


#include "WarlordsOfDarkness/Characters/BaseCharacter.h"
#include "Components/DecalComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SelectionDecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("SelectionDecal"));
	SelectionDecalComponent->SetupAttachment(RootComponent);
	SelectionDecalComponent->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	SelectionDecalComponent->SetRelativeLocation(FVector(0.f,0.f,-90.f));
	ConstructorHelpers::FObjectFinder<UMaterialInstance> DecalMaterial(TEXT("MaterialInstanceConstant'/Game/Materials/MI_DecalRing.MI_DecalRing'"));
	if(DecalMaterial.Object != nullptr)
	{
		SelectionDecalComponent->SetMaterial(0,DecalMaterial.Object);
	}
	SelectionDecalComponent->SetVisibility(false);
	this->GetMesh()->SetReceivesDecals(false);
	
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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


