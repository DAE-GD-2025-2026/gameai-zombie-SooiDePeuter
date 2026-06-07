#include "BTTasksDePeuterSooi.h"

#include "AIController.h"
#include "../public/GlobalVars.h"

EBTNodeResult::Type UBTTaskSetWanderDePeuterSooi::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GlobalVars::steeringBehavior = new Wander();
	
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UBTTaskWanderDePeuterSooi::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	SteeringOutput output = GlobalVars::steeringBehavior->CalculateSteering((FVector2D)OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation());
	
	output.LinearVelocity.Normalize();
	
	OwnerComp.GetAIOwner()->GetPawn()->AddMovementInput(FVector{output.LinearVelocity.X, output.LinearVelocity.Y, 0}, 1.0f);
	OwnerComp.GetAIOwner()->GetPawn()->FaceRotation({0, output.AngularVelocity, 0});
	
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UBTTaskSetSeekDePeuterSooi::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GlobalVars::steeringBehavior = new Seek();
	
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UBTTaskSeekDePeuterSooi::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (GlobalVars::activeStimulus == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	SteeringOutput output = GlobalVars::steeringBehavior->CalculateSteering((FVector2D)OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation());
	
	output.LinearVelocity.Normalize();
	
	OwnerComp.GetAIOwner()->GetPawn()->AddMovementInput(FVector{output.LinearVelocity.X, output.LinearVelocity.Y, 0}, 1.0f);
	
	return EBTNodeResult::Succeeded;
}