// Fill out your copyright notice in the Description page of Project Settings.


#include "HelloARManager.h"
#include "CustomGameMode.h"
#include "CustomGameState.h"
#include "TeleportPickup.h"
#include "ARPlaneActor.h"
#include "ARPin.h"
#include "ARSessionConfig.h"
#include "ARBlueprintLibrary.h"
#include "GameManager.h"
#include <string>

#include "MushroomPickup.h"
#include "TaskPickup.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AHelloARManager::AHelloARManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// This constructor helper is useful for a quick reference within UnrealEngine and if you're working alone. But if you're working in a team, this could be messy.
	// If the artist chooses to change the location of an art asset, this will throw errors and break the game.
	// Instead let unreal deal with this. Usually avoid this method of referencing.
	// For long term games, create a Data-Only blueprint (A blueprint without any script in it) and set references to the object using the blueprint editor.
	// This way, unreal will notify your artist if the asset is being used and what can be used to replace it.
	// 
	static ConstructorHelpers::FObjectFinder<UARSessionConfig> ConfigAsset(TEXT("ARSessionConfig'/Game/Blueprints/HelloARSessionConfig2.HelloARSessionConfig2'"));
	//Config = NewObject<UARSessionConfig>();
	if (!ConfigAsset.Object)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("DID NOT FIND SHIT"));
	}
	Config = ConfigAsset.Object;
	if (!Config)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("OH NOOOOO"));
	}
	//Config->bUseSceneDepthForOcclusion = true;
	//Config->SetSessionTrackingFeatureToEnable(EARSessionTrackingFeature::SceneDepth);

	//Populate the plane colours array
	PlaneColors.Add(FColor::Blue);
	PlaneColors.Add(FColor::Red);
	PlaneColors.Add(FColor::Green);
	PlaneColors.Add(FColor::Cyan);
	PlaneColors.Add(FColor::Magenta);
	PlaneColors.Add(FColor::Emerald);
	PlaneColors.Add(FColor::Orange);
	PlaneColors.Add(FColor::Purple);
	PlaneColors.Add(FColor::Turquoise);
	PlaneColors.Add(FColor::White);
	PlaneColors.Add(FColor::Yellow);
}

// Called when the game starts or when spawned, initialise all variables
void AHelloARManager::BeginPlay()
{
	Super::BeginPlay();
	UARBlueprintLibrary::StartARSession(Config);
	
	//Start the AR Session
	auto Temp = GetWorld()->GetAuthGameMode();
	GM = Cast<ACustomGameMode>(Temp);
	
	auto Temp1 = GetWorld()->GetGameState();
	GameState = Cast<ACustomGameState>(Temp1);
	
	LowestPlane = FVector::Zero();
	FirstPlaneSpawned = false;
	ScorePickupSpawnTimer = 0;
	TaskPickupSpawnTimer = 0;
	TaskPickupCounter = 0;
	MushroomPickupSpawnTimer = 0;
	ColorShiftingTimer = 0;
}

// Called every frame
void AHelloARManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (UARBlueprintLibrary::GetARSessionStatus().Status)
	{
	case EARSessionStatus::Running:
		UpdatePlaneActors();			//Update plane actors 
		PlayerFallCheck();				//Check if player falls
		if (GM->GameManager->Player)		//Start pickup timers only when player is spawned
		{
			ScorePickupSpawnTimer += DeltaTime;		//Increase pickup timer to spawn
			MushroomPickupSpawnTimer+=DeltaTime;
			if(TaskPickupCounter<15)		//Do not update task pickup timer when 15 pickups are spawned 
			{
				TaskPickupSpawnTimer +=DeltaTime;
			}
			if (GameState->GetAreARPlanesColorShifting())	//if the planes colours are shifting, set the duration of color change to 7 seconds
			{
				ColorShiftingTimer += DeltaTime;		//Update timer to stop planes from shifting colors
				if (ColorShiftingTimer >=7.f)
				{
					GameState->SetAreARPlanesColorShifting(false);		//Disable plane shifting 
					ColorShiftingTimer=0;		//Reset timer
				}
			}
		}
		break;
	case EARSessionStatus::FatalError:
		ResetARCoreSession();
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("SESSION RESET, FATAL ERROR"));
		UARBlueprintLibrary::StartARSession(Config);
		break;
	}
}

//Updates the geometry actors in the world
void AHelloARManager::UpdatePlaneActors()
{
	//Get all world geometries and store in an array
	auto Geometries = UARBlueprintLibrary::GetAllGeometriesByClass<UARPlaneGeometry>();
	//Loop through all geometries
	for (auto& It : Geometries)
	{
			//Check if current plane exists 
			if (PlaneActors.Contains(It))
			{
				AARPlaneActor* CurrentPActor = *PlaneActors.Find(It);
				//Check if plane is subsumed
				if (It->GetSubsumedBy()->IsValidLowLevel())
				{
					CurrentPActor->Destroy();
					PlaneActors.Remove(It);
					break;
				}
				else		//Always update planes even when device is not pointing at the planes, to avoid the player falling 
				{
					//Get tracking state switch
					switch (It->GetTrackingState())
					{
						//If tracking update
					case EARTrackingState::Tracking:
						CurrentPActor->UpdatePlanePolygonMesh();
						break;
					}
				}
			}
			else
			{
				//Get tracking state switch
				switch (It->GetTrackingState())
				{
				case EARTrackingState::Tracking:
					if (!It->GetSubsumedBy()->IsValidLowLevel())//If planes are not being subsumed
					{
						if(!FirstPlaneSpawned)			//If the first plane has not been spawned
						{
							PlaneActor = SpawnPlaneActor();		//Spawn first plane
							PlaneActor->ARCorePlaneObject = It;	//Assign PlaneActor to the ARCore plane object
							PlaneActors.Add(It, PlaneActor);	//Add Planeactor to the map
							PlaneActor->UpdatePlanePolygonMesh();	//Update mesh (function in ARPlaneActor)
							FirstPlanePosition = It->GetLocalToWorldTransform().GetLocation();
							PlaneIndex++;
							RandomXPosition = FMath::FRandRange(-100.0f, 100.0f);	//Random range for spawning task pickups.
							RandomYPosition = FMath::FRandRange(-100.0f, 100.0f);
							
							//Spawn the teleport pickup (spawned only once) at a random position on the first plane
							SpawnTeleportPickupActor(FVector(It->GetLocalToWorldTransform().GetLocation().X+RandomXPosition,	
								It->GetLocalToWorldTransform().GetLocation().Y+RandomYPosition,
								It->GetLocalToWorldTransform().GetLocation().Z+15));
						}
						else if(FirstPlaneSpawned &&GM->GameManager->Player)		//Once the player is spawned, spawn more planes
						{
							PlaneActor = SpawnPlaneActor();		//Spawn plane
							PlaneActor->ARCorePlaneObject = It;	//Assign PlaneActor to the ARCore plane object
							PlaneActors.Add(It, PlaneActor);	//Add Planeactor to the map
							PlaneActor->UpdatePlanePolygonMesh();	//Update mesh (function in ARPlaneActor)
							PlaneIndex++;
							
							if(LowestPlane == FVector::Zero())	//Get lowest plane height to avoid player falling, if unitialised / ==0, set it to the current plane
								{
									LowestPlane = It->GetLocalToWorldTransform().GetLocation();
								}
							else if(PlaneActor->GetActorLocation().Z<LowestPlane.Z)	//If a plane is lower than the actual lowest plane, save the Z
								{
									LowestPlane = It->GetLocalToWorldTransform().GetLocation();
									//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("New lowest plane detected at height: %f"), LowestPlane.Z));
								}
							PickupsSpawnManager(It->GetLocalToWorldTransform().GetLocation());		//Handle Pickups
						}
					}
					break;
				}

			}
	}
}

void AHelloARManager::PickupsSpawnManager(FVector location)
{
	if(GM->GameManager->Player&&ScorePickupSpawnTimer >=1.f)		//Spawn pickup every 1 second on new planes, to avoid instant collection
	{
		RandomXPosition = FMath::FRandRange(-100.0f, 100.0f);	//Random range for spawning task pickups.
		RandomYPosition = FMath::FRandRange(-100.0f, 100.0f);
		SpawnPickupActor(FVector(
		location.X+RandomXPosition,
		location.Y+RandomYPosition ,
		location.Z+10));	//Spawn Pickups over the planes
		ScorePickupSpawnTimer = 0;		//Reset timer to spawn pickups
	}
	
	if(TaskPickupSpawnTimer >=1 && TaskPickupCounter <15)		//Spawn task pickup every 1 second and when a new surface is detected, limit of 15
	{
		RandomXPosition = FMath::FRandRange(-100.0f, 100.0f);	//Random range for spawning task pickups.
		RandomYPosition = FMath::FRandRange(-100.0f, 100.0f);
		SpawnTaskPickupActor(FVector(
		location.X+RandomXPosition,
		location.Y+ RandomYPosition,
	 location.Z+10));	//Spawn Pickups over the planes
		TaskPickupSpawnTimer = 0;
	}
	
	if(MushroomPickupSpawnTimer >=4)	//Spawn mushroom pickup every 4 seconds and when a new surface is detected
	{
		RandomXPosition = FMath::FRandRange(-100.0f, 100.0f);	//Random range for spawning task pickups.
		RandomYPosition = FMath::FRandRange(-100.0f, 100.0f);
		SpawnMushroomPickupActor(FVector(
		location.X+RandomXPosition,
		location.Y+ RandomYPosition,
	 location.Z+10));	//Spawn Pickups over the planes
		MushroomPickupSpawnTimer = 0;
	}
}
//Simple spawn function for the tracked AR planes
AARPlaneActor* AHelloARManager::SpawnPlaneActor()
{
	const FActorSpawnParameters SpawnInfo;
	const FRotator MyRot(0, 0, 0);
	const FVector MyLoc(0, 0, 0);
	AARPlaneActor* CustomPlane = GetWorld()->SpawnActor<AARPlaneActor>(MyLoc, MyRot, SpawnInfo);
	FirstPlaneSpawned = true;
	return CustomPlane;
}
//Spawn score pickups
void AHelloARManager::SpawnPickupActor(FVector location)
{
	const FActorSpawnParameters SpawnInfo;
	const FRotator MyRot(0, 0, 0);
	const FVector MyLoc(0, 0, 30);
	GetWorld()->SpawnActor<AScorePickup>(PickupToSpawn, location, MyRot, SpawnInfo);
}

void AHelloARManager::SpawnTeleportPickupActor(FVector location)
{
	const FActorSpawnParameters SpawnInfo;
	const FRotator MyRot(0, 0, 0);
	const FVector MyLoc(0, 0, 30);
	GetWorld()->SpawnActor<ATeleportPickup>(TeleportPickupToSpawn, location, MyRot, SpawnInfo);
}
void AHelloARManager::SpawnMushroomPickupActor(FVector location)
{
	const FActorSpawnParameters SpawnInfo;
	const FRotator MyRot(0, 0, 0);
	const FVector MyLoc(0, 0, 30);
	GetWorld()->SpawnActor<AMushroomPickup>(MushroomPickupToSpawn, location, MyRot, SpawnInfo);
}
void AHelloARManager::SpawnTaskPickupActor(FVector location)
{
	const FActorSpawnParameters SpawnInfo;
	const FRotator MyRot(0, 0, 0);
	const FVector MyLoc(0, 0, 30);
	TaskPickupCounter++;
	GetWorld()->SpawnActor<ATaskPickup>(TaskPickupToSpawn, location, MyRot, SpawnInfo);
}

void AHelloARManager::ResetARCoreSession()
{
	//Get all actors in the level and destroy them as well as emptying the respective arrays
	TArray<AActor*> Planes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AARPlaneActor::StaticClass(), Planes);

	for ( auto& It : Planes)
		It->Destroy();
	
	Planes.Empty();
	PlaneActors.Empty();
	
}

void AHelloARManager::DestroyAllPlanes()
{
	auto Geometries = UARBlueprintLibrary::GetAllGeometriesByClass<UARPlaneGeometry>();
	auto planes = UARBlueprintLibrary::GetAllGeometriesByClass<AARPlaneActor>();

	while (planes.Num() > 0) {
		planes[0]->Destroy();
		planes.RemoveAt(0);
	}

	while (Geometries.Num() > 0) {
		Geometries[0]->ConditionalBeginDestroy();
		Geometries.RemoveAt(0);
	}
	ResetARCoreSession();
	//while (stillDestroying) {
	//	stillDestroying = false;
	//
	//	for (const TPair<UARPlaneGeometry*, AARPlaneActor*>& pair_ : PlaneActors)
	//	{
	//		pair_.Value->Destroy();
	//		UARPlaneGeometry* ref_ = pair_.Key;
	//		PlaneActors.Remove(ref_);
	//		ref_->ConditionalBeginDestroy();
	//		stillDestroying = true;
	//		break;
	//	}
	//}
}

void AHelloARManager::PlayerFallCheck()
{
	if(GM->GameManager->Player)
	{
		if(GM->GameManager->Player->GetActorLocation().Z<LowestPlane.Z-100.f)//If player fell, reset its location to be on the lowest plane + 15
		{
			GM->GameManager->Player->SetActorLocation(FVector(LowestPlane.X,LowestPlane.Y,LowestPlane.Z+15));
		}
	}
}