// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "ZombieCharacter.generated.h"

UCLASS()
class BLASTER_API AZombieCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombieCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatorController, AActor* DamageCauser);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Behavior Tree for Zombie AI */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

private:
	UPROPERTY()
	class AZombiesGameMode* ZombiesGameMode;

	UPROPERTY()
	class AZombieAIController* ZombieController;
	/**
	*	Player health
	*/
	// Maximum
	UPROPERTY(EditAnywhere, Category = "Zombie Stats")
	float MaxHealth = 100.f;

	// Current
	UPROPERTY(ReplicatedUsing = OnRep_Health, VisibleAnywhere, Category = "Zombie Stats")
	float Health = 100.f;

	// Called to replicate the health variable
	UFUNCTION()
	void OnRep_Health(float LastHealth);

};
