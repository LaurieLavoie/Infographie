#pragma once

#include <memory>

#include "ofMain.h"
#include "ofxGui.h"
#include "Renderer.h"
#include "ofxAssimpModelLoader.h"
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
		void modelShowPrimitivesListener();
		void modelParticleListener();
		bool isLine;

		bool isKeyPressUp;
		bool isKeyPressDown;
		bool isKeyPressLeft;
		bool isKeyPressRight;

		ofxPanel gui;

		ofxIntSlider hue;
		ofxIntSlider saturation;
		ofxIntSlider brightness;

		ofxButton circleButton;
		ofxButton rectangleButton;
		ofxButton lineButton;
		ofxButton translationButton;
		ofxButton rotationButton;
		ofxButton proportionButton;


		ofxButton importButton;
		ofxButton exportButton;

		void cameraStartListener();
		void cameraProjectionListener();
		void cameraNearClipListener(float&);
		void cameraFarClipListener(float&);
		void cameraVFovListener(float&);
		void cameraHFovListener(float&);
		void cameraAspectRatioListener(float&);
		
		void translationListener();
		void rotationListener();
		void proportionListener();


		int lastMouseReleasedX;
		int lastMouseReleasedY;

		ofxPanel cameraGui;
		ofxButton cameraStartButton;
		ofxButton cameraProjectionButton;
		ofxFloatSlider cameraNearClipSlider;
		ofxFloatSlider cameraFarClipSlider;
		ofxFloatSlider cameraVFovSlider;
		ofxFloatSlider cameraHFovSlider;
		ofxFloatSlider cameraAspectRatioSlider;
		ofxPanel modelGui;
		ofxButton modelParticleButton;
		ofxButton modelShowPrimitivesButton;
		ofxAssimpModelLoader * objModel;

		ofxPanel curbGui;
		ofxButton hermiteButton;
		ofxButton bezierButton;
		ofxButton splineButton;
		ofxButton catmullButton;
		void hermiteListener();
		void bezierListener();
		void splineListener();
		void catmullListener();
		int indexPointCurb;

		~ofApp();

	private:
		std::unique_ptr<Scene> scene;
		
};
