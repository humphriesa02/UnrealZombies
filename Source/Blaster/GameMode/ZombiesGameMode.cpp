// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombiesGameMode.h"
#include "Blaster/GameState/BlasterGameState.h"
#include "Blaster/PlayerState/BlasterPlayerState.h"
#include "Blaster/PlayerController/BlasterPlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "Blaster/Character/BlasterCharacter.h"
#include "GameFramework/PlayerStart.h"


float AZombiesGameMode::CalculateDamage(AController* Attacker, AController* Victim, float BaseDamage)
{
	// Only can do damage to other players if friendly fire is on
	return bFriendlyFire ? BaseDamage : 0.f;;
}

void AZombiesGameMode::ZombieEliminated(AZombieCharacter* ElimmedZombie, AZombieAIController* VictimController, ABlasterPlayerController* AttackerController)
{
}

void AZombiesGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
	// Start the round based match
	StartRound();
}

void AZombiesGameMode::StartRound()
{
	// Load up number of zombies and spawn them
	ZombiesRemaining = CurrentRound * ZombiesPerRound;
	SpawnZombies(ZombiesRemaining);
}

void AZombiesGameMode::SpawnZombies(int32 Count)
{
	// Locate all player starts (subject to change)
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStarts);

	if (PlayerStarts.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PlayerStart actors found!"));
		return;
	}

	// Spawn a zombie type at player starts
	for (int32 i = 0; i < Count; ++i)
	{
		int32 Selection = FMath::RandRange(0, PlayerStarts.Num() - 1);
		AActor* SpawnPoint = PlayerStarts[Selection];

		// Spawn the player character as a zombie for now
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ABlasterCharacter* SpawnedZombie = GetWorld()->SpawnActor<ABlasterCharacter>(
			ZombieClass,  // Use your player character class here
			SpawnPoint->GetActorLocation(),
			SpawnPoint->GetActorRotation(),
			SpawnParams
		);

		if (SpawnedZombie)
		{
			// Optionally, initialize zombie-specific logic here
			// Example: Set a tag or team to distinguish it as a zombie
		}
	}
}

void AZombiesGameMode::CheckRoundEnd()
{
	// After each zombie is killed, check if round is done.
	if (ZombiesRemaining <= 0) {
		CurrentRound++;
		// Todo, have a cooldown between rounds
		StartRound();
	}
}
