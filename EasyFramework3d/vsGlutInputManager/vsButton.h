// author : Marc-Stefan Cassola
// started at 29.03.05

#include "vsMenuElement.h"

// TODO : Template?

// composite : leaf
class VsButton : public VsMenuElement
{
	typedef void (*func)(void);
	func lmbFunc;
	func rmbFunc;
	func mmbFunc;
	void (*)(int iX1, int iY1, int iX2, int iY2, bool bLeftClicking, bool bMouseOver) drawFunc;
	
	VsButton(String strMenuText,
			 int iX1, int iY1, int iX2, int iY2,
			 lmbFunc, mmbFunc, rmbFunc, drawFunc);
	
	void lmbClicked() { lmbFunc(); }
	void mmbClicked() { mmbFunc(); }
	void rmbClicked() { rmbFunc(); }
	
	void draw() { drawFunc(iX1, iY1, iX2, iY2, bLeftClicking, bMouseOver); }
};
