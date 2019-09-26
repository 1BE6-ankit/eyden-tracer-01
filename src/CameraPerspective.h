// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"
#include <math.h>
#include <iostream>

/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{
public:
	/**
	 * @brief Constructor
	 * @param pos Camera origin (center of projection)
	 * @param dir Camera viewing direction
	 * @param up Up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
	 * @param resolution The image resolution
	 */
	CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)
		: ICamera(resolution)
		, m_pos(pos)
		, m_dir(dir)
		, m_up(up)
	{
		// --- PUT YOUR CODE HERE ---
		m_aspect = (float) resolution.width / (float) resolution.height;
		angle_rad = (float) (M_PI/180 ) * angle;

		m_focus = (float) 1 / tan(angle_rad/2);

		// set coordinate system
		m_xAxis = m_dir.cross(m_up);
		m_yAxis = m_up;
		m_zAxis = m_dir;
	}
	virtual ~CCameraPerspective(void) = default;

	virtual bool InitRay(float x, float y, Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---

		// normalize coordinates to convert from object space raster coordinates
		float ndc_x = (float) (x + 0.5) / getResolution().width;
		float ndc_y = (float) (y + 0.5) / getResolution().height;

		// now convert [-0,1] ray-tracing NDC space to [-1,1] screen space coordinates
		float screen_x = 2 * (ndc_x - 0.5) * m_aspect;
		float screen_y = 2 * (0.5 - ndc_y);

		// now find the direction vector
		ray.dir = normalize(m_dir * m_focus + screen_x * m_xAxis + screen_y * m_yAxis);

		ray.org = m_pos;
		ray.t = std::numeric_limits<int>::max();

		return true;
	}


private:
	// input values
	Vec3f m_pos;
	Vec3f m_dir;
	Vec3f m_up;

	// preprocessed values
	float m_focus;
	Vec3f m_xAxis;
	Vec3f m_yAxis;
	Vec3f m_zAxis;
	float m_aspect;

	// added fields
	float angle_rad;
};

