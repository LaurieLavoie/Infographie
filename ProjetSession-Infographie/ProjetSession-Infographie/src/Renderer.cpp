// IFT3100H17_Tryptique/renderer.cpp
// Classe responsable du rendu de l'application.

	/* cos */
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

	if (isMouseButtonPressed && drawMode != VectorPrimitive::NONE)
	{
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

	drawCursor(xMouseCurrent, yMouseCurrent);


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
			ofPushMatrix();
			ofSetRectMode(OF_RECTMODE_CORNER);
			ofTranslate(shape[index].position1[0], 0, 0);
			ofTranslate(0, shape[index].position1[1], 0);
			ofRotateZ(anglesShapes[index]);

			drawRectangle(
				0,
				0,
				shape[index].position2[0] - shape[index].position1[0],
				shape[index].position2[1] - shape[index].position1[1]);

			ofPopMatrix();



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

	anglesShapes.push_back(0);

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

void Renderer::drawCursor(float x, float y) const
{
	ofSetLineWidth(2);
	ofSetColor(32);
	float length = 10.0f;
	float offset = 5.0f;
	float place = 15.0f;
	if (modeCursor == 0)
	{

	}
	else if (modeCursor == 1) {
		ofDrawLine(x + offset, y, x + offset + length, y);
		ofDrawLine(x - offset, y, x - offset - length, y);
		ofDrawLine(x, y + offset, x, y + offset + length);
		ofDrawLine(x, y - offset, x, y - offset - length);
	}
	else if (modeCursor == 2) {
		ofSetLineWidth(5);
		ofDrawArrow(ofVec3f(x + offset, y), ofVec3f(x + offset + length, y), 5);
		ofDrawArrow(ofVec3f(x - offset, y), ofVec3f(x - offset - length, y), 5);
		ofDrawArrow(ofVec3f(x, y + offset), ofVec3f(x, y + offset + length), 5);
		ofDrawArrow(ofVec3f(x, y - offset), ofVec3f(x, y - offset - length), 5);
	}
	else if (modeCursor == 3) {
		ofDrawLine(x - offset, y + offset + place, x + offset + length, y + offset + place);
		ofDrawLine(x + offset + length, y + offset + place, x + offset * 2 + length, y + place);
		ofDrawLine(x + offset + length, y - offset + place, x + offset * 2 + length, y + place);
		ofDrawLine(x - offset, y - offset + place, x + offset + length, y - offset + place);
		ofDrawArrow(ofVec3f(x - offset, y + offset + place), ofVec3f(x - offset - length, y + offset + place), 3);
	}
	else if (modeCursor == 4) {
		ofSetLineWidth(5);
		ofDrawLine(x - offset, y + offset + place, x - offset + 25, y + offset + place + 25);
		ofDrawEllipse(x - offset, y + offset + place, 20, 20);
		ofSetColor(100);
		ofDrawEllipse(x - offset, y + offset + place, 15, 15);
	}
	else if (modeCursor == 5) {
		ofNoFill();
		ofRectangle myRect;
		myRect.x = x - offset;
		myRect.y = y - offset;
		myRect.width = 65;
		myRect.height = 40;

		ofDrawRectRounded(myRect, 10);
		ofPoint position = ofPoint(x + 35, y + 15);
		ofDrawCircle(position, 7);
		ofDrawCircle(position, 3);
		ofDrawRectangle(x + 4, y - 12, 10, 7);

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
		shape[head - 1].type = VectorPrimitive::NONE;

		head = head - 1;
	}
}

void Renderer::translateShape(float xPressed, float yPressed, float xReleased, float yReleased)
{
	int tolerance = 1;
	int translateX = xReleased - xPressed;
	int translateY = yReleased - yPressed;
	for (index = 0; index < count; ++index)
	{
		if (shape[index].type == VectorPrimitive::LINE)
		{
			if (std::abs((xPressed - shape[index].position2[0]) / (shape[index].position2[0] - shape[index].position1[0]) - (yPressed - shape[index].position1[1]) / (shape[index].position2[1] - shape[index].position1[1])) < tolerance)
			{
				ofLog() << "Line here";

				shape[index].position1[0] = shape[index].position1[0] + translateX;
				shape[index].position1[1] = shape[index].position1[1] + translateY;
				shape[index].position2[0] = shape[index].position2[0] + translateX;
				shape[index].position2[1] = shape[index].position2[1] + translateY;
			}
		}
		else if (shape[index].type == VectorPrimitive::RECTANGLE)
		{
			if (xPressed < shape[index].position2[0] && xPressed > shape[index].position1[0] && yPressed < shape[index].position2[1] && yPressed > shape[index].position1[1])
			{
				ofLog() << "Rectangle here";
				shape[index].position1[0] = shape[index].position1[0] + translateX;
				shape[index].position1[1] = shape[index].position1[1] + translateY;
				shape[index].position2[0] = shape[index].position2[0] + translateX;
				shape[index].position2[1] = shape[index].position2[1] + translateY;
			}
		}
		else if (shape[index].type == VectorPrimitive::ELLIPSE)
		{

		}
	}
}

void Renderer::proportionShape(float xPressed, float yPressed, float xReleased, float yReleased)
{
	int tolerance = 1;
	for (index = 0; index < count; ++index)
	{
		if (shape[index].type == VectorPrimitive::LINE)
		{
			if (std::abs((xPressed - shape[index].position2[0]) / (shape[index].position2[0] - shape[index].position1[0]) - (yPressed - shape[index].position1[1]) / (shape[index].position2[1] - shape[index].position1[1])) < tolerance)
			{
				ofLog() << "Line here";

				shape[index].position2[0] = xReleased;
				shape[index].position2[1] = yReleased;
			}
		}
		else if (shape[index].type == VectorPrimitive::RECTANGLE)
		{
			if (xPressed < shape[index].position2[0] && xPressed > shape[index].position1[0] && yPressed < shape[index].position2[1] && yPressed > shape[index].position1[1])
			{
				ofLog() << "Rectangle here";
				shape[index].position2[0] = xReleased;
				shape[index].position2[1] = yReleased;
			}
		}
		else if (shape[index].type == VectorPrimitive::ELLIPSE)
		{

		}
	}
}

void Renderer::rotateShape(float xPressed, float yPressed, float xReleased, float yReleased)
{
	int tolerance = 1;
	int angle = 0;


	for (index = 0; index < count; ++index)
	{
		if (shape[index].type == VectorPrimitive::LINE)
		{
			if (std::abs((xPressed - shape[index].position2[0]) / (shape[index].position2[0] - shape[index].position1[0]) - (yPressed - shape[index].position1[1]) / (shape[index].position2[1] - shape[index].position1[1])) < tolerance)
			{
				ofLog() << "Line here";

				//shape[index].position2[0] = xReleased;
				//shape[index].position2[1] = yReleased;
			}
		}
		else if (shape[index].type == VectorPrimitive::RECTANGLE)
		{

			if (isOnRectangle(index, xPressed, yPressed))
			{
				ofLog() << "Rectangle here";
				if (anglesShapes[index] == 360) {
					anglesShapes[index] = 0;
				}
					anglesShapes[index] += 45;
			}
		}
		else if (shape[index].type == VectorPrimitive::ELLIPSE)
		{

		}
	}
}

bool Renderer::isOnRectangle(int index, int x, int y)
{
	if (anglesShapes[index] == 0) {
		return x < shape[index].position2[0] && x > shape[index].position1[0] && y < shape[index].position2[1] && y > shape[index].position1[1];
	}
	else {
		int xmin = (shape[index].position1[0] - (shape[index].position2[0] - shape[index].position1[0]));
		int xmax = (shape[index].position2[0] + (shape[index].position2[0] - shape[index].position1[0]));
		int ymin = (shape[index].position1[1] - (shape[index].position2[1] - shape[index].position1[1]));
		int ymax = (shape[index].position2[1] + (shape[index].position2[1] - shape[index].position1[1]));
		
	/*	float x1 = shape[index].position1[0];
		float y1 = shape[index].position1[1];

		float x0 = x1;
		float y0 = y1;
 

		float x2 = shape[index].position2[0];
		float y2 = shape[index].position1[1];

		float x3 = shape[index].position2[0];
		float y3 = shape[index].position2[1];

		float x4 = shape[index].position1[0];
		float y4 = shape[index].position2[1];

		int angle = 360 - anglesShapes[index];
		float x1b = x0 + (x1 - x0) * cos(angle) + (y1 - y0) *sin(angle);
		float y1b = y0 - (x1 - x0) * sin(angle) + (y1 - y0) * cos(angle);

		float x2b = x0 + (x2 - x0) * cos(angle) + (y2 - y0) *sin(angle);
		float y2b = y0 - (x2 - x0) * sin(angle) + (y2 - y0) * cos(angle);

		float x3b = x0 + (x3 - x0) * cos(angle) + (y3 - y0) *sin(angle);
		float y3b = y0 - (x3 - x0) * sin(angle) + (y3 - y0) * cos(angle);

		float x4b = x0 + (x4 - x0) * cos(angle) + (y4 - y0) *sin(angle);
		float y4b = y0 - (x4 - x0) * sin(angle) + (y4 - y0) * cos(angle);

		vector<float> xs = {x1b,x2b,x3b,x4b };
		vector<float>  ys = {y1b,y2b,y3b,y4b };

		std::sort(xs.begin(), xs.end());

		std::sort(ys.begin(), ys.end());

		float xmin = xs[0];
		float xmax = xs[xs.size() - 1];
		float ymin = ys[0];
		float ymax = ys[ys.size() - 1];*/

		return x >  xmin && x < xmax && y > ymin  && y < ymax;
	}
}

Renderer::~Renderer()
{
}
