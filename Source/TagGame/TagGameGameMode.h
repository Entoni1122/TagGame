#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/TargetPoint.h"
#include "BallBase.h"
#include "TagGameGameMode.generated.h"

UCLASS(minimalapi)
class ATagGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<class ATargetPoint*> TargetPoints;
	
	UPROPERTY(EditAnywhere)
	TArray<class ABallBase*> GameBalls;

public:
	ATagGameGameMode();
	void BeginPlay() override;

	void ResetMatch();
	
	const TArray<class ABallBase*>& GetBalls() const;
};



