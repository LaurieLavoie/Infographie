#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.setup();
	gui.add(posX.setup("Position X", 0, 0, 600));
	gui.add(posY.setup("Position Y", 30, 0, 600));
	gui.add(radius.setup("radius", 60, 0 , 300));

	gui.add(hue.setup("hue", 0, 0, 255));
	gui.add(saturation.setup("saturation", 0, 0, 255));
	gui.add(brightness.setup("brightness", 0, 0, 255));
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	gui.draw();
	ofColor c = ofColor::fromHsb(hue, saturation, brightness);
	ofSetColor(c);
	ofCircle(posX, posY, radius);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
