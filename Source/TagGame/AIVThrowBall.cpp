// Fill out your copyright notice in the Description page of Project Settings.


#include "AIVThrowBall.h"

void UAIVThrowBall::OnStateEnter(AAIStateMachineController* InStateMachine)
{
	Super::OnStateEnter(InStateMachine);
	if (StateMachine->BestBall)
	{
		StateMachine->BestBall->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		StateMachine->BestBall->SetActorEnableCollision(true);
		StateMachine->BestBall->Mesh->SetSimulatePhysics(true);
		FVector direction = (StateMachine->GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - StateMachine->GetPawn()->GetActorLocation());
		direction.Normalize();
		FVector Force = direction * StateMachine->ForceToBall;
		Force += FVector::UpVector * (StateMachine->ForceToBall / 2);
		StateMachine->BestBall->Mesh->AddForce(Force, NAME_None, true);
	}
	StateMachine->ChangeTheState(&StateMachine->GetStateSearchBall());
}

void UAIVThrowBall::OnStateUpdate()
{
	return;
}
