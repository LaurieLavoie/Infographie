// IFT3100H17_ImageImport/main.cpp
// Exemple d'importation et d'affichage en pleine fenêtre d'une image,
// chargée à partir d'un fichier qui se trouve dans le répertoire ./bin/data
// ou à partir d'une image qui est glissée-déposée sur la fenêtre de l'application.

#include "ofMain.h"
#include "ofApp.h"

int main()
{
	ofSetupOpenGL(1400, 768, OF_WINDOW);			// <-------- setup the GL context
	if (!ofGLCheckExtension("GL_ARB_geometry_shader4") && !ofGLCheckExtension("GL_EXT_geometry_shader4") && !ofIsGLProgrammableRenderer()) {
		ofLogFatalError() << "geometry shaders not supported on this graphics card";
		return 1;
	}

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

	
}
