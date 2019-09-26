// Plane Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief The Plane Geaometrical Primitive class
 */
class CPrimPlane : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param origin Point on the plane
	 * @param normal Normal to the plane
	 */
	CPrimPlane(Vec3f color, Vec3f origin, Vec3f normal)
		: CPrim(color)
		, m_normal(normal)
		, m_origin(origin)
	{
		normalize(m_normal);
	}
	virtual ~CPrimPlane(void) = default;

	virtual bool Intersect(Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---

		// ray-plane; (o + td).n - a.n = 0
		// t = (a.n-o.n)/(d.n)
		
		float numerator = m_origin.dot(m_normal) - ray.org.dot(m_normal);
		float denom = ray.dir.dot(m_normal);

		// parallel rays
		if(denom == 0)
			return false;

		float t = (float) numerator / (float) denom;
		if(t > ray.t || t < Epsilon)
			return false;

		ray.t = t;
	
		return true;
	}
	
	
private:
	Vec3f m_normal;	///< Point on the plane
	Vec3f m_origin;	///< Normal to the plane
};
