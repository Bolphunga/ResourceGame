// Fill out your copyright notice in the Description page of Project Settings.


#include "SGhostGameInstance.h"

void USGhostGameInstance::AddGhostRun(const TArray<FGhostFrame>& RunData)
{
	AllGhostRuns.Add(RunData);

	if (AllGhostRuns.Num() > 5)
	{
		// Remove oldest run
		AllGhostRuns.RemoveAt(0); 
	}
}
