#pragma once

struct CustomVars
{
	static float maxLinearSpeed;
	static void SetMaxLinearSpeed(float value) { maxLinearSpeed = value; }
};