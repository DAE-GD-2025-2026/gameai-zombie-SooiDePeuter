#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BTTasksDePeuterSooi.generated.h"

UCLASS()
class DEPEUTERSOOIZOMBIERUNTIME_API UBTTaskSetWanderDePeuterSooi : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskSetWanderDePeuterSooi() = default;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

UCLASS()
class DEPEUTERSOOIZOMBIERUNTIME_API UBTTaskWanderDePeuterSooi : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskWanderDePeuterSooi() = default;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

UCLASS()
class DEPEUTERSOOIZOMBIERUNTIME_API UBTTaskSetSeekDePeuterSooi : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskSetSeekDePeuterSooi() = default;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};

UCLASS()
class DEPEUTERSOOIZOMBIERUNTIME_API UBTTaskSeekDePeuterSooi : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskSeekDePeuterSooi() = default;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};