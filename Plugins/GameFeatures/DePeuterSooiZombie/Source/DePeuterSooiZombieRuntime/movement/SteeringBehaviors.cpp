#include "SteeringBehaviors.h"

//predict target of another actor
FVector2D ISteeringBehavior::PredictTarget(FVector2D position, const FTargetData& target)
{
	//calculate time to reach target
	const float time{ (float)(position - Target.Position).Length() / CustomVars::maxLinearSpeed };

	//calculate predicted position
	const FVector2D predictPosition{ Target.Position + time * Target.LinearVelocity };

	return predictPosition;
}

//predict target of self
FVector2D ISteeringBehavior::PredictTarget(FVector2D position, FVector2D velocity, float time)
{
	//calculate predicted position
	const FVector2D predictPosition{ position.X + time * velocity.X,
									 position.Y + time * velocity.Y};

	return predictPosition;
}

//SEEK
SteeringOutput Seek::CalculateSteering(FVector2D position)
{
	//make an output object
	SteeringOutput result;
	
	//set Velocity
	result.LinearVelocity = Target.Position - position;
	
	return result;
}

//FLEE
SteeringOutput Flee::CalculateSteering(FVector2D position)
{
	//make an output object
	SteeringOutput result;

	//set Velocity
	result.LinearVelocity = position - Target.Position;

	return result;
}

//ARRIVE
SteeringOutput Arrive::CalculateSteering(FVector2D position)
{
	//hardcode arrive radiuses
	const float slowRadius{2000.f};

	//make an output object
	SteeringOutput result;

	//set Velocity
	result.LinearVelocity = Target.Position - position;

	//set max speed
	if ((Target.Position - position).Length() < m_TargetRadius)
	{
		CustomVars::SetMaxLinearSpeed(0);
	}
	if ((Target.Position - position).Length() < slowRadius)
	{
		CustomVars::SetMaxLinearSpeed((Target.Position - position).Length() / slowRadius * CustomVars::maxLinearSpeed);
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

//PURSUIT
SteeringOutput Pursuit::CalculateSteering(FVector2D position)
{
	//make an output object
	SteeringOutput result;

	//set direction if target is immobile VS mobile
	if (Target.LinearVelocity.Length() < FLT_EPSILON)
	{
		result.LinearVelocity = Target.Position - position;
	}
	else
	{
		result.LinearVelocity = PredictTarget(position, Target) - position;
	}

	return result;
}

//EVADE
SteeringOutput Evade::CalculateSteering(FVector2D position)
{
	//make an output object
	SteeringOutput result;

	//hardcode evade radius
	float evadeRadius{ 250.f };

	//implement evade radius
	result.IsValid = (evadeRadius > position.Length());

	//set direction if target is immobile VS mobile
	if (Target.LinearVelocity.Length() < FLT_EPSILON)
	{
		result.LinearVelocity = position - Target.Position;
	}
	else
	{
		result.LinearVelocity = position - PredictTarget(position, Target);
	}

	return result;
}

//Wander
SteeringOutput Wander::CalculateSteering(FVector2D position)
{
	//make an output object
	SteeringOutput result;

	//calculate walking circle
	const FVector2D center{ PredictTarget(position, {200, 200}, 1.f) };
	float radius{float((position - center).Length())};
	if (radius < 1.f)
	{
		radius = 1.f;
	}

	//calculate random angle
	const float angle{ 0.25f * float(rand() % 8 * PI) };
	
	//calculate point on circle
	const FVector2D target{ center.X + radius * cos(angle), center.Y + radius * sin(angle) };
	
	//set Velocity
	result.LinearVelocity = target - position;

	return result;
}