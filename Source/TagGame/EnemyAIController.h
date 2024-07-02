// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "EnemyAIController.generated.h"

struct FEnemyState : public TSharedFromThis<FEnemyState>
{
private:
	TFunction<void(AAIController*)> Enter;
	TFunction<void(AAIController*)> Exit;
	TFunction<TSharedPtr<FEnemyState>(AAIController*, const float)> Tick;
public:
	FEnemyState()
	{
		Enter = nullptr;
		Exit = nullptr;
		Tick = nullptr;
	}
	FEnemyState(TFunction<void(AAIController*)> InEnter = nullptr,
		TFunction<void(AAIController*)> InExit = nullptr,
		TFunction<TSharedPtr<FEnemyState>(AAIController*, const float)> InOnTick = nullptr)
	{
		Enter = InEnter;
		Exit = InExit;
		Tick = InOnTick;
	}

	FEnemyState(const FEnemyState& Other) = delete;
	FEnemyState& operator=(const FEnemyState& Other) = delete;
	FEnemyState(FEnemyState&& Other) = delete;
	FEnemyState& operator=(FEnemyState& Other) = delete;


	void CallEnter(AAIController* AIController)
	{
		if (Enter)
		{
			Enter(AIController);
		}
	}
	void CallExit(AAIController* AIController)
	{
		if (Exit)
		{
			Exit(AIController);
		}
	}
	TSharedPtr<FEnemyState> CallTick(AAIController* AIController, const float deltaTime)
	{
		if (Tick)
		{
			TSharedPtr<FEnemyState> state = Tick(AIController, deltaTime);

			if (state != nullptr && state != AsShared())
			{
				CallExit(AIController);
				state->CallEnter(AIController);
				return state;
			}
		}
		return AsShared();
	}
};

/**
 *
 */
UCLASS()
class TAGGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:

	TSharedPtr<FEnemyState> CurrentState;
	TSharedPtr<FEnemyState> SearchForBall;
	TSharedPtr<FEnemyState> GoToBall;
	TSharedPtr<FEnemyState> GrabBall;
	TSharedPtr<FEnemyState> GoToPlayer;
	TSharedPtr<FEnemyState> ThrowBall;

	UPROPERTY(VisibleAnywhere)
	UBlackboardData* BBData;

	UPROPERTY(VisibleAnywhere)
	UBlackboardComponent* BBComponent;

	UPROPERTY(EditAnywhere)
	float Radius;

	UPROPERTY(EditAnywhere)
	float ForceToBall;

	ABallBase* BestBall;

	void BeginPlay() override;
	void Tick(float DeltaTime) override;

};
