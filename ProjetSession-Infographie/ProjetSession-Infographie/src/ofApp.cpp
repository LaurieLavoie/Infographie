#include "ofApp.h"

ofApp::ofApp()
{
	renderer = nullptr;
}

void ofApp::setup()
{
	/*isKeyPressUp = false;
	isKeyPressDown = false;
	isKeyPressLeft = false;
	isKeyPressRight = false;
*/
	indexPointCurb = 0;

#ifdef TARGET_OPENGLES
	shader.load("shadersES2/shader");
#else
	if (ofIsGLProgrammableRenderer()) {
		shader.load("shadersGL3/shader");
	}
	else {
		ofSetLogLevel(OF_LOG_VERBOSE);
		ofBackground(50, 50, 50);
		ofSetVerticalSync(false);
		ofEnableAlphaBlending();
		shader.load("shadersGL2/shader");
		shaderGeo.setGeometryInputType(GL_LINE);
		shaderGeo.setGeometryOutputType(GL_TRIANGLE_STRIP);
		shaderGeo.setGeometryOutputCount(4);
		shaderGeo.load("shadersGL3/vert.glsl", "shadersGL3/frag.glsl", "shadersGL3/geom.glsl");
	
		ofEnableDepthTest();
	}
#endif


	ofSetWindowTitle("Projet session");

	isLine = false;

	gui.setup();

	gui.add(hue.setup("hue", 0, 0, 255));
	gui.add(saturation.setup("saturation", 0, 0, 255));
	gui.add(brightness.setup("brightness", 0, 0, 255));

	gui.add(circleButton.setup("circle"));
	circleButton.addListener(this, &ofApp::circleListener);
	gui.add(rectangleButton.setup("rectangle"));
	rectangleButton.addListener(this, &ofApp::rectangleListener);
	gui.add(lineButton.setup("line"));
	lineButton.addListener(this, &ofApp::lineListener);
	gui.add(importButton.setup("import"));
	importButton.addListener(this, &ofApp::importListener);
	gui.add(exportButton.setup("export"));
	exportButton.addListener(this, &ofApp::exportListener);
	gui.add(translationButton.setup("translation"));
	translationButton.addListener(this, &ofApp::translationListener);
	gui.add(rotationButton.setup("rotation"));
	rotationButton.addListener(this, &ofApp::rotationListener);
	gui.add(proportionButton.setup("proportion"));
	proportionButton.addListener(this, &ofApp::proportionListener);
	gui.add(shaderColorButton.setup("shader de couleur"));
	shaderColorButton.addListener(this, &ofApp::shaderColorListener);
	gui.add(shaderGeoButton.setup("shader de geometrie"));
	shaderGeoButton.addListener(this, &ofApp::shaderGeoListener);

	cameraGui.setup();
	cameraGui.setPosition(210, 10);
	cameraGui.add(cameraStartButton.setup("Camera start"));
	cameraStartButton.addListener(this, &ofApp::cameraStartListener);
	cameraGui.add(cameraProjectionButton.setup("Projecion"));
	cameraProjectionButton.addListener(this, &ofApp::cameraProjectionListener);
	cameraGui.add(cameraNearClipSlider.setup("Near clipping plane", 0.1f, 0.1f, 1000.0f));
	cameraNearClipSlider.addListener(this, &ofApp::cameraNearClipListener);
	cameraGui.add(cameraFarClipSlider.setup("Far clipping plane", 250.0f, 0.1f, 1000.0f));
	cameraFarClipSlider.addListener(this, &ofApp::cameraFarClipListener);
	cameraGui.add(cameraVFovSlider.setup("Vertical fov", 60.0f, 10.0f, 179.0f));
	cameraVFovSlider.addListener(this, &ofApp::cameraVFovListener);
	cameraGui.add(cameraHFovSlider.setup("Horizontal fov", 60.0f, 10.0f, 179.0f));
	cameraHFovSlider.addListener(this, &ofApp::cameraHFovListener);
	cameraGui.add(cameraAspectRatioSlider.setup("Aspect ratio", 1.666f, 0.25f, 4.0f));
	cameraAspectRatioSlider.addListener(this, &ofApp::cameraAspectRatioListener);

	modelGui.setup();
	modelGui.setPosition(410, 10);
	modelGui.add(modelParticleButton.setup("Particles"));
	modelParticleButton.addListener(this, &ofApp::modelParticleListener);
	modelGui.add(modelShowPrimitivesButton.setup("Procedural Geometry"));
	modelShowPrimitivesButton.addListener(this, &ofApp::modelShowPrimitivesListener);

	curbGui.setup();
	curbGui.setPosition(610, 10);
	curbGui.add(hermiteButton.setup("Hermite"));
	hermiteButton.addListener(this, &ofApp::hermiteListener);
	curbGui.add(bezierButton.setup("Bezier"));
	bezierButton.addListener(this, &ofApp::bezierListener);
	curbGui.add(splineButton.setup("Spline bezier"));
	splineButton.addListener(this, &ofApp::splineListener);
	curbGui.add(voronoiButton.setup("Voronoi diagram"));
	voronoiButton.addListener(this, &ofApp::voronoiListener);

	renderer = new Renderer(shader, shaderGeo);
	renderer->setup();

	scene = std::make_unique<Scene>();

	ofEnableAlphaBlending();

	// Add dummy mesh for tests
	objModel = nullptr;

	// Add dummy light
	auto raw_light = new ofLight();
	raw_light->enable();
	raw_light->setAmbientColor(ofColor(250.0f, 240.0f, 220.0f) * 0.1f);
	raw_light->setPointLight();
	raw_light->boom(50.0f);
	raw_light->setDiffuseColor(ofColor(250.0f, 240.0f, 220.0f));
	raw_light->setSpecularColor(ofColor(250.0f, 240.0f, 220.0f));
	std::shared_ptr<Entity> light(new Entity(raw_light));
	scene->mainCamera.addChild(light);
	scene->mainCamera.dolly(250.0f);
	scene->mainCamera.boom(50.0f);

	scene->mainCamera.setOrbitRadius(300.0f);


}

void ofApp::update()
{

}

void ofApp::hermiteListener() {
	renderer->curveID = Curve::HERMITE;
	indexPointCurb = 0;
}

void ofApp::bezierListener() {

		renderer->curveID = Curve::BEZIER_CUBIC;
		indexPointCurb = 0;
}

void ofApp::splineListener() {
	renderer->curveID = Curve::SPLINE;
	indexPointCurb = 0;
}

void ofApp::voronoiListener() {
	if (renderer->isVoronoi)
	{
		renderer->isVoronoi = false;
	}
	else
	{
		renderer->isVoronoi = true;
	}
}

void ofApp::cameraStartListener() {
	renderer->modeCursor = 5;
}


void ofApp::cameraProjectionListener() {
	if (scene == nullptr) return;

	scene->mainCamera.setOrtho(!scene->mainCamera.isOrtho());
}

void ofApp::cameraNearClipListener(float& v)
{
	this->scene->mainCamera.setNearClip(v);
}

void ofApp::cameraFarClipListener(float& v)
{
	this->scene->mainCamera.setFarClip(v);
}

void ofApp::cameraVFovListener(float& v)
{
	scene->mainCamera.setVerticalFov(v);

	// Update HFov slider
	cameraHFovSlider.removeListener(this, &ofApp::cameraHFovListener);
	cameraHFovSlider = RAD_TO_DEG(Camera::VFovToHFov(DEG_TO_RAD(v), scene->mainCamera.getAspectRatio()));
	cameraHFovSlider.addListener(this, &ofApp::cameraHFovListener);
}

void ofApp::cameraHFovListener(float& v)
{
	scene->mainCamera.setHorizontalFov(v);

	// Update VFov slider
	cameraVFovSlider.removeListener(this, &ofApp::cameraVFovListener);
	cameraVFovSlider = RAD_TO_DEG(Camera::HFovToVFov(DEG_TO_RAD(v), scene->mainCamera.getAspectRatio()));
	cameraVFovSlider.addListener(this, &ofApp::cameraVFovListener);
}

void ofApp::cameraAspectRatioListener(float& v)
{
	scene->mainCamera.setAspectRatio(v);

	// Update HFov slider
	cameraHFovSlider.removeListener(this, &ofApp::cameraHFovListener);
	cameraHFovSlider = RAD_TO_DEG(Camera::VFovToHFov(DEG_TO_RAD(scene->mainCamera.getVerticalFov()), scene->mainCamera.getAspectRatio()));
	cameraHFovSlider.addListener(this, &ofApp::cameraHFovListener);
}

void ofApp::translationListener()
{
	renderer->drawMode = VectorPrimitive::NONE;
	renderer->modeCursor = 2;
	renderer->drawCursor(renderer->xMouseCurrent, renderer->yMouseCurrent);
}

void ofApp::rotationListener()
{
	renderer->drawMode = VectorPrimitive::NONE;
	renderer->modeCursor = 3;
	renderer->drawCursor(renderer->xMouseCurrent, renderer->yMouseCurrent);
}

void ofApp::proportionListener()
{
	renderer->drawMode = VectorPrimitive::NONE;
	renderer->modeCursor = 4;
	renderer->drawCursor(renderer->xMouseCurrent, renderer->yMouseCurrent);
}

void ofApp::shaderColorListener()
{
	if (renderer->shaderMode) {
		renderer->shaderMode = false;
	}
	else {
		renderer->shaderMode = true;
	}
}

void ofApp::shaderGeoListener()
{
	if (renderer->shaderModeGeo) {
		renderer->shaderModeGeo = false;
	}
	else {
		renderer->shaderModeGeo = true;
	}

}

void ofApp::exportListener() {
	renderer->imageExport("test", "jpg");
}

void ofApp::colorListener() {
	renderer->fillColorH = hue;
	renderer->fillColorS = saturation;
	renderer->fillColorB = brightness;
}

void ofApp::importListener() {
	ofFileDialogResult result = ofSystemLoadDialog("Load file");
	if (result.bSuccess) {
		string path = result.getPath();
		if (path.find(".jpg") != std::string::npos || path.find(".png") != std::string::npos)
		{
			renderer->imageImport(path);
		}
		else if (path.find(".obj") != std::string::npos) {
			objModel = new ofxAssimpModelLoader();
			objModel->loadModel(path);
		}
	}
}
void ofApp::modelShowPrimitivesListener() {
	renderer->setupProceduralGeometry();
}

void ofApp::modelParticleListener() {
	renderer->setupParticles();

}


void ofApp::circleListener() {
	renderer->modeCursor = 1;
	renderer->fillColorH = hue;
	renderer->fillColorS = saturation;
	renderer->fillColorB = brightness;
	renderer->drawMode = VectorPrimitive::ELLIPSE;

}

void ofApp::rectangleListener() {
	renderer->modeCursor = 1;
	renderer->fillColorH = hue;
	renderer->fillColorS = saturation;
	renderer->fillColorB = brightness;
	renderer->drawMode = VectorPrimitive::RECTANGLE;
}

void ofApp::lineListener() {
	renderer->modeCursor = 1;
	renderer->fillColorH = hue;
	renderer->fillColorS = saturation;
	renderer->fillColorB = brightness;
	renderer->drawMode = VectorPrimitive::LINE;
}

void ofApp::draw()
{

	ofClear(50.0f, 50.0f, 250.0f);





	renderer->draw();

	if (scene != nullptr)
	{
		ofSetColor(255);

		ofEnableLighting();
		ofEnableDepthTest();

		scene->mainCamera.getOfCamera().begin();
		renderer->image.getTexture().bind();
		scene->mainCamera.draw();
		scene->getRoot().draw();
		if (objModel != nullptr) {
			objModel->draw(OF_MESH_FILL);
		}
		ofDisableLighting();
		renderer->image.getTexture().unbind();
		ofDisableDepthTest();
		if (renderer->isProceduralGeometryON) {
			renderer->meshProceduralGeometry.draw();
		}
		if (renderer->isParticlesON) {
			ofEnableAlphaBlending();
			ofEnablePointSprites();
			renderer->textureParticles.getTextureReference().bind();
			renderer->meshParticles.drawFaces();
			renderer->textureParticles.getTextureReference().unbind();
		}
		scene->mainCamera.getOfCamera().end();

	}


	gui.draw();
	cameraGui.draw();
	modelGui.draw();
}

void ofApp::mouseMoved(int x, int y)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	ofLog() << "<app::mouse move at: (" << x << ", " << y << ")>";
}

void ofApp::mouseDragged(int x, int y, int button)
{
	auto delta_x = x - renderer->xMouseCurrent;
	auto delta_y = y - renderer->yMouseCurrent;

	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	if (renderer->modeCursor == 5)
	{
		if (button == OF_MOUSE_BUTTON_LEFT)
		{
			auto longitude = scene->mainCamera.getLongitude() + delta_x;
			auto latitude = scene->mainCamera.getLatitude() + delta_y;
			scene->mainCamera.setLongitude(longitude);
			scene->mainCamera.setLatitude(latitude);
		}
		else if (button == OF_MOUSE_BUTTON_RIGHT)
		{
			auto oldRadius = scene->mainCamera.getOrbitRadius();
			auto radius = oldRadius + (delta_y * log(oldRadius) * 0.75f);
			radius = radius <= 100.0f ? 100.0f : radius;
			scene->mainCamera.setOrbitRadius(radius);
		}
	}

	ofLog() << "<app::mouse drag at: (" << x << ", " << y << ") button:" << button << ">";
}

void ofApp::mousePressed(int x, int y, int button)
{
	renderer->isMouseButtonPressed = true;

	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	renderer->xMousePress = x;
	renderer->yMousePress = y;

	renderer->fillColorH = hue;
	renderer->fillColorS = saturation;
	renderer->fillColorB = brightness;

	ofLog() << "<app::mouse pressed  at: (" << x << ", " << y << ")>";
}

void ofApp::mouseReleased(int x, int y, int button)
{
	renderer->isMouseButtonPressed = false;

	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	lastMouseReleasedX = x;
	lastMouseReleasedY = y;

	renderer->addVectorShape(renderer->drawMode);
	renderer->drawCursor(0, 0);

	if (renderer->modeCursor == 2)
	{
		renderer->translateShape(renderer->xMousePress, renderer->yMousePress, x, y);
	}
	else if (renderer->modeCursor == 3)
	{
		renderer->rotateShape(renderer->xMousePress, renderer->yMousePress, x, y);
	}
	else if (renderer->modeCursor == 4)
	{
		renderer->proportionShape(renderer->xMousePress, renderer->yMousePress, x, y);
	}
	
	ofLog() << "<app::mouse released at: (" << x << ", " << y << ")>";
}

void ofApp::mouseEntered(int x, int y)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	ofLog() << "<app::mouse entered  at: (" << x << ", " << y << ")>";
}

void ofApp::mouseExited(int x, int y)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	ofLog() << "<app::mouse exited   at: (" << x << ", " << y << ")>";
}


void ofApp::keyReleased(int key) {

	switch (key)
	{
	case 114: //key r
		ofLog() << "Key R released";
		renderer->addToShape(renderer->xMousePress + 5, renderer->yMousePress + 5, lastMouseReleasedX + 5, lastMouseReleasedY + 5, renderer->fillColorH, renderer->fillColorS, renderer->fillColorB, renderer->drawMode);
		renderer->xMousePress = renderer->xMousePress + 5;
		renderer->yMousePress = renderer->yMousePress + 5;
		renderer->xMouseCurrent = lastMouseReleasedX + 5;
		renderer->yMouseCurrent = lastMouseReleasedY + 5;
		break;

	case 117:
		renderer->removeFromShape();
		ofLog() << "Key U released";
		break;

	default:
		break;
	}
}

void ofApp::exit()
{
	ofLog() << "<app::exit>";
}

ofApp::~ofApp()
{
	if (nullptr != renderer)
		delete renderer;
}
