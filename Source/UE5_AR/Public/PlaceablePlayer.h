// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlaceableCharacter.h"
#include "AIController.h"
#include "PlaceablePlayer.generated.h"
class ACustomGameMode;
class AGameManager;

//UENUM()
//enum State
//{
//	Idle,
//	Running,
//	Jumping
//};
UCLASS()
class UE5_AR_API APlaceablePlayer : public APlaceableCharacter
{
	GENERATED_BODY()
public:
	APlaceablePlayer();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MovePlayer();

	void DistanceToTarget(FVector DestinationRange);

	AGameManager* GameManager;

protected:

	AAIController* AIController;
};
