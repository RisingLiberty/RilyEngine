#include "stdafx.h"

#include "Camera.h"


Camera::Camera(const Math::Vec2& aspectRatio, const Math::Vec2& fov, float nearClip, float farClip, const std::string& name):
	SceneObject(name, new Component::TransformComponent(ZeroVec3, ZeroVec3, UnitVec3)),
	m_AspectRatio(aspectRatio),
	m_NearClip(nearClip),
	m_FarClip(farClip),
	m_Mode(CameraMode::PERSPECTIVE),
	m_FOV(fov)
{
}


Camera::~Camera()
{
}

int Camera::Initialize()
{
	CalculateProjectionMatrix();
	glViewport(0, 0, (int)m_AspectRatio.x, (int)m_AspectRatio.y);
	//glOrtho(-m_AspectRatio.x, m_AspectRatio.x, -m_AspectRatio.y, m_AspectRatio.y, m_NearClip, m_FarClip);
	return OK;
}

void Camera::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	m_ViewMatrix = rlm::CalculateWorldMatrix(m_pTransform->GetPosition(), m_pTransform->GetRotation(), UnitVec3).GetInverse();
}

void Camera::Render()
{
}

void Camera::CalculateProjectionMatrix()
{
	glViewport(0, 0, (int)m_AspectRatio.x, (int)m_AspectRatio.y);
	//glOrtho(-m_AspectRatio.x, m_AspectRatio.x, -m_AspectRatio.y, m_AspectRatio.y, m_NearClip, m_FarClip);
	float f = tanf(m_FOV.y / (float)RL_PI * 180 / 2);

	//depth buffer -1 --> 1
	float aspect = GetCalculatedAspectRatio();
	float x = 1.0f / (aspect * f);
	float y = 1.0f / f;
	float a = -(m_FarClip + m_NearClip) / (m_FarClip - m_NearClip);
	float b = -(2 * m_NearClip * m_FarClip) / (m_FarClip - m_NearClip);

	//depth buffer 0 --> 1
	//float aspect = GetCalculatedAspectRatio();
	//float x = 1.0f / (aspect * f);
	//float y = 1.0f / f;
	//float a = m_FarClip / (m_FarClip - m_NearClip);
	//float b = (-m_NearClip * m_FarClip) / (m_FarClip - m_NearClip);

	m_ProjectionMatrix = Math::Mat44({
		x,0,0,0,
		0,y,0,0,
		0,0,a,-1,
		0,0,b,0
		});
}
