#pragma once

#include <vector>
#include "Common.h"

namespace Manurocker95
{
	class Transform
	{
	protected:
		glm::mat3x3 m_matrix;

	public:
		Transform();
		Transform(glm::mat3x3 _mat);
		Transform(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale);
		~Transform();
	public:
		virtual glm::vec3 GetPosition();
		virtual glm::vec3 GetRotation();
		virtual glm::vec3 GetScale();

		virtual void SetMatrix(glm::mat3x3 _mat);
		virtual void SetMatrix(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale);
		virtual void SetPosition(glm::vec3 _pos);
		virtual void SetRotation(glm::vec3 _pos);
		virtual void SetScale(glm::vec3 _pos);

		virtual double GetPosX();
		virtual double GetPosY();
		virtual double GetPosZ();

		virtual void SetPosX(double _value);
		virtual void SetPosY(double _value);
		virtual void SetPosZ(double _value);

		virtual void MoveX(double _value);
		virtual void MoveY(double _value);
		virtual void MoveZ(double _value);

		virtual void MoveToCoord(double _x, double _y);
		virtual void MoveToCoord(double _x, double _y, double _z);
	};
}
