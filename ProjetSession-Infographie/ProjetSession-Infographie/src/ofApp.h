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
		ofxButton shaderColorButton;
		ofxButton shaderGeoButton;

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
		void shaderColorListener();
		void shaderGeoListener();

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

		ofxPanel lightsGui;
		ofxButton pointButton;
		ofxButton spotButton;
		ofxButton directionalButton;
		ofxButton ambientButton;
		void pointLightListener();
		void spotLightListener();
		void directionalLightListener();
		void ambientLightListener();
		ofxButton matButton;
		ofxButton mat1Button;
		ofxButton mat2Button;
		void materialListener();
		void material1Listener();
		void material2Listener();

		ofxPanel curbGui;
		ofxButton hermiteButton;
		ofxButton bezierButton;
		ofxButton splineButton;
		ofxButton voronoiButton;
		void hermiteListener();
		void bezierListener();
		void splineListener();
		void voronoiListener();
		int indexPointCurb;

		ofMaterial material;
		ofMaterial material1;
		ofMaterial material2;
		ofMaterial* activeMaterial;

		ofLight ambient;
		ofLight point;
		ofLight spot;
		ofLight directional;

		~ofApp();

	private:
		std::unique_ptr<Scene> scene;
		ofShader shader;
		ofShader shaderGeo;
};
