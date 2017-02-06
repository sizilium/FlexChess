#define ISSERVER false
#define MOUSE

// OpenGLUT input manager class
// Author: Marc-Stefan Cassola
// Project startet on 25.03.2005

#include <GL/openglut.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <nl.h>
#include <cassert>
#include "vsglm.h"

#if defined WIN32 || defined WIN64
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define sleep(x)    Sleep(1000 * (x))
#endif

#define USE_OPENAL

#ifdef USE_OPENAL			// if sound shold be supportet define USE_OPENAL
#include <al/alut.h>
#include <al/al.h>
#endif

#include "vsInputManager.h"

using namespace std;

#define MAX_FIELD 300
#define HOUSE_NUM ((int)((((float)MAX_FIELD / 500) * ((float)MAX_FIELD / 500)) * 700))
#define MAX_HEIGHT 10.0f
#define MIN_HEIGHT 7.0f
#define TYPE_NUM 2
#define MAX_HOUSE_DIM 20.0f
#define MIN_HOUSE_DIM 8.0f
#define MAX_BULLETS 100
#define BULLET_SPEED 60.0f
#define MAX_SPLASHS (MAX_BULLETS/10)
#define DEBREE_NUM 70
#define DEBREE_SPEED 25.0f
#define MAX_SPLASH_AGE 0.4f
#define BULLET_HEIGHT 0.5f
#define BORDER_WIDTH 2.0f
#define BORDER_HEIGHT (MIN_HEIGHT - 1)
#define PLAYER_SIZE 0.5
#define PLAYER_SIZE_SQR 0.24

#define SCHROT_NUM 6
#define MAX_SCHROT_ANGLE 0.3f
#define SCHROT_FIRE_RATE 0.5

#define X_VIEW 70.0f
#define Y_VIEW 60.0f

#define TEX_NUM 2

#define MAX_PLAYERS 64
#define PLAYER_STRENGTH 5

#define MSG_BULLET 0
#define MSG_PLAYER 1
#define MSG_BALL 2
#define MSG_HIT 3

#define BALL_SIZE_SQR 0.25
#define BALL_SIZE 50
#define BALL_SPEED 30.0f

int window;

float speed = 30.0f;	// speed in gl-units per second

float mx, my;		// mouse pos
float px, py;		// players pos
float dpx, dpy, dpx2, dpy2;		// delta values for movement
char health = PLAYER_STRENGTH;
short team;
bool myball = false;

struct player {
	bool exist;
	float x, y;
	float dx, dy;
	float dx2, dy2;
	float speed;
	char health;
	short team;
	bool ball;
};

int bulletcounter = 0;

struct tball {
	float x, y;
	float dx, dy;
	short owner;
};

tball ball;

struct bullet {
	bool exist;
	float x, y;
	float dx, dy;
	int player;
	float speed;
};

int splashcounter = 0;

struct splash {
	float color[3];
	float x[DEBREE_NUM];
	float y[DEBREE_NUM];
	float z[DEBREE_NUM];
	bool exist;
	float age;
	float dx[DEBREE_NUM];
	float dy[DEBREE_NUM];
	float dz[DEBREE_NUM];
};

splash *splashs = new splash[MAX_SPLASHS];

bullet *bullets = new bullet[MAX_BULLETS];

player *players = new player[MAX_PLAYERS];

double frametime;	// time since last frame in seconds
double time1 = 0;
double time2 = 0;
double framecounter = 0;

double schrotTime = 0;

int changed = 0;

int scrh, scrw;		// height and width of screen

struct house {
	float x1, y1, x2, y2;
	float height;
	char type;
};

GLuint uiTexObjects1[TEX_NUM];
GLuint uiTexObjects2[TEX_NUM];
GLuint uiDisplayLists[TYPE_NUM];
int iTexNum;
int iObjNum;

house *houses = new house[HOUSE_NUM];

#ifdef USE_OPENAL
ALuint buffers[2];
ALuint sources[MAX_SPLASHS+1];

ALfloat listenerPos[]={0.0, 0.0, 50.0};
ALfloat listenerVel[]={0.0, 0.0, 0.0};
ALfloat listenerOri[]={0.0, 0.0, -1.0,
					   0.0, 1.0, 0.0}; // “at”, then “up”
#endif

NLboolean   isserver = ISSERVER;
NLsocket    serversock;
NLsocket    clientsock;
NLint       clientnum = 0;
NLsocket    client[MAX_PLAYERS];
NLint		clientNum;


float myRand();
void networkClient(NLsocket);
void networkServer(NLsocket);
void networkWrite(int, int, int);
void networkRead(NLbyte);
void initPlayer();
bool checkBallCollision();

void end(int)
{
	delete [] splashs;
	delete [] bullets;
	delete [] houses;
#ifdef USE_OPENAL
	alDeleteSources(1 + MAX_SPLASHS, sources);
	alDeleteBuffers(2, buffers);
	alutExit();
#endif
	glDeleteLists(uiDisplayLists[0], iObjNum);	
	glDeleteLists(uiDisplayLists[1], iObjNum);	
	glDeleteTextures(iTexNum, uiTexObjects1);
	glDeleteTextures(iTexNum, uiTexObjects2);

	if (isserver)
	{
		for (int i = 0; i < clientnum; i++)
		{
			nlClose(client[i]);
		}
		nlClose(serversock);
	}
	else
		nlClose(clientsock);
		
	nlShutdown();
	glutDestroyWindow(window);
}

void click(int event, int x, int y)
{
	if (event | VsInputManager::EVT_KEY_PRESS_DOWN)
	{
		mx = x; my = y;
		int dx = x - (scrw / 2);
		int dy = (scrh / 2) - y;
		float length = sqrt(dx*dx + dy*dy);
		bullets[bulletcounter].dx = dx/length * BULLET_SPEED;
		bullets[bulletcounter].dy = dy/length * BULLET_SPEED;
		bullets[bulletcounter].x = px + (dx/length) * (PLAYER_SIZE + 0.01f);
		bullets[bulletcounter].y = py + (dy/length) * (PLAYER_SIZE + 0.01f);
		bullets[bulletcounter].exist = true;
		bullets[bulletcounter].speed = BULLET_SPEED;
		
		networkWrite(MSG_BULLET, bulletcounter, clientNum);
		
		++bulletcounter %= MAX_BULLETS;

#ifdef USE_OPENAL
		alSource3f(sources[0], AL_POSITION, px, py, BULLET_HEIGHT);
		alSourceStop(sources[0]);
		alSourceRewind(sources[0]);
		alSourcePlay(sources[0]);
#endif
	}
}

void rightClick(int event, int x, int y)
{
	if ((schrotTime >= SCHROT_FIRE_RATE) && (event & VsInputManager::EVT_KEY_PRESS_DOWN))
	{
		schrotTime = 0;
		
		for (int i = 0; i < SCHROT_NUM; i++)
		{
			mx = x; my = y;
			int dx = x - (scrw / 2);
			int dy = (scrh / 2) - y;
			float length = sqrt(dx*dx + dy*dy);
			float angle = atan2(dy, dx) + myRand() * MAX_SCHROT_ANGLE - (MAX_SCHROT_ANGLE / 2);
			
			bullets[bulletcounter].dx = cos(angle) * BULLET_SPEED;
			bullets[bulletcounter].dy = sin(angle) * BULLET_SPEED;
			bullets[bulletcounter].x = px + (dx/length) * (PLAYER_SIZE + 0.01f);
			bullets[bulletcounter].y = py + (dy/length) * (PLAYER_SIZE + 0.01f);
			bullets[bulletcounter].exist = true;
			bullets[bulletcounter].speed = BULLET_SPEED;

			networkWrite(MSG_BULLET, bulletcounter, clientNum);
			
			++bulletcounter %= MAX_BULLETS;
		}
#ifdef USE_OPENAL
		alSource3f(sources[0], AL_POSITION, px, py, BULLET_HEIGHT);
		alSourceStop(sources[0]);
		alSourceRewind(sources[0]);
		alSourcePlay(sources[0]);
#endif
	}
}

void middleClick(int event, int x, int y)
{
	if (myball)
	{
		mx = x; my = y;
		int dx = x - (scrw / 2);
		int dy = (scrh / 2) - y;
		float length = sqrt(dx*dx + dy*dy);
		ball.dx = dx/length * BALL_SPEED;
		ball.dy = dy/length * BALL_SPEED;
		ball.x = px + (dx/length) * (2.05f);
		ball.y = py + (dy/length) * (2.05f);
		myball = false;
		
		networkWrite(MSG_BALL, 0, clientNum);
		
#ifdef USE_OPENAL
		alSource3f(sources[0], AL_POSITION, px, py, BULLET_HEIGHT);
		alSourceStop(sources[0]);
		alSourceRewind(sources[0]);
		alSourcePlay(sources[0]);
#endif
	}
}

inline void restart(int)
{
	initPlayer();
}

inline void keyup(int)
{
	dpy2 = speed;
}

inline void keydown(int)
{
	dpy2 = -speed;
}

inline void keyleft(int)
{
	dpx2 = -speed;
}

inline void keyright(int)
{
	dpx2 = speed;
}

inline void keyyrel(int)
{
	dpy2 = 0.0f;
	dpy = 0.0f;
}

inline void keyxrel(int)
{
	dpx2 = 0.0f;
	dpx = 0.0f;
}

inline void keypress(int)
{
	changed = 3;
}

static void resize(int w, int h)
{
	scrh = h; scrw = w;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

inline float myRand()
{
	return static_cast<float>(rand())/32767;
}

void initBall()
{
	if (isserver)
	{
		do {
			ball.x = myRand()*MAX_FIELD;
			ball.y = myRand()*MAX_FIELD;
		} while (checkBallCollision());
		ball.dx = ball.dy = 0.0f;
	}
	ball.owner = 255;
}

void initHouses()
{
	if (isserver)
	{
		for (int i = 0; i < HOUSE_NUM / 3; i++)
		{
			houses[i].height = myRand()*(MAX_HEIGHT-MIN_HEIGHT) + MIN_HEIGHT;
			houses[i].type = static_cast<char>(myRand()*TYPE_NUM);
	
			houses[i].x1 = floor(myRand() * MAX_FIELD / MAX_HOUSE_DIM) * MAX_HOUSE_DIM;
			houses[i].y1 = floor(myRand() * MAX_FIELD / MAX_HOUSE_DIM) * MAX_HOUSE_DIM;
			houses[i].x2 = houses[i].x1 + floor((myRand() * (MAX_HOUSE_DIM - MIN_HOUSE_DIM) + MIN_HOUSE_DIM) / MAX_HOUSE_DIM) * MAX_HOUSE_DIM;
			houses[i].y2 = houses[i].y1 + floor((myRand() * (MAX_HOUSE_DIM - MIN_HOUSE_DIM) + MIN_HOUSE_DIM) / MAX_HOUSE_DIM) * MAX_HOUSE_DIM;
		}
		bool valid;
		for (int i = HOUSE_NUM / 3; i < HOUSE_NUM; i++)
		{
			valid = false;
			houses[i].height = myRand()*(MAX_HEIGHT-MIN_HEIGHT) + MIN_HEIGHT;
			houses[i].type = static_cast<char>(myRand()*TYPE_NUM);
	
			houses[i].x1 = floor(myRand() * MAX_FIELD / 2) * 2;
			houses[i].y1 = floor(myRand() * MAX_FIELD / 2) * 2;
			houses[i].x2 = houses[i].x1 + floor((myRand() * (MAX_HOUSE_DIM - MIN_HOUSE_DIM) + MIN_HOUSE_DIM) / 2) * 2;
			houses[i].y2 = houses[i].y1 + floor((myRand() * (MAX_HOUSE_DIM - MIN_HOUSE_DIM) + MIN_HOUSE_DIM) / 2) * 2;
				
			while (!valid)		// if invalid house coordinates, move them randomly until they're valid
			{
				valid = true;
				for (int j = 0; j < i; j++)
				{
					bool inx1 = (houses[i].x1 >= houses[j].x1-10.0) && (houses[i].x1 <= houses[j].x2+10.0);
					bool inx2 = (houses[i].x2 >= houses[j].x1-10.0) && (houses[i].x2 <= houses[j].x2+10.0);
					bool iny1 = (houses[i].y1 >= houses[j].y1-10.0) && (houses[i].y1 <= houses[j].y2+10.0);
					bool iny2 = (houses[i].y2 >= houses[j].y1-10.0) && (houses[i].y2 <= houses[j].y2+10.0);
					
					bool eqx1 = fabs(houses[i].x1 - houses[j].x1) < 0.5;
					bool eqx2 = fabs(houses[i].x2 - houses[j].x2) < 0.5;
					bool eqy1 = fabs(houses[i].y1 - houses[j].y1) < 0.5;
					bool eqy2 = fabs(houses[i].y2 - houses[j].y2) < 0.5;
					
					// is this house hidden in another?
					if (inx1 && iny1 && inx2 && iny2)
					{
						float deltax = floor(myRand()*2.99)-1;
						float deltay = floor(myRand()*2.99)-1;
						deltax *= 10;
						deltay *= 10;
						valid = false;
						houses[i].x1 +=  deltax;
						houses[i].y1 +=  deltay;
						houses[i].x2 +=  deltax;
						houses[i].y2 +=  deltay;
						break;
					}
					// check if there are walls that share some field
					if ((inx1 || inx2) && (eqy1 || eqy2)) 
					{
						float deltay = floor(myRand()*2.99)-1;
						deltay *= 10;
						valid = false;
						houses[i].y1 +=  deltay;
						houses[i].y2 +=  deltay;
						break;
					}
					
					if ((iny1 || iny2) && (eqx1 || eqx2))
					{
						float deltax = floor(myRand()*2.99)-1;
						deltax *= 10;
						valid = false;
						houses[i].x1 +=  deltax;
						houses[i].x2 +=  deltax;
						break;
					}
				}
			}
		}
	}
	else					// client receives the house-data
	{
		NLbyte buffer[256];
		int i = 0;
		cout << "Receiving house data";
		while (i < HOUSE_NUM)
		{
			if (nlRead(clientsock, buffer, sizeof(buffer)) > 0)
			{
				if ((i % 10) == 0)
				{
					nlWrite(clientsock, "baaa", sizeof(short));
					cout << ".";
				}
				memcpy((void *)&(houses[i].x1), (void *)buffer, sizeof(float));
				memcpy((void *)&(houses[i].y1), (void *)(buffer + sizeof(float)), sizeof(float));
				memcpy((void *)&(houses[i].x2), (void *)(buffer + 2*sizeof(float)), sizeof(float));
				memcpy((void *)&(houses[i].y2), (void *)(buffer + 3*sizeof(float)), sizeof(float));
				memcpy((void *)&(houses[i].height), (void *)(buffer + 4*sizeof(float)), sizeof(float));
				memcpy((void *)&(houses[i].type), (void *)(buffer + 5*sizeof(float)), sizeof(char));
				
				i++;
			}
		}
		cout << " Done." << endl;
	}
	
	// borders-------
	// north
	houses[0].height = BORDER_HEIGHT;
	houses[0].x1 = -BORDER_WIDTH;
	houses[0].y1 = MAX_FIELD;
	houses[0].x2 = MAX_FIELD+BORDER_WIDTH;
	houses[0].y2 = MAX_FIELD+BORDER_WIDTH;

	// south
	houses[1].type = houses[0].type;
	houses[1].height = BORDER_HEIGHT;
	houses[1].x1 = -BORDER_WIDTH;
	houses[1].y1 = -BORDER_WIDTH;
	houses[1].x2 = MAX_FIELD+BORDER_WIDTH;
	houses[1].y2 = 0.0f;

	// west
	houses[2].type = houses[0].type;
	houses[2].height = BORDER_HEIGHT;
	houses[2].x1 = -BORDER_WIDTH;
	houses[2].y1 = -BORDER_WIDTH;
	houses[2].x2 = 0.0f;
	houses[2].y2 = MAX_FIELD+BORDER_WIDTH;

	// east
	houses[3].type = houses[0].type;
	houses[3].height = BORDER_HEIGHT;
	houses[3].x1 = MAX_FIELD;
	houses[3].y1 = -BORDER_WIDTH;
	houses[3].x2 = MAX_FIELD+BORDER_WIDTH;
	houses[3].y2 = MAX_FIELD+BORDER_WIDTH;
}

void drawHouse(house &h)
{
/*	float colmod = static_cast<float>(h.type) / (2*TYPE_NUM);
	glBegin(GL_QUADS);
		glColor3f(0.5f - colmod, 0.2f + colmod / 2, 0.2f + colmod);	// top
		glVertex3f(h.x1, h.y1, h.height);
		glVertex3f(h.x2, h.y1, h.height);
		glVertex3f(h.x2, h.y2, h.height);
		glVertex3f(h.x1, h.y2, h.height);
		
		glColor3f(0.1f + colmod, 0.7f - colmod, 0.3f + colmod / 4);
		
		glVertex3f(h.x1, h.y1, 0.0f);		// west
		glVertex3f(h.x1, h.y1, h.height);
		glVertex3f(h.x1, h.y2, h.height);
		glVertex3f(h.x1, h.y2, 0.0f);

		glVertex3f(h.x2, h.y1, 0.0f);		// east
		glVertex3f(h.x2, h.y2, 0.0f);
		glVertex3f(h.x2, h.y2, h.height);
		glVertex3f(h.x2, h.y1, h.height);

		glVertex3f(h.x1, h.y2, 0.0f);		// north
		glVertex3f(h.x1, h.y2, h.height);
		glVertex3f(h.x2, h.y2, h.height);
		glVertex3f(h.x2, h.y2, 0.0f);

		glVertex3f(h.x1, h.y1, 0.0f);		// south
		glVertex3f(h.x2, h.y1, 0.0f);
		glVertex3f(h.x2, h.y1, h.height);
		glVertex3f(h.x1, h.y1, h.height);
	glEnd();*/
	
	glPushMatrix();
	
	glTranslatef((h.x1+h.x2) / 2, (h.y1+h.y2) / 2, 0.0f);
	glScalef(h.x2-h.x1, h.y2-h.y1, h.height);
	for (int i = 0; i < iObjNum; i++)
		glCallList(uiDisplayLists[h.type] + i);
		
	glPopMatrix();
}

void drawHouses()
{
	for (int i = 4; i < HOUSE_NUM; i++)
	{
		if ((fabs(houses[i].x1 - px) <= X_VIEW) and (fabs(houses[i].y1 - py) <= Y_VIEW))
			drawHouse(houses[i]);
	}
	// draw borders
	if (px <= X_VIEW)
		drawHouse(houses[2]);
	else
	if (px >= (MAX_FIELD - X_VIEW))
		drawHouse(houses[3]);
	if (py <= Y_VIEW)
		drawHouse(houses[1]);
	else
	if (py >= (MAX_FIELD - Y_VIEW))
		drawHouse(houses[0]);
}

void drawPlayers()
{
	// draw computers
	// draw other players
	
	// draw player
	glPushMatrix();
	
	glTranslatef(px, py, 0.0f);
	
	if (myball)
		glColor3f(1.0f, 0.9f, 0.9f);
	else
		glColor3f(1.0f, 0.5f, 0.5f);
	
	glBegin(GL_LINES);	// draw
		glVertex3f(-PLAYER_SIZE, -PLAYER_SIZE, 0.1f);
		glVertex3f(PLAYER_SIZE, PLAYER_SIZE, 0.1f);
		
		glVertex3f(PLAYER_SIZE, -PLAYER_SIZE, 0.1f);
		glVertex3f(-PLAYER_SIZE, PLAYER_SIZE, 0.1f);
		
		// direction indicator for ball
		
		float length = sqrt((ball.x-px) * (ball.x-px) + (ball.y-py) * (ball.y-py));
		
		glVertex3f((ball.x-px)/length, (ball.y-py)/length, 0.1f);
		glVertex3f((ball.x-px)/(length * 0.6), (ball.y-py)/(length * 0.6), 0.1f);
		
	glEnd();
	
	glPopMatrix();
	
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (players[i].exist)
		{
			players[i].x += players[i].dx * frametime;
			players[i].y += players[i].dy * frametime;
			
			glPushMatrix();
			
			glTranslatef(players[i].x, players[i].y, 0.0f);
			
			glColor3f(0.5f, 1.0f, 0.5f);
			glBegin(GL_LINES);	// draw
				glVertex3f(-PLAYER_SIZE, -PLAYER_SIZE, 0.1f);
				glVertex3f(PLAYER_SIZE, PLAYER_SIZE, 0.1f);
				
				glVertex3f(PLAYER_SIZE, -PLAYER_SIZE, 0.1f);
				glVertex3f(-PLAYER_SIZE, PLAYER_SIZE, 0.1f);
			glEnd();
			
			glPopMatrix();
		}
	}
}

void drawBullets()
{
	glColor3f(1.0f, 1.0f, 0.5f);
	glBegin(GL_LINES);
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		if (bullets[i].exist) {
			glVertex3f(bullets[i].x, bullets[i].y, BULLET_HEIGHT);
			glVertex3f(bullets[i].x + bullets[i].dx / BULLET_SPEED / 2, bullets[i].y + bullets[i].dy / BULLET_SPEED / 2, BULLET_HEIGHT);
		}
	}
	glEnd();
}

void drawSplashs()
{
	glPushMatrix();
	
	glBegin(GL_POINTS);
	for (int i = 0; i < MAX_SPLASHS; i++)
	{
		if (splashs[i].exist)
		{
			splashs[i].age += frametime;
			if (splashs[i].age > MAX_SPLASH_AGE)
				splashs[i].exist = false;
				
			for (int j = 0; j < DEBREE_NUM; j++)
			{
				 
				splashs[i].dz[j] -= frametime;
				
				splashs[i].x[j] += splashs[i].dx[j] * frametime;
				splashs[i].y[j] += splashs[i].dy[j] * frametime;
				splashs[i].z[j] += splashs[i].dz[j] * frametime;
				if (splashs[i].z[j] < 0.0f)
				{
					splashs[i].dz[j] = -splashs[i].dz[j] / 1.2f;
					
				}
				glColor3fv(splashs[i].color);
					
				glVertex3f(splashs[i].x[j], splashs[i].y[j], splashs[i].z[j]);
			}
		}
	}
	glEnd();
	
	glPopMatrix();
}

void createSplash(float x, float y, float dx, float dy, float *col)		// dx, dy reflectionsvector normalized
{
	splashs[splashcounter].exist = true;
	splashs[splashcounter].age = 0;
	splashs[splashcounter].color[0] = 0.1f;
	splashs[splashcounter].color[1] = 0.2f;
	splashs[splashcounter].color[2] = 0.2f;
	
#ifdef USE_OPENAL
	alSource3f((sources[splashcounter+1]), AL_POSITION, x, y, BULLET_HEIGHT);
	alSourceStop((sources[splashcounter+1]));
	alSourceRewind((sources[splashcounter+1]));
	alSourcePlay((sources[splashcounter+1]));
#endif

	for (int i = 0; i < DEBREE_NUM; i++)
	{
		splashs[splashcounter].x[i] = x;
		splashs[splashcounter].y[i] = y;
		splashs[splashcounter].z[i] = BULLET_HEIGHT;
		
		splashs[splashcounter].dx[i] = (((myRand()-0.5f)*2 + dx) / 5)*DEBREE_SPEED;
		splashs[splashcounter].dy[i] = (((myRand()-0.5f)*2 + dy) / 5)*DEBREE_SPEED;
		splashs[splashcounter].dz[i] = (myRand()-0.5f)*DEBREE_SPEED;
	}
	
	++splashcounter %= MAX_SPLASHS;
}

bool checkCollision()		// border and house collision
{
	bool coll = false;
	
	for (int i = 0; i < HOUSE_NUM; i++)
	{
		if ((px > houses[i].x1) && (px < houses[i].x2) && (py > houses[i].y1) && (py < houses[i].y2))
		{
			px -= dpx * frametime;
			py -= dpy * frametime;
			
			if (px < houses[i].x1)
			{
				dpx = 0.0f;
				px = houses[i].x1;
				py += dpy * frametime;
			}
			else
			if (px > houses[i].x2)
			{
				dpx = 0.0f;
				px = houses[i].x2;
				py += dpy * frametime;
			}

			if (py < houses[i].y1)
			{
				dpy = 0.0f;
				py = houses[i].y1;
				px += dpx * frametime;
			}
			else
			if (py > houses[i].y2)
			{
				dpy = 0.0f;
				py = houses[i].y2;
				px += dpx * frametime;
			}
			coll = true;
		}
	}
	return coll;
}

void drawBall()
{
	if (myball)
	{
		ball.x = px;
		ball.y = py;
	}
	else
	if ((ball.owner != 255))
	{
		ball.x = players[ball.owner].x;
		ball.y = players[ball.owner].y;
	}
	else
	{
		ball.x += ball.dx * frametime;
		ball.y += ball.dy * frametime;
	}
	
	// draw player
	glPushMatrix();
	
	glTranslatef(ball.x, ball.y, 0.0f);
	
	glRotatef(myRand()*360, 0.0f, 0.0f, 1.0f);
	
	glColor3f(1.0f, 1.0f, 0.0f);
	
	glBegin(GL_LINES);	// draw
		glVertex3f(-PLAYER_SIZE, -PLAYER_SIZE, 0.1f);
		glVertex3f(PLAYER_SIZE, PLAYER_SIZE, 0.1f);
		
		glVertex3f(PLAYER_SIZE, -PLAYER_SIZE, 0.1f);
		glVertex3f(-PLAYER_SIZE, PLAYER_SIZE, 0.1f);
	glEnd();
	
	glPopMatrix();
}

bool checkBallCollision()		// ball to border and house collision
{
	bool coll = false;
	
	for (int i = 0; i < HOUSE_NUM; i++)
	{
		if ((!myball) &&
			(((ball.x - px) * (ball.x - px) + 
			(ball.y - py) * (ball.y - py)) <= (2.0f)) &&
			(ball.owner == 255))
		{
			myball = true;
			
			networkWrite(MSG_BALL, 0, clientNum);
		}

		if ((ball.x > houses[i].x1) && (ball.x < houses[i].x2) && (ball.y > houses[i].y1) && (ball.y < houses[i].y2))
		{
			ball.x -= ball.dx * frametime;
			ball.y -= ball.dy * frametime;
			
			if (ball.x < houses[i].x1)
			{
				ball.dx = -ball.dx*0.8;
				ball.x = houses[i].x1;
				ball.y += ball.dy * frametime;
			}
			else
			if (ball.x > houses[i].x2)
			{
				ball.dx = -ball.dx*0.8;
				ball.x = houses[i].x2;
				ball.y += ball.dy * frametime;
			}

			if (ball.y < houses[i].y1)
			{
				ball.dy = -ball.dy*0.8;
				ball.y = houses[i].y1;
				ball.x += ball.dx * frametime;
			}
			else
			if (ball.y > houses[i].y2)
			{
				ball.dy = -ball.dy*0.8;
				ball.y = houses[i].y2;
				ball.x += ball.dx * frametime;
			}
			coll = true;
		}
	}
	return coll;
}

void checkBulletCollision()
{
	for (int j = 0; j < MAX_BULLETS; j++)
	{
		if (bullets[j].exist)
		{
			if (((bullets[j].x - px) * (bullets[j].x - px) + 
				(bullets[j].y - py) * (bullets[j].y - py)) <= PLAYER_SIZE_SQR)
			{
				bullets[j].exist = false;
				
				if (--health == 0)
				{
					initPlayer();
					myball = false;
				}
					
				changed = 3;
				
				networkWrite(MSG_HIT, 0, clientNum);
				networkWrite(MSG_BALL, 0, clientNum);
				
			}
			
			for (int i = 0; i < HOUSE_NUM; i++)
			{
				if ((bullets[j].x > houses[i].x1) && (bullets[j].x < houses[i].x2) && (bullets[j].y > houses[i].y1) && (bullets[j].y < houses[i].y2))
				{
					bullets[j].exist = false;

					float colmod = static_cast<float>(houses[i].type) / (2*TYPE_NUM);
					float col[3];
					col[0] = 0.1f + colmod;
					col[1] = 0.7f - colmod;
					col[2] = 0.3f + colmod / 4;
					
					bullets[j].x -= bullets[j].dx * frametime;
					bullets[j].y -= bullets[j].dy * frametime;
					
					if (bullets[j].x < houses[i].x1)
					{
						bullets[j].x = houses[i].x1;
						createSplash(bullets[j].x, bullets[j].y, -bullets[j].dx / BULLET_SPEED, bullets[j].dy / BULLET_SPEED, col);
					}
					else
					if (bullets[j].x > houses[i].x2)
					{
						bullets[j].x = houses[i].x2;
						createSplash(bullets[j].x, bullets[j].y, -bullets[j].dx / BULLET_SPEED, bullets[j].dy / BULLET_SPEED, col);
					}
		
					if (bullets[j].y < houses[i].y1)
					{
						bullets[j].y = houses[i].y1;
						createSplash(bullets[j].x, bullets[j].y, bullets[j].dx / BULLET_SPEED, -bullets[j].dy / BULLET_SPEED, col);
					}
					else
					if (bullets[j].y > houses[i].y2)
					{
						bullets[j].y = houses[i].y2;
						createSplash(bullets[j].x, bullets[j].y, bullets[j].dx / BULLET_SPEED, -bullets[j].dy / BULLET_SPEED, col);
					}
				}
			}	
		}
	}
}

static void display(void)
{
    time1 = time2;
    time2 = clock();
    
    frametime = (time2 - time1) / CLK_TCK;
    
    schrotTime += frametime;
    
	framecounter += frametime;
	
	if (framecounter > 10) {
		framecounter -= 10;
		changed = 1;
	}
	
    dpx = dpx2; dpy = dpy2;
    
	
	if ((dpx != 0) && (dpy != 0))
	{
	    px += dpx / 1.4f * frametime;
		py += dpy / 1.4f * frametime;
	}
	else
	{
	    px += dpx * frametime;
	    py += dpy * frametime;
	}
	
    if (isserver)
		networkServer(serversock);
	else
	{
		networkClient(clientsock);
	}
		
	if (changed > 0)
	{
		networkWrite(MSG_PLAYER, 0, clientNum);
		changed--;
	}
	
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		bullets[i].x += bullets[i].dx * frametime;
		bullets[i].y += bullets[i].dy * frametime;
	}
	
	checkCollision();
	checkBulletCollision();
	checkBallCollision();
	
 	glLoadIdentity();
	gluLookAt(px, py, 80.0, 
		      px, py, -1.0,
			  0.0, 1.0, 0.0);
	
#ifdef USE_OPENAL
	listenerPos[0] = px;
	listenerPos[1] = py;
	alListenerfv(AL_POSITION, listenerPos);
#endif
   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawHouses();

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	drawBall();

	drawPlayers();

	drawBullets();
	
	drawSplashs();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

void networkWrite(int type, int num, int clientNum)
{
    NLbyte  buffer[128];
    memset(buffer, 0, sizeof(buffer));
    NLbyte *temp;

	if (type == MSG_PLAYER)
	{
		buffer[0] = MSG_PLAYER;
		
		temp = buffer + sizeof(NLbyte);
	    memcpy((void *)temp, (void *)&px, sizeof(float));
	    
		temp = temp + sizeof(float);
	    memcpy((void *)temp, (void *)&py, sizeof(float));
	    
		temp = temp + sizeof(float);
	    memcpy((void *)temp, (void *)&dpx, sizeof(float));

		temp = temp + sizeof(float);
	    memcpy((void *)temp, (void *)&dpy, sizeof(float));
	    
		temp = temp + sizeof(float);
	    memcpy((void *)temp, (void *)&clientNum, sizeof(int));
	} else
	if (type == MSG_BULLET)
	{
		buffer[0] = MSG_BULLET;
		
		temp = buffer + sizeof(NLbyte);
	    memcpy((void *)temp, (void *)&(bullets[num].x), sizeof(float));

		temp = temp + sizeof(float);
	    memcpy((void *)temp, (void *)&(bullets[num].y), sizeof(float));

		temp = temp + sizeof(float);
	    memcpy((void *)temp, (void *)&(bullets[num].dx), sizeof(float));

		temp = temp + sizeof(float);
	    memcpy((void *)temp, (void *)&(bullets[num].dy), sizeof(float));

		temp = temp + sizeof(float);
	    memcpy((void *)temp, (void *)&(bullets[num].speed), sizeof(float));

		temp = temp + sizeof(float);
	    memcpy((void *)temp, (void *)&clientNum, sizeof(int));
	} else
	if (type == MSG_HIT)
	{
		buffer[0] = MSG_HIT;
		
		temp = buffer + sizeof(NLbyte);
	    memcpy((void *)temp, (void *)&(health), sizeof(float));

		temp = temp + sizeof(float);
	    memcpy((void *)temp, (void *)&clientNum, sizeof(int));
	} else
	if (type == MSG_BALL)
	{
		buffer[0] = MSG_BALL;
		
		temp = buffer + sizeof(NLbyte);
	    memcpy((void *)temp, (void *)&(ball.x), sizeof(float));
	    
		temp = temp + sizeof(float);
	    memcpy((void *)temp, (void *)&(ball.y), sizeof(float));
	    
		temp = temp + sizeof(float);
	    memcpy((void *)temp, (void *)&(ball.dx), sizeof(float));

		temp = temp + sizeof(float);
	    memcpy((void *)temp, (void *)&(ball.dy), sizeof(float));
	    
		temp = temp + sizeof(float);
	    memcpy((void *)temp, (void *)&(myball), sizeof(bool));

		temp = temp + sizeof(bool);
	    memcpy((void *)temp, (void *)&clientNum, sizeof(int));
	}
	
	if (isserver)
	{
		for (int i = 0; i < clientnum; i++)
		{
			nlWrite(client[i], buffer, sizeof(buffer));
		}
	}
	else
    	nlWrite(clientsock, buffer, sizeof(buffer));
}

void networkRead(NLbyte *buffer)
{
	int clientNum;
	NLbyte *temp;
	
	if ((*buffer) == MSG_PLAYER)
	{
		cout << "Player data" << endl;
		memcpy((void *)&clientNum, (void *)(buffer + (sizeof(float)*4 + 1)), sizeof(int));
		
		temp = buffer + sizeof(NLbyte);
	    memcpy((void *)&(players[clientNum].x), (void *)temp, sizeof(float));
	    
		temp = temp + sizeof(float);
	    memcpy((void *)&(players[clientNum].y), (void *)temp, sizeof(float));
	    
		temp = temp + sizeof(float);
	    memcpy((void *)&(players[clientNum].dx), (void *)temp, sizeof(float));

		temp = temp + sizeof(float);
	    memcpy((void *)&(players[clientNum].dy), (void *)temp, sizeof(float));
	    
//		cout << "x: " << players[clientNum].x << "     y: " << players[clientNum].y << endl;
	    
	    players[clientNum].exist = true;
	} else
	if ((*buffer) == MSG_BULLET)
	{
		cout << "Bullet data" << endl;
		memcpy((void *)&clientNum, (void *)(buffer + (sizeof(float)*4 + 1)), sizeof(int));

		temp = buffer + sizeof(NLbyte);
	    memcpy((void *)&(bullets[bulletcounter].x), (void *)temp, sizeof(float));
	    
		temp = temp + sizeof(float);
	    memcpy((void *)&(bullets[bulletcounter].y), (void *)temp, sizeof(float));
	    
		temp = temp + sizeof(float);
	    memcpy((void *)&(bullets[bulletcounter].dx), (void *)temp, sizeof(float));

		temp = temp + sizeof(float);
	    memcpy((void *)&(bullets[bulletcounter].dy), (void *)temp, sizeof(float));
	    
		temp = temp + sizeof(float);
	    memcpy((void *)&(bullets[bulletcounter].speed), (void *)temp, sizeof(float));
	    
	    bullets[bulletcounter].player = clientNum;
	    bullets[bulletcounter].exist = true;

		++bulletcounter %= MAX_BULLETS;
	} else
	if ((*buffer) == MSG_HIT)
	{
		cout << "Hit data" << endl;
		memcpy((void *)&clientNum, (void *)(buffer + (sizeof(float) + 1)), sizeof(int));

		temp = buffer + sizeof(NLbyte);
	    memcpy((void *)&(players[clientNum].health), (void *)temp, sizeof(float));
	} else
	if ((*buffer) == MSG_BALL)
	{
		cout << "Ball data" << endl;
		temp = buffer + sizeof(NLbyte);
	    memcpy((void *)&(ball.x), (void *)temp, sizeof(float));
	    
		temp = temp + sizeof(float);
	    memcpy((void *)&(ball.y), (void *)temp, sizeof(float));
	    
		temp = temp + sizeof(float);
	    memcpy((void *)&(ball.dx), (void *)temp, sizeof(float));

		temp = temp + sizeof(float);
	    memcpy((void *)&(ball.dy), (void *)temp, sizeof(float));
	    
	    bool hasball;
		temp = temp + sizeof(float);
	    memcpy((void *)&(hasball), (void *)temp, sizeof(bool));
	    
	    temp = temp + sizeof(bool);
	    memcpy((void *)&clientNum, (void *)temp, sizeof(int));
	    
	    if (hasball)
	    {
	    	ball.owner = clientNum;
	    	cout << "Player " << clientNum << " got the ball" << endl;
		}
	    else
		if (clientNum == ball.owner)
		{
	    	ball.owner = 255;
	    	cout << "Player " << clientNum << " lost the ball" << endl;
		}
	}
}

void networkServer(NLsocket sock)
{
    NLbyte      string[NL_MAX_STRING_LENGTH];

    NLbyte  buffer[256];

    /* check for a new client */
    NLsocket newsock = nlAcceptConnection(sock);

    if(newsock != NL_INVALID)
    {
        NLaddress   addr;

        nlGetRemoteAddr(newsock, &addr);
        client[clientnum] = newsock;
		cout << "Client " << clientnum << " connected from " << nlAddrToString(&addr, string) << endl;
        clientnum++;
        
        buffer[0] = clientnum;
        nlWrite(newsock, buffer, sizeof(NLbyte));
        cout << "PlayerID " << clientnum << " assigned." << endl;
        
        while (nlRead(newsock, buffer, sizeof(team)) <= 0) {}
        players[clientnum].team = buffer[0];
        cout << "Player is member of team " << players[clientnum].team << endl;

		cout << "Sending house data";
		for (int i = 0; i < HOUSE_NUM; i++)
		{
			if ((i % 10) == 5)
			{
				while (nlRead(newsock, buffer, sizeof(short)) <= 0) {}
				cout << ".";
			}
				
			memcpy((void *)buffer, (void *)&(houses[i].x1), sizeof(float));
			memcpy((void *)(buffer + sizeof(float)), (void *)&(houses[i].y1), sizeof(float));
			memcpy((void *)(buffer + 2*sizeof(float)), (void *)&(houses[i].x2), sizeof(float));
			memcpy((void *)(buffer + 3*sizeof(float)), (void *)&(houses[i].y2), sizeof(float));
			memcpy((void *)(buffer + 4*sizeof(float)), (void *)&(houses[i].height), sizeof(float));
			memcpy((void *)(buffer + 5*sizeof(float)), (void *)&(houses[i].type), sizeof(char));
			nlWrite(newsock, buffer, sizeof(buffer));
		}
		cout << " Done." << endl;
		
		networkWrite(MSG_BALL, 0, clientNum);
    }
    else
    {
        if(nlGetError() == NL_SYSTEM_ERROR)
        {
			assert(false);
//            printErrorExit();
        }
    }
    /* loop through the clients and read the packets */
    for(int i = 0; i < clientnum; i++)
    {
        if(nlRead(client[i], buffer, sizeof(buffer)) > 0)
        {
//			cout << "client nummer " << i << endl; //": " << (char *)buffer << endl;
			
            for(int j = 0;j < clientnum; j++)
            {
                if(i != j)
                    nlWrite(client[j], buffer, sizeof(buffer));
            }
            
            networkRead(buffer);
        }
    }
}

void networkClient(NLsocket sock)
{
	NLbyte buffer[256];
	while (nlRead(sock, buffer, sizeof(buffer)) > 0)
		networkRead(buffer);
}

void initPlayer()
{
	px = myRand() * MAX_FIELD;
	py = myRand() * MAX_FIELD;

	health = PLAYER_STRENGTH;

	while (checkCollision())
	{
		px = myRand() * MAX_FIELD;
		py = myRand() * MAX_FIELD;
	}
	
	myball = false;
}

const GLfloat light_ambient[]  = { 0.1f, 0.1f, 0.1f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 6.0f, 1.0f, 30.0f, 1.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 0.1f, 0.1f, 0.1f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
	cout << "starting program" << endl;
	
	scrh = 320; scrw = 280;
	char *windowTitle;
    glutInitWindowSize(scrh, scrw);
    
    if (isserver)
    {
    	glutInitWindowPosition(50,40);
    	windowTitle = "Server";
	}
    else
    {
    	glutInitWindowPosition(400, 40);
    	windowTitle = "Client";
	}

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    window = glutCreateWindow(windowTitle);

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    
#ifdef MOUSE
    glutSetCursor(3);
#endif
	glutIgnoreKeyRepeat(1);
	
    glClearColor(0.3,0.3,0.3,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glShadeModel(GL_FLAT);

    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    
    glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glEnable(GL_TEXTURE_2D);
	
	cout << "house1" << endl;
	vsglInitModel("house1.vsm");
	
	iTexNum = vsglGetTexNum();
	glGenTextures(iTexNum, uiTexObjects1);
	
	iObjNum = vsglGetObjNum();
	uiDisplayLists[0] = glGenLists(iObjNum);
	
	vsglBindModel(uiDisplayLists[0], uiTexObjects1);
	
	cout << "house2" << endl;
	vsglInitModel("house2.vsm");
	
	iTexNum = vsglGetTexNum();
	glGenTextures(iTexNum, uiTexObjects2);
	
	iObjNum = vsglGetObjNum();
	uiDisplayLists[1] = glGenLists(iObjNum);
	
	vsglBindModel(uiDisplayLists[1], uiTexObjects2);
	
//	cout << "ball" << endl;
//	ballmodel = new VsglFileModel("ball.vsm");
	cout << "loaded" << endl;

#ifdef USE_OPENAL
    ////////////////////////////////////// OpenAL Init
    
    alutInit(0, 0);
    
    alGenBuffers(2, buffers);
	alGenSources(MAX_SPLASHS + 1, sources);
	
	ALenum format;
    ALsizei size, bits, freq;
    ALboolean loop;
    char *data;

	//alutLoadWAVFile(ALbyte *file,ALenum *format,ALvoid **data,ALsizei *size,ALsizei *freq,ALboolean *loop);
    
    alutLoadWAVFile("shoot.wav", &format, (void **) &data, &size, &freq, &loop);
    alBufferData(buffers[0], format, data, size, freq);
	alutUnloadWAV(format,data,size,freq);

    alutLoadWAVFile("splash.wav", &format, (void **) &data, &size, &freq, &loop);
    alBufferData((buffers[1]), format, data, size, freq);
	alutUnloadWAV(format,data,size,freq);

	for (int i = 1; i <= MAX_SPLASHS; i++)
	{
		alSourcei((sources[i]), AL_BUFFER, (buffers[1]));		// splashs
	}
	alSourcei(sources[0], AL_BUFFER, buffers[0]);				// player

	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
#endif

// network staff ----------------------------------------------------------------------

    NLaddress   addr;
    NLbyte      server[] = "169.254.102.219:25000";
    NLenum      type = NL_UNRELIABLE; /* Change this to NL_RELIABLE for reliable connection */
    NLbyte      string[NL_MAX_STRING_LENGTH];
	
	if (!nlInit())
		assert(false);
		
    if (!nlSelectNetwork(NL_IP))
    	assert(false);

	if (!nlEnable(NL_TCP_NO_DELAY))
		assert(false);

//	cout << "Team wählen: ";
//	team = 0;
//	cin >> team;
		
    if(isserver)
    {
        /* create a server socket */
        serversock = nlOpen(25000, type); /* just a random port number ;) */

        if(serversock == NL_INVALID)
        	assert(false);

        if(!nlListen(serversock))       /* let's listen on this socket */
        {
            nlClose(serversock);
            assert(false);
        }
        nlGetLocalAddr(serversock, &addr);
        cout << "Our (Server) address is " << nlAddrToString(&addr, string) << endl;
        
	    memset(client, 0, sizeof(client));
	    
		clientNum = 0;    
	}
    else
    {
	    /* create a client socket */
	    clientsock = nlOpen(0, type); /* let the system assign the port number */
	    nlGetLocalAddr(clientsock, &addr);
        cout << "Our address is " << nlAddrToString(&addr, string) << endl;
	
		if(clientsock == NL_INVALID)
			assert(false);
			
		cout << "Bitte Server IP eingeben: ";
		cin >> server;
	    /* create the NLaddress */
	    nlStringToAddr(server, &addr);
        cout << "Server address is " << nlAddrToString(&addr, string) << endl;;
	    /* now connect */
	    if(!nlConnect(clientsock, &addr))
	    {
	        nlClose(clientsock);
	        assert(false);
	    }
	    NLbyte buf[2];
	    
	    while (nlRead(clientsock, buf, sizeof(NLbyte)) <= 0) {}
   	    nlWrite(clientsock, (void *)&team, sizeof(team));
	    
	    clientNum = buf[0];
	    players[0].team = buf[1];
	}
	
	cout << "Our PlayerID: " << clientNum << endl;

// game staff --------------------------------------------------------------------------

	initHouses();
	initBall();
	
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		players[i].exist = false;
	}

	initPlayer();

	dpx2 = dpy2 = 0.0f;
	
	for (int i = 0; i < MAX_SPLASHS; i++)
	{
		splashs[i].exist = false;
	}
	
	VsInputManager::initVsInputManager();
	VsInputManager::registerFunc(VsInputManager::EVT_LEFT_CLICKED | VsInputManager::EVT_KEY_PRESS_DOWN, click);
	VsInputManager::registerFunc(VsInputManager::EVT_RIGHT_CLICKED | VsInputManager::EVT_KEY_PRESS_DOWN, rightClick);
	VsInputManager::registerFunc(VsInputManager::EVT_MIDDLE_CLICKED | VsInputManager::EVT_KEY_PRESS_DOWN, middleClick);

	VsInputManager::registerKeyFunc(VsInputManager::EVT_KEY_W | VsInputManager::EVT_KEY_PRESS_DOWN, keyup);
	VsInputManager::registerKeyFunc(VsInputManager::EVT_KEY_S | VsInputManager::EVT_KEY_PRESS_DOWN, keydown);
	VsInputManager::registerKeyFunc(VsInputManager::EVT_KEY_A | VsInputManager::EVT_KEY_PRESS_DOWN, keyleft);
	VsInputManager::registerKeyFunc(VsInputManager::EVT_KEY_D | VsInputManager::EVT_KEY_PRESS_DOWN, keyright);

	VsInputManager::registerKeyFunc(VsInputManager::EVT_KEY_W | VsInputManager::EVT_KEY_PRESS_UP, keyyrel);
	VsInputManager::registerKeyFunc(VsInputManager::EVT_KEY_S | VsInputManager::EVT_KEY_PRESS_UP, keyyrel);
	VsInputManager::registerKeyFunc(VsInputManager::EVT_KEY_A | VsInputManager::EVT_KEY_PRESS_UP, keyxrel);
	VsInputManager::registerKeyFunc(VsInputManager::EVT_KEY_D | VsInputManager::EVT_KEY_PRESS_UP, keyxrel);
	
	VsInputManager::registerKeyFunc(VsInputManager::EVT_KEY_ESC | VsInputManager::EVT_KEY_PRESS_DOWN, end);
	
	VsInputManager::registerKeyFunc(VsInputManager::EVT_KEY_PRESSED | VsInputManager::EVT_KEY_PRESS_DOWN, keypress);
	VsInputManager::registerKeyFunc(VsInputManager::EVT_KEY_PRESSED | VsInputManager::EVT_KEY_PRESS_UP, keypress);
	
	VsInputManager::registerKeyFunc(VsInputManager::EVT_KEY_R | VsInputManager::EVT_KEY_PRESS_DOWN, restart);
	

    glutMainLoop();

	end(1);

    return EXIT_SUCCESS;
}
