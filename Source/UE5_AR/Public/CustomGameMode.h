// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/EngineTypes.h"
#include "CustomGameMode.generated.h"

//Forward Declarations
class APlaceableCharacter;
class AGameManager;
class AHelloARManager;
/**
 * 
 */

UCLASS()
class UE5_AR_API ACustomGameMode : public AGameModeBase
{
	GENERATED_BODY()
private:

	FTimerHandle Ticker;


public:
	ACustomGameMode();
	virtual ~ACustomGameMode() = default;

	virtual void StartPlay() override;

	/**
	 * @brief An example of an event as generally seen within the Event Graph of Blueprints
	 *  You can have different implementations of this event which will be called when you call this as a delegate.
	 *	See the CPP For more information on the implementation
	 */
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	virtual void SpawnInitialActors();
	
	UPROPERTY(Category = "ARPlanesRender", EditAnywhere, BlueprintReadWrite)
	AGameManager* GameManager;

	UPROPERTY(Category = "ARPlanesRender", EditAnywhere, BlueprintReadWrite)
	AHelloARManager*ARManager;
	
	UPROPERTY(Category = "Placeable", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AGameManager> SpawnedGameManager;

	UPROPERTY(Category = "Placeable", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AHelloARManager> SpawnedARManager;
};
