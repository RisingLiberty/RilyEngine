#pragma once

enum class CameraMode : char
{
	ORTHO,
	PERSPECTIVE
};

#include "../Scenegraph/SceneObject.h"

class Camera : public Scenegraph::SceneObject
{
public:
	Camera(const Math::Vec2& aspectRatio, const Math::Vec2& fov = Math::Vec2((float)RL_PI_DIV_2, (float)RL_PI_DIV_4), float nearClip = 0.1f, float farClip = 100.0f, const std::string& name = "Main Camera");
	~Camera();

	int Initialize();
	void Update(float deltaTime) override;
	void Render();
	void SetAspectRatio(const Math::Vec2& aspectRatio) { m_AspectRatio = aspectRatio; CalculateProjectionMatrix(); }
	Math::Vec2 GetAspectRatio() const { return m_AspectRatio; }
	float GetCalculatedAspectRatio() const { return m_AspectRatio.x / m_AspectRatio.y; }

	Math::Vec2 GetFieldOfView() const { return m_FOV; }

	Math::Mat44 GetViewMatrix() const { return m_ViewMatrix; }
	Math::Mat44 GetProjectionMatrix() const { return m_ProjectionMatrix; }

	CameraMode GetMode() const { return m_Mode; }

	float GetNearClip() const { return m_NearClip; }
	float GetFarClip() const { return m_FarClip; }

private:
	void CalculateProjectionMatrix();

private:
	Math::Vec2 m_AspectRatio;

	Math::Mat44 m_ViewMatrix;
	Math::Mat44 m_ProjectionMatrix;

	float m_NearClip;
	float m_FarClip;

	CameraMode m_Mode;
	Math::Vec2 m_FOV;

};

