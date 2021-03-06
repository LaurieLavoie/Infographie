// IFT3100H17_Tryptique/renderer.cpp
// Classe responsable du rendu de l'application.

	/* cos */
#include "renderer.h"


Renderer::Renderer(ofShader sshaderColor, ofShader sshaderGeo)
{
	shaderGeo = sshaderGeo;
	shaderColor = sshaderColor;
}

void Renderer::setup()
{
	isVoronoi = false;
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

	isParticlesON = false;
	isProceduralGeometryON = false;

	lineResolution = 100;

	radius = 32.0f;
	scale = 10.0f;
	offset = 64.0f;

	lineWidthOutline = 4.0f;
	lineWidthCurve = 8.0f;

	motionSpeed = 250.0f;

	for (indexCurb = 0; indexCurb <= lineResolution; ++indexCurb)
		lineRenderer.addVertex(ofPoint());

	curveID = Curve::NONE;

}
void Renderer::setupParticles() {
	meshParticles.clear();
	meshParticles.setMode(OF_PRIMITIVE_POINTS);
	for (int i = 0; i < nbrParticles; i++) {
		ofVec2f p = ofVec2f(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
		meshParticles.addVertex(p);
		meshParticles.addColor(ofColor(255, 255, 255));
	}
	ofDisableArbTex();
	textureParticles.loadImage("fire.jpg");
	glPointSize(28);
	isParticlesON = !isParticlesON;
	isProceduralGeometryON = !isProceduralGeometryON;


}
void Renderer::setupProceduralGeometry() {
	meshProceduralGeometry.clear();
	meshProceduralGeometry.setMode(OF_PRIMITIVE_POINTS);
	isProceduralGeometryON = !isProceduralGeometryON;
	if (isProceduralGeometryON) {

		int w = image.getWidth();
		int h = image.getHeight();
		for (int x = 0; x < w; ++x) {
			for (int y = 0; y < h; ++y) {
				ofColor c = image.getColor(x, y);
				float intensity = c.getLightness();
				ofVec3f pos(x, y, intensity * 10);
				meshProceduralGeometry.addVertex(pos);
				meshProceduralGeometry.addColor(ofColor(c));
			}
		}
	}
}
void Renderer::draw()
{
	// couleur de l'arri�re-plan
	ofClear(0);

	// tinte de l'image (blanc pour les couleurs d'origine)
	ofSetColor(255);

	// afficher l'image sur toute la surface de la fen�tre
	image.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	//if (isParticlesON) {
	//	ofEnableAlphaBlending();
	//	ofEnablePointSprites();
	//	textureParticles.getTextureReference().bind();
	//	meshParticles.drawFaces();
	//	textureParticles.getTextureReference().unbind();
	//}
	//
	//if (isProceduralGeometryON) {
	//	meshProceduralGeometry.draw();
	//}

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
		ofFill();
	}

	ofColor c = ofColor(0);

	drawCursor(xMouseCurrent, yMouseCurrent);


	for (index = 0; index < count; ++index)
	{
		switch (shape[index].type)
		{


		case VectorPrimitive::LINE:


			ofPushMatrix();

			if (shaderModeGeo)
			{
				shaderGeo.begin();

				shaderGeo.setUniform1f("thickness", 20);
				shaderGeo.setUniform3f("lightDir", sin(ofGetElapsedTimef() / 10), cos(ofGetElapsedTimef() / 10), 0);
			}
				
			
				ofSetLineWidth(shape[index].strokeWidth);
				c.setHsb(shape[index].fillColor[0], shape[index].fillColor[1], shape[index].fillColor[2]);
				ofSetColor(c);

				drawLine(
					shape[index].position1[0],
					shape[index].position1[1],
					shape[index].position2[0],
					shape[index].position2[1]);

				if (shaderModeGeo) {
					shaderGeo.end();
				}
		

			ofPopMatrix();

			break;

		case VectorPrimitive::RECTANGLE:

			ofFill();
			ofSetLineWidth(0);
			c.setHsb(shape[index].fillColor[0], shape[index].fillColor[1], shape[index].fillColor[2]);
			ofSetColor(c);
			ofPushMatrix();

			if (shaderMode)
			{
				shaderColor.begin();
			}

			ofSetRectMode(OF_RECTMODE_CORNER);
			ofTranslate(shape[index].position1[0], 0, 0);
			ofTranslate(0, shape[index].position1[1], 0);
			ofRotateZ(anglesShapes[index]);

			drawRectangle(
				0,
				0,
				shape[index].position2[0] - shape[index].position1[0],
				shape[index].position2[1] - shape[index].position1[1]);

			if (shaderMode)
			{
				shaderColor.end();
			}

			ofPopMatrix();

			break;

		case VectorPrimitive::ELLIPSE:

			ofFill();
			ofSetLineWidth(0);
			ofSetCircleResolution(48);
			c.setHsb(shape[index].fillColor[0], shape[index].fillColor[1], shape[index].fillColor[2]);
			ofSetColor(c);

			ofPushMatrix();
			ofSetRectMode(OF_RECTMODE_CORNER);
			ofTranslate(shape[index].position1[0], 0, 0);
			ofTranslate(0, shape[index].position1[1], 0);
			ofRotateZ(anglesShapes[index]);

			drawEllipse(
				0,
				0,
				shape[index].position2[0] - shape[index].position1[0],
				shape[index].position2[1] - shape[index].position1[1]);

			ofPopMatrix();
			break;


		default:
			break;
		}
	}

	if (curveID != Curve::NONE)
	{

		ofSetColor(63, 63, 63);

		// dessiner la ligne contour
		ofSetColor(0, 0, 255);
		ofSetLineWidth(lineWidthOutline);

		ofDrawLine(ctrlPoint1.x, ctrlPoint1.y, ctrlPoint2.x, ctrlPoint2.y);
		ofDrawLine(ctrlPoint3.x, ctrlPoint3.y, ctrlPoint4.x, ctrlPoint4.y);
			ofDrawLine(ctrlPoint2.x, ctrlPoint2.y, ctrlPoint3.x, ctrlPoint3.y);
			
			if (curveID == Curve::SPLINE)
			{
				ofDrawLine(ctrlPoint4.x, ctrlPoint4.y, ctrlPoint5.x, ctrlPoint5.y);
				ofDrawLine(ctrlPoint5.x, ctrlPoint5.y, ctrlPoint1.x, ctrlPoint1.y);
			}
			else
			{
				ofDrawLine(ctrlPoint4.x, ctrlPoint4.y, ctrlPoint1.x, ctrlPoint1.y);
			}


		// dessiner la courbe
		ofSetColor(0, 255, 0);
		ofSetLineWidth(lineWidthCurve);

		lineRenderer.draw();

		// dessiner les points de contr�le
		ofSetColor(255, 0, 0);

		ofDrawEllipse(ctrlPoint1.x, ctrlPoint1.y, radius, radius);
		ofDrawEllipse(ctrlPoint2.x, ctrlPoint2.y, radius, radius);
		ofDrawEllipse(ctrlPoint3.x, ctrlPoint3.y, radius, radius);
		ofDrawEllipse(ctrlPoint4.x, ctrlPoint4.y, radius, radius);
		if (curveID == Curve::SPLINE)
		{
			ofDrawEllipse(ctrlPoint5.x, ctrlPoint5.y, radius, radius);
		}

		ofVec3f tangent1 = ctrlPoint2 - ctrlPoint1;
		ofVec3f tangent2 = ctrlPoint3 - ctrlPoint4;

		for (index = 0; index <= lineResolution; ++index)
		{
			// param�tres selon le type de courbe
			switch (curveID)
			{
			case Curve::HERMITE:

				hermite(
					index / (float)lineResolution,
					ctrlPoint1.x, ctrlPoint1.y, ctrlPoint1.z,
					tangent1.x, tangent1.y, tangent1.z,
					tangent2.x, tangent2.y, tangent2.z,
					ctrlPoint4.x, ctrlPoint4.y, ctrlPoint4.z,
					position.x, position.y, position.z);
				break;

			case Curve::BEZIER_CUBIC:
				bezierCubic(
					index / (float)lineResolution,
					ctrlPoint1.x, ctrlPoint1.y, ctrlPoint1.z,
					ctrlPoint2.x, ctrlPoint2.y, ctrlPoint2.z,
					ctrlPoint3.x, ctrlPoint3.y, ctrlPoint3.z,
					ctrlPoint4.x, ctrlPoint4.y, ctrlPoint4.z,
					position.x, position.y, position.z);
				break;
			case Curve::SPLINE:
				spline(
					index / (float)lineResolution,
					ctrlPoint1.x, ctrlPoint1.y, ctrlPoint1.z,
					ctrlPoint2.x, ctrlPoint2.y, ctrlPoint2.z,
					ctrlPoint3.x, ctrlPoint3.y, ctrlPoint3.z,
					ctrlPoint4.x, ctrlPoint4.y, ctrlPoint4.z,
					ctrlPoint5.x, ctrlPoint5.y, ctrlPoint5.z,
					position.x, position.y, position.z);
				break;
			default:
				break;
			}
			// affecter la position du point sur la courbe
			lineRenderer[index] = position;
		}
	}

	if (isVoronoi)
	{
		drawVoronoi();
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

void Renderer::objImport(string path) {
	objModel = new ofxAssimpModelLoader();
	objModel->loadModel(path);

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
		ofFill();
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
			float radius1 = (shape[index].position2[0] - shape[index].position1[0]) / 2;
			float radius2 = (shape[index].position2[1] - shape[index].position1[1]) / 2;
			float test1 = yPressed - shape[index].position1[1] - radius2;
			float test2 = xPressed - shape[index].position1[0] - radius1;
			float firstFormula = ((test1 * test1) / (radius2 * radius2));
			float secondFormula = ((test2*test2) / (radius1 * radius1));
			float result = firstFormula + secondFormula;

			if (result < 1)
			{
				ofLog() << "Ellipse here";
				shape[index].position1[0] = shape[index].position1[0] + translateX;
				shape[index].position1[1] = shape[index].position1[1] + translateY;
				shape[index].position2[0] = shape[index].position2[0] + translateX;
				shape[index].position2[1] = shape[index].position2[1] + translateY;

			}
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
			if (isOnLine(index, xPressed, yPressed))
			{
				ofLog() << "Line here";

				float tempX = shape[index].position2[0] - shape[index].position1[0];
				float tempY = shape[index].position2[1] - shape[index].position1[1];

				float rotatedX = tempX*cos(45) - tempY*sin(45);
				float rotatedY = tempX*sin(45) + tempY*cos(45);

				shape[index].position2[0] = rotatedX + shape[index].position1[0];
				shape[index].position2[1] = rotatedY + shape[index].position1[1];



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

			if (isOnEllipse(index, xPressed, yPressed))
			{
				ofLog() << "Ellipse here";
				if (anglesShapes[index] == 360) {
					anglesShapes[index] = 0;
				}
				anglesShapes[index] += 45;
			}

		}
	}
}


bool Renderer::isOnLine(int index, int x, int y)
{
	int tolerance = 3;
	return 	std::abs((x - shape[index].position2[0]) / (shape[index].position2[0] - shape[index].position1[0]) - (y - shape[index].position1[1]) / (shape[index].position2[1] - shape[index].position1[1])) < tolerance;

}

bool Renderer::isOnEllipse(int index, int x, int y)
{
	//if (anglesShapes[index] == 0) {
	if (anglesShapes[index] == 0) {
		float radius1 = (shape[index].position2[0] - shape[index].position1[0]) / 2;
		float radius2 = (shape[index].position2[1] - shape[index].position1[1]) / 2;
		float test1 = y - shape[index].position1[1] - radius2;
		float test2 = x - shape[index].position1[0] - radius1;
		float firstFormula = ((test1 * test1) / (radius2 * radius2));
		float secondFormula = ((test2*test2) / (radius1 * radius1));
		float result = firstFormula + secondFormula;

		return result < 1;
	}
	else {

		int xmin = (shape[index].position1[0] - (shape[index].position2[0] - shape[index].position1[0]));
		int xmax = (shape[index].position2[0] + (shape[index].position2[0] - shape[index].position1[0]));
		int ymin = (shape[index].position1[1] - (shape[index].position2[1] - shape[index].position1[1]));
		int ymax = (shape[index].position2[1] + (shape[index].position2[1] - shape[index].position1[1]));

		return x > xmin && x < xmax && y > ymin  && y < ymax;
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



		return x > xmin && x < xmax && y > ymin  && y < ymax;
	}
}

void Renderer::drawVoronoi()
{
	ofxVoronoi2D voronoi;
	vector<ofVec2f> pts;
	pts.push_back(ofVec2f(float(15), float(155)));
	pts.push_back(ofVec2f(float(78), float(261)));
	pts.push_back(ofVec2f(float(456), float(82)));
	pts.push_back(ofVec2f(float(756), float(432)));
	pts.push_back(ofVec2f(float(715), float(264)));

	voronoi.compute(pts, ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));

	for (ofxSegmentIterator it = voronoi.edges(); it; ++it) {
		ofxSegment s = *it;
		ofLine(s.p1, s.p2);
	}

	ofMesh mesh;
	voronoi.buildMesh(mesh);
	mesh.setColorForIndices(0, mesh.getNumIndices(), ofFloatColor(1.0f, 1.0f, 1.0f));
	for (unsigned int i = 0; i < mesh.getNumIndices(); i += 3) {
		mesh.setColor(mesh.getIndex(i), ofFloatColor(0.0f, 0.0f, 1.0f)); // cell centers
	}
	mesh.draw();
}


Renderer::~Renderer()
{
	delete objModel;
}
