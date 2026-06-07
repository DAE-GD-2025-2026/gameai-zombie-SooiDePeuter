#pragma once

#include "SteeringHelpers.h"
#include "CustomVars.h"

// SteeringBehavior base, all steering behaviors should derive from this.
class ISteeringBehavior
{
public:
	ISteeringBehavior() = default;
	virtual ~ISteeringBehavior() = default;

	// Override to implement your own behavior
	virtual SteeringOutput CalculateSteering(FVector2D position) = 0;

	void SetTarget(const FTargetData& NewTarget) { Target = NewTarget; }
	
	template<class T, std::enable_if_t<std::is_base_of_v<ISteeringBehavior, T>>* = nullptr>
	T* As()
	{ return static_cast<T*>(this); }
	
	FVector2D PredictTarget(FVector2D position, const FTargetData& target);
	FVector2D PredictTarget(FVector2D position, FVector2D velocity, float time);

protected:
	FTargetData Target;

};

class Seek: public ISteeringBehavior
{
public:
	Seek() = default;
	virtual ~Seek() = default;

	virtual SteeringOutput CalculateSteering(FVector2D position) override;
};

class Flee : public ISteeringBehavior
{
public:
	Flee() = default;
	virtual ~Flee() = default;

	virtual SteeringOutput CalculateSteering(FVector2D position) override;
};

class Arrive : public ISteeringBehavior
{
public:
	Arrive() = default;
	virtual ~Arrive() = default;

	virtual SteeringOutput CalculateSteering(FVector2D position) override;
	void SetTargetRadius(float radius);
	
private:
	float m_TargetRadius{200};
};

class Pursuit : public ISteeringBehavior
{
public:
	Pursuit() = default;
	virtual ~Pursuit() = default;

	virtual SteeringOutput CalculateSteering(FVector2D position) override;
};

class Evade : public ISteeringBehavior
{
public:
	Evade() = default;
	virtual ~Evade() = default;

	virtual SteeringOutput CalculateSteering(FVector2D position) override;
};

class Wander : public ISteeringBehavior
{
public:
	Wander() = default;
	virtual ~Wander() = default;

	virtual SteeringOutput CalculateSteering(FVector2D position) override;
};