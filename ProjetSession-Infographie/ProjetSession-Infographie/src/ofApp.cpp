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

	renderer = new Renderer();
	renderer->setup();

	scene = std::make_unique<Scene>();

	ofEnableAlphaBlending();

	// Add dummy mesh for tests
	auto raw_dummy = new ofCylinderPrimitive;
	std::shared_ptr<Entity> dummy(new Entity(raw_dummy));
	scene->getRoot().addChild(dummy);
	// Add dummy light
	auto raw_light = new ofLight();
	raw_light->enable();
	raw_light->setAmbientColor(ofColor(250.0f, 240.0f, 220.0f) * 0.1);
	raw_light->setPointLight();
	raw_light->dolly(250.0f);
	raw_light->setDiffuseColor(ofColor(250.0f, 240.0f, 220.0f));
	std::shared_ptr<Entity> light(new Entity(raw_light)); // FIXME why is this not fixed at the camera's position? gotta investigate
	scene->mainCamera.addChild(light);
	scene->mainCamera.getOfNode().dolly(250.0f);
	scene->mainCamera.getOfNode().boom(50.0f);
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
		ofEnableDepthTest();
		scene->mainCamera.getOfNode().tilt(0.1); // TODO get rid of me eventually
		scene->mainCamera.getOfNode().boom(-0.5); // TODO get rid of me eventually

		scene->mainCamera.getOfCamera().begin();
		renderer->image.getTexture().bind();
		scene->mainCamera.draw();
		scene->getRoot().draw();
		renderer->image.getTexture().unbind();
		scene->mainCamera.getOfCamera().end();

		ofDisableDepthTest();
	}


	gui.draw();
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

void ofApp::exit()
{
	ofLog() << "<app::exit>";
}

ofApp::~ofApp()
{
	if (nullptr != renderer)
		delete renderer;
}
