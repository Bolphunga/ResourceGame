// Fill out your copyright notice in the Description page of Project Settings.

#include "AGameModeBase.h"
#include "SGameInstance.h"
#include "SPlayerCharacter.h"
#include "SGhostCharacter.h"
#include "SGhostGameInstance.h"
#include "Kismet/GameplayStatics.h"

void AAGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	SpawnGhostWithPath();
}


void AAGameModeBase::SpawnGhostWithPath()
{
	ASPlayerCharacter* PC = Cast<ASPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(!PC) return;
	
	USGhostGameInstance* GI = Cast<USGhostGameInstance>(GetGameInstance());
	if (!GI) return;
	
	for (const TArray<FGhostFrame> GhostRun : GI->AllGhostRuns)
	{
		float OffsetByIndex = (FMath::RandRange(-1.5f, 1.5f ) + 0.5f )* -100.f;
		
		//FVector SpawnLoc = PC->GetActorLocation() + FVector(0, OffsetByIndex, 0);
		//FRotator SpawnRotator = PC->GetActorRotation();
		FVector SpawnLoc = GhostRun[0].Location + FVector(0, OffsetByIndex, 0);;
		FRotator SpawnRotator = GhostRun[0].Rotation;
				
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ASGhostCharacter* Ghost = GetWorld()->SpawnActor<ASGhostCharacter>(GhostClass, SpawnLoc, SpawnRotator, Params);
		if (Ghost)
		{
			Ghost->SetGhostPath(GhostRun);
		}
	}
}

void AAGameModeBase::EndCurrentRun()
{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			APawn* Pawn = PC->GetPawn();
			if (ASPlayerCharacter* PlayerChar = Cast<ASPlayerCharacter>(Pawn))
			{
				//LastGhostMemory = PlayerChar->GetGhostMemory();
				if (USGhostGameInstance* GI = Cast<USGhostGameInstance>(GetGameInstance()))
                {
					//Add previous run to the array of runs (array of arrays)
					GI->AddGhostRun(PlayerChar->GetGhostMemory());
                }
			}
		}

	//Level restart
	UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
}


