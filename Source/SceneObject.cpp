#include "SceneObject.h"

namespace Manurocker95
{
	SceneObject::SceneObject()
	{
		m_transform = std::make_shared<Transform>();
		m_children = std::vector<std::shared_ptr<SceneObject>>();
	}

	SceneObject::SceneObject(glm::mat3x3 _matrix) : SceneObject()
	{
		SetTransformMatrix(_matrix);
	}

	SceneObject::SceneObject(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale) : SceneObject()
	{
		SetTransformMatrix(_pos, _rot, _scale);
	}

	SceneObject::~SceneObject()
	{

	}	

	void SceneObject::SetTransformMatrix(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale)
	{
		m_transform->SetMatrix(_pos, _rot, _scale);
	}

	void SceneObject::SetTransformMatrix(glm::mat3x3 _matrix)
	{
		m_transform->SetMatrix(_matrix);
	}

	void SceneObject::AddChildren(std::shared_ptr<SceneObject> _child)
	{
		m_children.push_back(_child);
	}

	void SceneObject::RemoveChildren(size_t _idx)
	{
		m_children.erase(m_children.begin() + _idx);
	}

	void SceneObject::Render(GLFWwindow* window)
	{

	}

	void SceneObject::Update(double ticks)
	{

	}

	void SceneObject::Free()
	{

	}

	void SceneObject::SetActive(bool _value)
	{
		m_isActive = _value;
	}

	bool SceneObject::IsActive()
	{
		return m_isActive;
	}

	void SceneObject::SetVisible(bool _value)
	{
		m_isVisible = _value;
	}

	bool SceneObject::IsVisible()
	{
		return m_isVisible;
	}

	std::shared_ptr <Transform> SceneObject::GetTransform()
	{
		return m_transform;
	}	
	
	bool SceneObject::HasChildren()
	{
		return ChildrenCount() > 0;
	}


	size_t SceneObject::ChildrenCount()
	{
		return m_children.size();
	}	
	
	std::vector<std::shared_ptr<SceneObject>> SceneObject::GetChildren()
	{
		return m_children;
	}

	std::shared_ptr<SceneObject> SceneObject::GetChild(size_t idx)
	{
		return m_children.at(idx);
	}

	void SceneObject::SetPosition(glm::vec3 _pos)
	{
		m_transform->SetPosition(_pos);
	}

	glm::vec3 SceneObject::GetPosition()
	{
		return m_transform->GetPosition();
	}

	glm::vec3 SceneObject::GetRotation()
	{
		return m_transform->GetRotation();
	}

	glm::vec3 SceneObject::GetScale()
	{
		return m_transform->GetScale();
	}

	void SceneObject::MoveToCoord(double _x, double _y)
	{
		m_transform->MoveToCoord(_x, _y);
	}

	void SceneObject::MoveToCoord(double _x, double _y, double _z)
	{
		m_transform->MoveToCoord(_x, _y, _z);
	}

	void SceneObject::MoveX(double _value)
	{
		m_transform->MoveX(_value);
	}

	void SceneObject::MoveY(double _value)
	{
		m_transform->MoveY(_value);
	}	
	
	void SceneObject::MoveZ(double _value)
	{
		m_transform->MoveZ(_value);
	}

	void SceneObject::SetX(double _value)
	{
		m_transform->SetPosX(_value);
	}

	double SceneObject::GetX()
	{
		return m_transform->GetPosX();
	}

	void SceneObject::SetY(double _value)
	{
		m_transform->SetPosY(_value);
	}

	double SceneObject::GetY()
	{
		return m_transform->GetPosY();
	}

	void SceneObject::SetZ(double _value)
	{
		m_transform->SetPosZ(_value);
	}

	double SceneObject::GetZ()
	{
		return m_transform->GetPosZ();
	}
}