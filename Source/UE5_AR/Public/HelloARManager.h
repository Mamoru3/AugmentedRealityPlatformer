// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CustomGameMode.h"
#include "ScorePickup.h"
#include "GameFramework/Actor.h"
#include "HelloARManager.generated.h"


class UARSessionConfig;
class AARPlaneActor;
class UARPlaneGeometry;
class AScorePickup;
class ATeleportPickup;
class ATaskPickup;
class AMushroomPickup;
class ACustomGameState;
UCLASS()
class UE5_AR_API AHelloARManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHelloARManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Create a default Scene Component
	UPROPERTY(Category = "SceneComp", VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* SceneComponent;

	void SpawnPickupActor(FVector location);
	void SpawnTaskPickupActor(FVector location);
	void SpawnTeleportPickupActor(FVector location);
	void SpawnMushroomPickupActor(FVector location);
	void PickupsSpawnManager(FVector location);
protected:
	
	// Updates the plane actors on every frame as long as the AR Session is running
	void UpdatePlaneActors();

	AARPlaneActor* SpawnPlaneActor();

	void PlayerFallCheck();

	void ResetARCoreSession();

	UFUNCTION(BlueprintCallable, Category = "ResetSession")
	void DestroyAllPlanes();

	//Base plane actor for geometry detection
	AARPlaneActor* PlaneActor;


	//Map of geometry planes
	TMap<UARPlaneGeometry*, AARPlaneActor*> PlaneActors;

	//Index for plane colours adn array of colours
	int PlaneIndex = 0;
	TArray<FColor> PlaneColors;

	ACustomGameState* GameState;
	ACustomGameMode* GM;

public:
	// Configuration file for AR Session
	UARSessionConfig* Config;

	
	AScorePickup* Pickup;
	UPROPERTY(Category = "Pickup", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AScorePickup> PickupToSpawn;

	ATaskPickup* TaskPickup;
	UPROPERTY(Category = "TaskPickup", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATaskPickup> TaskPickupToSpawn;

	ATeleportPickup* TeleportPickup;
	UPROPERTY(Category = "TeleportPickup", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ATeleportPickup> TeleportPickupToSpawn;
	
	AMushroomPickup* MushroomPickup;
	UPROPERTY(Category = "MushroomPickup", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMushroomPickup> MushroomPickupToSpawn;
	
	FVector LowestPlane;

	UPROPERTY(Category = "FirstPlane", EditAnywhere, BlueprintReadWrite)
	bool FirstPlaneSpawned;

	FVector FirstPlanePosition;

	float ScorePickupSpawnTimer;
	float TaskPickupSpawnTimer;
	float MushroomPickupSpawnTimer;
	int TaskPickupCounter;

	float RandomXPosition;
	float RandomYPosition;

	float ColorShiftingTimer;	

};

