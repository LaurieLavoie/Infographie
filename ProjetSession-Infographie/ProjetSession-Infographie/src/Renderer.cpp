// IFT3100H17_Tryptique/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

Renderer::Renderer()
{

}

void Renderer::setup()
{
	ofSetFrameRate(60);
	image.load("image.jpg");
	ofSetWindowShape(image.getWidth(), image.getHeight());
}

void Renderer::draw()
{
	// couleur de l'arrière-plan
	ofClear(0);

	// tinte de l'image (blanc pour les couleurs d'origine)
	ofSetColor(255);

	// afficher l'image sur toute la surface de la fenêtre
	image.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
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
	/*int imageWidth;
	int imageHeight;
	int imageComponent;
	int imagePixelCount;
	int imageSize;

	GLuint textureID;
	GLubyte * pixels;

	imagePixelCount = imageWidth * imageHeight;
	imageSize = imagePixelCount * imageComponent;
	pixels = (GLubyte *)calloc(imageSize, sizeof(GLubyte));
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glGenerateMipmap(GL_TEXTURE_2D);

	free(pixels);*/
	image.load(path);
	ofSetWindowShape(image.getWidth(), image.getHeight());
}

Renderer::~Renderer()
{
}
