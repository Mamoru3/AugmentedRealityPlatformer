// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Pickup.h"
#include "GameFramework/Actor.h"
#include "TeleportPickup.generated.h"

class APlaceablePlayer;
class ACustomGameMode;
UCLASS()
class UE5_AR_API ATeleportPickup : public APickup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATeleportPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pickup")
		void PickupCollected();

	UPROPERTY(Category = "TeleportPickup", EditAnywhere, BlueprintReadWrite)
	bool IsHidden;

	float SpawnDelay; 
};
