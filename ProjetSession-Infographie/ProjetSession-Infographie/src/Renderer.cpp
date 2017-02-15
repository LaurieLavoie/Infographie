// IFT3100H17_Tryptique/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer()
{

}

void Renderer::setup()
{
	ofSetFrameRate(1);

	

}

void Renderer::draw()
{
 
}


void Renderer::imageExport(const string name, const string extension) const
{
	ofImage imageTemp;
	string timestamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");
	string fileName = name + timestamp + "." + extension;

	imageTemp.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
	imageTemp.save(fileName);
}

Renderer::~Renderer()
{
}
