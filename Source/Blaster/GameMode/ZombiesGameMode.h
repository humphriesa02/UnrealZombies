// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlasterGameMode.h"
#include "ZombiesGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BLASTER_API AZombiesGameMode : public ABlasterGameMode
{
	GENERATED_BODY()
	
public:
	virtual float CalculateDamage(AController* Attacker, AController* Victim, float BaseDamage) override;

	UPROPERTY(BlueprintReadOnly, Category = "Zombies")
	int32 CurrentRound = 1;

	UPROPERTY(BlueprintReadOnly, Category = "Zombies")
	int32 ZombiesRemaining = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Zombies")
	int32 ZombiesPerRound = 10;

	virtual void ZombieEliminated(class AZombieCharacter* ElimmedZombie, class AZombieAIController* VictimController, class ABlasterPlayerController* AttackerController);
protected:
	virtual void HandleMatchHasStarted() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABlasterCharacter> ZombieClass;

private:
	void StartRound();
	void SpawnZombies(int32 Count);
	void CheckRoundEnd();

	UPROPERTY(EditAnywhere)
	bool bFriendlyFire = false;
};
