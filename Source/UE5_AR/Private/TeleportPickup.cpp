// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportPickup.h"
#include <string>
#include "UObject/ConstructorHelpers.h"
#include "CustomGameMode.h"
#include "GameManager.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATeleportPickup::ATeleportPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void ATeleportPickup::BeginPlay()
{
	Super::BeginPlay();
	IsHidden = true;
	SetActorHiddenInGame(true);
	SpawnDelay = 0;
}

//Called every frame
void ATeleportPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GM->GameManager->Player && IsHidden == true)		//When player spawn and the object is hidden
	{
		SpawnDelay += DeltaTime;		//Delay to spawn the pickup after player spawns
		if (SpawnDelay > 3.f)		//After the delay
		{
			//GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Blue, FString::Printf(TEXT("Spawned teleport pickup")));
			SetActorHiddenInGame(false);	//Show pickup
			IsHidden = false;
		}
	}
	
}

void ATeleportPickup::PickupCollected()
{
	if (GM->GameManager->Player)		//If pickup is collected, player can teleport 
	{
		GM->GameManager->Player->IsTeleportDeviceCollected = true;
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("Collected Teleport Pickup"));
	}
}
