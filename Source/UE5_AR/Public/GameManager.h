// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"
#include "PlaceablePlayer.h"
#include "ARPlaneActor.h"
#include "GameManager.generated.h"

class AHelloARManager;
UCLASS()
class UE5_AR_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Spawn")
		void SpawnPlayer();
	
 //* @brief Perform a line trace at the screen position provided and place a default Placeable actor on it.
 //* Create another actor class that inherits from APlaceableActor and is spawned here instead of the default one. Make sure this new object is placed on the Plane rather than halfway through a plane
 //* @param ScreenPos Pass the Screen Position as an FVector
 //*/
	virtual void LineTraceSpawnActor(FVector ScreenPos);

	void LineTraceMovement(FVector ScreenPos);

	FTransform LineTraceResult(FVector ScreenPos);
	bool WorldHitTest(FVector ScreenPos, FHitResult& HitResult);

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	void flipPlaneVisibility();

	
	UPROPERTY(Category = "Placeable", EditAnywhere, BlueprintReadWrite)
		APlaceablePlayer* Player;
	
	UPROPERTY(Category = "Placeable", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<APlaceableCharacter> PlacableToSpawn;

	FVector MoveLocation;
	FVector ActualPosition;


	FTransform TraceResultTransform;

	//IMPORTANT, Pin components are not used as the application will be available for both ARCore but specifically to ARKit. 
	APlayerController* playerController;
	FVector WorldPos;
	FVector WorldDir;
	FHitResult HR;

	AHelloARManager* ARGameManager;
};
