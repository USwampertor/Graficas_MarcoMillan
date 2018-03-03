#ifndef IDV_TEST_APPLICATION
#define IDV_TEST_APPLICATION
#include <IDVMath.h>
#include <IDVBase/IDVCoreBase.h>
#include <IDVScene/IDVPrimitiveManager.h>
#include <IDVScene/IDVPrimitiveInstance.h>

class IDVTestApplication : public IDVBaseApplication {
public:
	IDVTestApplication() : IDVBaseApplication() {}
	void InitVars();
	void CreateAssets();
	void DestroyAssets();
	void OnUpdate();
	void OnDraw();
	void OnInput();

	PrimitiveManager *PrimitiveMgr;
	PrimitiveInst	 QuadInst;
	XMATRIX44 View;
	XMATRIX44 Projection;
	XMATRIX44 Camera;
};

#endif