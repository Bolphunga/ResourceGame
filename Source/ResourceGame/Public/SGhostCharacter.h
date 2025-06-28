// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FGhostTypes.h"
#include "SGhostCharacter.generated.h"

UCLASS()
class RESOURCEGAME_API ASGhostCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASGhostCharacter();

	UFUNCTION(BlueprintCallable)
	void SetGhostPath(const TArray<FGhostFrame>& InPath);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void UpdateGhostPosition(float DeltaTime);
	
	TArray<FGhostFrame> GhostPath;
	
	int32 CurrentFrameIndex;
	
	float GhostPlaybackTime;
	
	FVector LastLocation;
	
	float GhostSpeed;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
