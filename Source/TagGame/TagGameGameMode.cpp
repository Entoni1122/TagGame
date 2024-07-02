// Copyright Epic Games, Inc. All Rights Reserved.

#include "TagGameGameMode.h"
#include "TagGameCharacter.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"

ATagGameGameMode::ATagGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATagGameGameMode::BeginPlay()
{
	Super::BeginPlay();

	ResetMatch();

}

void ATagGameGameMode::ResetMatch()
{
	UWorld* World = GetWorld();
	//Targte Reset
	TargetPoints.Empty();

	for (TActorIterator<ATargetPoint> It(World); It; ++It)
	{
		TargetPoints.Add(*It);
	}

	//Ball Reset
	GameBalls.Empty();

	int lenght = TargetPoints.Num() - 1;

	for (TActorIterator<ABallBase> It(World); It; ++It)
	{
		if (lenght <= 0)
		{
			return;
		}
		int i = UKismetMathLibrary::RandomIntegerInRange(0, lenght);
		It->SetActorLocation(TargetPoints[i]->GetActorLocation());
		TargetPoints.RemoveAt(i);
		GameBalls.Add(*It);
		lenght--;
	}
}

const TArray<class ABallBase*>& ATagGameGameMode::GetBalls() const
{
	return GameBalls;
}
