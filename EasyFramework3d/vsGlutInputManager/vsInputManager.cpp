#include "vsInputManager.h"

namespace VsInputManager {

// dummies for unused func-pointers
inline static void emptyFunc(int) {}
inline static void emptyFunc2(int, int, int) {}

KeyFunc aKeyFuncs[300];
EventFunc aEventFuncs[50];
int iOldX, iOldY;

void initVsInputManager()
{
	for (int i = 0; i < 150; i++)
	{
		unregisterFunc(i | EVT_KEY_PRESS_DOWN);
		unregisterFunc(i | EVT_KEY_PRESS_UP);
		if (i < 50)
			unregisterFunc(i + 300);
	}
}

int getEvent(unsigned char ucKey)
{
	if ((ucKey >= 'a') and (ucKey <= 'z'))
		return EVT_KEY_A + (ucKey - 'a');

	if ((ucKey >= 'A') and (ucKey <= 'Z'))
		return EVT_KEY_A_UC + (ucKey - 'A');

	if ((ucKey >= '0') and (ucKey <= '9'))
		return EVT_KEY_0 + (ucKey - '0');
		
	switch (ucKey)
	{
		case 'ß' : return EVT_KEY_SS;
		case '´' : return EVT_KEY_ACCENT1;
		case '^' : return EVT_KEY_HAT;
		case  8  : return EVT_KEY_BACKSPACE;

		case '+' : return EVT_KEY_PLUS;
		case '#' : return EVT_KEY_SHARP;
		case '-' : return EVT_KEY_MINUS;
		case '.' : return EVT_KEY_DOT;
		case ',' : return EVT_KEY_COMMA;
		case '<' : return EVT_KEY_LESS;
		case  9  : return EVT_KEY_TAB;
		case '/' : return EVT_KEY_SLASH;
		case '*' : return EVT_KEY_ASTERIX;

		case ' ' : return EVT_KEY_SPACE;
		case 127 : return EVT_KEY_DEL;
		case  27 : return EVT_KEY_ESC;
		case  13 : return EVT_KEY_ENTER;
	
		case '\'' : return EVT_KEY_APOSTROPH;
		case '~' : return EVT_KEY_TILDE;
		case '`' : return EVT_KEY_ACCENT2;
		case '_' : return EVT_KEY_UNDERLINE;
		case ';' : return EVT_KEY_SEMICOLON;
		case ':' : return EVT_KEY_COLON;
		case '>' : return EVT_KEY_GREATER;
		case '|' : return EVT_KEY_OR;
		case '!' : return EVT_KEY_EXCLAMATION;
		case '"' : return EVT_KEY_QUOTATION;
		case '§' : return EVT_KEY_PARAGRAPH;
		case '$' : return EVT_KEY_DOLLAR;
		case '%' : return EVT_KEY_PROCENT;
		case '&' : return EVT_KEY_AND;
		case '(' : return EVT_KEY_BRACKET1_LEFT;
		case ')' : return EVT_KEY_BRACKET1_RIGHT;
		case '=' : return EVT_KEY_EQUAL;
		case '?' : return EVT_KEY_QUESTION;
		case '\\' : return EVT_KEY_BACKSLASH;
		case '[' : return EVT_KEY_BRACKET2_LEFT;
		case ']' : return EVT_KEY_BRACKET2_RIGHT;
		case '{' : return EVT_KEY_BRACKET3_LEFT;
		case '}' : return EVT_KEY_BRACKET3_RIGHT;
		case '°' : return EVT_KEY_DEGREE;
		// TODO : Exception werfen
		default : return -1;
	} 
}

void keyFunc(unsigned char ucKey, int x, int y)
{
	int iEvent = getEvent(ucKey);
	
	aKeyFuncs[iEvent](iEvent | EVT_KEY_PRESS_DOWN);

	aKeyFuncs[EVT_KEY_PRESSED](iEvent | EVT_KEY_PRESS_DOWN);
}

void keyUpFunc(unsigned char ucKey, int x, int y)
{
	int iEvent = getEvent(ucKey);
	
	aKeyFuncs[iEvent + 150](iEvent | EVT_KEY_PRESS_UP);
	
	aKeyFuncs[EVT_KEY_PRESSED + 150](iEvent | EVT_KEY_PRESS_UP);
}

void specialFunc(int iKey, int x, int y)
{
	int iEvent = getSpecialEvent(iKey);
	
	aKeyFuncs[iEvent](iEvent | EVT_KEY_PRESS_DOWN);
	
	aKeyFuncs[EVT_KEY_PRESSED](iEvent | EVT_KEY_PRESS_DOWN);
}

void specialUpFunc(int iKey, int x, int y)
{
	int iEvent = getSpecialEvent(iKey);
	
	aKeyFuncs[iEvent + 150](iEvent | EVT_KEY_PRESS_UP);
	
	aKeyFuncs[EVT_KEY_PRESSED + 150](iEvent | EVT_KEY_PRESS_UP);
}

void passiveMotionFunc(int x, int y)
{
	aEventFuncs[EVT_MOUSE_MOVED - 300](EVT_MOUSE_MOVED, x, y);
	
	// this func should call setMouseCursor
	aEventFuncs[EVT_MOUSE_MOVED_DELTA - 300](EVT_MOUSE_MOVED_DELTA, x - iOldX, y - iOldY);
}

void motionFunc(int x, int y)
{
	passiveMotionFunc(x, y);
}

int getSpecialEvent(int iKey)
{
	switch (iKey)
	{
		case GLUT_KEY_F1		: return EVT_KEY_F1;
		case GLUT_KEY_F2		: return EVT_KEY_F2;
		case GLUT_KEY_F3		: return EVT_KEY_F3;
		case GLUT_KEY_F4		: return EVT_KEY_F4;
		case GLUT_KEY_F5		: return EVT_KEY_F5;
		case GLUT_KEY_F6		: return EVT_KEY_F6;
		case GLUT_KEY_F7		: return EVT_KEY_F7;
		case GLUT_KEY_F8		: return EVT_KEY_F8;
		case GLUT_KEY_F9		: return EVT_KEY_F9;
		case GLUT_KEY_F10		: return EVT_KEY_F10;
		case GLUT_KEY_F11		: return EVT_KEY_F11;
		case GLUT_KEY_F12		: return EVT_KEY_F12;
		case GLUT_KEY_LEFT		: return EVT_KEY_LEFT;
		case GLUT_KEY_UP		: return EVT_KEY_UP;
		case GLUT_KEY_RIGHT		: return EVT_KEY_RIGHT;
		case GLUT_KEY_DOWN		: return EVT_KEY_DOWN;
		case GLUT_KEY_PAGE_UP	: return EVT_KEY_PAGE_UP;
		case GLUT_KEY_PAGE_DOWN	: return EVT_KEY_PAGE_DOWN;
		case GLUT_KEY_HOME		: return EVT_KEY_HOME;
		case GLUT_KEY_END		: return EVT_KEY_END;
		case GLUT_KEY_INSERT	: return EVT_KEY_INSERT;
		default					: break; // TODO Fehler!!!
	}
}

void mouseFunc(int iButton, int iState, int x, int y)
{
	int iEvent;
	switch (iButton)
	{
		case GLUT_LEFT_BUTTON 	: iEvent = EVT_LEFT_CLICKED;
								  break;
		case GLUT_RIGHT_BUTTON	: iEvent = EVT_RIGHT_CLICKED;
								  break;
		case GLUT_MIDDLE_BUTTON : iEvent = EVT_MIDDLE_CLICKED;
								  break;
	}
	
	if (iState == GLUT_DOWN)
	{
		aEventFuncs[iEvent - 300](iEvent | EVT_KEY_PRESS_DOWN, x, y);
	}
	else
	{
		aEventFuncs[iEvent - 300](iEvent | EVT_KEY_PRESS_UP, x, y);
	}
}

void registerKeyFunc(int iEvent, KeyFunc newKeyFunc)
{
	int iUD = 0;							// check an remove KEY_PRESS_UP/DOWN
	if (iEvent & EVT_KEY_PRESS_UP)
		iUD = EVT_KEY_PRESS_UP;
	else
		iUD = EVT_KEY_PRESS_DOWN;
		
	iEvent &= ~iUD;
	
	if (iUD == EVT_KEY_PRESS_DOWN)
		aKeyFuncs[iEvent] = newKeyFunc;
	else
		aKeyFuncs[iEvent + 150] = newKeyFunc;
	
	switch (iEvent)						// special or key func to register?
	{
		case EVT_KEY_UP : // no break
		case EVT_KEY_DOWN : // no break
		case EVT_KEY_LEFT : // no break
		case EVT_KEY_RIGHT : // no break
		case EVT_KEY_INSERT : // no break
		case EVT_KEY_HOME : // no break
		case EVT_KEY_END : // no break
		case EVT_KEY_PAGE_UP : // no break
		case EVT_KEY_PAGE_DOWN : // no break
		case EVT_KEY_F1 : // no break
		case EVT_KEY_F2 : // no break
		case EVT_KEY_F3 : // no break
		case EVT_KEY_F4 : // no break
		case EVT_KEY_F5 : // no break
		case EVT_KEY_F6 : // no break
		case EVT_KEY_F7 : // no break
		case EVT_KEY_F8 : // no break
		case EVT_KEY_F9 : // no break
		case EVT_KEY_F10 : // no break
		case EVT_KEY_F11 : // no break
		case EVT_KEY_F12 : if (iUD == EVT_KEY_PRESS_DOWN)
							   glutSpecialFunc(specialFunc);
						   else
						   	   glutSpecialUpFunc(specialUpFunc);
						   break;
		default : if (iUD == EVT_KEY_PRESS_DOWN)
					  glutKeyboardFunc(keyFunc);
				  else
				  	  glutKeyboardUpFunc(keyUpFunc);
	}
}

void registerFunc(int iEvent, EventFunc newEventFunc)
{
	int iUD = 0;							// check an remove KEY_PRESS_UP/DOWN
	if (iEvent & EVT_KEY_PRESS_UP)
		iUD = EVT_KEY_PRESS_UP;
	else
		iUD = EVT_KEY_PRESS_DOWN;
		
	iEvent &= ~iUD;
	
	aEventFuncs[iEvent - 300] = newEventFunc;
	
	switch (iEvent)
	{
		case EVT_MOUSE_MOVED_DELTA : // no break
		case EVT_MOUSE_MOVED : 	glutMotionFunc(motionFunc);
								glutPassiveMotionFunc(passiveMotionFunc);
								break;
		case EVT_LEFT_CLICKED : // no break
		case EVT_RIGHT_CLICKED : // no break
		case EVT_MIDDLE_CLICKED : 	glutMouseFunc(mouseFunc);
									break;
		case EVT_WHEEL_UP : break;	// no glutfunc yet
		case EVT_WHEEL_DOWN : break;
		
		// TODO : Joystick and other events
		default : break;	// TODO : Exception
	}
}

void unregisterFunc(int iEvent)
{
	int iUD = 0;							// check an remove KEY_PRESS_UP/DOWN
	if (iEvent & EVT_KEY_PRESS_UP)
		iUD = EVT_KEY_PRESS_UP;
	else
		iUD = EVT_KEY_PRESS_DOWN;
		
	iEvent &= ~iUD;
	
	if (iEvent < 300)
	{
		if (iUD == EVT_KEY_PRESS_DOWN)
			aKeyFuncs[iEvent] = emptyFunc;
		else
			aKeyFuncs[iEvent + 150] = emptyFunc;
	}
	else
		aEventFuncs[iEvent - 300] = emptyFunc2;
}

char *getEventString(int iEvent)			// TODO : Load strings from file
{
	int iUD = 0;							// check an remove KEY_PRESS_UP/DOWN
	if (iEvent & EVT_KEY_PRESS_UP)
		iUD = EVT_KEY_PRESS_UP;
	else
		iUD = EVT_KEY_PRESS_DOWN;
		
	iEvent &= ~iUD;
	switch (iEvent)
	{
		case EVT_KEY_PRESSED : return "key pressed";
		case EVT_MOUSE_MOVED_DELTA : return "mouse moved delta";
		case EVT_LEFT_CLICKED : return "left mouse button";
		case EVT_RIGHT_CLICKED : return "right mouse button";
		case EVT_MIDDLE_CLICKED : return "middle mouse button";
		case EVT_WHEEL_UP : return "mouse wheel up";
		case EVT_WHEEL_DOWN : return "mouse wheel down";
		case EVT_MOUSE_MOVED : return "mouse moved";
		
		case EVT_KEY_A : return "a";
		case EVT_KEY_B : return "b";
		case EVT_KEY_C : return "c";
		case EVT_KEY_D : return "d";
		case EVT_KEY_E : return "e";
		case EVT_KEY_F : return "f";
		case EVT_KEY_G : return "g";
		case EVT_KEY_H : return "h";
		case EVT_KEY_I : return "i";
		case EVT_KEY_J : return "j";
		case EVT_KEY_K : return "k";
		case EVT_KEY_L : return "l";
		case EVT_KEY_M : return "m";
		case EVT_KEY_N : return "n";
		case EVT_KEY_O : return "o";
		case EVT_KEY_P : return "p";
		case EVT_KEY_Q : return "q";
		case EVT_KEY_R : return "r";
		case EVT_KEY_S : return "s";
		case EVT_KEY_T : return "t";
		case EVT_KEY_U : return "u";
		case EVT_KEY_V : return "v";
		case EVT_KEY_W : return "w";
		case EVT_KEY_X : return "x";
		case EVT_KEY_Y : return "y";
		case EVT_KEY_Z : return "z";
	
		case EVT_KEY_0 : return "0";
		case EVT_KEY_1 : return "1";
		case EVT_KEY_2 : return "2";
		case EVT_KEY_3 : return "3";
		case EVT_KEY_4 : return "4";
		case EVT_KEY_5 : return "5";
		case EVT_KEY_6 : return "6";
		case EVT_KEY_7 : return "7";
		case EVT_KEY_8 : return "8";
		case EVT_KEY_9 : return "9";
		case EVT_KEY_SS : return "ß";
		case EVT_KEY_ACCENT1 : return "´";
		case EVT_KEY_HAT : return "^";
		case EVT_KEY_BACKSPACE : return "backspace";
	
		case EVT_KEY_PLUS : return "+";
		case EVT_KEY_SHARP : return "#";
		case EVT_KEY_MINUS : return "-";
		case EVT_KEY_DOT : return ".";
		case EVT_KEY_COMMA : return ",";
		case EVT_KEY_LESS : return "<";
		case EVT_KEY_TAB : return "tab";
		case EVT_KEY_SLASH : return "/";
		case EVT_KEY_ASTERIX : return "*";
	
		case EVT_KEY_SPACE : return " ";
		case EVT_KEY_UP : return "up";
		case EVT_KEY_DOWN : return "down";
		case EVT_KEY_LEFT : return "left";
		case EVT_KEY_RIGHT : return "right";
		case EVT_KEY_INSERT : return "insert";
		case EVT_KEY_DEL : return "del";
		case EVT_KEY_HOME : return "home";
		case EVT_KEY_END : return "end";
		case EVT_KEY_PAGE_UP : return "page up";
		case EVT_KEY_PAGE_DOWN : return "page down";
		case EVT_KEY_ESC : return "esc";
		case EVT_KEY_ENTER : return "enter";
		case EVT_KEY_F1 : return "f1";
		case EVT_KEY_F2 : return "f2";
		case EVT_KEY_F3 : return "f3";
		case EVT_KEY_F4 : return "f4";
		case EVT_KEY_F5 : return "f5";
		case EVT_KEY_F6 : return "f6";
		case EVT_KEY_F7 : return "f7";
		case EVT_KEY_F8 : return "f8";
		case EVT_KEY_F9 : return "f9";
		case EVT_KEY_F10 : return "f10";
		case EVT_KEY_F11 : return "f11";
		case EVT_KEY_F12 : return "f12";
		
		case EVT_KEY_APOSTROPH : return "'";
		case EVT_KEY_TILDE : return "~";
		case EVT_KEY_ACCENT2 : return "`";
		case EVT_KEY_UNDERLINE : return "_";
		case EVT_KEY_SEMICOLON : return ";";
		case EVT_KEY_COLON : return ":";
		case EVT_KEY_GREATER : return ">";
		case EVT_KEY_OR : return "|";
		case EVT_KEY_EXCLAMATION : return "!";
		case EVT_KEY_QUOTATION : return "\"";
		case EVT_KEY_PARAGRAPH : return "§";
		case EVT_KEY_DOLLAR : return "$";
		case EVT_KEY_PROCENT : return "%";
		case EVT_KEY_AND : return "&";
		case EVT_KEY_BRACKET1_LEFT : return "(";
		case EVT_KEY_BRACKET1_RIGHT : return ")";
		case EVT_KEY_EQUAL : return "=";
		case EVT_KEY_QUESTION : return "?";
		case EVT_KEY_BACKSLASH : return "\\";
		case EVT_KEY_BRACKET2_LEFT : return "[";
		case EVT_KEY_BRACKET2_RIGHT : return "]";
		case EVT_KEY_BRACKET3_LEFT : return "{";
		case EVT_KEY_BRACKET3_RIGHT : return "}";
		case EVT_KEY_DEGREE : return "°";
		
		// uppercase characters
		case EVT_KEY_A_UC : return "A";
		case EVT_KEY_B_UC : return "B";
		case EVT_KEY_C_UC : return "C";
		case EVT_KEY_D_UC : return "D";
		case EVT_KEY_E_UC : return "E";
		case EVT_KEY_F_UC : return "F";
		case EVT_KEY_G_UC : return "G";
		case EVT_KEY_H_UC : return "H";
		case EVT_KEY_I_UC : return "I";
		case EVT_KEY_J_UC : return "J";
		case EVT_KEY_K_UC : return "K";
		case EVT_KEY_L_UC : return "L";
		case EVT_KEY_M_UC : return "M";
		case EVT_KEY_N_UC : return "N";
		case EVT_KEY_O_UC : return "O";
		case EVT_KEY_P_UC : return "P";
		case EVT_KEY_Q_UC : return "Q";
		case EVT_KEY_R_UC : return "R";
		case EVT_KEY_S_UC : return "S";
		case EVT_KEY_T_UC : return "T";
		case EVT_KEY_U_UC : return "U";
		case EVT_KEY_V_UC : return "V";
		case EVT_KEY_W_UC : return "W";
		case EVT_KEY_X_UC : return "X";
		case EVT_KEY_Y_UC : return "Y";
		case EVT_KEY_Z_UC : return "Z";
	
		case EVT_KEY_PRESS_DOWN : return "key press down";		// | together with key-event when a key is pressed
		case EVT_KEY_PRESS_UP : return "key press up";			// | together with key-event when a key is released
		
		// TODO : Joystick and other events (have to be > 300)
		default : break; // TODO : Exception
	}
}

void setMouseCursorPos(int x, int y)
{
	glutWarpPointer(x, y);
}

} // end namespace
