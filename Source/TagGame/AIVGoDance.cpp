// Fill out your copyright notice in the Description page of Project Settings.


#include "AIVGoDance.h"
#include "BPIAnim.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"

void UAIVGoDance::OnStateEnter(AAIStateMachineController* InStateMachine)
{
	Super::OnStateEnter(InStateMachine);
	USkeletalMeshComponent* Skeletal = StateMachine->GetPawn()->FindComponentByClass<USkeletalMeshComponent>();

	if (Skeletal)
	{
		IBPIAnim* AnimI = Cast<IBPIAnim>(Skeletal->GetAnimInstance());
		AnimI->Execute_CanDance(Skeletal->GetAnimInstance(), true);

		Skeletal->SetSimulatePhysics(true);
		Skeletal->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	StateMachine = nullptr;
}

void UAIVGoDance::OnStateUpdate()
{


}
