#include "Utility.h"

namespace PFG
{
	float distanceToPlane(const glm::vec3 & n, const glm::vec3 & p, const glm::vec3 & q)
	{
		float d = glm::dot((p - q), n);
		return d;
	}

	bool movingSphereToPlaneCollision(const glm::vec3 & n, const glm::vec3 & c0, const glm::vec3 & c1, const glm::vec3 & q, float r, glm::vec3 & ci)
	{
		float t;

		float d0 = distanceToPlane(n, c0, q);
		float d1 = distanceToPlane(n, c1, q);

		if (glm::abs(d0) <= r)
		{
			ci = c0;
			t = 0.0f;
			return true;
		}
		if (d0 > r && d1 < r)
		{
			t = (d0 - r) / (d0 - d1);

			ci = (1 - t)*c0 + t * c1;

			return true;
		}

		return false;
	}

	bool movingSphereToPlaneCollision2(glm::vec3 n, glm::vec3 c0, glm::vec3 c1, glm::vec3 q, float r, glm::vec3& ci)
	{
		float t;

		float d0 = distanceToPlane(n, c0, q);
		float d1 = distanceToPlane(n, c1, q);

		if (glm::abs(d0) <= r)
		{
			ci = c0;
			t = 0.0f;
			return true;
		}
		if (d0 > r && d1 < r)
		{
			t = (d0 - r) / (d0 - d1);

			ci = (1 - t)*c0 + t * c1;

			return true;
		}

		return false;
	}

	bool sphereToSphereCollision(const glm::vec3 c0, glm::vec3 c1, float r1, float r2, glm::vec3& cp)
	{
		float d = glm::length(c0 - c1);
		glm::vec3 n;

		if (d <= (r1 + r2))
		{
			n = glm::normalize(c0 - c1);
			cp = r1 * n;

			return true;
		}

		return false;
	}

	bool axisABoundingBox(glm::vec3 c0, glm::vec3 c1, glm::vec3 scale0, glm::vec3 scale1)
	{
		c1 -= c0;
		if ((scale0.x < c1.x - scale1.x) || (-scale0.x > c1.x + scale1.x))
		{
			return false;
		}
		if ((scale0.y < c1.y - scale1.y) || (-scale0.y > c1.y + scale1.y))
		{
			return false;
		}
		if ((scale0.z < c1.z - scale1.z) || (-scale0.z > c1.z + scale1.z))
		{
			return false;
		}
		return true;
	}

	bool triBoxCollision(glm::vec3 c0, glm::vec3 c1)
	{
		return false;
	}
}
