// author : Marc-Stefan Cassola
// startet at 29.03.05

#include <vsInputManager>

// composite : element
class VsMenuElement
{
	int iX1, iY1, iX2, iY2;			// coordinates of ll and ur
	bool bMouseOver;				// true when mouse cursor is over this menu element
	bool bLeftClicking;				// true while left mouse button is beeing held down over this menu el.
	bool bMiddleClicking;			// true while left mouse button is beeing held down over this menu el.
	bool bRightClicking;			// true while left mouse button is beeing held down over this menu el.
	String strMenuText;
	
	VsMenuElement(String strMenuText, int iX1, int iY1, int iX2, int iY2);
	
	int *getCoords1() const;
	int *getCoords2() const;
	bool getMouseOver() const;
	String getName() const;
	bool getLeftClicking() const;
	bool getMiddleClicking() const;
	bool getRightClicking() const;
	
	////////////////////////////// left mouse button -----------------------------------
	void lmbDown()
	{
		bLeftClicking = true;
		lmbClicking();
	}
	void lmbUp()
	{
		bLeftClicking = false;
		lmbClicked;
	}
	
	// schablonenmethoden TODO : engl!
	void lmbClicking() = 0; 		// overwrite these for the action to be performed when the left
	void lmbClicked() = 0;			// mouse button is beeing pressed and is released over thie menu el.
	
	////////////////////////////// right mouse button -----------------------------------
	void rmbDown()
	{
		bRightClicking = true;
		rmbClicking();
	}
	void rmbUp()
	{
		bRightClicking = false;
		rmbClicked;
	}
	
	// schablonenmethoden TODO : engl!
	void rmbClicking() = 0; 		// overwrite these for the action to be performed when the Right
	void rmbClicked() = 0;			// mouse button is beeing pressed and is released over thie menu el.

	////////////////////////////// middle mouse button -----------------------------------
	void mmbDown()
	{
		bMiddleClicking = true;
		mmbClicking();
	}
	void mmbUp()
	{
		bLeftClicking = false;
		mmbClicked;
	}
	
	// schablonenmethoden TODO : engl!
	void mmbClicking() = 0; 		// overwrite these for the action to be performed when the left
	void mmbClicked() = 0;			// mouse button is beeing pressed and is released over thie menu el.
	
	void setMouseOver(bool bMouse) { bMouseOver = bMouse; }
	
	void draw() = 0;
};
