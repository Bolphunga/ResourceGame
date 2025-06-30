// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGhostCharacter.h"
#include "AGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class RESOURCEGAME_API AAGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnGhostWithPath();

	UFUNCTION(BlueprintCallable)
	void EndCurrentRun();

	UPROPERTY(EditAnywhere, Category = "Ghost")
	TSubclassOf<ASGhostCharacter> GhostClass;

	UPROPERTY(VisibleAnywhere)
	TArray<FGhostFrame> LastGhostMemory;

	UPROPERTY(VisibleAnywhere)
	TArray<ASGhostCharacter*> SpawnedGhosts;
};
