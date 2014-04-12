#include <GFK/Math/EasingFunctions.hpp>
#include <GFK/Math/MathHelper.hpp>
#include <cmath>

namespace gfk
{

float EasingFunctions::easeInBack(float t, float b, float c, float d)
{
	float s = 1.70158f;
	float postFix = t /= d;
	return c * (postFix) * t * ((s + 1) * t - s) + b;
}

float EasingFunctions::easeOutBack(float t, float b, float c, float d)
{	
	float s = 1.70158f;
	return c * ((t = t / d - 1) * t * ((s + 1) * t + s) + 1) + b;
}

float EasingFunctions::easeInOutBack(float t, float b, float c, float d)
{
	float s = 1.70158f;

	if ((t /= d / 2) < 1)
	{
		return c / 2 * (t * t * (((s *= (1.525f)) + 1) * t - s)) + b;
	}
	else
	{
		float postFix = t -= 2;
		return c / 2 * ((postFix) * t * (((s *= (1.525f)) + 1) * t + s) + 2) + b;
	}
}

float EasingFunctions::easeInBounce(float t, float b, float c, float d)
{
	return c - easeOutBounce(d - t, 0, c, d) + b;
}

float EasingFunctions::easeOutBounce(float t, float b, float c, float d)
{
	if ((t /= d) < (1 / 2.75f))
	{
		return c * (7.5625f * t * t) + b;
	}
	else if (t < (2 / 2.75f))
	{
		float postFix = t -= (1.5f / 2.75f);
		return c * (7.5625f * (postFix) * t + 0.75f) + b;
	}
	else if (t < (2.5 / 2.75))
	{
		float postFix = t -= (2.25f / 2.75f);
		return c * (7.5625f * (postFix) * t + 0.9375f) + b;
	}
	else {
		float postFix = t -= (2.625f / 2.75f);
		return c * (7.5625f * (postFix) * t + 0.984375f) + b;
	}
}

float EasingFunctions::easeInOutBounce(float t, float b, float c, float d)
{
	if (t < d / 2)
	{
		return easeInBounce(t * 2, 0, c, d) * 0.5f + b;
	}
	else
	{
		return easeOutBounce(t * 2 - d, 0, c, d) * 0.5f + c * 0.5f + b;
	}
}

float EasingFunctions::easeInCirc(float t, float b, float c, float d)
{
	return -c * (sqrt(1 - (t /= d) * t) - 1) + b;
}

float EasingFunctions::easeOutCirc(float t, float b, float c, float d)
{
	return c * sqrt(1 - (t = t / d - 1) * t) + b;
}

float EasingFunctions::easeInOutCirc(float t, float b, float c, float d)
{
	if ((t /= d / 2) < 1)
	{
		return -c / 2 * (sqrt(1 - t * t) - 1) + b;
	}
	else
	{
		return c / 2 * (sqrt(1 - t * (t -= 2)) + 1) + b;
	}
}

float EasingFunctions::easeInCubic(float t, float b, float c, float d)
{
	return c * (t /= d) * t * t + b;
}

float EasingFunctions::easeOutCubic(float t, float b, float c, float d)
{
	return c * ((t = t / d - 1) * t * t + 1) + b;
}

float EasingFunctions::easeInOutCubic(float t, float b, float c, float d)
{
	if ((t /= d / 2) < 1)
	{
		return c / 2 * t * t * t + b;
	}
	else
	{
		return c / 2 * ((t -= 2) * t * t + 2) + b;
	}
}

float EasingFunctions::easeInElastic(float t, float b, float c, float d)
{
	if (t == 0)
	{
		return b;
	}

	if ((t /= d) == 1)
	{
		return b + c;
	}

	float p = d * 0.3f;
	float a = c;
	float s = p / 4;
	float postFix = a * pow(2, 10 * (t -= 1));

	return -(postFix * sin((t * d - s) * (2 * MathHelper::Pi) / p)) + b;
}

float EasingFunctions::easeOutElastic(float t, float b, float c, float d)
{
	if (t == 0)
	{
		return b;
	}

	if ((t /= d) == 1)
	{
		return b + c;
	}

	float p = d * 0.3f;
	float a = c; 
	float s = p / 4;

	return (a * pow(2, -10 * t) * sin((t * d - s) * (2 * MathHelper::Pi) / p) + c + b);
}

float EasingFunctions::easeInOutElastic(float t, float b, float c, float d)
{
	if (t == 0)
	{
		return b;
	}

	if ((t /= d / 2) == 2)
	{
		return b + c;
	}

	float p = d * (0.3f * 1.5f);
	float a = c;
	float s = p / 4;
	 
	if (t < 1)
	{
		float postFix = a * pow(2, 10 * (t -= 1));
		return -0.5f * (postFix * sin((t * d - s) * (2 * MathHelper::Pi) / p)) + b;
	} 

	float postFix = a * pow(2, -10 * (t -= 1));

	return postFix * sin((t * d - s) * (2 * MathHelper::Pi) / p) * 0.5f + c + b;
}

float EasingFunctions::easeInExpo(float t, float b, float c, float d)
{
	return (t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b;
}

float EasingFunctions::easeOutExpo(float t, float b, float c, float d)
{
	return (t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b;
}

float EasingFunctions::easeInOutExpo(float t, float b, float c, float d)
{
	if (t == 0)
	{
		return b;
	}

	if (t == d)
	{
		return b + c;
	}

	if ((t /= d / 2) < 1)
	{
		return c / 2 * pow(2, 10 * (t - 1)) + b;
	}

	return c / 2 * (-pow(2, -10 * --t) + 2) + b;
}

float EasingFunctions::easeInLinear(float t, float b, float c, float d)
{
	return c * t / d + b;
}

float EasingFunctions::easeOutLinear(float t, float b, float c, float d)
{	
	return c * t / d + b;
}

float EasingFunctions::easeInOutLinear(float t, float b, float c, float d)
{
	return c * t / d + b;
}

float EasingFunctions::easeInQuad(float t, float b, float c, float d)
{
	return c * (t /= d) * t + b;
}

float EasingFunctions::easeOutQuad(float t, float b, float c, float d)
{
	return -c * (t /= d) * (t - 2) + b;
}

float EasingFunctions::easeInOutQuad(float t, float b, float c, float d)
{
	if ((t /= d / 2) < 1)
	{
		return ((c / 2) * (t * t)) + b;
	}
	else
	{
		return -c / 2 * (((t - 2) * (--t)) - 1) + b;
	}
}

float EasingFunctions::easeInQuart(float t, float b, float c, float d)
{
	return c * (t /= d) * t * t * t + b;
}

float EasingFunctions::easeOutQuart(float t, float b, float c, float d)
{
	return -c * ((t = t / d - 1) * t * t * t - 1) + b;
}

float EasingFunctions::easeInOutQuart(float t, float b, float c, float d)
{
	if ((t /= d / 2) < 1)
	{
		return c / 2 * t * t * t * t + b;
	}
	else
	{
		return -c / 2 * ((t -= 2) * t * t * t - 2) + b;
	}
}

float EasingFunctions::easeInQuint(float t, float b, float c, float d)
{
	return c * (t /= d) * t * t * t * t + b;
}

float EasingFunctions::easeOutQuint(float t, float b, float c, float d)
{
	return c * ((t = t / d - 1) * t * t * t * t + 1) + b;
}

float EasingFunctions::easeInOutQuint(float t, float b, float c, float d)
{
	if ((t /= d / 2) < 1)
	{
		return c / 2 * t * t * t * t * t + b;
	}
	else
	{
		return c / 2 * ((t -= 2) * t * t * t * t + 2) + b;
	}
}

float EasingFunctions::easeInSine(float t, float b, float c, float d)
{
	return -c * cos(t / d * (MathHelper::Pi / 2)) + c + b;
}

float EasingFunctions::easeOutSine(float t, float b, float c, float d)
{	
	return c * sin(t / d * (MathHelper::Pi / 2)) + b;
}

float EasingFunctions::easeInOutSine(float t, float b, float c, float d)
{
	return -c / 2 * (cos(MathHelper::Pi * t / d) - 1) + b;
}

}
