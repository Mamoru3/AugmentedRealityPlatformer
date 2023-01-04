// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameMode.h"
#include "GameManager.h"
#include "CustomARPawn.h"
#include "CustomGameState.h"
#include "HelloARManager.h"
#include "ARBlueprintLibrary.h"
#include "ARPlaneActor.h"
#include "Kismet/GameplayStatics.h"

ACustomGameMode::ACustomGameMode()
{
	// Add this line to your code if you wish to use the Tick() function
	PrimaryActorTick.bCanEverTick = true;

	// Set the default pawn and gamestate to be our custom pawn and gamestate programatically
	DefaultPawnClass = ACustomARPawn::StaticClass();
	GameStateClass = ACustomGameState::StaticClass();
}


void ACustomGameMode::StartPlay() 
{
	SpawnInitialActors();
	// This is called before BeginPlay
	// This function will transcend to call BeginPlay on all the actors 
	Super::StartPlay();
}

void ACustomGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ACustomGameMode::SpawnInitialActors()
{	// Spawn an instance of the HelloARManager and Manager class
	ARManager = GetWorld()->SpawnActor<AHelloARManager>(SpawnedARManager);
	GameManager = GetWorld()->SpawnActor<AGameManager>(SpawnedGameManager);
}
