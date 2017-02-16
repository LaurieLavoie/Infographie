// IFT3100H17_Tryptique/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

	Renderer();
	ofImage image;
	void imageExport(const string name, const string extension) const;
	void imageImport(string path);
	void setup();
	void draw();


	~Renderer();
};
