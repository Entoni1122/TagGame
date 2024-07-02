#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AIStateMachineController.h"
#include "AIVBaseState.generated.h"
/**
 * 
 */

UCLASS()
class TAGGAME_API UAIVBaseState : public UObject
{
	GENERATED_BODY()

public:
	AAIStateMachineController* StateMachine;

	virtual void OnStateEnter(AAIStateMachineController* InStateMachine);
	virtual void OnStateUpdate();
	virtual void OnStateExit();
};
