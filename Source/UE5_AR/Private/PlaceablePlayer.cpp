// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceablePlayer.h"
#include "GameManager.h"
#include "CustomGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"

APlaceablePlayer::APlaceablePlayer()
{
	PrimaryActorTick.bCanEverTick = true;

}
void APlaceablePlayer::BeginPlay()
{
	Super::BeginPlay();
	auto Temp = GetWorld()->GetAuthGameMode();
	GM = Cast<ACustomGameMode>(Temp);
	GameManager = GM->GameManager;
	GetMesh()->BodyInstance.bLockYRotation = true;		//Lock rotation on X and Y axis not to rotate while moving
	GetMesh()->BodyInstance.bLockXRotation = true;
	
	AIController = Cast<AAIController>(GetController());		//Get AI controller

	if(!AIController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, TEXT("AIController not found"));
	}
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);

	auto GameS = GetWorld()->GetGameState();		//Get gamestate
	ACustomGameState* GameState = Cast<ACustomGameState>(GameS);
	GameState->SetScore(0);
}

void APlaceablePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlayer();
}

// Called to bind functionality to input
void APlaceablePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlaceablePlayer::MovePlayer()		//Function for player movement
{
	if(AIController)		//If the AIController is vlaid
	{
		FVector ActualPosition = GetActorLocation();		//Store Actor location in a variable
		if (DoesPlayerWalk == true)		//If player walks 
		{
			//Use pathfinding and navmesh to reach the desired location (walking)
			AIController->MoveToLocation(GameManager->MoveLocation,-1,false, true );
		}
		if (DoesPlayerTeleport == true)	//If player jumps
		{
			//If player teleports, set location to new location, but increase Z to be on top of the plane, calculate rotation and reset all variables
			FVector dirV = GameManager->MoveLocation - GameManager->ActualPosition;
			FRotator rot_ = dirV.Rotation();
			SetActorLocation(FVector(GameManager->MoveLocation.X, GameManager->MoveLocation.Y, GameManager->MoveLocation.Z+20));
			SetActorRotation(rot_);
			DoesPlayerWalk = false;
			CanPlayerTeleport = false;
			DoesPlayerTeleport = false;
		}
		DistanceToTarget(GameManager->MoveLocation - GetActorLocation());	//Function called after movement to check how close the player is to the target
	}
}

void APlaceablePlayer::DistanceToTarget(FVector DestinationRange)
{
	//Check distance to target, it is different depending on whether the player is jumping or flying. Flying needs a bigger acceptance radius
	if(DoesPlayerWalk)		//If player is walking
	{
		if((DestinationRange.Length() < 5))	//Distance check, if player is close to the destination
		{
			Controller->StopMovement();		//Stop movement, reset all variables and collision
			DoesPlayerWalk = false;
			DoesPlayerTeleport = false;
			CanPlayerTeleport = false;
		}
	}
}