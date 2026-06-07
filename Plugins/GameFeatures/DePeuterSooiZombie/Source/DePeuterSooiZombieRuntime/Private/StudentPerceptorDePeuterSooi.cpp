// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptorDePeuterSooi.h"
#include "GlobalVars.h"


UStudentPerceptorDePeuterSooi::UStudentPerceptorDePeuterSooi()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStudentPerceptorDePeuterSooi::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptorDePeuterSooi::OnPerceptionUpdated);
	}
}

void UStudentPerceptorDePeuterSooi::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (GlobalVars::activeStimulus == nullptr)
	{
		GlobalVars::activeStimulus = &Stimulus;
	}
	
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something!")));
}
