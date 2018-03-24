#include <IDVUtils/Camera.h>
//#include <IDVMath.h>
 



Camera::Camera()
{
	
	Right = XVECTOR3(0, 0, 1);
	Up = XVECTOR3(0, 1, 0);
}
void Camera::Init(XVECTOR3 position, float fov, float ratio, float np, float fp, bool lf)
{
	XMatTranslation(Position, position);
	Fov = fov;
	AspectRatio = ratio;
	NPlane = np;
	FPlane = fp;
	Yaw = 0;
	Pitch = 0;
	Roll = 0;
	MaxRoll = Deg2Rad(45.0f);
	MaxPitch = Deg2Rad(90.0f);
	MaxYaw = Deg2Rad(360.0f);
	Speed = 10;
	Friction = 1;
	LeftHanded = lf;
	CreatePojection();
	Eye = position;
	SetLookAt(XVECTOR3(0,0,0));
	Update(1.0f);
}
void Camera::CreatePojection()
{
	XMatPerspectiveLH(Projection, Fov, AspectRatio, NPlane, FPlane);
	
}
void Camera::SetLookAt(XVECTOR3 v)
{
	
	Look = v;
	XMatViewLookAtLH(View,Eye,Look, Up);
}
void Camera::MoveForward(float dt)
{
	XMatTranslation(Position,-(dt*Speed),0,0);
	SetLookAt(XVECTOR3(0, 0, 0));
}
void Camera::MoveBackward(float dt)
{
	XMatTranslation(Position, (dt*Speed), 0, 0);
}
void Camera::StrafeLeft(float dt)
{
	XMatTranslation(Position, 0, 0, (dt*Speed));
}
void Camera::StrafeRight(float dt)
{
	XMatTranslation(Position, 0, 0, -(dt*Speed));
}
void Camera::MoveYaw(float f)
{

}
void Camera::MovePitch(float f)
{

}
void Camera::MoveRoll(float f)
{

}
void Camera::Update(float dt)
{
	VP = View*Projection;
}
void Camera::Reset()
{

}
void Camera::SetFov(float f)
{

}
void Camera::SetRatio(float r)
{

}
void Camera::SetPlanes(float n, float f)
{

}