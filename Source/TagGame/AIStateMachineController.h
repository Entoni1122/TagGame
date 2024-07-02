// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BallBase.h"
#include "Navigation/PathFollowingComponent.h"
#include "TagGameGameMode.h"
#include "AIStateMachineController.generated.h"

//class BaseState
//{
//public:
//	AAIStateMachineController* StateMachine;
//	AAIController* Controller;
//	void OnStateEnter(AAIStateMachineController* InStateMachine,AAIController* InController)
//	{
//		StateMachine = InStateMachine;
//		Controller = InController;
//		OnEnter();
//	}
//	virtual void OnEnter()
//	{
//
//	}
//
//
//	void OnStateUpdate()
//	{
//		OnUpdate();
//	}
//	virtual void OnUpdate()
//	{
//
//	}
//
//
//	void OnStateExit()
//	{
//		OnExit();
//	}
//	virtual void OnExit()
//	{
//
//	}
//};

//class GoToBallState : public BaseState
//{
//public:
//	void OnEnter() override
//	{
//		Controller->MoveToActor(StateMachine->BestBall, 100);
//	}
//	void OnUpdate() override
//	{
//		EPathFollowingStatus::Type state = StateMachine->Controller->GetMoveStatus();
//		if (state == EPathFollowingStatus::Moving)
//		{
//			return;
//		}
//		StateMachine->ChangeState(StateMachine->GrabBalState);
//	}
//};
//class GrabBallState : public BaseState
//{
//public:
//	void OnEnter() override
//	{
//		if (StateMachine->BestBall->GetAttachParentActor())
//		{
//			StateMachine->BestBall = nullptr;
//		}
//	}
//	void OnUpdate() override
//	{
//		if (!StateMachine->BestBall)
//		{
//			StateMachine->ChangeState(StateMachine->SearchBall);
//		}
//
//		StateMachine->BestBall->SetActorEnableCollision(false);
//		StateMachine->BestBall->Mesh->SetSimulatePhysics(false);
//		StateMachine->BestBall->AttachToActor(StateMachine->Controller->GetPawn(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_r"));
//		StateMachine->BestBall->SetActorRelativeLocation(FVector(0, 0, 0));
//		StateMachine->BestBall->SetActorLocation(StateMachine->Controller->GetPawn()->GetActorLocation() + (StateMachine->Controller->GetPawn()->GetActorForwardVector() * 150));
//
//		StateMachine->ChangeState(StateMachine->GoPlayer);
//	}
//};
//class GoToPlayer : public BaseState
//{
//public:
//	void OnEnter() override
//	{
//		StateMachine->Controller->MoveToActor(StateMachine->Controller->GetWorld()->GetFirstPlayerController()->GetPawn(), 100);
//	}
//	void OnUpdate() override
//	{
//		EPathFollowingStatus::Type state = StateMachine->Controller->GetMoveStatus();
//		if (state == EPathFollowingStatus::Moving)
//		{
//			float distance = FVector::Distance(StateMachine->Controller->GetPawn()->GetActorLocation(),
//				StateMachine->Controller->GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
//			if (StateMachine->BestBall)
//			{
//				if (distance < StateMachine->Radius)
//				{
//					StateMachine->ChangeState(StateMachine->ThrowBalState);
//
//				}
//			}
//		}
//		StateMachine->ChangeState(StateMachine->SearchBall);
//	}
//};
//class ThrowBallState : public BaseState
//{
//public:
//	void OnEnter() override
//	{
//		if (StateMachine->BestBall)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Throw Ball"));
//			StateMachine->BestBall->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
//			StateMachine->BestBall->SetActorEnableCollision(true);
//			StateMachine->BestBall->Mesh->SetSimulatePhysics(true);
//			FVector direction = (StateMachine->Controller->GetPawn()->GetActorLocation() - StateMachine->Controller->GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
//			direction.Normalize();
//			FVector Force = direction * StateMachine->ForceToBall;
//			Force += FVector::UpVector * (StateMachine->ForceToBall / 2);
//			StateMachine->BestBall->Mesh->AddForce(Force, NAME_None, true);
//		}
//		StateMachine->ChangeState(StateMachine->SearchBall);
//	}
//};
//class SearchForBallState : public BaseState
//{
//public:
//	void OnEnter() override
//	{
//		AGameModeBase* GameMode = StateMachine->Controller->GetWorld()->GetAuthGameMode();
//		ATagGameGameMode* AiGameMode = Cast<ATagGameGameMode>(GameMode);
//		const TArray<ABallBase*>& Balls = AiGameMode->GetBalls();
//
//		ABallBase* currentBall = nullptr;
//
//		for (int32 i = 0; i < Balls.Num(); i++)
//		{
//			if (!Balls[i]->GetAttachParentActor() && (!currentBall ||
//				FVector::Distance(StateMachine->Controller->GetPawn()->GetActorLocation(), Balls[i]->GetActorLocation()) <
//				FVector::Distance(StateMachine->Controller->GetPawn()->GetActorLocation(), currentBall->GetActorLocation())))
//			{
//				currentBall = Balls[i];
//			}
//		}
//		StateMachine->BestBall = currentBall;
//	}
//	void OnUpdate() override
//	{
//		if (StateMachine->BestBall)
//		{
//			StateMachine->ChangeState(StateMachine->GoBallState);
//		}
//		StateMachine->ChangeState(StateMachine->SearchBall);
//	}
//};
/**
 *
 */
#pragma region States
 //class UAIVBaseState;
 //class UAIVGoToBall;
 //class UAIVSearchBall;
 //class UAIVGrabBall;
 //class UAIVThrowBall;
 //class UAIVGoPlayer;
 //class UAIVGoDance;
#pragma endregion

UCLASS()
class TAGGAME_API AAIStateMachineController : public AAIController
{
	GENERATED_BODY()

	AAIStateMachineController(const FObjectInitializer& InObjectInitializer = FObjectInitializer::Get());
public:
	//----------------STATES----------------------
	class UAIVBaseState* CurrentState;
	class ABallBase* BestBall;
	class UAIVGoToBall* GoBall;
	class UAIVSearchBall* GoSearchBall;
	class UAIVGrabBall* GoGrabBall;
	class UAIVThrowBall* GoThrowBall;
	class UAIVGoPlayer* GoPlayer;
	class UAIVGoDance* GoDancing;


	//-------------------VARIABLES---------------------
	UPROPERTY(EditAnywhere)
	bool bShouldThrowBall;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bShouldThrowBall"))
	float Radius;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bShouldThrowBall"))
	float ForceToBall;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bShouldThrowBall"))
	float DistanceToPickUpBall;

	UAIVBaseState& GetStateThrowBall();
	UAIVBaseState& GetStateSearchBall();
	UAIVBaseState& GetStateGrabBall();
	UAIVBaseState& GetStateGoPlayer();
	UAIVBaseState& GetStateGoBall();
	UAIVBaseState& GetStateGoDance();

	//-----------------FUNCTIONS------------------------
	void BeginPlay() override;
	void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;

	void ChangeTheState(UAIVBaseState* InState);
	void ChangeStateCheat();
};
