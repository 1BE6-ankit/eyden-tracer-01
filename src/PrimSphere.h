// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"
#include <math.h>

/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param center Position of the center of the sphere
	 * @param radius Radius of the sphere
	 */
	CPrimSphere(Vec3f color, Vec3f center, float radius)
		: CPrim(color)
		, m_center(center)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		// --- PUT YOUR CODE HERE ---

		// ray: o + td
		// sphere: (p - c) . (p - c) = r^2

		// t^2.d.d + 2.t.d.(o - c) + (o - c) . (o - c) - r^2 = 0
		// a = d . d 
		// b = 2 . d . (o - c)
		// c = (o - c) . (o - c) - r^2

		float a = ray.dir.dot(ray.dir);
		float b = 2 * ray.dir.dot(ray.org - m_center);
		float c = (ray.org - m_center).dot(ray.org - m_center) - m_radius * m_radius;

		float discriminant = b*b - 4 * a * c;

		if(discriminant < 0)
			return false;

		// two quadratic solution
		float t_minus = (float) (-b - pow(discriminant, (float) 1/2)) / (2 * a);
		float t_plus = (float) (-b + pow(discriminant, (float) 1/2)) / (2 * a);
		float t = t_minus;

		if(t > t_plus)
			t = t_plus;

		if(t > ray.t || t < Epsilon)
			return false;

		ray.t = t;

		return true;
	}
	
	
private:
	Vec3f m_center;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};

