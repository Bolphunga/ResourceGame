// Fill out your copyright notice in the Description page of Project Settings.

#include "AGameModeBase.h"
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

	// Get the total number of runs from our instance
	const int32 TotalRuns = GI->AllGhostRuns.Num();
	int32 Index = 0;

	// Loop through recorded runs (likely 5) and spawn a ghost at the first frame of every run
	for (const auto& GhostRun : GI->AllGhostRuns)
	{
		// Offset the spawn location by a random value to prevent collision with the original
		float OffsetByIndex = (FMath::RandRange(-1.5f, 1.5f ) + 0.5f )* -100.f;
		
		FVector SpawnLoc = GhostRun[0].Location; //+ FVector(0, OffsetByIndex, 0);
		FRotator SpawnRotator = GhostRun[0].Rotation;
				
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ASGhostCharacter* Ghost = GetWorld()->SpawnActor<ASGhostCharacter>(GhostClass, SpawnLoc, SpawnRotator, Params);
		if (Ghost)
		{
			// Set the spawned ghost on the corresponding path
			Ghost->SetGhostPath(GhostRun);

			// 🔥 NEW: Set ghost age
			float FadeAmount = static_cast<float>(Index) / static_cast<float>(TotalRuns - 1); // 0 = newest, 1 = oldest
			//Ghost->SetGhostFade(FadeAmount);
			Index++;
			// Add the spawned ghost to a saved array of ghosts			
			Ghost->SetGhostPath(GhostRun);

		}
	}

	// After the loop that spawns ghosts, remove the earliest ghost if the number is more than 5
	while (SpawnedGhosts.Num() > 5)
	{
		if (SpawnedGhosts[0])
		{
			SpawnedGhosts[0]->Destroy();
		}
		SpawnedGhosts.RemoveAt(0);
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

					// Advance stage
					GI->AdvanceStage();

					// Load next level
					FName NextLevel = GI->GetNextLevelName();
					UGameplayStatics::OpenLevel(GetWorld(), NextLevel);
					UE_LOG(LogTemp, Warning, TEXT("Current Stage Index: %d"), GI->CurrentStageIndex)
					UE_LOG(LogTemp, Warning, TEXT("Current Stage Name: %s"), *NextLevel.ToString());
                }
			}
		}
	//Level restart
	//UGameplayStatics::OpenLevel(GetWorld(), FName(*GetWorld()->GetName()), false);
}


