// Fill out your copyright notice in the Description page of Project Settings.


#include "SGhostCharacter.h"

#include "FGhostTypes.h"
#include "GameFramework/CharacterMovementComponent.h"


void ASGhostCharacter::SetGhostPath(const TArray<FGhostFrame>& InPath)
{
	GhostPath = InPath;
	GhostPlaybackTime = 0.0f;
	CurrentFrameIndex = 0;

	if (!GhostPath.IsEmpty())
	{
		// Offset the first location by a random value to prevent collision with the original
		//float OffsetByIndex = (FMath::RandRange(-1.5f, 1.5f ) + 0.5f )* -100.f;
		
		SetActorLocationAndRotation(GhostPath[0].Location, GhostPath[0].Rotation);
	}
}

/*void ASGhostCharacter::SetGhostFade(float AgeNormalized)
{
	USkeletalMeshComponent* GhostMesh = GetMesh();
	if (!GhostMesh) return;

	// Oldest ghost = 0.25 opacity
	float Opacity = FMath::Lerp(1.0f, 0.25f, AgeNormalized); 

	for (int32 i = 0; i < GhostMesh->GetNumMaterials(); i++)
	{
		UMaterialInstanceDynamic* DynMat = GhostMesh->CreateAndSetMaterialInstanceDynamic(i);
		if (DynMat)
		{
			DynMat->SetScalarParameterValue(TEXT("Opacity"), Opacity);
		}
	}
}*/

void ASGhostCharacter::UpdateGhostPosition(float DeltaTime)
{
	// Don't update/stop updating positing if there aren't enough frames, or it's an early frame, then pause animation
	if (GhostPath.Num() < 2 || (CurrentFrameIndex >= GhostPath.Num()-1))
	{
		if (GetMesh())
		{
			GetMesh()->bPauseAnims = true;
			SetActorTickEnabled(false);
		}
		return;
	}

	GhostPlaybackTime += DeltaTime;
	const FGhostFrame CurrentFrame = GhostPath[CurrentFrameIndex];
	const FGhostFrame NextFrame = GhostPath[CurrentFrameIndex + 1];
	
	float FrameDelta = NextFrame.TimeStamp - CurrentFrame.TimeStamp;
	if (FrameDelta <= 0.0f) FrameDelta = 0.01f;
	
	float Alpha = (GhostPlaybackTime - CurrentFrame.TimeStamp) / FrameDelta;

	FVector NewLocation = FMath::Lerp(CurrentFrame.Location, NextFrame.Location, Alpha);
	FRotator NewRotation = FMath::Lerp(CurrentFrame.Rotation, NextFrame.Rotation, Alpha);
	
	FVector DeltaMove = NewLocation - GetActorLocation();
	CalculatedVelocity = DeltaMove / DeltaTime;

	// Set the character's to use for animation
	GetCharacterMovement()->Velocity = CalculatedVelocity;
	
	SetActorLocation(NewLocation);
	SetActorRotation(NewRotation);
	
	if (GhostPlaybackTime >= NextFrame.TimeStamp)
	{
		CurrentFrameIndex++;
	}

	// We exposed these values to BP because we need them in the AnimBP to freeze the movement
	GhostSpeed = (GetActorLocation() - LastLocation).Size() / DeltaTime;
	LastLocation = GetActorLocation();
}

// Called when the game starts or when spawned
void ASGhostCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->bOnlyAllowAutonomousTickPose = false;
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetUpdateAnimationInEditor(true);
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

