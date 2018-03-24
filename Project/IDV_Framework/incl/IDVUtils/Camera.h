#ifndef IDV_CAMERA_H
#define IDV_CAMERA_H
#include <IDVMath.h>
#include <IDVUtils/Timer.h>
class Camera {
public:
	Camera();

	void	Init(XVECTOR3 position, float fov, float ratio, float np, float fp, bool lf = true);
	void	CreatePojection();

	void	SetLookAt(XVECTOR3 v);

	void	MoveForward(float dt);
	void	MoveBackward(float dt);
	void	StrafeLeft(float dt);
	void	StrafeRight(float dt);
	void	MoveUp(float dt);
	void	MoveDown(float dt);
	void	TurnLeft(float dt);
	void	TurnRight(float dt);
	void	TurnUp(float dt);
	void	TurnDown(float dt);
	void	MoveYaw(float f);
	void	MovePitch(float f);
	void	MoveRoll(float f);

	void	Update(float dt);
	void	Reset();

	void	SetFov(float f);
	void	SetRatio(float r);
	void	SetPlanes(float n, float f);

	float		Fov;
	float		AspectRatio;
	float		NPlane;
	float		FPlane;

	float		Yaw;
	float		Pitch;
	float		Roll;

	float		MaxRoll;
	float		MaxPitch;
	float		MaxYaw;

	float		Speed;
	float		Friction;

	bool		LeftHanded;

	XVECTOR3	Eye;
	XVECTOR3	Look;
	XVECTOR3	Right;
	XVECTOR3	Up;
	XVECTOR3	LookAt;
	XVECTOR3	Velocity;

	XMATRIX44	Position;
	XMATRIX44	RotX;
	XMATRIX44	RotY;
	XMATRIX44	RotZ;

	XMATRIX44	View;
	XMATRIX44	Projection;
	XMATRIX44	VP;

	static const	XVECTOR3	LookConstCameraSpace;
	static const	XVECTOR3	RightConstCameraSpace;
	static const	XVECTOR3	UpConstCameraSpace;
};


#endif
