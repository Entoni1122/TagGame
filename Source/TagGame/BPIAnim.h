// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BPIAnim.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBPIAnim : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TAGGAME_API IBPIAnim
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "AIVAnimation")
	void CanDance(bool InCanDance);

	virtual void CanDance_Implementation(bool InCanDance);
};
