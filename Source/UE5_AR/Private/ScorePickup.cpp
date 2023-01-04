// Fill out your copyright notice in the Description page of Project Settings.

#include "ScorePickup.h"
#include <string>
#include "UObject/ConstructorHelpers.h"
#include "CustomGameMode.h"
#include "GameManager.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AScorePickup::AScorePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AScorePickup::BeginPlay()
{
	Super::BeginPlay();
}

//Called every frame
void AScorePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AScorePickup::PickupCollected()		//Increase score on pickup collection
{
	auto Temp = GetWorld()->GetGameState();
	ACustomGameState * GameState = Cast<ACustomGameState>(Temp);
	auto score = GameState->GetScore();
	GameState->SetScore(score+=1);
}
