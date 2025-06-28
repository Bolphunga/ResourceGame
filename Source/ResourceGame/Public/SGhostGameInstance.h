// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FGhostTypes.h"
#include "SGhostGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RESOURCEGAME_API USGhostGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	TArray<TArray<FGhostFrame>> AllGhostRuns;

	UFUNCTION(BlueprintCallable, Category = "SGhostGameInstance")
	void AddGhostRun(const TArray<FGhostFrame>& RunData);
	
};
