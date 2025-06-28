// Fill out your copyright notice in the Description page of Project Settings.


#include "SGhostCharacter.h"

#include "FGhostTypes.h"
#include "VectorTypes.h"

// Sets default values
ASGhostCharacter::ASGhostCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASGhostCharacter::SetGhostPath(const TArray<FGhostFrame>& InPath)
{
	GhostPath = InPath;
	GhostPlaybackTime = 0.0f;
	CurrentFrameIndex = 0;

	if (!GhostPath.IsEmpty())
	{
		SetActorLocationAndRotation(GhostPath[0].Location, GhostPath[0].Rotation);
	}
}

void ASGhostCharacter::UpdateGhostPosition(float DeltaTime)
{
	if (GhostPath.Num() < 2 || (CurrentFrameIndex >= GhostPath.Num()-1))
		return;

	GhostPlaybackTime += DeltaTime;
	const FGhostFrame CurrentFrame = GhostPath[CurrentFrameIndex];
	const FGhostFrame NextFrame = GhostPath[CurrentFrameIndex + 1];
	
	float FrameDelta = NextFrame.TimeStamp - CurrentFrame.TimeStamp;
	if (FrameDelta <= 0.0f) FrameDelta = 0.01f;
	
	float Alpha = (GhostPlaybackTime - CurrentFrame.TimeStamp) / FrameDelta;

	FVector NewLocation = FMath::Lerp(CurrentFrame.Location, NextFrame.Location, Alpha);
	FRotator NewRotation = FMath::Lerp(CurrentFrame.Rotation, NextFrame.Rotation, Alpha);
		
	SetActorLocation(NewLocation);
	SetActorRotation(NewRotation);
	
	if (GhostPlaybackTime >= NextFrame.TimeStamp)
	{
		CurrentFrameIndex++;
	}
}

// Called when the game starts or when spawned
void ASGhostCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASGhostCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateGhostPosition(DeltaTime);
}

// Called to bind functionality to input
void ASGhostCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

