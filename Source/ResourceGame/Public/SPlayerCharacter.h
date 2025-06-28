// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPlayerCharacter.generated.h"

UCLASS()
class RESOURCEGAME_API ASPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASPlayerCharacter();

	UPROPERTY(EditAnywhere, Category = "Ghost")
	TArray<FGhostFrame> GhostMemory;

	UPROPERTY(EditAnywhere, Category = "Ghost")
	float RecordingInterval;

	UPROPERTY(EditAnywhere, Category = "Ghost")
	float TotalElapsedTime;

	UPROPERTY(EditAnywhere, Category = "Ghost")
	float TimeSinceLastRecord;

	

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void RecordGhostFrame(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	const TArray<FGhostFrame>& GetGhostMemory() const {return GhostMemory;};

	UFUNCTION(BlueprintCallable)
	void ResetGhostMemory();

};
