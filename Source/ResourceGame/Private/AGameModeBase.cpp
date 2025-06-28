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

void AAGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	/*FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAGameModeBase::SpawnGhostWithPath, 1.f, false);*/
}

void AAGameModeBase::SpawnGhostWithPath()
{
	if(ASPlayerCharacter* PC = Cast<ASPlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		if (PC->GetGhostMemory().Num() > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("GhostMemory is empty."));
			return;
		}
		if (GhostClass == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Ghost Class."));
			return;
		}

		
		if (USGhostGameInstance* GI = Cast<USGhostGameInstance>(GetGameInstance()))
		{
			if (!GI->LastGhostMemory.IsEmpty())
			{
				FVector SpawnLoc = PC->GetActorLocation() + FVector(200, 0, 0);
				FRotator SpawnRotator = PC->GetActorRotation();
				//FVector SpawnLoc = PC->GetGhostMemory()[0].Location;
				//FRotator SpawnRotator = PC->GetGhostMemory()[0].Rotation;
				
				FActorSpawnParameters Params;
				Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				
				if (ASGhostCharacter* Ghost = GetWorld()->SpawnActor<ASGhostCharacter>(GhostClass, SpawnLoc, SpawnRotator, Params))
				{
					Ghost->SetGhostPath(GI->LastGhostMemory);
				}
				
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("LastGhostMemory array is Empty"));
			}
		}
	}
}
	


void AAGameModeBase::EndCurrentRun()
{
	if (USGhostGameInstance* GI = Cast<USGhostGameInstance>(GetGameInstance()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Instance is fine."));
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (PC)
		{
			UE_LOG(LogTemp, Warning, TEXT("Controller is fine."));
			APawn* Pawn = PC->GetPawn();
			if (ASPlayerCharacter* PlayerChar = Cast<ASPlayerCharacter>(Pawn))
			{
				UE_LOG(LogTemp, Warning, TEXT("PlayerChar is fine."));
				if (PlayerChar->GetGhostMemory().Num() > 0) // make sure this isn't null
				{
					UE_LOG(LogTemp, Warning, TEXT("GhostMemory is fine."));
					GI->LastGhostMemory = PlayerChar->GetGhostMemory();
				}
				if (UWorld* World = GetWorld())
				{
					UGameplayStatics::OpenLevel(World, FName(*GetWorld()->GetName()), false);
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("World is null."));
				}
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("PlayerChar is null or not castable."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerController is null."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance is null or not of expected class."));
	}
}


