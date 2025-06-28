// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGhostTypes.generated.h" 

USTRUCT(BlueprintType)
struct FGhostFrame
{
	GENERATED_BODY()

	public:
	
	UPROPERTY(BlueprintReadWrite)
	float TimeStamp;

	UPROPERTY(BlueprintReadWrite)
	FVector Location;

	UPROPERTY(BlueprintReadWrite)
	FRotator Rotation;

	FGhostFrame()
		: TimeStamp(0.f), Location(FVector::ZeroVector), Rotation(FRotator::ZeroRotator)
	{}
};
