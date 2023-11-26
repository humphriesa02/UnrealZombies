// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterGameMode.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Blaster/PlayerController/BlasterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Blaster/PlayerState/BlasterPlayerState.h"

void ABlasterGameMode::PlayerEliminated(ABlasterCharacter* ElimmedCharacter, ABlasterPlayerController* VictimController, ABlasterPlayerController* AttackerController)
{
	ABlasterPlayerState* AttackerPlayerState = AttackerController ? Cast<ABlasterPlayerState>(AttackerController->PlayerState) : nullptr;
	ABlasterPlayerState* VictimPlayerState = VictimController ? Cast<ABlasterPlayerState>(VictimController->PlayerState) : nullptr;

	// The attacker is not also the victim (player did not kill themselves)
	if (AttackerPlayerState && AttackerPlayerState != VictimPlayerState)
	{
		AttackerPlayerState->AddToScore(1.f);
	}
	// Add to the victims defeat variables
	if (VictimPlayerState)
	{
		VictimPlayerState->AddToDefeats(1);
	}

	if (ElimmedCharacter)
	{
		VictimPlayerState->ShowElimmedText(true);
		ElimmedCharacter->Elim();
	}
}

void ABlasterGameMode::RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController)
{
	// First Reset and Destroy the Player Character (the thing the player is controlling)
	if (ElimmedCharacter)
	{
		ElimmedCharacter->Reset();
		ElimmedCharacter->Destroy();
	}
	// Then utilize the Player Controller (Player Input essentially) in order to respawn a new Character
	if (ElimmedController)
	{
		// Get all player start actors
		TArray<AActor*> PlayerStarts;
		UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);
		// Generate a random index for a random Player Start
		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		RestartPlayerAtPlayerStart(ElimmedController, PlayerStarts[Selection]);

		// Remove Elimmed text after the player respawns
		ABlasterPlayerState* VictimPlayerState = ElimmedController ? Cast<ABlasterPlayerState>(ElimmedController->PlayerState) : nullptr;
		VictimPlayerState->ShowElimmedText(false);

	}
}
