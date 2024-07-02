// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIVBaseState.h"
#include "AIVGoDance.generated.h"

/**
 * 
 */
UCLASS()
class TAGGAME_API UAIVGoDance : public UAIVBaseState
{
	GENERATED_BODY()
	

public:
	void OnStateEnter(AAIStateMachineController* InStateMachine) override;
	void OnStateUpdate() override;
};
