#include "AIStateMachineController.h"
#include "AIVBaseState.h"
#include "AIVGoToBall.h"
#include "AIVGoPlayer.h"
#include "AIVThrowBall.h"
#include "AIVSearchBall.h"
#include "AIVGrabBall.h"
#include "AIVGoDance.h"
#include "TimerManager.h"
#include "Navigation/CrowdFollowingComponent.h"

AAIStateMachineController::AAIStateMachineController(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("Crowder")))
{

	UCrowdFollowingComponent* Crwod = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
	if (Crwod)
	{
		Crwod->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
	}
}

void AAIStateMachineController::BeginPlay()
{
	Super::BeginPlay();
}

void AAIStateMachineController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentState)
	{
		CurrentState->OnStateUpdate();
	}
}


void AAIStateMachineController::ChangeTheState(UAIVBaseState* InState)
{
	if (CurrentState != nullptr)
	{
		CurrentState->OnStateExit();
	}

	CurrentState = InState;
	CurrentState->OnStateEnter(this);
}

void AAIStateMachineController::ChangeStateCheat()
{
	ChangeTheState(GoSearchBall);
}


void AAIStateMachineController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GoBall = NewObject<UAIVGoToBall>();
	GoSearchBall = NewObject<UAIVSearchBall>();
	GoGrabBall = NewObject<UAIVGrabBall>();
	GoThrowBall = NewObject<UAIVThrowBall>();
	GoPlayer = NewObject<UAIVGoPlayer>();
	GoDancing = NewObject<UAIVGoDance>();
	bAllowTickBeforeBeginPlay = true;

	FTimerHandle Handler;

	GetWorldTimerManager().SetTimer(Handler, this, &AAIStateMachineController::ChangeStateCheat, 2, false, 0);
}
#pragma region StateGet
UAIVBaseState& AAIStateMachineController::GetStateThrowBall()
{
	return *GoThrowBall;
}

UAIVBaseState& AAIStateMachineController::GetStateSearchBall()
{
	return *GoSearchBall;
}
UAIVBaseState& AAIStateMachineController::GetStateGrabBall()
{
	return *GoGrabBall;
}
UAIVBaseState& AAIStateMachineController::GetStateGoPlayer()
{
	return *GoPlayer;
}
UAIVBaseState& AAIStateMachineController::GetStateGoBall()
{
	return *GoBall;
}
UAIVBaseState& AAIStateMachineController::GetStateGoDance()
{
	return *GoDancing;
}
#pragma endregion
