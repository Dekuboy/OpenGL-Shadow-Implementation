#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace PFG
{
	float distanceToPlane(const glm::vec3& n, const glm::vec3& p, const glm::vec3& q);

	bool movingSphereToPlaneCollision(const glm::vec3& n, const glm::vec3& c0, const glm::vec3& c1, const glm::vec3& q, float r, glm::vec3& ci);

	bool movingSphereToPlaneCollision2(glm::vec3 n, glm::vec3 c0, glm::vec3 c1, glm::vec3 q, float r, glm::vec3& ci);

	bool sphereToSphereCollision(const glm::vec3 c0, glm::vec3 c1, float r1, float r2, glm::vec3& cp);

	bool axisABoundingBox(glm::vec3 c0, glm::vec3 c1, glm::vec3 scale0, glm::vec3 scale1);

	// bool triBoxCollision();

	// bool movingBpxBoxCollision();
}