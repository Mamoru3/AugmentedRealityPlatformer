// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include <string>
#include "CustomActor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "HelloARManager.h"
#include "ARPin.h"
#include "ARBlueprintLibrary.h"
#include "HelloARManager.h"
#include <string>
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AGameManager::AGameManager() :
	Player(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	Super::BeginPlay();
	playerController = UGameplayStatics::GetPlayerController(this, 0);
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameManager::SpawnPlayer()
{
		const FActorSpawnParameters SpawnInfo;
		const FRotator MyRot(0, 0, 0);
		const FVector MyLoc(0, 0, 1000);
		Player = GetWorld()->SpawnActor<APlaceablePlayer>(PlacableToSpawn, MyLoc, MyRot, SpawnInfo);
}

FTransform AGameManager::LineTraceResult(FVector ScreenPos)		//Function to return touch position in real world
{
	//Deproject screen touch to real world, cast the screenPosition vector passed from CustomARPawn to a 2D vector for the screen coordinates.
	UGameplayStatics::DeprojectScreenToWorld(playerController, FVector2D(ScreenPos), WorldPos, WorldDir); 
	auto TraceResult = UARBlueprintLibrary::LineTraceTrackedObjects(FVector2D(ScreenPos), false, false, false, true);
	//Checks if the location is valid
	if (TraceResult.IsValidIndex(0))
	{
		// Get the first found object in the line trace - ignoring the rest of the array elements
		auto TrackedTF = TraceResult[0].GetLocalToWorldTransform();
		if (FVector::DotProduct(TrackedTF.GetRotation().GetUpVector(), WorldDir) < 0)		//If the position is not under the plane, dot product for angle
		{
			return TrackedTF;		//Return deprojected location of touch (will be the location in the real world.
		}
	}
	return FTransform::Identity;		//Return identity if Trace result index is not valid
}
bool AGameManager::WorldHitTest(FVector ScreenPos,FHitResult& HitResult)
{
	bool deprojectionSuccess = UGameplayStatics::DeprojectScreenToWorld(playerController, FVector2D(ScreenPos), /*out*/
		WorldPos, /*out*/ WorldDir);
	
	if (deprojectionSuccess)
		{
		// construct trace vector (from point clicked to 1000.0 units beyond in same direction)
		FVector traceEndVector = WorldDir * 1000.0;
		traceEndVector = WorldPos + traceEndVector;
		// perform line trace (Raycast)
		bool traceSuccess = GetWorld()->LineTraceSingleByChannel(HitResult, WorldPos, traceEndVector, ECollisionChannel::ECC_WorldDynamic);
		// return if the operation was successful
		return traceSuccess;
	}
	else
		return false;
}

void AGameManager::LineTraceSpawnActor(FVector ScreenPos)	
{
		TraceResultTransform = LineTraceResult(ScreenPos);		//Get the location of touch in the real world to spawn Player
		//Spawn a new Actor at the location if not done yet
		if (!Player)		//If the player has not been spawned
		{
			if(!TraceResultTransform.Equals(FTransform::Identity))
			{
				SpawnPlayer();
				//Player->SetActorTransform(TraceResultTransform);	//Set transform to pinTransform
				Player->SetActorLocation(FVector(
						TraceResultTransform.GetLocation().X,
						TraceResultTransform.GetLocation().Y
					,TraceResultTransform.GetLocation().Z+60));	//Add offset for collision with plane, else the player will fall under the planes
			}
		}
		if (WorldHitTest(ScreenPos, HR))		//Get the plane that is being tapped on
		{
			AARPlaneActor* planeActorRef = Cast<AARPlaneActor>(HR.GetActor());
			if (planeActorRef)		//If it is valid
			{
				Player->LastClickedPlane = planeActorRef;		//Assign it as the last plane clicked, variable held in the player class.
			}
		}
}
void AGameManager::LineTraceMovement(FVector ScreenPos)		//Movement function for player
{
	TraceResultTransform = LineTraceResult(ScreenPos);		//Get location of touch
	MoveLocation =TraceResultTransform.GetLocation();		//Set player move location to touch location
	if (WorldHitTest(ScreenPos, HR))		//Line Trace by channel to the plane
	{
		AARPlaneActor* planeActorRef = Cast<AARPlaneActor>(HR.GetActor());		//Get the plane that is being tapped on
		if (planeActorRef)		//If it is valid
		{
			if (Player->LastClickedPlane)		//If the plane where the player is is valid
			{
				//If the distance is high and the player is tring to reach a different plane, fly to the new plane
				if (((planeActorRef->GetActorLocation() - Player->LastClickedPlane->GetActorLocation()).Length() > 200) && planeActorRef!=Player->LastClickedPlane)	
				{
					if (Player->IsTeleportDeviceCollected) 
					{
						Player->CanPlayerTeleport = true;		//Fly variable
						//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("Player can teleport"));
					}
				}
				Player->LastClickedPlane = planeActorRef;		//The plane tapped is the player's plane
			}
		}
	}
	if(!TraceResultTransform.Equals(FTransform::Identity))		//if the traceresult
	{
		//get distance of height between the actual location and the move location to detect whether player jumps or run towards location
		float DistanceToLocationZ = MoveLocation.Z - Player->GetActorLocation().Z;
		//If the distance in height to the destination is not considerable or the plane is not too far, the player walks
		if (abs(DistanceToLocationZ) <= 35.f && Player->CanPlayerTeleport == false)
		{
			Player->GetMovementComponent()->StopMovementImmediately();
			Player->DoesPlayerWalk = true;
			Player->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		}
		else if (abs(DistanceToLocationZ) > 35.f && Player->IsTeleportDeviceCollected == true|| Player->CanPlayerTeleport)	//If the distance in height to the destination or the destination is far, the player flies
		{
			Player->DoesPlayerTeleport = true;

		}
	}
}

void AGameManager::flipPlaneVisibility()	//Function to flip the plane visibility, called in the widget blueprints.
{
	auto Temp = GetWorld()->GetGameState();
	ACustomGameState * GameState = Cast<ACustomGameState>(Temp);
	GameState->SetAreARPlanesDisplayed(!GameState->GetAreARPlanesDisplayed());
}
