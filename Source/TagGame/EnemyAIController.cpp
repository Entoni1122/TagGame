// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "TagGameGameMode.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	GoToPlayer = MakeShared<FEnemyState>(
		[](AAIController* AIController) {
			AIController->MoveToActor(AIController->GetWorld()->GetFirstPlayerController()->GetPawn(), 100);
		},
		nullptr,
		[this](AAIController* AIController, const float DeltaTime) -> TSharedPtr<FEnemyState>
		{
			EPathFollowingStatus::Type state = AIController->GetMoveStatus();
			if (state == EPathFollowingStatus::Moving)
			{
				float distance = FVector::Distance(AIController->GetPawn()->GetActorLocation(),
					AIController->GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
				if (BestBall)
				{
					if (distance < Radius)
					{
						return ThrowBall;
					}
				}
				return nullptr;
			}
			return SearchForBall;

			/*if (BestBall)
			{
				BestBall->AttachToActor(AIController->GetWorld()->GetFirstPlayerController()->GetPawn(), FAttachmentTransformRules::KeepRelativeTransform);
				BestBall->SetActorRelativeLocation(FVector(0, 0, 0));

				BestBall = nullptr;
			}*/
		}
	);
	ThrowBall = MakeShared<FEnemyState>(
		[this](AAIController* AIController) {
			if (BestBall)
			{
				UE_LOG(LogTemp, Warning, TEXT("Throw Ball"));
				BestBall->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				BestBall->SetActorEnableCollision(true);
				BestBall->Mesh->SetSimulatePhysics(true);
				FVector direction = (AIController->GetPawn()->GetActorLocation() - AIController->GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
				direction.Normalize();
				FVector Force = direction * ForceToBall;
				Force += FVector::UpVector * (ForceToBall / 2);
				BestBall->Mesh->AddForce(Force, NAME_None, true);
			}
			return SearchForBall;
		},
		nullptr,
		nullptr
	);
	SearchForBall = MakeShared<FEnemyState>(
		[this](AAIController* AIController)
		{
			AGameModeBase* GameMode = AIController->GetWorld()->GetAuthGameMode();
			ATagGameGameMode* AiGameMode = Cast<ATagGameGameMode>(GameMode);
			const TArray<ABallBase*>& Balls = AiGameMode->GetBalls();

			ABallBase* currentBall = nullptr;

			for (int32 i = 0; i < Balls.Num(); i++)
			{
				if (!Balls[i]->GetAttachParentActor() && (!currentBall ||
					FVector::Distance(AIController->GetPawn()->GetActorLocation(), Balls[i]->GetActorLocation()) <
					FVector::Distance(AIController->GetPawn()->GetActorLocation(), currentBall->GetActorLocation())))
				{
					currentBall = Balls[i];
				}
			}
			BestBall = currentBall;
		},
		nullptr,
		[this](AAIController* AIController, const float DeltaTime)->TSharedPtr<FEnemyState> {
			if (BestBall)
			{
				return GoToBall;
			}
			return SearchForBall;
		}
	);
	GoToBall = MakeShared<FEnemyState>(
		[this](AAIController* AIController) {

			AIController->MoveToActor(BestBall, 100);
		},
		nullptr,
		[this](AAIController* AIController, const float DeltaTime) -> TSharedPtr<FEnemyState>
		{
			EPathFollowingStatus::Type state = AIController->GetMoveStatus();
			if (state == EPathFollowingStatus::Moving)
			{
				return nullptr;
			}
			return GrabBall;
		}
	);
	GrabBall = MakeShared<FEnemyState>(
		[this](AAIController* AIController)
		{
			if (BestBall->GetAttachParentActor())
			{
				BestBall = nullptr;
			}
		},
		nullptr,
		[this](AAIController* AIController, const float DeltaTime) -> TSharedPtr<FEnemyState>
		{
			if (!BestBall)
			{
				return SearchForBall;
			}

			BestBall->SetActorEnableCollision(false);
			BestBall->Mesh->SetSimulatePhysics(false);
			BestBall->AttachToActor(AIController->GetPawn(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_r"));
			BestBall->SetActorRelativeLocation(FVector(0, 0, 0));
			BestBall->SetActorLocation(AIController->GetPawn()->GetActorLocation() + (AIController->GetPawn()->GetActorForwardVector() * 150));

			return GoToPlayer;
		}
	);
	CurrentState = SearchForBall;
	CurrentState->CallEnter(this);

}

void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentState)
	{
		CurrentState = CurrentState->CallTick(this, DeltaTime);
	}


}
