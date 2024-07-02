// Fill out your copyright notice in the Description page of Project Settings.


#include "AIVGoPlayer.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"


void UAIVGoPlayer::OnStateEnter(AAIStateMachineController* InStateMachine)
{
	Super::OnStateEnter(InStateMachine);
	StateMachine->MoveToActor(StateMachine->GetWorld()->GetFirstPlayerController()->GetPawn(), 100);
}

void UAIVGoPlayer::OnStateUpdate()
{
	EPathFollowingStatus::Type state = StateMachine->GetMoveStatus();
	if (state == EPathFollowingStatus::Moving)
	{
		return;
	}
	if (StateMachine->BestBall)
	{
		if (StateMachine->bShouldThrowBall)
		{
			float distance = FVector::Distance(StateMachine->GetPawn()->GetActorLocation(),
				StateMachine->GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
			if (distance < StateMachine->Radius)
			{
				StateMachine->ChangeTheState(&StateMachine->GetStateThrowBall());
			}
		}

		ACharacter* Character = Cast<ACharacter>(StateMachine->GetWorld()->GetFirstPlayerController()->GetPawn());


		StateMachine->BestBall->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("HandSocket"));
		StateMachine->BestBall->SetActorRelativeLocation(FVector(0, 0, 0));
		StateMachine->BestBall = nullptr;
	}
	StateMachine->ChangeTheState(&StateMachine->GetStateSearchBall());
}
