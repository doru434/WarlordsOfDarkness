// Fill out your copyright notice in the Description page of Project Settings.


#include "WOD/Systems/Spawner/WODSpawner.h"

// Sets default values
AWODSpawner::AWODSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWODSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWODSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

