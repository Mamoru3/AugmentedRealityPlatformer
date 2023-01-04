// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CustomGameMode.h"
#include "Components/CapsuleComponent.h"
#include "ARPlaneActor.h"
#include "PlaceableCharacter.generated.h"
class UARPin;

UCLASS()
class UE5_AR_API APlaceableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlaceableCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(Category = "myCategory", VisibleAnywhere, BlueprintReadWrite)
		USceneComponent* SceneComponent;
	
	//UMaterialInstance* PlaceableMaterial;

	//	UPROPERTY(Category = "PlaceableActorMaterial", EditAnywhere, BlueprintReadWrite)

	ACustomGameMode* GM;
	
	UPROPERTY(Category = "CharacterMovement", EditAnywhere, BlueprintReadWrite)
	bool DoesPlayerWalk = false;
	//UPROPERTY(Category = "CharacterMovement", EditAnywhere, BlueprintReadWrite)
	//bool DoesPlayerFly = false;
	//UPROPERTY(Category = "CharacterMovement", EditAnywhere, BlueprintReadWrite)
	bool DoesPlayerTeleport = false;
	UPROPERTY(Category = "CharacterMovement", EditAnywhere, BlueprintReadWrite)
	bool CanPlayerTeleport = false;
	
	UPROPERTY(Category = "CharacterMovement", EditAnywhere, BlueprintReadWrite)
	bool IsTeleportDeviceCollected = false;

	AARPlaneActor* LastClickedPlane;

	UPROPERTY(Category = "CharacterMovement", EditAnywhere, BlueprintReadWrite)
	bool AnimationPlay = false;
};
