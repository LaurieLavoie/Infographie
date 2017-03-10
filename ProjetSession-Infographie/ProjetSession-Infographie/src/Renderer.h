// IFT3100H17_Tryptique/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

enum class VectorPrimitive { NONE, PIXEL, POINT, LINE, RECTANGLE, ELLIPSE };

typedef struct
{
	VectorPrimitive type;          // 1 * 4 = 4  octets
	float         position1[2]; // 2 * 4 = 8  octets
	float         position2[2]; // 2 * 4 = 8  octets
	float         strokeWidth;     // 1 * 4 = 4  octets
	unsigned char strokeColor[4]; // 4 * 1 = 4  octets
	unsigned char fillColor[4]; // 4 * 1 = 4  octets
} StructVectorPrimitive;         //       = 32 octets


class Renderer
{
public:

	Renderer();
	ofImage image;
	void imageExport(const string name, const string extension) const;
	void imageImport(string path);
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
	void rotationShape(float xPressed, float yPressed, float xReleased, float yReleased);

	bool isMouseButtonPressed;



	~Renderer();
};
