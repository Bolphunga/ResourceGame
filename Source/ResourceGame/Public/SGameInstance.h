// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelInstance/LevelInstanceActor.h"
#include "FGhostTypes.h"
#include "SGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RESOURCEGAME_API ASGameInstance : public ALevelInstance
{
	GENERATED_BODY()

public:

	TArray<FGhostFrame> LastGhostMemory;
	
	TArray<TArray<FGhostFrame>> AllGhostRuns;
	
};
