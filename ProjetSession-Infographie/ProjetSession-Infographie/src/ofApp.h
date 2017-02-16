#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Renderer.h"

class ofApp : public ofBaseApp{

	public:
		Renderer * renderer;
		ofApp();

		void setup();
		void draw();
		void exit();

		void keyReleased(int key);
		void windowResized(int w, int h);


		ofxPanel gui;
		ofxIntSlider posX;
		ofxIntSlider posY;
		ofxIntSlider radius;

		ofxIntSlider hue;
		ofxIntSlider saturation;
		ofxIntSlider brightness;

		//ofxToggle toggle;
		//ofxButton button;

		~ofApp();
		
};
