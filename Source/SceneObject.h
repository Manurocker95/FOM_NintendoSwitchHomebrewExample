#pragma once
#include "Transform.h"
#include <sstream>
#include "Common.h"

namespace Manurocker95
{
	class SceneObject
	{
	protected:
		bool m_isActive;
		bool m_isVisible;
	protected:
		std::shared_ptr<Transform> m_transform;
		std::vector< std::shared_ptr<SceneObject>> m_children;

	public:
		SceneObject();
		SceneObject(glm::mat3x3 _mat);
		SceneObject(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale);
		~SceneObject();

		virtual void SetActive(bool _value);
		virtual bool IsActive();		
		
		virtual void SetVisible(bool _value);
		virtual bool IsVisible();

		virtual std::shared_ptr <Transform> GetTransform();
		virtual void AddChildren(std::shared_ptr<SceneObject> _child);
		virtual void RemoveChildren(size_t _idx);
		virtual bool HasChildren();
		virtual size_t ChildrenCount();
		virtual std::vector< std::shared_ptr<SceneObject>> GetChildren();
		virtual std::shared_ptr <SceneObject> GetChild(size_t idx);
		
		virtual void SetTransformMatrix(glm::mat3x3 _mat);
		virtual void SetTransformMatrix(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale);
		virtual glm::vec3 GetPosition();
		virtual glm::vec3 GetRotation();
		virtual glm::vec3 GetScale();

		virtual void SetPosition(glm::vec3 _pos);
		virtual void MoveX(double _value);
		virtual void MoveY(double _value);
		virtual void MoveZ(double _value);
		virtual void MoveToCoord(double _x, double _y);
		virtual void MoveToCoord(double _x, double _y, double _z);

		virtual double GetX();
		virtual void SetX(double _value);
		virtual double GetY();
		virtual void SetY(double _value);
		virtual double GetZ();
		virtual void SetZ(double _value);

		virtual void Render(GLFWwindow* _window);
		virtual void Update(double ticks);
		virtual void Free();
	};
}