// author : Marc-Stefan Cassola
// started at 29.03.05

// composite
class VsMenu : public VsMenuElement
{
	list<VsMenuElement> *lstctMenuElements;
	
	// these functions are registered on the input manager
	void moveFunc(int iX, int iY);
	void lmbFunc(int iEvent);
	void rmbFunc(int iEvent);
	void mmbFunc(int iEvent);
	
	void keyDownFunc(int);
	void keyUpFunc(int);
	void keyLeftFunc(int);
	void keyRightFunc(int);
	
	void keyEnterFunc(int);
	void keyEscFunc(int);
	
	void draw();
};
