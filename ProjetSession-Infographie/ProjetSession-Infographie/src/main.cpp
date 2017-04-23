// IFT3100H17_ImageImport/main.cpp
// Exemple d'importation et d'affichage en pleine fen�tre d'une image,
// charg�e � partir d'un fichier qui se trouve dans le r�pertoire ./bin/data
// ou � partir d'une image qui est gliss�e-d�pos�e sur la fen�tre de l'application.

#include "ofMain.h"
#include "ofApp.h"

int main()
{
		ofAppGlutWindow window;
		window.setDoubleBuffering(true);
		ofSetupOpenGL(&window, 1400, 768, OF_WINDOW);
		ofRunApp(new ofApp());
}
