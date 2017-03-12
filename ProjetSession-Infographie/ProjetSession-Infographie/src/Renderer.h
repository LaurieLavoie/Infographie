// IFT3100H17_Tryptique/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include <stdio.h>      /* printf */
#include <math.h>   
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

enum class VectorPrimitive { NONE, PIXEL, POINT, LINE, RECTANGLE, ELLIPSE, PARTICLE };

typedef struct
{
	VectorPrimitive type;          // 1 * 4 = 4  octets
	float         position1[2]; // 2 * 4 = 8  octets
	float         position2[2]; // 2 * 4 = 8  octets
	float         strokeWidth;     // 1 * 4 = 4  octets
	unsigned char strokeColor[4]; // 4 * 1 = 4  octets
	unsigned char fillColor[4]; // 4 * 1 = 4  octets
} StructVectorPrimitive;         //       = 32 octets

typedef struct 
{
	GLfloat position[3]; // 3 * 4 = 12 octets
	GLfloat normal[3]; // 3 * 4 = 12 octets
	GLfloat texcoord[2]; // 2 * 4 = 8  octets
	GLubyte color[4]; // 4 * 1 = 4  octets
} VertexStruct; // = 36 octets

class Renderer
{
public:

	Renderer();
	ofImage image;
	void imageExport(const string name, const string extension) const;
	void imageImport(string path);
	void objImport(string path);
	void setup();
	void draw();

	void drawZone(float x1, float y1, float x2, float y2) const;
	void drawCursor(float x, float y) const;

	int xMousePress;
	int yMousePress;

	int xMouseCurrent;
	int yMouseCurrent;

	int modeCursor;

	VectorPrimitive drawMode;
	StructVectorPrimitive * shape;
	VertexStruct * vertexArray;
	GLuint vertexBufferID;
	int vertexBufferSize;
	vector<int> anglesShapes;
	int size;
	int stride;
	int head;
	int count;
	int index;
	float strokeWidthDefault;
	unsigned char fillColorH;
	unsigned char fillColorS;
	unsigned char fillColorB;

	void addVectorShape(VectorPrimitive type);
	void drawLine(float x1, float y1, float x2, float y2) const;
	void drawRectangle(float x1, float y1, float x2, float y2) const;
	void drawEllipse(float x1, float y1, float x2, float y2) const;

	void addToShape(float x1, float y1, float x2, float y2, unsigned char fillColorH, unsigned char fillColorS, unsigned char fillColorB, VectorPrimitive type);
	void removeFromShape();
	void translateShape(float xPressed, float yPressed, float xReleased, float yReleased);
	void proportionShape(float xPressed, float yPressed, float xReleased, float yReleased);
	void rotateShape(float xPressed, float yPressed, float xReleased, float yReleased);

	bool isOnRectangle(int index, int x, int y);

	bool isMouseButtonPressed;

	bool isOnLine(int index, int x, int y);

	bool isOnEllipse(int index, int x, int y);

	ofxAssimpModelLoader * objModel;
	bool isParticlesON;
	bool isProceduralGeometryON;
	const int nbrParticles = 500;
	void setupParticles();
	void setupProceduralGeometry();
	ofMesh meshParticles;
	ofMesh meshProceduralGeometry;
	ofImage textureParticles;
	~Renderer();
};
