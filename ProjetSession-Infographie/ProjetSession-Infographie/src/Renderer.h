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

				// fonction d'évaluation d'une courbe de Bézier cubique (4 points de contrôle)
inline void bezierCubic(
	float t,
	float p1x, float p1y, float p1z,
	float p2x, float p2y, float p2z,
	float p3x, float p3y, float p3z,
	float p4x, float p4y, float p4z,
	float&  x, float& y, float&  z)
{
	float u = 1 - t;
	float uu = u * u;
	float uuu = uu * u;
	float tt = t * t;
	float ttt = tt * t;

	x = uuu * p1x + 3 * uu * t * p2x + 3 * u * tt * p3x + ttt * p4x;
	y = uuu * p1y + 3 * uu * t * p2y + 3 * u * tt * p3y + ttt * p4y;
	z = uuu * p1z + 3 * uu * t * p2z + 3 * u * tt * p3z + ttt * p4z;
}

enum class Curve { BEZIER_CUBIC, HERMITE, SPLINE, NONE };

// fonction d'évaluation d'une courbe de hermite (4 points de contrôle)
inline void hermite(
	float t,
	float p1x, float p1y, float p1z,
	float p2x, float p2y, float p2z,
	float p3x, float p3y, float p3z,
	float p4x, float p4y, float p4z,
	float&  x, float& y, float&  z)
{
	float u = 1 - t;
	float uu = u * u;
	float uuu = uu * u;
	float tt = t * t;
	float ttt = tt * t;

	x = (2 * ttt - 3 * tt + 1) * p1x + (ttt - 2 * tt + t) * p2x + (ttt - tt) * p3x + (-2 * ttt + 3 * tt) * p4x;
	y = (2 * ttt - 3 * tt + 1) * p1y + (ttt - 2 * tt + t) * p2y + (ttt - tt) * p3y + (-2 * ttt + 3 * tt) * p4y;
	z = (2 * ttt - 3 * tt + 1) * p1z + (ttt - 2 * tt + t) * p2z + (ttt - tt) * p3z + (-2 * ttt + 3 * tt) * p4z;
}

inline void spline(
	float t,
	float p1x, float p1y, float p1z,
	float p2x, float p2y, float p2z,
	float p3x, float p3y, float p3z,
	float p4x, float p4y, float p4z,
	float p5x, float p5y, float p5z,
	float&  x, float& y, float&  z)
{
	float u = 1 - t;
	float uu = u * u;
	float uuu = uu * u;
	float uuuu = uuu * u;
	float tt = t * t;
	float ttt = tt * t;
	float tttt = ttt * t;

	x = uuuu * p1x + 4 * uuu * t * p2x + 4 * uu * tt * p3x + 4 * u * ttt * p4x + tttt * p5x;
	y = uuuu * p1y + 4 * uuu * t * p2y + 4 * uu * tt * p3y + 4 * u * ttt * p4y + tttt * p5y;
	z = uuuu * p1z + 4 * uuu * t * p2z + 4 * uu * tt * p3z + 4 * u * ttt * p4z + tttt * p5z;
}


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

	Curve curveID;
	ofPolyline lineRenderer;
	ofVec3f * selectedCtrlPoint;
	ofVec3f ctrlPoint1;
	ofVec3f ctrlPoint2;
	ofVec3f ctrlPoint3;
	ofVec3f ctrlPoint4;
	ofVec3f ctrlPoint5;
	ofVec3f position;
	int lineResolution;
	float radius;
	float scale;
	float smooth;
	float offset;
	float lineWidthOutline;
	float lineWidthCurve;
	float xDelta;
	float yDelta;
	float motionSpeed;
	int framebufferWidth;
	int framebufferHeight;
	int indexCurb;
	~Renderer();
};
