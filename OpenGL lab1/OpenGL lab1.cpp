#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#include "Camera.h"
#include "Mesh.h"
#include "supportClass.h"

using namespace std;

#define CAN2 1.41421356
#define PI 3.14159265


int	screenWidth = 600;
int	screenHeight = 600;
int maxstep = 75;


float ambient[] = { 0.9, 0, 0 };
float defuse[] = { 0.9, 0.9, 0 };
float specular[] = { 0.9, 0.9, 0 };

GLint step = 0;

Texture   floorTex;

bool	bWireFrame = false;
bool	bAuto = false;
bool	b4View = false;
bool	bDone = true;
bool	light1 = false;

int		light = 0;
float	baseRadius = 0.8;
float	baseHeight = 0.1;
float	baseRotateStep = 5;

float	supportRadius = 0.1;
float	supportHeight = 0.5;

float	frameRadius = 2;
float	frameRingRadius = 0.1;

float	gimbal1Radius = 1.5;
float	gimbal2Radius = 1;

float	rotorRadius = 0.5;
float	rotorThickness = 0.1;

Mesh	base;
Mesh	support;
Mesh	frame, frame1, frame2;
Mesh	gimbal1, gimbal1a, gimbal1b;
Mesh	gimbal2, gimbal2a, gimbal2b;
Mesh	axle;
Mesh	rotor;

MyCamera cam;

void drawAxis()
{
	glPushMatrix();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-4, 0, 0);//x
	glVertex3f(4, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);//y
	glVertex3f(0, 4, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -4);//z
	glVertex3f(0, 0, 4);
	glEnd();

	glPopMatrix();
}
void auto_loop(int n)
{
	if (bAuto) {
		base.rotateY -= baseRotateStep * 5 / 200;
		if (base.rotateY < 0)
			base.rotateY += 360;
		gimbal1.rotateX += baseRotateStep * 15 / 200;
		if (gimbal1.rotateX > 360)
			gimbal1.rotateX -= 360;
		gimbal2.rotateY -= baseRotateStep * 25 / 200;
		if (gimbal2.rotateY < 0)
			gimbal2.rotateY += 360;
		rotor.rotateX += baseRotateStep * 35 / 200;
		if (rotor.rotateX > 360)
			rotor.rotateX -= 360;
		glutPostRedisplay();
		glutTimerFunc(5, auto_loop, 0);
	}
}

void reset_loop(int n)
{
	if(step>0&&!bAuto&&!bDone){
		base.rotateY *= (float)(step-1) / step;
		gimbal1.rotateX  *= (float)(step - 1) / step;
		gimbal2.rotateY *= (float)(step - 1) / step;
		rotor.rotateX  *= (float)(step - 1) / step;
		step--;
		glutPostRedisplay();
		glutTimerFunc(5, reset_loop, 0);
	}
	else bDone = true;
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		bDone = true;
		bAuto = false;
		base.rotateY += baseRotateStep;
		if (base.rotateY > 360)
			base.rotateY -= 360;
		break;
	case '2':
		bDone = true;
		bAuto = false;
		base.rotateY -= baseRotateStep;
		if (base.rotateY < 0)
			base.rotateY += 360;
		break;
	case '3':
		bDone = true;
		bAuto = false;
		gimbal1.rotateX += baseRotateStep;
		if (gimbal1.rotateX > 360)
			gimbal1.rotateX -= 360;
		break;
	case '4':
		bDone = true;
		bAuto = false;
		gimbal1.rotateX -= baseRotateStep;
		if (gimbal1.rotateX < 0)
			gimbal1.rotateX += 360;
		break;
	case '5':
		bDone = true;
		bAuto = false;
		gimbal2.rotateY += baseRotateStep;
		if (gimbal2.rotateY > 360)
			gimbal2.rotateY -= 360;
		break;
	case '6':
		bDone = true;
		bAuto = false;
		gimbal2.rotateY -= baseRotateStep;
		if (gimbal2.rotateY < 0)
			gimbal2.rotateY += 360;
		break;
	case '7':
		bDone = true;
		bAuto = false;
		rotor.rotateX += baseRotateStep;
		if (rotor.rotateX > 360)
			rotor.rotateX -= 360;
		break;
	case '8':
		bDone = true;
		bAuto = false;
		rotor.rotateX -= baseRotateStep;
		if (rotor.rotateX < 0)
			rotor.rotateX += 360;
		break;

	case 'w':
	case 'W':
		bWireFrame = !bWireFrame;
		break;
	case 'r':
	case 'R':
		bDone = false;
		bAuto = false;
		step = maxstep;
		if (base.rotateY > 180) base.rotateY -= 360;
		else if (base.rotateY < -180) base.rotateY += 360;
		if (gimbal1.rotateX > 180) gimbal1.rotateX -= 360;
		else if (gimbal1.rotateX < -180) gimbal1.rotateX += 360;
		if (gimbal2.rotateY > 180) gimbal2.rotateY -= 360;
		else if (gimbal2.rotateY < -180) gimbal2.rotateY += 360;
		if (rotor.rotateX > 180) rotor.rotateX -= 360;
		else if (rotor.rotateX < -180) rotor.rotateX += 360;
		printf("%f\t%f\t%f\t%f\n", base.rotateY, gimbal1.rotateX, gimbal2.rotateY, rotor.rotateX);
		reset_loop(5);
		break;
	case 'a':
	case 'A':
		bAuto = !bAuto;
		auto_loop(5);
		break;
	case 's':
	case 'S':
		glEnable(GL_SMOOTH);
		glShadeModel(GL_SMOOTH);
		break;
	case 'f':
	case 'F':
		glEnable(GL_FLAT);
		glShadeModel(GL_FLAT);
		break;
	case 'd':
	case 'D':
		if (light1)
		{
			light1 = false;
			glDisable(GL_LIGHT1);
		}
		else {
			light1 = true;
			glEnable(GL_LIGHT1);
		}
		break;
	case 'v':
	case 'V':
		b4View = !b4View;
		break;
	case '-':
		cam.distance -= 0.1;
		cam.Calculate();
		break;
	case '+':
		cam.distance += 0.1;
		cam.Calculate();
		break;
	}
	glutPostRedisplay();
}

void mySpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		cam.height += 0.2;
		break;
	case GLUT_KEY_DOWN:
		cam.height -= 0.2;
		break;
	case GLUT_KEY_LEFT:
		cam.angle -= 2;
		break;
	case GLUT_KEY_RIGHT:
		cam.angle += 2;
		break;
	}
	cam.Calculate();
	glutPostRedisplay();
}

void setupMaterial(float ambient[], float diffuse[], float specular[], float shiness)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiness);
}

void loadTextures(void) {
	bool status = LoadTGA(&floorTex, "marble.tga");
	if (status) {
		glGenTextures(1, &floorTex.texID);
		glBindTexture(GL_TEXTURE_2D, floorTex.texID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, floorTex.width,
			floorTex.height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, floorTex.imageData);

		if (floorTex.imageData)
			free(floorTex.imageData);
	}
}

void drawFloor(float alpha)
{
	glPushMatrix();

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, floorTex.texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor4f(1, 1, 1, alpha);

	glBegin(GL_QUADS); 
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-10, 0, 10);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-10, 0, -10);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(10, 0, -10);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(10, 0, 10);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glPopMatrix();


}

void drawBase()
{
	glPushMatrix();

	glTranslated(0, baseHeight / 2.0, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	base.CalculateFaceNorm();
	base.Draw();
	glPopMatrix();
}

void drawSupport()
{
	glPushMatrix();

	glTranslated(0, supportHeight / 2 + baseHeight, 0);
	glRotatef(base.rotateY, 0, 1, 0);

	support.CalculateFaceNorm();
	support.Draw();
	glPopMatrix();
}

void drawFrame()
{
	glPushMatrix();

	glTranslated(0, supportHeight*1.5 + baseHeight+ frameRadius+frameRingRadius/2, 0);
	glRotatef(base.rotateY, 0, 1, 0);

	frame.CalculateFaceNorm();
	frame.Draw();
	glRotatef(90, 0, 0, 1);
	glTranslated(0, +frameRadius - 2 * frameRingRadius, 0);
	frame1.CalculateFaceNorm();
	frame1.Draw();
	glTranslated(0, 2.0 * (-frameRadius + 2.0 * frameRingRadius), 0);
	frame2.CalculateFaceNorm();
	frame2.Draw();

	glPopMatrix();
}

void drawGimbal1()
{
	glPushMatrix();

	glTranslated(0, supportHeight*1.5 + baseHeight + frameRadius + frameRingRadius / 2, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glRotatef(gimbal1.rotateX, 1, 0, 0);
	glRotatef(90, 0, 0, 1);

	gimbal1.CalculateFaceNorm();
	gimbal1.Draw();
	glRotatef(90, 0, 0, 1);
	glTranslated(0, +gimbal1Radius - 2 * frameRingRadius, 0);
	gimbal1a.CalculateFaceNorm();
	gimbal1a.Draw();
	glTranslated(0, 2.0 * (-gimbal1Radius + 2.0 * frameRingRadius), 0);
	gimbal1b.CalculateFaceNorm();
	gimbal1b.Draw();

	glPopMatrix();
}

void drawGimbal2()
{
	glPushMatrix();

	glTranslated(0, supportHeight*1.5 + baseHeight + frameRadius + frameRingRadius / 2, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glRotatef(gimbal1.rotateX, 1, 0, 0);
	glRotatef(gimbal2.rotateY, 0, 1, 0);

	gimbal2.CalculateFaceNorm();
	gimbal2.Draw();
	glRotatef(90, 0, 0, 1);
	glTranslated(0, +gimbal2Radius - 2 * frameRingRadius, 0);
	gimbal2a.CalculateFaceNorm();
	gimbal2a.Draw();
	glTranslated(0, 2.0 * (-gimbal2Radius + 2.0 * frameRingRadius), 0);
	gimbal2b.CalculateFaceNorm();
	gimbal2b.Draw();

	glPopMatrix();
}

void drawAxle()
{
	glPushMatrix();

	glTranslated(0, supportHeight*1.5 + baseHeight + frameRadius + frameRingRadius / 2, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glRotatef(gimbal1.rotateX, 1, 0, 0);
	glRotatef(gimbal2.rotateY, 0, 1, 0);
	glRotatef(90, 0, 0, 1);

	axle.CalculateFaceNorm();
	axle.Draw();

	glPopMatrix();
}

void drawRotor()
{
	glPushMatrix();

	glTranslated(0, supportHeight*1.5 + baseHeight + frameRadius + frameRingRadius / 2, 0);
	glRotatef(base.rotateY, 0, 1, 0);
	glRotatef(gimbal1.rotateX, 1, 0, 0);
	glRotatef(gimbal2.rotateY, 0, 1, 0);
	glRotatef(rotor.rotateX, 1, 0, 0);
	glRotatef(90, 0, 0, 1);

	rotor.CalculateFaceNorm();
	rotor.Draw();

	glPopMatrix();
}

void drawGyroscope() {

	glPushMatrix();
	{
		ambient[0] = 0.9;	ambient[1] = 0;		ambient[2] = 0;
		defuse[0] = 0.9;	defuse[1] = 0;		defuse[2] = 0;
		specular[0] = 0;	specular[1] = 0;	specular[2] = 0;
		setupMaterial(ambient, defuse, specular, 128);

		drawAxis();
		drawBase();
		drawSupport();
		drawFrame();
	}
	{
		ambient[0] = 0.0;	ambient[1] = 0;		ambient[2] = 0.9;
		defuse[0] = 0.0;	defuse[1] = 0;		defuse[2] = 0.9;
		specular[0] = 0;	specular[1] = 0;	specular[2] = 0;
		setupMaterial(ambient, defuse, specular, 50);
		setupMaterial(ambient, defuse, specular, 50);
		drawGimbal1();
	}
	{
		ambient[0] = 0.0;	ambient[1] = .9;	ambient[2] = 0.;
		defuse[0] = 0.0;	defuse[1] = .9;		defuse[2] = 0;
		specular[0] = 0;	specular[1] = 0.9;	specular[2] = 0;
		setupMaterial(ambient, defuse, specular, 50);
		drawGimbal2();
		drawAxle();
	}
	{
		ambient[0] = 0.8;	ambient[1] = .0;	ambient[2] = 0.4;
		defuse[0] = 0.8;	defuse[1] = 0;		defuse[2] = 0.4;
		specular[0] = 0;	specular[1] = 0.;	specular[2] = 0;
		setupMaterial(ambient, defuse, specular, 50);
		drawRotor();
	}
	glPopMatrix();
}

void DrawAll() {

	glPushMatrix();
	drawGyroscope();
	glPopMatrix();
	glColorMask(0, 0, 0, 0);
	glEnable(GL_STENCIL_TEST);

	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 1);

	glDisable(GL_DEPTH_TEST);
	drawFloor(1);

	glColorMask(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);

	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); 


	glPushMatrix();
	glScalef(1, -1, 1);
	drawGyroscope();
	glPopMatrix();

	glDisable(GL_STENCIL_TEST); 

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	drawFloor(0.7);
	glDisable(GL_BLEND);
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	if(b4View){

		//top left (TOP DOWN VIEW)
		glViewport(0, screenHeight / 2, screenWidth / 2, screenHeight / 2);
		glLoadIdentity();
		gluLookAt(
			0.01, cam.distance+ cam.lookAt_Y, 0.01,
			cam.lookAt_X, cam.lookAt_Y, cam.lookAt_Z,
			0, 1, 0);

		DrawAll();

		//top right (FRONT VIEW)
		glViewport(screenWidth / 2, screenHeight / 2, screenWidth / 2, screenHeight / 2);
		glLoadIdentity();
		gluLookAt(
			cam.distance, cam.lookAt_Y, 0.01,
			cam.lookAt_X, cam.lookAt_Y, cam.lookAt_Z,
			0, 1, 0);

		DrawAll();

		//bottom left (RIGHT VIEW)
		glViewport(0, 0, screenWidth / 2, screenHeight / 2);
		glLoadIdentity();
		gluLookAt(
			0.01, cam.lookAt_Y, cam.distance,
			cam.lookAt_X, cam.lookAt_Y, cam.lookAt_Z,
			0, 1, 0);

		DrawAll();

		//bottom right (PERSPECTIVE VIEW)
		glViewport(screenWidth / 2, 0, screenWidth / 2, screenHeight / 2);
		glLoadIdentity();
		gluLookAt(
			cam.positionX, cam.positionY, cam.positionZ,
			cam.lookAt_X, cam.lookAt_Y, cam.lookAt_Z,
			0, 1, 0);

		DrawAll();
	}
	else {
		gluLookAt(
			cam.positionX, cam.positionY, cam.positionZ,
			cam.lookAt_X, cam.lookAt_Y, cam.lookAt_Z,
			0, 1, 0);
		glViewport(0, 0, screenWidth, screenHeight);
		
		DrawAll();
	}


	glFlush();
	glutSwapBuffers();
}

void myInit()
{
	float	fHalfSize = 2;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 0.001, 100);

	loadTextures();
	glPushMatrix();
	glLoadIdentity();
	{
		GLfloat	lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat	lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat	lightAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		GLfloat light_position1[] = { 6.0f, 6.0f, 6.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

	}
	{
		GLfloat	lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat	lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat	lightAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
		GLfloat light_position1[] = { 0.0f, 6.0f, 6.0f };
		glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
		glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
	}
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_FLAT);
	glShadeModel(GL_FLAT);
}

void createGyroscopeParts() {
	base.CreateCylinder(20, baseHeight, baseRadius);
	base.SetColor(2);

	support.CreateCylinder(10, supportHeight, supportRadius);
	support.SetColor(3);

	frame.CreateTorus(60, 10, frameRingRadius, frameRadius);
	frame.SetColor(4);
	frame1.CreateCylinder(10, (frameRadius - gimbal1Radius) / 2, frameRingRadius);
	frame1.SetColor(4);
	frame2.CreateCylinder(10, (frameRadius - gimbal1Radius) / 2, frameRingRadius);
	frame2.SetColor(4);

	gimbal1.CreateTorus(40, 10, frameRingRadius, gimbal1Radius);
	gimbal1.SetColor(1);
	gimbal1a.CreateCylinder(10, (gimbal1Radius - gimbal2Radius) / 2, frameRingRadius);
	gimbal1a.SetColor(1);
	gimbal1b.CreateCylinder(10, (gimbal1Radius - gimbal2Radius) / 2, frameRingRadius);
	gimbal1b.SetColor(1);

	gimbal2.CreateTorus(40, 10, frameRingRadius, gimbal2Radius);
	gimbal2.SetColor(0);

	axle.CreateCylinder(10, gimbal2Radius, frameRingRadius);
	axle.SetColor(0);

	rotor.CreateCylinder(10, rotorThickness, rotorRadius);
	rotor.SetColor(2);
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << endl << "  Gyroscope options:" << endl;
	cout << "    1, 2\t: Rotate the base" << endl;
	cout << "    3, 4\t: Rotate the gimbal 1" << endl;
	cout << "    5, 6\t: Rotate the gimbal 2" << endl;
	cout << "    7, 8\t: Rotate the rotor" << endl;
	cout << "    R, r\t: Reset the Gyroscope" << endl;
	cout << "    W, w\t: Switch between wireframe and solid mode" << endl;
	cout << "    A, a\t: Turn on/off animation" << endl;
	cout << endl << "  Camera options:" << endl;
	cout << "    V, v\t: Switch between 1 and 4 views" << endl;
	cout << "    +, -\t: Increase/Decrease camera distance" << endl;
	cout << "    up arrow\t: Increase camera height" << endl;
	cout << "    down arrow\t: Decrease camera height" << endl;
	cout << "    <-\t\t: Rotate camera clockwise" << endl;
	cout << "    ->\t\t: Rotate camera counter-clockwise" << endl;

	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Assignment 1 - Thai Ba Toan (1414065)"); // open the screen window

	createGyroscopeParts();

	myInit();
	glutTimerFunc(10,auto_loop, 0);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeyboard);
	glutDisplayFunc(myDisplay);
	glutMainLoop();

	return 0;
}