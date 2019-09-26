// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Triangle Geaometrical Primitive class
 */
class CPrimTriangle : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 */
	CPrimTriangle(Vec3f color, Vec3f a, Vec3f b, Vec3f c)
		: CPrim(color)
		, m_a(a)
		, m_b(b)
		, m_c(c)
  	{}
	virtual ~CPrimTriangle(void) = default;
	
	virtual bool Intersect(Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---
		Vec3f normal_ab = (m_b - ray.org).cross(m_a - ray.org);
		Vec3f normal_bc = (m_c - ray.org).cross(m_b - ray.org);
		Vec3f normal_ca = (m_a - ray.org).cross(m_c - ray.org);

		float signed_area = normal_ab.dot(ray.dir) + normal_bc.dot(ray.dir) + normal_ca.dot(ray.dir);
		float lamb_ab = (float) normal_ab.dot(ray.dir) / signed_area;
		float lamb_bc = (float) normal_bc.dot(ray.dir) / signed_area;
		float lamb_ca = (float) normal_ca.dot(ray.dir) / signed_area;

		if(lamb_ab < 0 || lamb_bc < 0 || lamb_ca < 0) {
			return false;
		}		

		Vec3f p = lamb_ab * m_a + lamb_bc * m_b + lamb_ca * m_c;
		float t = (float) p[0] / ray.dir[0];
		if(t < Epsilon || t > ray.t) {
			return false;
		}

		ray.t = t;

		return true;
	}

	
private:
	Vec3f m_a;	///< Position of the first vertex
	Vec3f m_b;	///< Position of the second vertex
	Vec3f m_c;	///< Position of the third vertex
};
