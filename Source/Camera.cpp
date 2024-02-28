#include "Camera.h"

namespace Manurocker95
{
	Camera::Camera() : SceneObject()
	{

	}

	Camera::Camera(float _fov, float _near, float _far, float _aspectRatio) : SceneObject()
	{
		Set(_fov, _near, _far, _aspectRatio);
	}

	Camera::Camera(glm::mat3x3 _matrix, float _fov, float _near, float _far, float _aspectRatio) : SceneObject(_matrix)
	{
		Set(_fov, _near, _far, _aspectRatio);
	}

	Camera::Camera(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale, float _fov, float _near, float _far, float _aspectRatio) : SceneObject(_pos, _rot, _scale)
	{
		Set(_fov, _near, _far, _aspectRatio);
	}

	Camera::~Camera()
	{

	}

	void Camera::Set(float _fov, float _near, float _far, float _aspectRatio)
	{

	}

	void Camera::SetFOV(float _fov)
	{
		m_fieldOfView = _fov;
		CalculatePerspective();
	}

	void Camera::SetNear(float _near)
	{
		m_near = _near;
		CalculatePerspective();
	}

	void Camera::SetFar(float _far)
	{
		m_far = _far;
		CalculatePerspective();
	}

	void Camera::SetAspectRatio(float _aspectRatio)
	{
		m_aspectRatio = _aspectRatio;
		CalculatePerspective();
	}


	void Camera::LookAt(glm::vec3 _pos)
	{
		glm::lookAt(GetPosition(), m_lookAtPoint, m_upVector);
	}


	float Camera::GetFOV()
	{
		return m_fieldOfView;
	}

	float Camera::GetNear()
	{
		return m_near;
	}

	float Camera::GetFar()
	{
		return m_far;
	}

	float Camera::GetAspectRatio()
	{
		return m_aspectRatio;
	}

	glm::mat4x4 Camera::GetProjectionMatrix()
	{
		return m_projectionMatrix;
	}

	void Camera::CalculatePerspective()
	{
		m_projectionMatrix = glm::perspective(m_fieldOfView * (float)TAU / 360.0f, m_aspectRatio, m_near, m_far);
	}
}