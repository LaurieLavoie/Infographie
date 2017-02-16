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
	gui.add(exportButton.setup("export"));
	exportButton.addListener(this, &ofApp::exportListener);

	renderer = new Renderer();
	renderer->setup();
}

void ofApp::exportListener() {
	renderer->imageExport("test", "jpg");
}

void ofApp::draw()
{
	renderer->draw();
	gui.draw();
	ofColor c = ofColor::fromHsb(hue, saturation, brightness);
	ofSetColor(c);
	ofCircle(posX, posY, radius);
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
