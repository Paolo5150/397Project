#pragma once
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/projection.hpp>

#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Maths
{

public:
	static std::string Vec3ToString(glm::vec3& v);
	static std::string Vec2ToString(glm::vec2& v);
	static glm::mat3 aiMatrix3x3ToGlm(const aiMatrix3x3 &from);
	static glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4 &from);
	static glm::vec3 aiVector3ToGlm(const aiVector3D &from);
	static glm::quat aiQuaternionToGlm(const aiQuaternion &from);
	static glm::quat nlerp(glm::quat a, glm::quat b, float blend);
	static glm::vec3 QuatToEuler(const glm::quat& q);

};