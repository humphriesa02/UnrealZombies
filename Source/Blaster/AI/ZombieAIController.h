// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "ZombieAIController.generated.h"
/**
 * 
 */
UCLASS()
class BLASTER_API AZombieAIController : public AAIController
{
	GENERATED_BODY()
public:
	AZombieAIController();
protected:
	virtual void BeginPlay() override;

	void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

private:
    /** Blackboard component */
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UBlackboardComponent* BlackboardComponent;

    /** Behavior Tree component */
    UPROPERTY(VisibleAnywhere, Category = "AI")
    UBehaviorTreeComponent* BehaviorTreeComponent;
};
