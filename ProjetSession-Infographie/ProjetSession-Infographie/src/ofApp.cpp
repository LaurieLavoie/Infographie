#include "ofApp.h"

ofApp::ofApp()
{
	renderer = nullptr;
}

void ofApp::setup()
{
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

	cameraGui.setup();
	cameraGui.setPosition(210, 10);
	cameraGui.add(cameraProjectionButton.setup("Projecion"));
	cameraProjectionButton.addListener(this, &ofApp::cameraProjectionListener);
	cameraGui.add(cameraNearClipSlider.setup("Near clipping plane", 0.1f, 0.1f, 500.0f));
	cameraGui.add(cameraFarClipSlider.setup("Far clipping plane", 100.0f, 0.1f, 500.0f));
	cameraGui.add(cameraVFovSlider.setup("Vertical fov", 60.0f, 10.0f, 179.0f));
	cameraGui.add(cameraHFovSlider.setup("Horizontal fov", 60.0f, 10.0f, 179.0f));
	cameraGui.add(cameraAspectRatioSlider.setup("Aspect ratio", 1.666f, 0.25f, 4.0f));

	renderer = new Renderer();
	renderer->setup();

	scene = std::make_unique<Scene>();

	ofEnableAlphaBlending();

	// Add dummy mesh for tests
	auto raw_dummy = new ofCylinderPrimitive;
	std::shared_ptr<Entity> dummy(new Entity(raw_dummy));
	dummy->dolly(100.0f);
	scene->getRoot().addChild(dummy);

	auto raw_dummy2 = new ofCylinderPrimitive;
	std::shared_ptr<Entity> dummy2(new Entity(raw_dummy2));
	dummy2->dolly(-100.0f);
	dummy->addChild(dummy2);

	// Add dummy light
	auto raw_light = new ofLight();
	raw_light->enable();
	raw_light->setAmbientColor(ofColor(250.0f, 240.0f, 220.0f) * 0.1);
	raw_light->setPointLight();
	raw_light->boom(250.0f);
	raw_light->setDiffuseColor(ofColor(250.0f, 240.0f, 220.0f));
	std::shared_ptr<Entity> light(new Entity(raw_light)); // FIXME why is this not fixed at the camera's position? gotta investigate
	scene->mainCamera.addChild(light);
	scene->mainCamera.dolly(250.0f);
	scene->mainCamera.boom(50.0f);
}

void ofApp::update()
{

}

void ofApp::cameraProjectionListener() {
	if (scene == nullptr) return;

	scene->mainCamera.setOrtho(!scene->mainCamera.isOrtho());
}

void ofApp::cameraNearClipListener()
{
	this->scene->mainCamera.setNearClip(cameraNearClipSlider);
}

void ofApp::cameraFarClipListener()
{
	this->scene->mainCamera.setFarClip(cameraFarClipSlider);
}

void ofApp::cameraVFovListener()
{
	scene->mainCamera.setVerticalFov(cameraVFovSlider);
}

void ofApp::cameraHFovListener()
{
	scene->mainCamera.setHorizontalFov(cameraHFovSlider);
}

void ofApp::cameraAspectRatioListener()
{
	scene->mainCamera.setAspectRatio(cameraAspectRatioSlider);
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
	}
}

void ofApp::circleListener() {
	renderer->fillColorH = hue;
	renderer->fillColorS = saturation;
	renderer->fillColorB = brightness;
	renderer->drawMode = VectorPrimitive::ELLIPSE;

}

void ofApp::rectangleListener() {
	renderer->fillColorH = hue;
	renderer->fillColorS = saturation;
	renderer->fillColorB = brightness;
	renderer->drawMode = VectorPrimitive::RECTANGLE;
}

void ofApp::lineListener() {
	renderer->fillColorH = hue;
	renderer->fillColorS = saturation;
	renderer->fillColorB = brightness;
	renderer->drawMode = VectorPrimitive::LINE;
}

void ofApp::draw()
{
	ofClear(50.0f, 50.0f, 125.0f);

	renderer->draw();


	if (scene != nullptr)
	{
		ofEnableLighting();
		ofEnableDepthTest();

		scene->mainCamera.getOfCamera().begin();
		renderer->image.getTexture().bind();
		scene->mainCamera.draw();
		scene->getRoot().draw();
		renderer->image.getTexture().unbind();
		scene->mainCamera.getOfCamera().end();

		ofDisableDepthTest();
		ofDisableLighting();
	}


	gui.draw();
	cameraGui.draw();
}

void ofApp::mouseMoved(int x, int y)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	ofLog() << "<app::mouse move at: (" << x << ", " << y << ")>";
}

void ofApp::mouseDragged(int x, int y, int button)
{
	renderer->xMouseCurrent = x;
	renderer->yMouseCurrent = y;

	scene->mainCamera.orbit(x, y, 300, scene->getRoot());

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

	renderer->addVectorShape(renderer->drawMode);
	renderer->drawCursor(0,0,0);
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

	if (key == 114) {	//key r
		// History will be there one day
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
