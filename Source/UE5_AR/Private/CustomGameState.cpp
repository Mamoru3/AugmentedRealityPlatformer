// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameState.h"


ACustomGameState::ACustomGameState() :
	Score(0)
{
	IsPlaceableSelected = false;
	IsPlaceableSpawned = false;
	AreARPlanesColorShifting = false;
	AreARPlanesDisplayed = true;
	TaskCompletion = 0;
}

int32 ACustomGameState::GetScore()
{
	return Score;
}

void ACustomGameState::SetScore(const int32 NewScore)
{
	Score = NewScore;
}

void ACustomGameState::SetPlaceableSelected(bool value)
{
	IsPlaceableSelected = value;
}

void ACustomGameState::SetAreARPlanesDisplayed(bool value)
{
	AreARPlanesDisplayed = value;
}

bool ACustomGameState::GetPlaceableSelected()
{
	return IsPlaceableSelected;
}

bool ACustomGameState::GetAreARPlanesDisplayed()
{
	return AreARPlanesDisplayed;
}

bool ACustomGameState::GetAreARPlanesColorShifting()
{
	return AreARPlanesColorShifting;
}

void ACustomGameState::SetAreARPlanesColorShifting(bool value)
{
	AreARPlanesColorShifting = value;
}

void ACustomGameState::SetTaskCompletion(int value)
{
	TaskCompletion = value;
}

int ACustomGameState::GetTaskCompletion()
{
	return TaskCompletion;
}
