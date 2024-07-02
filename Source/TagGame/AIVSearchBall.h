// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIVBaseState.h"
#include "AIVSearchBall.generated.h"

/**
 * 
 */
UCLASS()
class TAGGAME_API UAIVSearchBall : public UAIVBaseState
{
	GENERATED_BODY()
public:
	virtual void OnStateEnter(AAIStateMachineController* InStateMachine) override;
	virtual void OnStateUpdate() override;
};
