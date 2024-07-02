// Fill out your copyright notice in the Description page of Project Settings.


#include "AIVGoToBall.h"

void UAIVGoToBall::OnStateEnter(AAIStateMachineController* InStateMachine)
{
	Super::OnStateEnter(InStateMachine);

	StateMachine->MoveToActor(StateMachine->BestBall, StateMachine->DistanceToPickUpBall);
}

void UAIVGoToBall::OnStateUpdate()
{
	EPathFollowingStatus::Type state = StateMachine->GetMoveStatus();
	if (state == EPathFollowingStatus::Moving)
	{
		return;
	}

	if (StateMachine->BestBall)
	{
		StateMachine->ChangeTheState(&StateMachine->GetStateGrabBall());
	}
}
