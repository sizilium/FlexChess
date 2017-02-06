#include <gl/openglut.h>

#ifndef VS_INPUT_MANAGER
#define VS_INPUT_MANAGER
// no class becuase of glut function pointer types

namespace VsInputManager {

// TODO : Vielleicht template, weil funktionszeiger brauchen Klassenname dazu.

extern int iJoyPollInterval;

typedef void (*KeyFunc)(int iKey);		
extern KeyFunc aKeyFuncs[300];					// only one function per event allowed
												// first 150 for key down, last 150 for key up

typedef void (*EventFunc)(int iEvent, int x, int y);
extern EventFunc aEventFuncs[50];				// functions for mouse movement and other events

extern int iOldX, iOldY;						// previous mouse coordinates

void initVsInputManager();

// get event from GLUT special key constant
int getSpecialEvent(int iKey);

// register a function, which shall be called if event occurs
void registerKeyFunc(int iEvent, KeyFunc );
void registerFunc(int iEvent, EventFunc );

void unregisterFunc(int iEvent);

// functions passed as callback fundtions to GLUT
void keyFunc(unsigned char ucKey, int x, int y);
void specialFunc(int iKey, int x, int y);
void mouseFunc(int iButton, int iState, int x, int y);
void motionFunc(int x, int y);
void passiveMotionFunc(int x, int y);
void keyUpFunc(unsigned char ucKey, int x, int y);
void specialUpFunc(int iKey, int x, int y);

// get event from char
int getEvent(unsigned char ucKey);
// get string for event
char *getEventString(const int ciEvent);

// sets mouse cursor to the specified coordinates
// to use with mouse delta event because otherweise there won't be a delta because mouse is at the border
void setMouseCursorPos(int x, int y);

// event constants
const int EVT_KEY_PRESSED = 1;
const int EVT_MOUSE_MOVED_DELTA = 301;	// passes the delta x and delta y values
const int EVT_LEFT_CLICKED = 302;
const int EVT_RIGHT_CLICKED = 303;
const int EVT_MIDDLE_CLICKED = 304;
const int EVT_WHEEL_UP = 305;
const int EVT_WHEEL_DOWN = 306;
const int EVT_MOUSE_MOVED = 307;

const int EVT_KEY_A = 8;
const int EVT_KEY_B = 9;
const int EVT_KEY_C = 10;
const int EVT_KEY_D = 11;
const int EVT_KEY_E = 12;
const int EVT_KEY_F = 13;
const int EVT_KEY_G = 14;
const int EVT_KEY_H = 15;
const int EVT_KEY_I = 16;
const int EVT_KEY_J = 17;
const int EVT_KEY_K = 18;
const int EVT_KEY_L = 19;
const int EVT_KEY_M = 20;
const int EVT_KEY_N = 21;
const int EVT_KEY_O = 22;
const int EVT_KEY_P = 23;
const int EVT_KEY_Q = 24;
const int EVT_KEY_R = 25;
const int EVT_KEY_S = 26;
const int EVT_KEY_T = 27;
const int EVT_KEY_U = 28;
const int EVT_KEY_V = 29;
const int EVT_KEY_W = 30;
const int EVT_KEY_X = 31;
const int EVT_KEY_Y = 32;
const int EVT_KEY_Z = 33;

const int EVT_KEY_0 = 34;
const int EVT_KEY_1 = 35;
const int EVT_KEY_2 = 36;
const int EVT_KEY_3 = 37;
const int EVT_KEY_4 = 38;
const int EVT_KEY_5 = 39;
const int EVT_KEY_6 = 40;
const int EVT_KEY_7 = 41;
const int EVT_KEY_8 = 42;
const int EVT_KEY_9 = 43;
const int EVT_KEY_SS = 44;
const int EVT_KEY_ACCENT1 = 45;			// ´
const int EVT_KEY_HAT = 46;				// ^
const int EVT_KEY_BACKSPACE = 47;

const int EVT_KEY_PLUS = 48;
const int EVT_KEY_SHARP = 49;
const int EVT_KEY_MINUS = 50;
const int EVT_KEY_DOT = 51;
const int EVT_KEY_COMMA = 52;
const int EVT_KEY_LESS = 53;
const int EVT_KEY_TAB = 54;
const int EVT_KEY_SLASH = 55;
const int EVT_KEY_ASTERIX = 56;

const int EVT_KEY_SPACE = 57;
const int EVT_KEY_UP = 58;
const int EVT_KEY_DOWN = 59;
const int EVT_KEY_LEFT = 60;
const int EVT_KEY_RIGHT = 61;
const int EVT_KEY_INSERT = 62;
const int EVT_KEY_DEL = 63;
const int EVT_KEY_HOME = 64;
const int EVT_KEY_END = 65;
const int EVT_KEY_PAGE_UP = 66;
const int EVT_KEY_PAGE_DOWN = 67;
const int EVT_KEY_ESC = 68;
const int EVT_KEY_ENTER = 69;
const int EVT_KEY_F1 = 70;
const int EVT_KEY_F2 = 71;
const int EVT_KEY_F3 = 72;
const int EVT_KEY_F4 = 73;
const int EVT_KEY_F5 = 74;
const int EVT_KEY_F6 = 75;
const int EVT_KEY_F7 = 76;
const int EVT_KEY_F8 = 77;
const int EVT_KEY_F9 = 78;
const int EVT_KEY_F10 = 79;
const int EVT_KEY_F11 = 80;
const int EVT_KEY_F12 = 81;

const int EVT_KEY_APOSTROPH = 82;
const int EVT_KEY_TILDE = 83;			// ~
const int EVT_KEY_ACCENT2 = 84;			// `
const int EVT_KEY_UNDERLINE = 85;
const int EVT_KEY_SEMICOLON = 86;
const int EVT_KEY_COLON = 87;
const int EVT_KEY_GREATER = 88;
const int EVT_KEY_OR = 89;				// |
const int EVT_KEY_EXCLAMATION = 90;
const int EVT_KEY_QUOTATION = 91;
const int EVT_KEY_PARAGRAPH = 92;
const int EVT_KEY_DOLLAR = 93;
const int EVT_KEY_PROCENT = 94;
const int EVT_KEY_AND = 95;				// &
const int EVT_KEY_BRACKET1_LEFT = 96;	// (
const int EVT_KEY_BRACKET1_RIGHT = 97;	// )
const int EVT_KEY_EQUAL = 98;
const int EVT_KEY_QUESTION = 99;
const int EVT_KEY_BACKSLASH = 100;
const int EVT_KEY_BRACKET2_LEFT = 101;	// [
const int EVT_KEY_BRACKET2_RIGHT = 102;	// ]
const int EVT_KEY_BRACKET3_LEFT = 103;	// {
const int EVT_KEY_BRACKET3_RIGHT = 104;	// }
const int EVT_KEY_DEGREE = 105;			// °

// uppercase characters
const int EVT_KEY_A_UC = 106;
const int EVT_KEY_B_UC = 107;
const int EVT_KEY_C_UC = 108;
const int EVT_KEY_D_UC = 109;
const int EVT_KEY_E_UC = 110;
const int EVT_KEY_F_UC = 111;
const int EVT_KEY_G_UC = 112;
const int EVT_KEY_H_UC = 113;
const int EVT_KEY_I_UC = 114;
const int EVT_KEY_J_UC = 115;
const int EVT_KEY_K_UC = 116;
const int EVT_KEY_L_UC = 117;
const int EVT_KEY_M_UC = 118;
const int EVT_KEY_N_UC = 119;
const int EVT_KEY_O_UC = 120;
const int EVT_KEY_P_UC = 121;
const int EVT_KEY_Q_UC = 122;
const int EVT_KEY_R_UC = 123;
const int EVT_KEY_S_UC = 124;
const int EVT_KEY_T_UC = 125;
const int EVT_KEY_U_UC = 126;
const int EVT_KEY_V_UC = 127;
const int EVT_KEY_W_UC = 128;
const int EVT_KEY_X_UC = 129;
const int EVT_KEY_Y_UC = 130;
const int EVT_KEY_Z_UC = 131;

const int EVT_KEY_PRESS_DOWN = 0x4000;		// | together with key-event when a key is pressed
const int EVT_KEY_PRESS_UP = 0x8000;			// | together with key-event when a key is released

// TODO : Joystick and other events

// functions passed as callback fundtions to GLUT
void keyFunc(unsigned char ucKey, int x, int y);
void specialFunc(int iKey, int x, int y);
void mouseFunc(int iButton, int iState, int x, int y);
void motionFunc(int x, int y);
void passiveMotionFunc(int x, int y);
void keyUpFunc(unsigned char ucKey, int x, int y);
void specialUpFunc(int iKey, int x, int y);

} // end namespace

#endif
