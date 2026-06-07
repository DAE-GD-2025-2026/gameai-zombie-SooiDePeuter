#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISense_Damage.h"
#include "../movement/SteeringBehaviors.h"


struct GlobalVars
{
	static ISteeringBehavior* steeringBehavior;
	static FAIStimulus* activeStimulus;
};
