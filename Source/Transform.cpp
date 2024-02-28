#include "Transform.h"

namespace Manurocker95
{
	Transform::Transform()
	{
		SetMatrix(glm::mat3x3(0));
	}
	
	Transform::Transform(glm::mat3x3 _mat)
	{
		SetMatrix(_mat);
	}	
	
	Transform::Transform(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale)
	{
		SetMatrix(_pos, _rot, _scale);
	}

	Transform::~Transform()
	{

	}

	void Transform::SetMatrix(glm::mat3x3 _mat)
	{
		SetMatrix(_mat[0], _mat[1], _mat[2]);
	}

	void Transform::SetMatrix(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale)
	{
		SetPosition(_pos);
		SetRotation(_rot);
		SetScale(_scale);
	}

	void Transform::SetPosition(glm::vec3 _pos)
	{
		m_matrix[0][0] = _pos[0];
		m_matrix[0][1] = _pos[1];
		m_matrix[0][2] = _pos[2];
	}	
	
	void Transform::SetRotation(glm::vec3 _rot)
	{
		m_matrix[1][0] = _rot[0];
		m_matrix[1][1] = _rot[1];
		m_matrix[1][2] = _rot[2];
	}

	void Transform::SetScale(glm::vec3 _scale)
	{
		m_matrix[2][0] = _scale[0];
		m_matrix[2][1] = _scale[1];
		m_matrix[2][2] = _scale[2];
	}

	glm::vec3 Transform::GetPosition()
	{
		return m_matrix[0];
	}

	glm::vec3 Transform::GetRotation()
	{
		return m_matrix[1];
	}

	glm::vec3 Transform::GetScale()
	{
		return m_matrix[2];
	}

	void Transform::MoveToCoord(double _x, double _y)
	{
		SetPosX(_x);
		SetPosY(_y);
	}

	void Transform::MoveToCoord(double _x, double _y, double _z)
	{
		SetPosX(_x);
		SetPosY(_y);
		SetPosZ(_z);
	}

	void Transform::MoveX(double _value)
	{
		m_matrix[0][0] += _value;
	}

	void Transform::MoveY(double _value)
	{
		m_matrix[0][1] += _value;
	}

	void Transform::MoveZ(double _value)
	{
		m_matrix[0][2] += _value;
	}

	double Transform::GetPosX()
	{
		return m_matrix[0][0];
	}

	double Transform::GetPosY()
	{
		return m_matrix[0][1];
	}

	double Transform::GetPosZ()
	{
		return m_matrix[0][2];
	}

	void Transform::SetPosX(double _x)
	{
		m_matrix[0][0] = _x;
	}

	void Transform::SetPosY(double _y)
	{
		m_matrix[0][1] = _y;
	}

	void Transform::SetPosZ(double _z)
	{
		m_matrix[0][2] = _z;
	}
}
