// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "MushroomPickup.generated.h"

class APlaceablePlayer;
class ACustomGameMode;
class ACustomGameState;

UCLASS()
class UE5_AR_API AMushroomPickup : public APickup
{
	GENERATED_BODY()
	

public:
	// Sets default values for this actor's properties
	AMushroomPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void PickupCollected();


	ACustomGameState* GameState;
};
