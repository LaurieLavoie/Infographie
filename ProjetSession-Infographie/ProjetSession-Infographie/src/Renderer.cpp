// IFT3100H17_Tryptique/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer()
{

}

void Renderer::setup()
{
	ofSetFrameRate(60);
	image.load("image.jpg");
	ofSetWindowShape(image.getWidth(), image.getHeight());
	xMousePress = yMousePress = 0;
	xMouseCurrent = yMouseCurrent = 0;

	count = 100;
	stride = sizeof(StructVectorPrimitive);
	size = count * stride;
	head = 0;
	strokeWidthDefault = 2;
	shape = (StructVectorPrimitive *)calloc(size, stride);
	isMouseButtonPressed = false;
}

void Renderer::draw()
{
	// couleur de l'arrière-plan
	ofClear(0);

	// tinte de l'image (blanc pour les couleurs d'origine)
	ofSetColor(255);

	// afficher l'image sur toute la surface de la fenêtre
	image.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	if (isMouseButtonPressed)
	{
		drawCursor(xMouseCurrent, yMouseCurrent, 1);
		ofSetColor(255);
		ofSetLineWidth(3);
		ofNoFill();

		drawZone(
			xMousePress,
			yMousePress,
			xMouseCurrent,
			yMouseCurrent);
	}

	ofColor c = ofColor(0);
	for (index = 0; index < count; ++index)
	{
		switch (shape[index].type)
		{


		case VectorPrimitive::LINE:

			ofNoFill();
			ofSetLineWidth(shape[index].strokeWidth);
			c.setHsb(shape[index].fillColor[0], shape[index].fillColor[1], shape[index].fillColor[2]);
			ofSetColor(c);
			drawLine(
				shape[index].position1[0],
				shape[index].position1[1],
				shape[index].position2[0],
				shape[index].position2[1]);
			break;

		case VectorPrimitive::RECTANGLE:

			ofFill();
			ofSetLineWidth(0);
			c.setHsb(shape[index].fillColor[0], shape[index].fillColor[1], shape[index].fillColor[2]);
			ofSetColor(c);
			drawRectangle(
				shape[index].position1[0],
				shape[index].position1[1],
				shape[index].position2[0],
				shape[index].position2[1]);
			break;

		case VectorPrimitive::ELLIPSE:

			ofFill();
			ofSetLineWidth(0);
			ofSetCircleResolution(48);
			c.setHsb(shape[index].fillColor[0], shape[index].fillColor[1], shape[index].fillColor[2]);
			ofSetColor(c);
			drawEllipse(
				shape[index].position1[0],
				shape[index].position1[1],
				shape[index].position2[0],
				shape[index].position2[1]);

		default:
			break;
		}
	}
	
}


void Renderer::imageExport(const string name, const string extension) const
{
	ofImage imageTemp;
	string timestamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");
	string fileName = name + timestamp + "." + extension;

	imageTemp.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	imageTemp.save(fileName);
}

void Renderer::imageImport(string path) {
	/*int imageWidth;
	int imageHeight;
	int imageComponent;
	int imagePixelCount;
	int imageSize;

	GLuint textureID;
	GLubyte * pixels;

	imagePixelCount = imageWidth * imageHeight;
	imageSize = imagePixelCount * imageComponent;
	pixels = (GLubyte *)calloc(imageSize, sizeof(GLubyte));
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glGenerateMipmap(GL_TEXTURE_2D);

	free(pixels);*/
	image.load(path);
	ofSetWindowShape(image.getWidth(), image.getHeight());
}

void Renderer::addVectorShape(VectorPrimitive type)
{
	shape[head].type = type;

	shape[head].position1[0] = xMousePress;
	shape[head].position1[1] = yMousePress;

	shape[head].position2[0] = xMouseCurrent;
	shape[head].position2[1] = yMouseCurrent;

	shape[head].fillColor[0] = fillColorH;
	shape[head].fillColor[1] = fillColorS;
	shape[head].fillColor[2] = fillColorB;

	shape[head].strokeWidth = strokeWidthDefault;

	head = ++head >= count ? 0 : head;

	ofLog() << "<add a vector primitive to collection at index: " << head << ">";
}

void Renderer::drawLine(float x1, float y1, float x2, float y2) const
{
	ofDrawLine(x1, y1, x2, y2);
}

void Renderer::drawRectangle(float x1, float y1, float x2, float y2) const
{
	ofDrawRectangle(x1, y1, x2 - x1, y2 - y1);
}

void Renderer::drawEllipse(float x1, float y1, float x2, float y2) const
{
	float xDiameter = x2 - x1;
	float yDiameter = y2 - y1;

	ofDrawEllipse(x1 + xDiameter / 2.0f, y1 + yDiameter / 2.0f, xDiameter, yDiameter);
}

void Renderer::drawZone(float x1, float y1, float x2, float y2) const
{
	float x2Clamp = min(max(0.0f, x2), (float)ofGetWidth());
	float y2Clamp = min(max(0.0f, y2), (float)ofGetHeight());

	switch (drawMode)
	{

	case VectorPrimitive::LINE:
		drawLine(x1, y1, x2, y2);
		break;

	case VectorPrimitive::RECTANGLE:
		drawRectangle(x1, y1, x2, y2);
		break;

	case VectorPrimitive::ELLIPSE:
		drawEllipse(x1, y1, x2, y2);
		break;

	default:
		shape[head].strokeWidth = strokeWidthDefault;
		break;
	}
}

void Renderer::drawCursor(float x, float y,int cursorNum) const
{
	if (cursorNum == 0)
	{

	}
	else {
		ofSetLineWidth(2);
		ofSetColor(32);
		float length = 10.0f;
		float offset = 5.0f;

		ofDrawLine(x + offset, y, x + offset + length, y);
		ofDrawLine(x - offset, y, x - offset - length, y);
		ofDrawLine(x, y + offset, x, y + offset + length);
		ofDrawLine(x, y - offset, x, y - offset - length);
	}

	
}

void Renderer::addToShape(float x1, float y1, float x2, float y2, unsigned char fillColorH, unsigned char fillColorS, unsigned char fillColorB, VectorPrimitive type)
{
	if (head >= 1)
	{
		shape[head].position1[0] = x1;
		shape[head].position1[1] = y1;

		shape[head].position2[0] = x2;
		shape[head].position2[1] = y2;

		shape[head].fillColor[0] = fillColorH;
		shape[head].fillColor[1] = fillColorS;
		shape[head].fillColor[2] = fillColorB;

		shape[head].type = type;

		shape[head].strokeWidth = strokeWidthDefault;

		head = ++head >= count ? 0 : head;
	}
}

void Renderer::removeFromShape()
{
	if (head >= 1)
	{
		shape[head-1].type = VectorPrimitive::NONE;

		head = head - 1;
	}
}

Renderer::~Renderer()
{
}
