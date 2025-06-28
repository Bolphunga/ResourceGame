// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerCharacter.h"

#include "FGhostTypes.h"

// Sets default values
ASPlayerCharacter::ASPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GhostMemory.Empty();
	TimeSinceLastRecord = 0.f;
	TotalElapsedTime = 0.f;

}

// Called every frame
void ASPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TotalElapsedTime += DeltaTime;
	TimeSinceLastRecord += DeltaTime;
		if (TimeSinceLastRecord >= RecordingInterval)
    	{
    		RecordGhostFrame(TotalElapsedTime);
			TimeSinceLastRecord = 0.f;
    	}
}

// Called to bind functionality to input
void ASPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASPlayerCharacter::RecordGhostFrame(float TimeStamp)
{
	FGhostFrame NewGhostFrame;
	NewGhostFrame.Location = GetActorLocation();
	NewGhostFrame.Rotation = GetActorRotation();
	NewGhostFrame.TimeStamp = TimeStamp;
	GhostMemory.Add(NewGhostFrame);
}

void ASPlayerCharacter::ResetGhostMemory()
{
	GhostMemory.Empty();
	TotalElapsedTime = 0.f;
	TimeSinceLastRecord = 0.f;
}

