#include "stdafx.h"
#include <iostream>
#include "Mesh.h"
#include <math.h>

#define PI			3.1415926
#define	COLORNUM		14
#define DEG2RAD (3.1415926f/180.0f)


float	ColorArr[COLORNUM][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, { 0.0,  0.0, 1.0}, 
								{1.0, 1.0,  0.0}, { 1.0, 0.0, 1.0},{ 0.0, 1.0, 1.0}, 
								 {0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, { 0.9,  0.9, 0.9},
								{1.0, 0.5,  0.5}, { 0.5, 1.0, 0.5},{ 0.5, 0.5, 1.0},
									{0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}};





void Mesh::CreateFoo(float	fSize)
{
	int i;

	numVerts=10;
	pt = new Point3[numVerts];
	pt[0].set( 0, 0, 0);
	pt[1].set( fSize, 0, 0);
	pt[2].set( fSize, 0, fSize);
	pt[3].set( 0, 0, fSize);
	pt[4].set( 0, fSize, 0);
	pt[5].set( fSize, fSize, 0);
	pt[6].set( fSize, fSize, fSize / 2);
	pt[7].set( 0, fSize, fSize / 2);
	pt[8].set( 0, fSize / 2, fSize);
	pt[9].set( fSize, fSize / 2, fSize);


	numFaces= 7;
	face = new Face[numFaces];

	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 0;
	face[0].vert[1].vertIndex = 1;
	face[0].vert[2].vertIndex = 2;
	face[0].vert[3].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 4;
	face[1].vert[1].vertIndex = 5;
	face[1].vert[2].vertIndex = 1;
	face[1].vert[3].vertIndex = 0;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 4;
	face[2].vert[1].vertIndex = 5;
	face[2].vert[2].vertIndex = 6;
	face[2].vert[3].vertIndex = 7;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;

	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 6;
	face[3].vert[1].vertIndex = 7;
	face[3].vert[2].vertIndex = 8;
	face[3].vert[3].vertIndex = 9;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;

	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 8;
	face[4].vert[1].vertIndex = 9;
	face[4].vert[2].vertIndex = 2;
	face[4].vert[3].vertIndex = 3;
	for(i = 0; i<face[4].nVerts ; i++)
		face[4].vert[i].colorIndex = 4;

	face[5].nVerts = 5;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 1;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 9;
	face[5].vert[3].vertIndex = 6;
	face[5].vert[4].vertIndex = 5;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

	face[6].nVerts = 5;
	face[6].vert = new VertexID[face[6].nVerts];
	face[6].vert[0].vertIndex = 0;
	face[6].vert[1].vertIndex = 3;
	face[6].vert[2].vertIndex = 8;
	face[6].vert[3].vertIndex = 7;
	face[6].vert[4].vertIndex = 4;
	for (i = 0; i<face[6].nVerts; i++)
		face[5].vert[i].colorIndex = 6;

}

void Mesh::CreateCube(float	fSize)
{
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSize, fSize, fSize);
	pt[1].set(fSize, fSize, fSize);
	pt[2].set(fSize, fSize, -fSize);
	pt[3].set(-fSize, fSize, -fSize);
	pt[4].set(-fSize, -fSize, fSize);
	pt[5].set(fSize, -fSize, fSize);
	pt[6].set(fSize, -fSize, -fSize);
	pt[7].set(-fSize, -fSize, -fSize);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;

}

void Mesh::CreateTetrahedron()
{
	int i;
	numVerts=4;
	pt = new Point3[numVerts];
	pt[0].set(0, 0, 0);
	pt[1].set(1, 0, 0);
	pt[2].set(0, 1, 0);
	pt[3].set(0, 0, 1);

	numFaces= 4;
	face = new Face[numFaces];

	face[0].nVerts = 3;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 2;
	face[0].vert[2].vertIndex = 3;
	for(i = 0; i<face[0].nVerts ; i++)
		face[0].vert[i].colorIndex = 0;
	

	face[1].nVerts = 3;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;	
	face[1].vert[1].vertIndex = 2;
	face[1].vert[2].vertIndex = 1;
	for(i = 0; i<face[1].nVerts ; i++)
		face[1].vert[i].colorIndex = 1;

	
	face[2].nVerts = 3;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 3;
	face[2].vert[2].vertIndex = 2;
	for(i = 0; i<face[2].nVerts ; i++)
		face[2].vert[i].colorIndex = 2;


	face[3].nVerts = 3;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 1;
	face[3].vert[1].vertIndex = 3;
	face[3].vert[2].vertIndex = 0;
	for(i = 0; i<face[3].nVerts ; i++)
		face[3].vert[i].colorIndex = 3;
}
bool Face::contains(int vertexID) {
	for (int p = 0; p < nVerts; p++) {
		if (vert[p].vertIndex == vertexID)
		{
			return true;
		}
	}
	return false;
}

void Mesh::Draw() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++) {
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++) {
			int		iv = face[f].vert[v].vertIndex;
			glNormal3f(pt[iv].nx, pt[iv].ny, pt[iv].nz);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}


void Mesh::DrawWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int	iv = face[f].vert[v].vertIndex;

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColor()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;
			
			//ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]); 
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}

void Mesh::DrawColorWithBorder()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			//ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0]*0.8, ColorArr[ic][1]*0.8, ColorArr[ic][2]*0.8);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
	glPolygonMode(GL_FRONT, GL_LINE);
	for (int f = 0; f < numFaces; f++)
	{
		glBegin(GL_POLYGON);
		for (int v = 0; v < face[f].nVerts; v++)
		{
			int		iv = face[f].vert[v].vertIndex;
			int		ic = face[f].vert[v].colorIndex;

			//ic = f % COLORNUM;

			glColor3f(ColorArr[ic][0], ColorArr[ic][1], ColorArr[ic][2]);
			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		}
		glEnd();
	}
}


void Mesh::CreateCuboid(float	fSizeX, float fSizeY, float	fSizeZ) {
	int i;

	numVerts = 8;
	pt = new Point3[numVerts];
	pt[0].set(-fSizeX, fSizeY, fSizeZ);
	pt[1].set(fSizeX, fSizeY, fSizeZ);
	pt[2].set(fSizeX, fSizeY, -fSizeZ);
	pt[3].set(-fSizeX, fSizeY, -fSizeZ);
	pt[4].set(-fSizeX, -fSizeY, fSizeZ);
	pt[5].set(fSizeX, -fSizeY, fSizeZ);
	pt[6].set(fSizeX, -fSizeY, -fSizeZ);
	pt[7].set(-fSizeX, -fSizeY, -fSizeZ);


	numFaces = 6;
	face = new Face[numFaces];

	//Left face
	face[0].nVerts = 4;
	face[0].vert = new VertexID[face[0].nVerts];
	face[0].vert[0].vertIndex = 1;
	face[0].vert[1].vertIndex = 5;
	face[0].vert[2].vertIndex = 6;
	face[0].vert[3].vertIndex = 2;
	for (i = 0; i<face[0].nVerts; i++)
		face[0].vert[i].colorIndex = 0;

	//Right face
	face[1].nVerts = 4;
	face[1].vert = new VertexID[face[1].nVerts];
	face[1].vert[0].vertIndex = 0;
	face[1].vert[1].vertIndex = 3;
	face[1].vert[2].vertIndex = 7;
	face[1].vert[3].vertIndex = 4;
	for (i = 0; i<face[1].nVerts; i++)
		face[1].vert[i].colorIndex = 1;

	//top face
	face[2].nVerts = 4;
	face[2].vert = new VertexID[face[2].nVerts];
	face[2].vert[0].vertIndex = 0;
	face[2].vert[1].vertIndex = 1;
	face[2].vert[2].vertIndex = 2;
	face[2].vert[3].vertIndex = 3;
	for (i = 0; i<face[2].nVerts; i++)
		face[2].vert[i].colorIndex = 2;

	//bottom face
	face[3].nVerts = 4;
	face[3].vert = new VertexID[face[3].nVerts];
	face[3].vert[0].vertIndex = 7;
	face[3].vert[1].vertIndex = 6;
	face[3].vert[2].vertIndex = 5;
	face[3].vert[3].vertIndex = 4;
	for (i = 0; i<face[3].nVerts; i++)
		face[3].vert[i].colorIndex = 3;

	//near face
	face[4].nVerts = 4;
	face[4].vert = new VertexID[face[4].nVerts];
	face[4].vert[0].vertIndex = 4;
	face[4].vert[1].vertIndex = 5;
	face[4].vert[2].vertIndex = 1;
	face[4].vert[3].vertIndex = 0;
	for (i = 0; i<face[4].nVerts; i++)
		face[4].vert[i].colorIndex = 4;

	//Far face
	face[5].nVerts = 4;
	face[5].vert = new VertexID[face[5].nVerts];
	face[5].vert[0].vertIndex = 3;
	face[5].vert[1].vertIndex = 2;
	face[5].vert[2].vertIndex = 6;
	face[5].vert[3].vertIndex = 7;
	for (i = 0; i<face[5].nVerts; i++)
		face[5].vert[i].colorIndex = 5;
}


void Mesh::CreateCylinder(int nSegment, float fHeight, float fRadius) {
	pt = new Point3[2*nSegment + 2];
	pt[0].set(0, -fHeight, 0);
	pt[1].set(0, +fHeight, 0);
	for (int i = 0; i < nSegment; i++)
	{
		pt[2 * i + 2].set(fRadius*cos(360.0 / nSegment*i * DEG2RAD), -fHeight, fRadius*sin(360.0 / nSegment*i * DEG2RAD));
		pt[2 * i + 3].set(fRadius*cos(360.0 / nSegment*i * DEG2RAD), +fHeight, fRadius*sin(360.0 / nSegment*i * DEG2RAD));
	}

	numFaces = 3*nSegment;
	face = new Face[numFaces];
	
	for (int i = 0; i < nSegment; i++)
	{
		//side face
		face[i].nVerts = 4;
		face[i].vert = new VertexID[face[i].nVerts];
		face[i].vert[0].vertIndex = (2 * i + 0) % (2 * nSegment) + 2;
		face[i].vert[1].vertIndex = (2 * i + 1) % (2 * nSegment) + 2;
		face[i].vert[2].vertIndex = (2 * i + 3) % (2 * nSegment) + 2;
		face[i].vert[3].vertIndex = (2 * i + 2) % (2 * nSegment) + 2;
		
		//top face
		face[i + nSegment].nVerts = 3;
		face[i + nSegment].vert = new VertexID[face[i].nVerts];
		face[i + nSegment].vert[0].vertIndex = 0;
		face[i + nSegment].vert[1].vertIndex = (2 * i + 0) % (2 * nSegment) + 2;
		face[i + nSegment].vert[2].vertIndex = (2 * i + 2) % (2 * nSegment) + 2;

		//bottom face
		face[i + 2 * nSegment].nVerts = 3;
		face[i + 2 * nSegment].vert = new VertexID[face[i].nVerts];
		face[i + 2 * nSegment].vert[0].vertIndex = 1;
		face[i + 2 * nSegment].vert[1].vertIndex = (2 * i + 1) % (2 * nSegment) + 2;
		face[i + 2 * nSegment].vert[2].vertIndex = (2 * i + 3) % (2 * nSegment) + 2;
	}
}

void Mesh::CreateTorus(int nSlice, int nStack, float A, float D) {
	pt = new Point3[nSlice*nStack];
	int i, j;
	double s, t, x, y, z, twopi;

	twopi = 2 * PI;
	for (i = 0; i < nStack; i += 1) {
		for (j = 0; j < nSlice; j++) {
			s = i;
			t = j ;

			x = (D + A*cos(i*twopi / nStack))*cos(j*twopi / nSlice);
			y = (D + A*cos(i*twopi / nStack))*sin(j*twopi / nSlice);
			z = A * sin(s * twopi / nStack);
			pt[i * nSlice + j].set(x, y, z);
		}
	}
	numFaces = nSlice*nStack;
	face = new Face[numFaces];
	for (int i = 0; i < nStack-1; i++)
	{
		for (int j = 0; j < nSlice; j++)
		{
			face[i*nSlice + j].nVerts = 4;
			face[i*nSlice + j].vert = new VertexID[face[i*nSlice + j].nVerts];
			face[i*nSlice + j].vert[0].vertIndex = (j + i*nSlice) % (nSlice*nStack);
			face[i*nSlice + j].vert[1].vertIndex = (j + 1 + i*nSlice) % (nSlice*nStack);
			face[i*nSlice + j].vert[2].vertIndex = (j + 1 + (i + 1)*nSlice) % (nSlice*nStack);
			face[i*nSlice + j].vert[3].vertIndex = (j + (i + 1)*nSlice) % (nSlice*nStack);
		}
	}

}

void Mesh::SetColor(int colorIdx) {
	for (int f = 0; f < numFaces; f++)
	{
		for (int v = 0; v < face[f].nVerts; v++)
		{
			face[f].vert[v].colorIndex = colorIdx;
		}
	}
}

void Mesh::CalculateFaceNorm() {
	float mx, my, mz;
	for (int f = 0; f < numFaces; f++)
	{
		mx = my = mz = 0;
		for (int v = 0; v < face[f].nVerts - 2; v++)
		{
			int vi = face[f].vert[v].vertIndex;
			int vi_next = ((vi > face[f].nVerts - 1) ? vi + 1 - face[f].nVerts : vi + 1);
			mx += (pt[vi].y - pt[vi + 1].y) * (pt[vi].z + pt[vi_next].z);
			my += (pt[vi].z - pt[vi + 1].z) * (pt[vi].x + pt[vi_next].x);
			mz += (pt[vi].x - pt[vi + 1].x) * (pt[vi].y + pt[vi_next].y);
		}
		face[f].facenorm.set(mx, my, mz);
	}
	for (int i = 0; i < numVerts; i++)
	{
		Vector3 npv(0, 0, 0);
		for (int f = 0; f < numFaces; f++) {
			if (face[f].contains(i)) {
				npv.x = npv.x + face[f].facenorm.x;
				npv.y = npv.y + face[f].facenorm.y;
				npv.z = npv.z + face[f].facenorm.z;
			}
		}
		npv.normalize();
		pt[i].nx = npv.x;
		pt[i].ny = npv.y;
		pt[i].nz = npv.z;
	}
};

