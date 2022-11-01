#pragma once
#include "GameObject.h"
#include "InputListener.h"
#include "Vector3D.h"
#include "Matrix4x4.h"

class CameraComponent;
class SceneCamera : public GameObject, public InputListener
{
public:
	SceneCamera();
	~SceneCamera() override;

public:
	void Start() override;
	void Update(float deltaTime) override;
	
private:
	CameraComponent* camera = nullptr;

private:
	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& delta_mouse) override;
	virtual void onLeftMouseButtonDown(const Point& mouse_pos) override;
	virtual void onLeftMouseButtonUp(const Point& mouse_pos) override;
	virtual void onRightMouseButtonDown(const Point& mouse_pos) override;
	virtual void onRightMouseButtonUp(const Point& mouse_pos) override;

private:
	Vector3D input;
	float rotationX = 0.0f, rotationY = 0.0f;
	bool rmbDown = false;
	float cameraSpeed = 0.1f;
};

