#pragma once
#include "SceneObject.h"

namespace Manurocker95
{
	class Camera : public SceneObject
	{
	protected:
		float m_fieldOfView;
		float m_near;
		float m_far;
		float m_aspectRatio;

		glm::mat4x4 m_projectionMatrix;
		glm::vec3 m_lookAtPoint;
		glm::vec3 m_upVector;

	public:
		Camera();
		Camera(float _fov, float _near, float _far, float _aspectRatio);
		Camera(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale, float _fov, float _near, float _far, float _aspectRatio);
		Camera(glm::mat3x3 _matrix, float _fov, float _near, float _far, float _aspectRatio);
		~Camera();

	public:
		float GetFOV();
		float GetNear();
		float GetFar();
		float GetAspectRatio();
		glm::mat4x4 GetProjectionMatrix();

		void CalculatePerspective();
		void Set(float _fov, float _near, float _far, float _aspectRatio);
		void SetFOV(float _fov);
		void SetNear(float _fov);
		void SetFar(float _fov);
		void SetAspectRatio(float _fov);
		void LookAt(glm::vec3 _pos);
	};
}