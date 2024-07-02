// Fill out your copyright notice in the Description page of Project Settings.

#include "AIVSearchBall.h"

void UAIVSearchBall::OnStateEnter(AAIStateMachineController* InStateMachine)
{
	Super::OnStateEnter(InStateMachine);

	AGameModeBase* GameMode = StateMachine->GetWorld()->GetAuthGameMode();
	ATagGameGameMode* AiGameMode = Cast<ATagGameGameMode>(GameMode);
	const TArray<ABallBase*>& Balls = AiGameMode->GetBalls();

	ABallBase* currentBall = nullptr;

	for (int32 i = 0; i < Balls.Num(); i++)
	{
		if (!Balls[i]->GetAttachParentActor() && (!currentBall ||
			FVector::Distance(StateMachine->GetPawn()->GetActorLocation(), Balls[i]->GetActorLocation()) <
			FVector::Distance(StateMachine->GetPawn()->GetActorLocation(), currentBall->GetActorLocation())))
		{
			currentBall = Balls[i];
		}
	}
	StateMachine->BestBall = currentBall;
	if (!StateMachine->BestBall)
	{
		StateMachine->ChangeTheState(&StateMachine->GetStateGoDance());
		return;
	}
}

void UAIVSearchBall::OnStateUpdate()
{
	if (StateMachine->BestBall)
	{
		StateMachine->ChangeTheState(&StateMachine->GetStateGoBall());
	}
	else
	{
		StateMachine->ChangeTheState(&StateMachine->GetStateSearchBall());
	}
}
