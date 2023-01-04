// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "CustomGameState.generated.h"

/**
 * 
 */
UCLASS()
class UE5_AR_API ACustomGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ACustomGameState();
	~ACustomGameState() = default;
	

	UFUNCTION(BlueprintCallable, Category = "Score")
	void SetScore(const int32 NewScore);

	UFUNCTION(BlueprintCallable, Category = "Score")
	int32 GetScore();

	

	void SetPlaceableSelected(bool value);

	void SetAreARPlanesDisplayed(bool value);

	bool GetPlaceableSelected();

	UFUNCTION(BlueprintCallable, Category = "Volume")
	bool GetAreARPlanesDisplayed();

	UFUNCTION(BlueprintCallable, Category = "Volume")
	bool GetAreARPlanesColorShifting();

	void SetAreARPlanesColorShifting(bool value);

	
	UFUNCTION(BlueprintCallable, Category = "TaskCompletion")
	void SetTaskCompletion(int value);

	UFUNCTION(BlueprintCallable, Category = "TaskCompletion")
	int GetTaskCompletion();

private:
	bool IsPlaceableSelected;
	bool IsPlaceableSpawned;
	int Score;
	int TaskCompletion;

	bool AreARPlanesDisplayed;
	bool AreARPlanesColorShifting;
};
