#include <IDVScene/IDVPrimitiveInstance.h>
#include <IDVMath.h>
void IDVPrimitiveInst::TranslateAbsolute(float x, float y, float z){
	XMatTranslation(Position, x, y, z);
	//D3DXMatrixTranslation(&Position, x, y, z);
}

void IDVPrimitiveInst::RotateXAbsolute(float ang) {
	RotationX.Identity();
	XMatRotationXLH(RotationX, Deg2Rad(ang));
	//D3DXMatrixRotationX(&RotationX, D3DXToRadian(ang));
}

void IDVPrimitiveInst::RotateYAbsolute(float ang) {
	RotationY.Identity();
	XMatRotationYLH(RotationY, Deg2Rad(ang));
	//D3DXMatrixRotationY(&RotationY, D3DXToRadian(ang));
}

void IDVPrimitiveInst::RotateZAbsolute(float ang) {
	RotationZ.Identity();
	XMatRotationZLH(RotationZ, Deg2Rad(ang));
	//D3DXMatrixRotationZ(&RotationZ, D3DXToRadian(ang));
}

void IDVPrimitiveInst::ScaleAbsolute(float sc) {
	Scale.Identity();
	XMatScaling(Scale, sc, sc, sc);
	//D3DXMatrixScaling(&Scale,sc,sc,sc);
}

void IDVPrimitiveInst::TranslateRelative(float x, float y, float z) {
	XMATRIX44 tmp;
	XMatTranslation(tmp, x, y, z);
	//D3DXMatrixTranslation(&tmp, x, y, z);
	Position *= tmp;
}

void IDVPrimitiveInst::RotateXRelative(float ang) {
	XMATRIX44 tmp;
	XMatRotationXLH(tmp, Deg2Rad(ang));
	//D3DXMatrixRotationX(&tmp, D3DXToRadian(ang));
	RotationX *= tmp;
}

void IDVPrimitiveInst::RotateYRelative(float ang) {
	XMATRIX44 tmp;
	XMatRotationYLH(tmp, Deg2Rad(ang));
	//D3DXMatrixRotationY(&tmp, D3DXToRadian(ang));
	RotationY *= tmp;
}

void IDVPrimitiveInst::RotateZRelative(float ang) {
	XMATRIX44 tmp;
	XMatRotationZLH(tmp, Deg2Rad(ang));
	//D3DXMatrixRotationZ(&tmp, D3DXToRadian(ang));
	RotationZ *= tmp;
}

void IDVPrimitiveInst::ScaleRelative(float sc) {
	XMATRIX44 tmp;
	XMatScaling(tmp, sc, sc, sc);
	//D3DXMatrixScaling(&tmp, sc, sc, sc);
	Scale *= tmp;
}

void IDVPrimitiveInst::Update() {
	Final = Scale*RotationX*RotationY*RotationZ*Position;
}

void IDVPrimitiveInst::Draw(){
	if (!Visible)
		return;
	pBase->Draw(&Final.m[0][0],&pViewProj->m[0][0]);
}

void IDVPrimitiveInst::SetSignature(unsigned int f){
	pBase->SetGlobalSignature(f);
}
