// Fill out your copyright notice in the Description page of Project Settings.


#include "AIVGrabBall.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

void UAIVGrabBall::OnStateEnter(AAIStateMachineController* InStateMachine)
{
	Super::OnStateEnter(InStateMachine);
	if (StateMachine->BestBall->GetAttachParentActor())
	{
		StateMachine->BestBall = nullptr;
	}
}

void UAIVGrabBall::OnStateUpdate()
{
	if (!StateMachine->BestBall)
	{
		StateMachine->ChangeTheState(&StateMachine->GetStateSearchBall());
		return;
	}

	StateMachine->BestBall->SetActorEnableCollision(false);
	StateMachine->BestBall->Mesh->SetSimulatePhysics(false);
	ACharacter* character = Cast<ACharacter>(StateMachine->GetPawn());

	StateMachine->BestBall->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("HandSocket"));
	StateMachine->BestBall->SetActorRelativeLocation(FVector(0, 0, 0));

	StateMachine->ChangeTheState(&StateMachine->GetStateGoPlayer());
}
