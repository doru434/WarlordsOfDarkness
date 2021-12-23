// Fill out your copyright notice in the Description page of Project Settings.


#include "WarlordsOfDarkness/Systems/Selection/SelectionVolumeBox.h"
#include "SelectionInterface.h"

// Sets default values
ASelectionVolumeBox::ASelectionVolumeBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SelectionBox"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (MeshObj.Object)
	{
		MeshComponent->SetStaticMesh(MeshObj.Object);
	}
	const ConstructorHelpers::FObjectFinder<UMaterialInstance> MatInstObj(TEXT("MaterialInstanceConstant'/Game/MI_SelectionBox.MI_SelectionBox'"));
	if (MatInstObj.Object)
	{
		MeshComponent->SetMaterial(0, MatInstObj.Object);
	}
	RootComponent = BoxComponent;
	MeshComponent->SetupAttachment(BoxComponent);
	MeshComponent->SetCollisionProfileName(TEXT("OverlapAll"));
}

// Called when the game starts or when spawned
void ASelectionVolumeBox::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->SetHiddenInGame(false);
}

// Called every frame
void ASelectionVolumeBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
TArray<AActor*> ASelectionVolumeBox::GetAllSelectableActors()
{
	TArray<AActor*> OverlappingActors;
	TArray<int> IndexesForDelete;
	MeshComponent->GetOverlappingActors(OverlappingActors);
	for (int i = 0; i < OverlappingActors.Num(); i++)
	{		
		ISelectionInterface* TheInterface = Cast<ISelectionInterface>(OverlappingActors[i]);
		if (TheInterface) {
			// Don't call your functions directly, use the 'Execute_' prefix //the Execute_ReactToHighNoon
			// and Execute_ReactToMidnight are generated on compile //you may need to compile before these
			// functions will appear TheInterface->Execute_ReactToHighNoon (pointerToAnyUObject);
			TheInterface->SelectActor();
		}
		else
		{
			IndexesForDelete.Add(i);
		}			
		
	}
	for (int i = 0; i < IndexesForDelete.Num(); i++)
	{
		OverlappingActors.RemoveAt(IndexesForDelete[i], 1, true);
	}
	return OverlappingActors;
}
