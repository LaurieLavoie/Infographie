// IFT3100H17_ImageImport/main.cpp
// Exemple d'importation et d'affichage en pleine fen�tre d'une image,
// charg�e � partir d'un fichier qui se trouve dans le r�pertoire ./bin/data
// ou � partir d'une image qui est gliss�e-d�pos�e sur la fen�tre de l'application.

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
