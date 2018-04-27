#include <IDVUtils/Camera.h>
//#include <IDVMath.h>
 

const XVECTOR3 Camera::RightConstCameraSpace = XVECTOR3{ 1.0f, 0.0f, 0.0f, 0.0f };
const XVECTOR3 Camera::UpConstCameraSpace = XVECTOR3{ 0.0f, 1.0f, 0.0f, 0.0f };
const XVECTOR3 Camera::LookConstCameraSpace = XVECTOR3{ 0.0f, 0.0f, 1.0f, 0.0f };

Camera::Camera()
{
	LookConstCameraSpace;
	RightConstCameraSpace;

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
	Friction = .1f;
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
	XMatViewLookAtLH(View, Eye, Look, Up);
}
void Camera::MoveForward(float dt)
{
	XVECTOR3 moveDir = Look - Eye;
	moveDir.Normalize();
	Look += moveDir;
	Eye += moveDir;
	//Velocity.z -= Speed*dt;
}
void Camera::MoveBackward(float dt)
{
	XVECTOR3 moveDir = Look - Eye;
	moveDir.Normalize();
	Look -= moveDir;
	Eye -= moveDir;
	//Velocity.z += Speed*dt;

}
void Camera::StrafeLeft(float dt)
{
	XVECTOR3 moveDir = Right;
	moveDir.Normalize();
	Look -= moveDir;
	Eye -= moveDir;
	//Velocity.x += Speed*dt;
}
void Camera::StrafeRight(float dt)
{
	XVECTOR3 moveDir = Right;
	moveDir.Normalize();
	Look += moveDir;
	Eye += moveDir;
	//Velocity.x -= Speed*dt;

}
void Camera::MoveUp(float dt)
{
	XVECTOR3 moveDir = Up;
	moveDir.Normalize();
	Look -= moveDir;
	Eye -= moveDir;
}
void Camera::MoveDown(float dt)
{
	XVECTOR3 moveDir = Up;
	moveDir.Normalize();
	Look += moveDir;
	Eye += moveDir;
}
void Camera::TurnLeft(float dt)
{
}
void Camera::TurnRight(float dt)
{
}
void Camera::TurnUp(float dt)
{
	Velocity -= Up*dt * 2;
}
void Camera::TurnDown(float dt)
{
	Velocity += Up*dt * 2;
}
void Camera::MoveYaw(float radians)
{
	if (MaxYaw != 0.0f)
	{
		if (
			(Yaw + radians) > MaxYaw ||
			(Yaw + radians) < -MaxYaw)
		{
			return;

		}

	}
	Yaw += radians;
	/*radians += Yaw;
	XMATRIX44 rotation;
	XMatRotationAxisLH(rotation, Up, radians);
	XVecTransformNormalLH(Right,Right,rotation);
	XVecTransformNormalLH(Look, Look, rotation);*/
	
}
void Camera::MovePitch(float radians)
{
	if (MaxPitch != 0.0f)
	{
		if (
			(Pitch + radians) > MaxPitch ||
			(Pitch + radians) < -MaxPitch)
		return;
	}
	Pitch += radians;
	/*XMATRIX44 rotation;
	XMatRotationAxisLH(rotation, Right, radians);
	XVecTransformNormalLH(Up, Up, rotation);
	XVecTransformNormalLH(Look, Look, rotation);*/
	
}
void Camera::MoveRoll(float f)
{

}
void Camera::Update(float dt)
{
	XMATRIX44 X_, Y_, Z_, T_;
	XMatRotationXLH(X_, -Pitch);
	XMatRotationYLH(Y_, -Yaw);
	XMatRotationZLH(Z_, -Roll);
	View = Z_*Y_*X_;
	XMATRIX44 trans;
	XMatTranspose(trans, View);
	XVecTransformNormalLH(Look, LookConstCameraSpace, trans);
	XVecTransformNormalLH(Up, UpConstCameraSpace, trans);
	XVecTransformNormalLH(Right, RightConstCameraSpace, trans);
	Look.Normalize();
	Up.Normalize();
	Right.Normalize();

	XVECTOR3 currentvel =
		Velocity.x*Right + Velocity.y*Up + Velocity.z*Look;
	Velocity -= Velocity*Friction;
	Eye += currentvel;

	XVECTOR3 teye = -Eye;
	XMatTranslation(T_, teye);
	View = T_*View;
	VP = View*Projection;
	XMatViewLookAtLH(View, Eye, Look, Up);
	/*Right.x = View.m11;
	Right.y = View.m21;
	Right.z = View.m31;
	Up.x = View.m12;
	Up.y = View.m22;
	Up.z = View.m32;
	Look.x = View.m13;
	Look.y = View.m23;
	Look.z = View.m33;*/
	
	/*VP = View*Projection;
	XMatTranslation(Position, Velocity);
	Eye += Velocity;
	Velocity = XVECTOR3(0, 0, 0);
	Up = XVECTOR3(0, 1, 0);
	XMatTranslation(Position, Look);
	XMatViewLookAtLH(View, Eye, Look, Up);
	Right.x = View.m11;
	Right.y = View.m21;
	Right.z = View.m31;
	Up.x = View.m12;
	Up.y = View.m22;
	Up.z = View.m32;
	

	float lookLengthOnXZ = sqrtf(Look.z * Look.z + Look.x * Look.x);
	Pitch = atan2f(Look.y, lookLengthOnXZ);
	Yaw = atan2f(Look.x, Look.z);*/
}
void Camera::Reset()
{

}
void Camera::SetFov(float f)
{
	
}
void Camera::SetRatio(float r)
{
	AspectRatio = r;
}
void Camera::SetPlanes(float n, float f)
{

}