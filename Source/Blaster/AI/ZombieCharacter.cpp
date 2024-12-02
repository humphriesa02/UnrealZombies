// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieCharacter.h"
#include "Blaster/GameMode/ZombiesGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Blaster/Blaster.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AZombieCharacter::AZombieCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionObjectType(ECC_SkeletalMesh);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
}

// Called when the game starts or when spawned
void AZombieCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZombieCharacter::ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatorController, AActor* DamageCauser)
{
	ZombiesGameMode = ZombiesGameMode == nullptr ? GetWorld()->GetAuthGameMode<AZombiesGameMode>() : ZombiesGameMode;
	//if (bElimmed || ZombiesGameMode == nullptr) return;
	Damage = ZombiesGameMode->CalculateDamage(InstigatorController, Controller, Damage);


	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);

	/*UpdateHUDHealth();
	UpdateHUDShield();*/
	/*if (Damage != 0.f)
	{
		PlayHitReactMontage();
	}*/

	// Health is 0, player has died
	if (Health == 0.f)
	{
		if (ZombiesGameMode)
		{
			//// Get the attached AI Controller
			//BlasterPlayerController = BlasterPlayerController == nullptr ? Cast<ABlasterPlayerController>(Controller) : BlasterPlayerController;
			//// Get the attacker's Player Controller
			//ABlasterPlayerController* AttackerController = Cast<ABlasterPlayerController>(InstigatorController);
			//// Call the blaster game mode's player elim function
			//ZombiesGameMode->ZombieEliminated(this, BlasterPlayerController, AttackerController);
		}
	}
}

// Called every frame
void AZombieCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AZombieCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AZombieCharacter, Health);
}

void AZombieCharacter::OnRep_Health(float LastHealth)
{
	// Update visual queues?
}

