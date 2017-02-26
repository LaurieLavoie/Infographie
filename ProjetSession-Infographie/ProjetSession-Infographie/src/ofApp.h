#pragma once

#include <memory>

#include "ofMain.h"
#include "ofxGui.h"
#include "Renderer.h"

#include "Scene.h"

class ofApp : public ofBaseApp{

	public:
		Renderer * renderer;
		ofApp();

		void setup();
		void update();
		void draw();
		void exit();

		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void keyReleased(int key);

		void circleListener();
		void rectangleListener();
		void lineListener();
		void colorListener();
		void exportListener();
		void importListener();

		bool isLine;

		ofxPanel gui;

		ofxIntSlider hue;
		ofxIntSlider saturation;
		ofxIntSlider brightness;

		ofxButton circleButton;
		ofxButton rectangleButton;
		ofxButton lineButton;
		ofxButton importButton;
		ofxButton exportButton;

		void cameraProjectionListener();

		ofxPanel cameraGui;
		ofxButton cameraProjectionButton;

		~ofApp();

	private:
		std::unique_ptr<Scene> scene;
		
};
