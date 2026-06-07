// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "StudentPerceptorDePeuterSooi.generated.h"

class UBehaviorTreeComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEPEUTERSOOIZOMBIERUNTIME_API UStudentPerceptorDePeuterSooi : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStudentPerceptorDePeuterSooi();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};