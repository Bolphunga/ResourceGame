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

	UPROPERTY(BlueprintReadWrite)
	int32 CurrentStageIndex = 1;

	UFUNCTION(BlueprintCallable)
	FName GetNextLevelName() const
	{
		switch (CurrentStageIndex)
		{
		case 1: return FName("Map_Stage2");
		case 2: return FName("Map_Stage3");
		default: return FName("Map_Stage1"); // Restart or win
		}
	}

	UFUNCTION(BlueprintCallable)
	void AdvanceStage()
	{
		CurrentStageIndex++;
	}

	
};
