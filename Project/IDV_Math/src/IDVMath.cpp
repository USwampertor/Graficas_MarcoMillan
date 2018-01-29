#include <IDVMath.h>

void XMatMultiply(XMATRIX44 & result, const XMATRIX44 & A, const XMATRIX44 & B)
{
	memset(&result.m[0], 0, sizeof(result));
	result.m11 = (A.m11*B.m11 + A.m12*B.m21 + A.m13*B.m31 + A.m14*B.m41);
	result.m12 = (A.m11*B.m12 + A.m12*B.m22 + A.m13*B.m32 + A.m14*B.m42);
	result.m13 = (A.m11*B.m13 + A.m12*B.m23 + A.m13*B.m33 + A.m14*B.m43);
	result.m14 = (A.m11*B.m14 + A.m12*B.m24 + A.m13*B.m34 + A.m14*B.m44);

	result.m21 = (A.m21*B.m11 + A.m22*B.m21 + A.m23*B.m31 + A.m24*B.m41);
	result.m22 = (A.m21*B.m12 + A.m22*B.m22 + A.m23*B.m32 + A.m24*B.m42);
	result.m23 = (A.m21*B.m13 + A.m22*B.m23 + A.m23*B.m33 + A.m24*B.m43);
	result.m24 = (A.m21*B.m14 + A.m22*B.m24 + A.m23*B.m34 + A.m24*B.m44);

	result.m31 = (A.m31*B.m11 + A.m32*B.m21 + A.m33*B.m31 + A.m34*B.m41);
	result.m32 = (A.m31*B.m12 + A.m32*B.m22 + A.m33*B.m32 + A.m34*B.m42);
	result.m33 = (A.m31*B.m13 + A.m32*B.m23 + A.m33*B.m33 + A.m34*B.m43);
	result.m34 = (A.m31*B.m14 + A.m32*B.m24 + A.m33*B.m34 + A.m34*B.m44);

	result.m41 = (A.m41*B.m11 + A.m42*B.m21 + A.m43*B.m31 + A.m44*B.m41);
	result.m42 = (A.m41*B.m12 + A.m42*B.m22 + A.m43*B.m32 + A.m44*B.m42);
	result.m43 = (A.m41*B.m13 + A.m42*B.m23 + A.m43*B.m33 + A.m44*B.m43);
	result.m44 = (A.m41*B.m14 + A.m42*B.m24 + A.m43*B.m34 + A.m44*B.m44);
	
}
void XMatIdentity(XMATRIX44 & matrix)
{
	memset(&matrix.m[0], 0, sizeof(matrix));
	matrix.m11 = 1; matrix.m22 = 1; matrix.m33 = 1; matrix.m44 = 1;
}
void XMatViewLookAtLH(XMATRIX44 &mpout, const XVECTOR3 &camPos, const XVECTOR3 &lookAt, const XVECTOR3 &upAxis) {
	XVECTOR3 zaxe = lookAt - camPos;
	zaxe.Normalize();

	XVECTOR3 xaxe;
	XVecCross(xaxe, upAxis, zaxe);
	xaxe.Normalize();

	XVECTOR3 yaxe;
	XVecCross(yaxe, zaxe, xaxe);

	mpout.m[0][0] = xaxe.x;
	mpout.m[0][1] = yaxe.x;
	mpout.m[0][2] = zaxe.x;
	XVecDot(mpout.m[3][0], xaxe, camPos);
	mpout.m[3][0] = -mpout.m[3][0];

	mpout.m[1][0] = xaxe.y;
	mpout.m[1][1] = yaxe.y;
	mpout.m[1][2] = zaxe.y;
	XVecDot(mpout.m[3][1], yaxe, camPos);
	mpout.m[3][1] = -mpout.m[3][1];

	mpout.m[2][0] = xaxe.z;
	mpout.m[2][1] = yaxe.z;
	mpout.m[2][2] = zaxe.z;
	XVecDot(mpout.m[3][2], zaxe, camPos);
	mpout.m[3][2] = -mpout.m[3][2];

	mpout.m[0][3] = 0.0f;
	mpout.m[1][3] = 0.0f;
	mpout.m[2][3] = 0.0f;
	mpout.m[3][3] = 1.0f;
}

void XMatViewLookAtRH(XMATRIX44 &mpout, const XVECTOR3 &camPos, const XVECTOR3 &lookAt, const XVECTOR3 &upAxis) {
	XVECTOR3 zaxe = camPos - lookAt;
	zaxe.Normalize();

	XVECTOR3 xaxe;
	XVecCross(xaxe, upAxis, zaxe);
	xaxe.Normalize();

	XVECTOR3 yaxe;
	XVecCross(yaxe, zaxe, xaxe);

	mpout.m[0][0] = xaxe.x;
	mpout.m[0][1] = yaxe.x;
	mpout.m[0][2] = zaxe.x;
	XVecDot(mpout.m[3][0], xaxe, camPos);
	mpout.m[3][0] = -mpout.m[3][0];

	mpout.m[1][0] = xaxe.y;
	mpout.m[1][1] = yaxe.y;
	mpout.m[1][2] = zaxe.y;
	XVecDot(mpout.m[3][1], yaxe, camPos);
	mpout.m[3][1] = -mpout.m[3][1];

	mpout.m[2][0] = xaxe.z;
	mpout.m[2][1] = yaxe.z;
	mpout.m[2][2] = zaxe.z;
	XVecDot(mpout.m[3][2], zaxe, camPos);
	mpout.m[3][2] = -mpout.m[3][2];

	mpout.m[0][3] = 0.0f;
	mpout.m[1][3] = 0.0f;
	mpout.m[2][3] = 0.0f;
	mpout.m[3][3] = 1.0f;
}

void XMatPerspectiveLH(XMATRIX44 &mpout, const float &FOV, const float &Aspect, const float &NearPlane, const float &FarPlane) {
	float x, y;
	float ang = FOV / 2.0f;

	y = cos(ang) / sin(ang);
	x = y / Aspect;

	mpout.m[0][0] = x;
	mpout.m[1][1] = y;
	mpout.m[2][2] = FarPlane / (FarPlane - NearPlane);
	mpout.m[2][3] = 1.0;
	mpout.m[3][2] = -(NearPlane*FarPlane) / (FarPlane - NearPlane);
	mpout.m[3][3] = 0.0f;

}

void XMatPerspectiveRH(XMATRIX44 &mpout, const float &FOV, const float &Aspect, const float &NearPlane, const float &FarPlane)
{
	float x, y;
	float ang = FOV / 2.0f;

	y = cos(ang) / sin(ang);
	x = y / Aspect;

	mpout.m[0][0] = x;
	mpout.m[1][1] = y;
	mpout.m[2][2] = FarPlane / (NearPlane - FarPlane);
	mpout.m[2][3] = -1.0;
	mpout.m[3][2] = (NearPlane*FarPlane) / (NearPlane - FarPlane);
	mpout.m[3][3] = 0.0f;
}

void XMatOrthoLH(XMATRIX44 &m, const float &w, const float &h, const float &zn, const float &zf) {
	m.m[0][0] = 2.0f / w;
	m.m[1][1] = 2.0f / h;
	m.m[2][2] = 1.0f / (zf - zn);
	m.m[3][2] = -zn / (zf - zn);
	m.m[3][3] = 1.0f;
}

void XMatOrthoRH(XMATRIX44 &m, const float &w, const float &h, const float &zn, const float &zf) {
	m.m[0][0] = 2.0f / w;
	m.m[1][1] = 2.0f / h;
	m.m[2][2] = 1.0f / (zn - zf);
	m.m[3][2] = zn / (zn - zf);
	m.m[3][3] = 1.0f;
}


////////////////////////////VECTOR2

XVECTOR2& XVECTOR2:: operator+=(const XVECTOR2& other)
{
	this->x = this->x + other.x; this->y = this->y + other.y; return *this;
}
XVECTOR2& XVECTOR2::operator -= (const XVECTOR2& other)
{
	this->x = this->x - other.x; this->y = this->y - other.y; return *this;
}
XVECTOR2& XVECTOR2::operator *= (float times)
{
	this->x = this->x * times; this->y = this->y * times; return *this;
}
XVECTOR2& XVECTOR2::operator /= (float times)
{
	this->x = this->x / times; this->y = this->y / times; return *this;
}

XVECTOR2 XVECTOR2::operator + () const
{
	return *this;
}
XVECTOR2 XVECTOR2::operator - () const
{
	return XVECTOR2(-x, -y);
}

XVECTOR2 XVECTOR2::operator + (const XVECTOR2& other) const
{
	return XVECTOR2(x + other.x, y + other.y);
}
XVECTOR2 XVECTOR2::operator - (const XVECTOR2& other) const
{
	return XVECTOR2(x - other.x, y - other.y);
}
XVECTOR2 XVECTOR2::operator * (float times) const
{
	return XVECTOR2(x * times, y * times);
}
XVECTOR2 XVECTOR2::operator / (float times) const
{
	return XVECTOR2(x/times,y/times);
}

bool XVECTOR2::operator == (const XVECTOR2& other) const
{
	if (this->x==other.x&&this->y==other.y) return true;
	return false;
}
bool XVECTOR2::operator != (const XVECTOR2& other) const
{
	if (this->x != other.x&&this->y != other.y) return true;
	return false;
}
void XVECTOR2::Normalize()
{
	
	float v = sqrt((this->x * this->x)+ (this->y * this->y)); this->x = this->x / v; this->y = this->y / v;
}
float XVECTOR2::Length()
{
	return sqrt((this->x * this->x) + (this->y * this->y));
}
//////////////////VECTOR3
XVECTOR3::operator float* ()
{
	return &x;
}
XVECTOR3::operator const float* () const
{
	return &x;
}


XVECTOR3& XVECTOR3::operator += (const XVECTOR3& other)
{
	this->x = this->x + other.x; this->y = this->y + other.y; this->z = this->z + other.z; return *this;
}
XVECTOR3& XVECTOR3::operator -= (const XVECTOR3& other)
{
	this->x = this->x - other.x; this->y = this->y - other.y; this->z = this->z - other.z; return *this;

}
XVECTOR3& XVECTOR3::operator *= (float times)
{
	this->x = this->x * times; this->y = this->y * times; this->z = this->z * times; return *this;
}
XVECTOR3& XVECTOR3::operator /= (float times)
{
	this->x = this->x / times; this->y = this->y / times; this->z = this->z / times; return *this;

}

XVECTOR3 XVECTOR3::operator + () const
{
	return *this;
}
XVECTOR3 XVECTOR3::operator - () const
{
	return XVECTOR3(-x,-y,-z);
}

XVECTOR3 XVECTOR3::operator + (const XVECTOR3& other) const
{
	return XVECTOR3(x + other.x, y + other.y, z + other.z);
}

XVECTOR3 XVECTOR3::operator - (const XVECTOR3& other) const
{
	return XVECTOR3(x - other.x, y - other.y, z - other.z);
}
XVECTOR3 XVECTOR3::operator * (float times) const
{
	return XVECTOR3(x * times, y * times, z * times);
}
XVECTOR3 XVECTOR3::operator / (float times) const
{
	return XVECTOR3(x / times, y / times, z / times);
}

XVECTOR3 XVECTOR3::operator * (const XVECTOR3& other)
{
	this->x = this->x*other.x; this->y = this->y*other.y; this->z = this->z*other.z; return *this;
}


XVECTOR3 operator*(float times, const XVECTOR3 & other)
{
	return XVECTOR3(times*other.x,times*other.y,times*other.z);
}

bool XVECTOR3::operator == (const XVECTOR3& other) const
{
	if (this->x == other.x&&this->y == other.y&&this->z==other.z) return true;
	return false;
}
bool XVECTOR3::operator != (const XVECTOR3& other) const
{
	if (this->x != other.x&&this->y != other.y&&this->z != other.z) return true;
	return false;
}
void XVECTOR3::Normalize()
{
	float v = sqrt((this->x * this->x) + (this->y * this->y) + (this->z*this->z)); this->x = this->x / v; this->y = this->y / v; this->z = this->z / v;
}
float XVECTOR3::Length()
{
	return sqrt((this->x * this->x) + (this->y * this->y) + (this->z*this->z));
}

////////////MATRIX44

XMATRIX44& XMATRIX44::operator *= (const XMATRIX44& other)
{
	XMATRIX44 alfa;
	alfa.m11 = (m11*other.m11 + m12*other.m21 + m13*other.m31 + m14*other.m41);
	alfa.m12 = (m11*other.m12 + m12*other.m22 + m13*other.m32 + m14*other.m42);
	alfa.m13 = (m11*other.m13 + m12*other.m23 + m13*other.m33 + m14*other.m43);
	alfa.m14 = (m11*other.m14 + m12*other.m24 + m13*other.m34 + m14*other.m44);

	alfa.m21 = (m21*other.m11 + m22*other.m21 + m23*other.m31 + m24*other.m41);
	alfa.m22 = (m21*other.m12 + m22*other.m22 + m23*other.m32 + m24*other.m42);
	alfa.m23 = (m21*other.m13 + m22*other.m23 + m23*other.m33 + m24*other.m43);
	alfa.m24 = (m21*other.m14 + m22*other.m24 + m23*other.m34 + m24*other.m44);

	alfa.m31 = (m31*other.m11 + m32*other.m21 + m33*other.m31 + m34*other.m41);
	alfa.m32 = (m31*other.m12 + m32*other.m22 + m33*other.m32 + m34*other.m42);
	alfa.m33 = (m31*other.m13 + m32*other.m23 + m33*other.m33 + m34*other.m43);
	alfa.m34 = (m31*other.m14 + m32*other.m24 + m33*other.m34 + m34*other.m44);

	alfa.m41 = (m41*other.m11 + m42*other.m21 + m43*other.m31 + m44*other.m41);
	alfa.m42 = (m41*other.m12 + m42*other.m22 + m43*other.m32 + m44*other.m42);
	alfa.m43 = (m41*other.m13 + m42*other.m23 + m43*other.m33 + m44*other.m43);
	alfa.m44 = (m41*other.m14 + m42*other.m24 + m43*other.m34 + m44*other.m44);
	*this = alfa;
	return *this;

}
XMATRIX44& XMATRIX44::operator += (const XMATRIX44& other)
{
	m11 = m11 + other.m11; m12 = m12 + other.m12; m13 = m13 + other.m13; m14 = m14 + other.m14;
	m21 = m21 + other.m21; m22 = m22 + other.m22; m23 = m23 + other.m23; m24 = m24 + other.m24;
	m31 = m31 + other.m31; m32 = m32 + other.m32; m33 = m33 + other.m33; m34 = m34 + other.m34;
	m41 = m41 + other.m41; m42 = m42 + other.m42; m43 = m43 + other.m43; m44 = m44 + other.m44;
	return *this;
}
XMATRIX44& XMATRIX44::operator -= (const XMATRIX44& other)
{
	m11 = m11 - other.m11; m12 = m12 - other.m12; m13 = m13 - other.m13; m14 = m14 - other.m14;
	m21 = m21 - other.m21; m22 = m22 - other.m22; m23 = m23 - other.m23; m24 = m24 - other.m24;
	m31 = m31 - other.m31; m32 = m32 - other.m32; m33 = m33 - other.m33; m34 = m34 - other.m34;
	m41 = m41 - other.m41; m42 = m42 - other.m42; m43 = m43 - other.m43; m44 = m44 - other.m44;
	return *this;
}
XMATRIX44& XMATRIX44::operator *= (float times)
{
	m11 = m11 * times; m12 = m12 * times; m13 = m13 * times; m14 = m14 * times;
	m21 = m21 * times; m22 = m22 * times; m23 = m23 * times; m24 = m24 * times;
	m31 = m31 * times; m32 = m32 * times; m33 = m33 * times; m34 = m34 * times;
	m41 = m41 * times; m42 = m42 * times; m43 = m43 * times; m44 = m44 * times;
	return *this;
}
XMATRIX44& XMATRIX44::operator /= (float times)
{
	m11 = m11 / times; m12 = m12 / times; m13 = m13 / times; m14 = m14 / times;
	m21 = m21 / times; m22 = m22 / times; m23 = m23 / times; m24 = m24 / times;
	m31 = m31 / times; m32 = m32 / times; m33 = m33 / times; m34 = m34 / times;
	m41 = m41 / times; m42 = m42 / times; m43 = m43 / times; m44 = m44 / times;
	return *this;
}

XMATRIX44 XMATRIX44::operator + () const
{
	return *this;
}
XMATRIX44 XMATRIX44::operator - () const
{
	return XMATRIX44(
		-m11, -m12, -m13, -m14, 
		-m21, -m22, -m23, -m24, 
		-m31, -m32, -m33, -m34, 
		-m41, -m42, -m43, -m44);
}

XMATRIX44::operator float*()
{
	return  &m11;
}
XMATRIX44::operator const float* () const
{
	return  &m11;
}

XMATRIX44 XMATRIX44::operator * (const XMATRIX44& other) const
{
	XMATRIX44 alfa;
	alfa.m11 = (m11*other.m11 + m12*other.m21 + m13*other.m31 + m14*other.m41);
	alfa.m12 = (m11*other.m12 + m12*other.m22 + m13*other.m32 + m14*other.m42);
	alfa.m13 = (m11*other.m13 + m12*other.m23 + m13*other.m33 + m14*other.m43);
	alfa.m14 = (m11*other.m14 + m12*other.m24 + m13*other.m34 + m14*other.m44);

	alfa.m21 = (m21*other.m11 + m22*other.m21 + m23*other.m31 + m24*other.m41);
	alfa.m22 = (m21*other.m12 + m22*other.m22 + m23*other.m32 + m24*other.m42);
	alfa.m23 = (m21*other.m13 + m22*other.m23 + m23*other.m33 + m24*other.m43);
	alfa.m24 = (m21*other.m14 + m22*other.m24 + m23*other.m34 + m24*other.m44);

	alfa.m31 = (m31*other.m11 + m32*other.m21 + m33*other.m31 + m34*other.m41);
	alfa.m32 = (m31*other.m12 + m32*other.m22 + m33*other.m32 + m34*other.m42);
	alfa.m33 = (m31*other.m13 + m32*other.m23 + m33*other.m33 + m34*other.m43);
	alfa.m34 = (m31*other.m14 + m32*other.m24 + m33*other.m34 + m34*other.m44);

	alfa.m41 = (m41*other.m11 + m42*other.m21 + m43*other.m31 + m44*other.m41);
	alfa.m42 = (m41*other.m12 + m42*other.m22 + m43*other.m32 + m44*other.m42);
	alfa.m43 = (m41*other.m13 + m42*other.m23 + m43*other.m33 + m44*other.m43);
	alfa.m44 = (m41*other.m14 + m42*other.m24 + m43*other.m34 + m44*other.m44);
	return alfa;
}
XMATRIX44 XMATRIX44::operator + (const XMATRIX44& other) const
{
	return XMATRIX44(
		m11+other.m11, m12 + other.m12,m13 + other.m13,m14 + other.m14,
		m21+other.m21, m22 + other.m22,m23 + other.m23,m24 + other.m24,
		m31+other.m31, m32 + other.m32,m33 + other.m33,m34 + other.m34,
		m41+other.m41, m42 + other.m42,m43 + other.m43,m44 + other.m44);
}
XMATRIX44 XMATRIX44::operator - (const XMATRIX44& other) const
{
	return XMATRIX44(
		m11- other.m11, m12- other.m12, m13- other.m13, m14- other.m14,
		m21 -other.m21, m22 -other.m22, m23 -other.m23, m24 -other.m24,
		m31 -other.m31, m32 -other.m32, m33 -other.m33, m34 -other.m34,
		m41 -other.m41, m42 -other.m42, m43 -other.m43, m44 -other.m44);
}
XMATRIX44 XMATRIX44::operator * (float times) const
{
	return XMATRIX44(
		m11* times, m12 * times, m13* times, m14* times,
		m21 * times, m22 * times, m23* times, m24* times,
		m31 * times, m32 * times, m33* times, m34* times,
		m41 * times, m42 * times, m43* times, m44* times);
}
XMATRIX44 XMATRIX44::operator / (float times) const
{
	return XMATRIX44(
		m11/ times, m12 / times, m13/ times, m14/ times,
		m21 / times, m22 / times, m23/ times, m24/ times,
		m31 / times, m32 / times, m33/ times, m34/ times,
		m41 / times, m42 / times, m43/ times, m44/ times);
}

XMATRIX44 operator * (float times, const XMATRIX44& other)
{
	return XMATRIX44(
		other.m11 * times, other.m12 * times, other.m13 * times, other.m14 * times,
		other.m21 * times, other.m22 * times, other.m23 * times, other.m24 * times,
		other.m31 * times, other.m32 * times, other.m33 * times, other.m34 * times,
		other.m41 * times, other.m42 * times, other.m43 * times, other.m44 * times
	);
}

bool XMATRIX44::operator == (const XMATRIX44& other) const
{
	if (
	this->m11 == other.m11&& this->m12 == other.m12&& this->m13 == other.m13&& this->m14 == other.m14&
	this->m21 == other.m21&& this->m22 == other.m22&& this->m23 == other.m23&& this->m24 == other.m24&
	this->m31 == other.m31&& this->m32 == other.m32&& this->m33 == other.m33&& this->m34 == other.m34&
	this->m41 == other.m41&& this->m42 == other.m42&& this->m43 == other.m43&& this->m44 == other.m44
	)return true;
	return false;
}
bool XMATRIX44::operator != (const XMATRIX44& other) const
{
	if (
		this->m11 != other.m11&& this->m12 != other.m12&& this->m13 != other.m13&& this->m14 != other.m14&
		this->m21 != other.m21&& this->m22 != other.m22&& this->m23 != other.m23&& this->m24 != other.m24&
		this->m31 != other.m31&& this->m32 != other.m32&& this->m33 != other.m33&& this->m34 != other.m34&
		this->m41 != other.m41&& this->m42 != other.m42&& this->m43 != other.m43&& this->m44 != other.m44
		)return true;
	return false;
}

void XMATRIX44::Inverse(XMATRIX44 * o)
{
#if DOUBLE_FOR_INVERSE
	XMATRIX44_64 tmp64 = XMATRIX44_64(this);
	double det =
#else
	XMATRIX44 tmp64 = *this;
	float det =
#endif
		tmp64.m11*tmp64.m22*tmp64.m33*tmp64.m44 + tmp64.m11*tmp64.m23*tmp64.m34*tmp64.m42 + tmp64.m11*tmp64.m24*tmp64.m32*tmp64.m43
		+ tmp64.m12*tmp64.m21*tmp64.m34*tmp64.m43 + tmp64.m12*tmp64.m23*tmp64.m31*tmp64.m44 + tmp64.m12*tmp64.m24*tmp64.m33*tmp64.m41
		+ tmp64.m13*tmp64.m21*tmp64.m32*tmp64.m44 + tmp64.m13*tmp64.m22*tmp64.m34*tmp64.m41 + tmp64.m13*tmp64.m24*tmp64.m31*tmp64.m42
		+ tmp64.m14*tmp64.m21*tmp64.m33*tmp64.m42 + tmp64.m14*tmp64.m22*tmp64.m31*tmp64.m43 + tmp64.m14*tmp64.m23*tmp64.m32*tmp64.m41
		- tmp64.m11*tmp64.m22*tmp64.m34*tmp64.m43 - tmp64.m11*tmp64.m23*tmp64.m32*tmp64.m44 - tmp64.m11*tmp64.m24*tmp64.m33*tmp64.m42
		- tmp64.m12*tmp64.m21*tmp64.m33*tmp64.m44 - tmp64.m12*tmp64.m23*tmp64.m34*tmp64.m41 - tmp64.m12*tmp64.m24*tmp64.m31*tmp64.m43
		- tmp64.m13*tmp64.m21*tmp64.m34*tmp64.m42 - tmp64.m13*tmp64.m22*tmp64.m31*tmp64.m44 - tmp64.m13*tmp64.m24*tmp64.m32*tmp64.m41
		- tmp64.m14*tmp64.m21*tmp64.m32*tmp64.m43 - tmp64.m14*tmp64.m22*tmp64.m33*tmp64.m41 - tmp64.m14*tmp64.m23*tmp64.m31*tmp64.m42;
#if DOUBLE_FOR_INVERSE
	if (det == 0.0) {
#else
	if (det == 0.0f) {
#endif
		printf("\n\nThe Universe stopped, no det for Matrix, all ends here.\n\n");
		exit(666);
	}
#if DOUBLE_FOR_INVERSE
	det = 1.0 / det;
	XMATRIX44_64 out;
#else
	det = 1.0f / det;
	XMATRIX44 out;
#endif

	out.m11 = tmp64.m22*tmp64.m33*tmp64.m44 + tmp64.m23*tmp64.m34*tmp64.m42 + tmp64.m24*tmp64.m32*tmp64.m43 - tmp64.m22*tmp64.m34*tmp64.m43 - tmp64.m23*tmp64.m32*tmp64.m44 - tmp64.m24*tmp64.m33*tmp64.m42;
	out.m12 = tmp64.m12*tmp64.m34*tmp64.m43 + tmp64.m13*tmp64.m32*tmp64.m44 + tmp64.m14*tmp64.m33*tmp64.m42 - tmp64.m12*tmp64.m33*tmp64.m44 - tmp64.m13*tmp64.m34*tmp64.m42 - tmp64.m14*tmp64.m32*tmp64.m43;
	out.m13 = tmp64.m12*tmp64.m23*tmp64.m44 + tmp64.m13*tmp64.m24*tmp64.m42 + tmp64.m14*tmp64.m22*tmp64.m43 - tmp64.m12*tmp64.m24*tmp64.m43 - tmp64.m13*tmp64.m22*tmp64.m44 - tmp64.m14*tmp64.m23*tmp64.m42;
	out.m14 = tmp64.m12*tmp64.m24*tmp64.m33 + tmp64.m13*tmp64.m22*tmp64.m34 + tmp64.m14*tmp64.m23*tmp64.m32 - tmp64.m12*tmp64.m23*tmp64.m34 - tmp64.m13*tmp64.m24*tmp64.m32 - tmp64.m14*tmp64.m22*tmp64.m33;
	out.m21 = tmp64.m21*tmp64.m34*tmp64.m43 + tmp64.m23*tmp64.m31*tmp64.m44 + tmp64.m24*tmp64.m33*tmp64.m41 - tmp64.m21*tmp64.m33*tmp64.m44 - tmp64.m23*tmp64.m34*tmp64.m41 - tmp64.m24*tmp64.m31*tmp64.m43;
	out.m22 = tmp64.m11*tmp64.m33*tmp64.m44 + tmp64.m13*tmp64.m34*tmp64.m41 + tmp64.m14*tmp64.m31*tmp64.m43 - tmp64.m11*tmp64.m34*tmp64.m43 - tmp64.m13*tmp64.m31*tmp64.m44 - tmp64.m14*tmp64.m33*tmp64.m41;
	out.m23 = tmp64.m11*tmp64.m24*tmp64.m43 + tmp64.m13*tmp64.m21*tmp64.m44 + tmp64.m14*tmp64.m23*tmp64.m41 - tmp64.m11*tmp64.m23*tmp64.m44 - tmp64.m13*tmp64.m24*tmp64.m41 - tmp64.m14*tmp64.m21*tmp64.m43;
	out.m24 = tmp64.m11*tmp64.m23*tmp64.m34 + tmp64.m13*tmp64.m24*tmp64.m31 + tmp64.m14*tmp64.m21*tmp64.m33 - tmp64.m11*tmp64.m24*tmp64.m33 - tmp64.m13*tmp64.m21*tmp64.m34 - tmp64.m14*tmp64.m23*tmp64.m31;
	out.m31 = tmp64.m21*tmp64.m32*tmp64.m44 + tmp64.m22*tmp64.m34*tmp64.m41 + tmp64.m24*tmp64.m31*tmp64.m42 - tmp64.m21*tmp64.m34*tmp64.m42 - tmp64.m22*tmp64.m31*tmp64.m44 - tmp64.m24*tmp64.m32*tmp64.m41;
	out.m32 = tmp64.m11*tmp64.m34*tmp64.m42 + tmp64.m12*tmp64.m31*tmp64.m44 + tmp64.m14*tmp64.m32*tmp64.m41 - tmp64.m11*tmp64.m32*tmp64.m44 - tmp64.m12*tmp64.m34*tmp64.m41 - tmp64.m14*tmp64.m31*tmp64.m42;
	out.m33 = tmp64.m11*tmp64.m22*tmp64.m44 + tmp64.m12*tmp64.m24*tmp64.m41 + tmp64.m14*tmp64.m21*tmp64.m42 - tmp64.m11*tmp64.m24*tmp64.m42 - tmp64.m12*tmp64.m21*tmp64.m44 - tmp64.m14*tmp64.m22*tmp64.m41;
	out.m34 = tmp64.m11*tmp64.m24*tmp64.m32 + tmp64.m12*tmp64.m21*tmp64.m34 + tmp64.m14*tmp64.m22*tmp64.m31 - tmp64.m11*tmp64.m22*tmp64.m34 - tmp64.m12*tmp64.m24*tmp64.m31 - tmp64.m14*tmp64.m21*tmp64.m32;
	out.m41 = tmp64.m21*tmp64.m33*tmp64.m42 + tmp64.m22*tmp64.m31*tmp64.m43 + tmp64.m23*tmp64.m32*tmp64.m41 - tmp64.m21*tmp64.m32*tmp64.m43 - tmp64.m22*tmp64.m33*tmp64.m41 - tmp64.m23*tmp64.m31*tmp64.m42;
	out.m42 = tmp64.m11*tmp64.m32*tmp64.m43 + tmp64.m12*tmp64.m33*tmp64.m41 + tmp64.m13*tmp64.m31*tmp64.m42 - tmp64.m11*tmp64.m33*tmp64.m42 - tmp64.m12*tmp64.m31*tmp64.m43 - tmp64.m13*tmp64.m32*tmp64.m41;
	out.m43 = tmp64.m11*tmp64.m23*tmp64.m42 + tmp64.m12*tmp64.m21*tmp64.m43 + tmp64.m13*tmp64.m22*tmp64.m41 - tmp64.m11*tmp64.m22*tmp64.m43 - tmp64.m12*tmp64.m23*tmp64.m41 - tmp64.m13*tmp64.m21*tmp64.m42;
	out.m44 = tmp64.m11*tmp64.m22*tmp64.m33 + tmp64.m12*tmp64.m23*tmp64.m31 + tmp64.m13*tmp64.m21*tmp64.m32 - tmp64.m11*tmp64.m23*tmp64.m32 - tmp64.m12*tmp64.m21*tmp64.m33 - tmp64.m13*tmp64.m22*tmp64.m31;

	for (int i = 0; i < 16; i++) {
#if DOUBLE_FOR_INVERSE
		double val = det*out.mat[i];
		(*o).mat[i] = static_cast<float>(val);
#else
		(*o).mat[i] = det*out.mat[i];
#endif
	}
}