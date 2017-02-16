#include "ofApp.h"

ofApp::ofApp()
{
	renderer = nullptr;
}

void ofApp::setup()
{
	ofSetWindowTitle("Projet session");

	gui.setup();
	gui.add(posX.setup("Position X", 0, 0, 600));
	gui.add(posY.setup("Position Y", 30, 0, 600));
	gui.add(radius.setup("radius", 60, 0, 300));

	gui.add(hue.setup("hue", 0, 0, 255));
	gui.add(saturation.setup("saturation", 0, 0, 255));
	gui.add(brightness.setup("brightness", 0, 0, 255));

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

	ofColor c = ofColor::fromHsb(hue, saturation, brightness);
	ofSetColor(c);
	ofCircle(posX, posY, radius);

	gui.draw();
}

void ofApp::keyReleased(int key)
{
	ofLog() << "<app::keyReleased: " << key << ">";

	// valider si la clé relâchée est la barre d'espacement (space)
	if (key == ' ')
		renderer->imageExport("render", "png");
}

void ofApp::windowResized(int w, int h)
{
	ofLog() << "<app::windowResized to: (" << w << ", " << h << ")>";
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
