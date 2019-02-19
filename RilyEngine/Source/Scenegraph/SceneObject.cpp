#include "stdafx.h"

#include "SceneObject.h"
#include "../Components/MeshFilter.h"

namespace Scenegraph
{


uint_t SceneObject::s_CurrentID = 0;

SceneObject::SceneObject(const std::string& name, Component::TransformComponent* pTransform):
	m_pTransform(pTransform),
	m_Name(name),
	m_ID(s_CurrentID++)
{
	m_Components.AddC(m_pTransform);
}

int SceneObject::Initialize()
{
	return OK;
}

void SceneObject::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

bool SceneObject::ShouldDraw()
{
	return this->GetComponent<Component::MeshFilter>() != nullptr;
}

SceneObject::~SceneObject()
{
	delete m_pTransform;
}

void SceneObject::Translate(const Math::Vec3& vec) 
{ 
	m_pTransform->Translate(vec); 
}

void SceneObject::Rotate(const Math::Vec3& vec, float angle) 
{ 
	m_pTransform->Rotate(vec * angle);
}

void SceneObject::Scale(const Math::Vec3& scale) 
{ 
	m_pTransform->Scale(scale); 
}

Math::Vec3 SceneObject::GetFoward() const
{
	Math::Mat44 mat = rlm::CalculateRotationMatrix(m_pTransform->GetRotation());
	Math::Vec4 foward = Math::Vec4(Math::Vec3::Foward.x, Math::Vec3::Foward.y, Math::Vec3::Foward.z, 1.0f);
	foward = foward * mat;
	return -Math::Vec3(foward.x, foward.y, foward.z);
}

Math::Vec3 SceneObject::GetRight() const
{
	Math::Mat44 mat = rlm::CalculateRotationMatrix(m_pTransform->GetRotation());
	Math::Vec4 right = Math::Vec4(Math::Vec3::Right.x, Math::Vec3::Right.y, Math::Vec3::Right.z, 1.0f);
	right = right * mat;
	return Math::Vec3(right.x, right.y, right.z);
}

Math::Vec3 SceneObject::GetUp() const
{
	Math::Mat44 mat = rlm::CalculateRotationMatrix(m_pTransform->GetRotation());
	Math::Vec4 up = Math::Vec4(Math::Vec3::Up.x, Math::Vec3::Up.y, Math::Vec3::Up.z, 1.0f);
	up = up * mat;
	return Math::Vec3(up.x, up.y, up.z);
}

Math::Vec3 SceneObject::GetLeft() const
{
	return -GetRight();
}

Math::Vec3 SceneObject::GetBack() const
{
	return -GetFoward();
}

Math::Vec3 SceneObject::GetDown() const
{
	return -GetUp();
}

Math::Quaternion SceneObject::GetOrientation() const
{
	return Math::Quaternion::RotationY(-m_pTransform->GetRotation().y) * Math::Quaternion::RotationX(-m_pTransform->GetRotation().x);
}

Component::ComponentBase* SceneObject::GetComponent(uint_t index)
{
	ASSERT(!m_Components.IsEmpty(), "Component index out of range");

	return m_Components[index];
}

}