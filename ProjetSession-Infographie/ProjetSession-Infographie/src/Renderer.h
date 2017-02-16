// IFT3100H17_Tryptique/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"

class Renderer
{
public:

	Renderer();
	void imageExport(const string name, const string extension) const;
	void setup();
	void draw();

	~Renderer();
};
