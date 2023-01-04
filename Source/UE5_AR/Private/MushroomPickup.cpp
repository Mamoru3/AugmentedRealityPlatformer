// Fill out your copyright notice in the Description page of Project Settings.


#include "MushroomPickup.h"
#include <string>
#include "UObject/ConstructorHelpers.h"
#include "CustomGameMode.h"
#include "GameManager.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMushroomPickup::AMushroomPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMushroomPickup::BeginPlay()
{
	Super::BeginPlay();

	auto Temp = GetWorld()->GetGameState();
	GameState = Cast<ACustomGameState>(Temp);
}

//Called every frame
void AMushroomPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AMushroomPickup::PickupCollected()
{
	if (GM->GameManager->Player)		//If pickup is collected, planes will start changing colors
	{
		GameState->SetAreARPlanesColorShifting(true);
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Collected Mush Pickup"));
	}
}
