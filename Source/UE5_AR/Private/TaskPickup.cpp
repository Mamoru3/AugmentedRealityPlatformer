// Fill out your copyright notice in the Description page of Project Settings.
#include "TaskPickup.h"

ATaskPickup::ATaskPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATaskPickup::BeginPlay()
{
	Super::BeginPlay();

}

void ATaskPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATaskPickup::PickupCollected()		//Increase task completion
{
	auto Temp = GetWorld()->GetGameState();
	ACustomGameState* GameState = Cast<ACustomGameState>(Temp);
	auto score = GameState->GetTaskCompletion();		
	GameState->SetTaskCompletion(score += 1);
}
