// Fill out your copyright notice in the Description page of Project Settings.


#include "PlaceableCharacter.h"
#include "CustomGameState.h"
#include "ARPin.h"
#include "CustomGameMode.h"
#include "ARBlueprintLibrary.h"

// Sets default values
APlaceableCharacter::APlaceableCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SceneComponent->SetupAttachment(this->GetMesh());
	//SkeletalMeshComponent->SetupAttachment(SceneComponent);
	
	// Take material from editor
}


// Called when the game starts or when spawned
void APlaceableCharacter::BeginPlay()
{
	Super::BeginPlay();
	auto Temp = GetWorld()->GetAuthGameMode();
	SetActorScale3D(FVector(0.15,0.15,0.15));
	GM = Cast<ACustomGameMode>(Temp);
}

// Called to bind functionality to input
void APlaceableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind various player inputs to functions
	// There are a few types - BindTouch, BindAxis, and BindEvent.  
}


// Called every frame
void APlaceableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

