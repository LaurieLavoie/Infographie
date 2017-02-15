
#include "ofApp.h"


ofApp::ofApp()
{
	renderer = nullptr;
}

void ofApp::setup()
{
	ofSetWindowTitle("Projet session");

	renderer = new Renderer();
	renderer->setup();
}

void ofApp::draw()
{
	renderer->draw();
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
