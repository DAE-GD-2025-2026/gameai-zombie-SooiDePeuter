#include "SteeringBehaviors.h"

//predict target of another actor
FVector2D ISteeringBehavior::PredictTarget(const AActor* agent, const FTargetData& target)
{
	//calculate time to reach target
	const float time{ (float)(FVector2D(agent->GetActorTransform().GetLocation()) - Target.Position).Length() / CustomVars::maxLinearSpeed };

	//calculate predicted position
	const FVector2D predictPosition{ Target.Position + time * Target.LinearVelocity };

	return predictPosition;
}

//predict target of self
FVector2D ISteeringBehavior::PredictTarget(const AActor* agent, float time)
{
	//calculate predicted position
	const FVector2D predictPosition{ FVector2D(agent->GetActorTransform().GetLocation()).X + time * agent->GetVelocity().X,
									 FVector2D(agent->GetActorTransform().GetLocation()).Y + time * agent->GetVelocity().Y};

	return predictPosition;
}

//SEEK
SteeringOutput Seek::CalculateSteering(float DeltaTime, AActor* agent)
{
	//make an output object
	SteeringOutput result;
	
	//set Velocity
	result.LinearVelocity = Target.Position - (FVector2D)agent->GetActorTransform().GetLocation();
	
	return result;
}

//FLEE
SteeringOutput Flee::CalculateSteering(float DeltaTime, AActor* agent)
{
	//make an output object
	SteeringOutput result;

	//set Velocity
	result.LinearVelocity = (FVector2D)agent->GetActorTransform().GetLocation() - Target.Position;

	return result;
}

//ARRIVE
SteeringOutput Arrive::CalculateSteering(float DeltaTime, AActor* agent)
{
	//hardcode arrive radiuses
	const float slowRadius{2000.f};

	//make an output object
	SteeringOutput result;

	//set Velocity
	result.LinearVelocity = Target.Position - (FVector2D)agent->GetActorTransform().GetLocation();

	//set max speed
	if ((Target.Position - (FVector2D)agent->GetActorTransform().GetLocation()).Length() < m_TargetRadius)
	{
		CustomVars::SetMaxLinearSpeed(0);
	}
	if ((Target.Position - (FVector2D)agent->GetActorTransform().GetLocation()).Length() < slowRadius)
	{
		CustomVars::SetMaxLinearSpeed((Target.Position - (FVector2D)agent->GetActorTransform().GetLocation()).Length() / slowRadius * CustomVars::maxLinearSpeed);
	}
	else
	{
		CustomVars::SetMaxLinearSpeed(CustomVars::maxLinearSpeed);
	}
	
	return result;
}

void Arrive::SetTargetRadius(float radius)
{
	m_TargetRadius = radius;
}

//FACE
SteeringOutput Face::CalculateSteering(float DeltaTime, AActor* agent)
{
	SteeringOutput result{};

	const FVector2D targetDirection { Target.Position - (FVector2D)agent->GetActorTransform().GetLocation() };
	const float actorAngle{ float(FMath::DegreesToRadians(agent->GetActorRotation().Yaw)) };
	const float rotationSpeed{ 5 };
	
	//rotate over the smallest angle
	const float rotation = FMath::FindDeltaAngleRadians(actorAngle, FMath::Atan2(targetDirection.Y, targetDirection.X));

	result.AngularVelocity = rotation * DeltaTime * rotationSpeed;

	//stop rotating if angle < 0.05 rads
	if (FMath::Abs(rotation) < 0.05f)
	{
		result.AngularVelocity = 0.f;
	}

	return result;
}

//PURSUIT
SteeringOutput Pursuit::CalculateSteering(float DeltaTime, AActor* agent)
{
	//make an output object
	SteeringOutput result;

	//set direction if target is immobile VS mobile
	if (Target.LinearVelocity.Length() < FLT_EPSILON)
	{
		result.LinearVelocity = Target.Position - (FVector2D)agent->GetActorTransform().GetLocation();
	}
	else
	{
		result.LinearVelocity = PredictTarget(agent, Target) - (FVector2D)agent->GetActorTransform().GetLocation();
	}

	return result;
}

//EVADE
SteeringOutput Evade::CalculateSteering(float DeltaTime, AActor* agent)
{
	//make an output object
	SteeringOutput result;

	//hardcode evade radius
	float evadeRadius{ 250.f };

	//implement evade radius
	result.IsValid = (evadeRadius > ((FVector2D)agent->GetActorTransform().GetLocation() - Target.Position).Length());

	//set direction if target is immobile VS mobile
	if (Target.LinearVelocity.Length() < FLT_EPSILON)
	{
		result.LinearVelocity = (FVector2D)agent->GetActorTransform().GetLocation() - Target.Position;
	}
	else
	{
		result.LinearVelocity = (FVector2D)agent->GetActorTransform().GetLocation() - PredictTarget(agent, Target);
	}

	return result;
}

//Wander
SteeringOutput Wander::CalculateSteering(float DeltaTime, AActor* agent)
{
	//make an output object
	SteeringOutput result;

	//calculate walking circle
	const FVector2D center{ PredictTarget(agent, 1.f) };
	float radius{float(((FVector2D)agent->GetActorTransform().GetLocation() - center).Length())};
	if (radius < 1.f)
	{
		radius = 1.f;
	}

	//calculate random angle
	const float angle{ 0.25f * float(rand() % 8 * PI) };

	//calculate point on circle
	const FVector2D target{ center.X + radius * cos(angle), center.Y + radius * sin(angle) };

	//set Velocity
	result.LinearVelocity = target - (FVector2D)agent->GetActorTransform().GetLocation();

	return result;
}