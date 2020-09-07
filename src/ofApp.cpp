/*
 Project Title: randomWalker
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    ofSetBackgroundColor(0);
    
    //Audio?
    int bufferSize		= 512;
	sampleRate 			= 44100;
	phase 				= 0;
	phaseAdder 			= 0.0f;
	phaseAdderTarget 	= 0.0f;
	volume				= 0.1f;
	bNoise 				= false;

	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);
	
	soundStream.printDeviceList();

	ofSoundStreamSettings settings;
	settings.setOutListener(this);
	settings.sampleRate = sampleRate;
	settings.numOutputChannels = 2;
	settings.numInputChannels = 0;
	settings.bufferSize = bufferSize;
	soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update(){
    walker.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    walker.draw();
    phaseAdderTarget = 1000.0f * (float)(walker.radius[walker.radius.size()-1] % 4); //attempt to change frequency
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
walker::walker(){
    xyPoint = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    // make a first point in the centre of the screen
    walk.push_back(xyPoint);
    color.b = 200; // draw our dots white with random color and transparency
    radius.push_back(5); // dotsize
}

//--------------------------------------------------------------
walker::~walker(){
    
}

//--------------------------------------------------------------
void walker::update(){
    // choose a random direction for the next step
    int stepSize = ofRandom(8); // how far is each step from the last step
    int random = ofRandom(4);
    switch (random) {
        case 0: // up
            xyPoint += ofVec2f(0, stepSize);
            break;
        case 1: // down
            xyPoint += ofVec2f(0, -stepSize);
            break;
        case 2: // right
            xyPoint += ofVec2f(stepSize, 0);
            break;
        case 3: // left
            xyPoint += ofVec2f(-stepSize, 0);
            break;
        default:
            break;
    }
    walk.push_back(xyPoint); // add our step into the list of steps
    radius.push_back(random); // change the radius, too
    
}

//--------------------------------------------------------------
void walker::draw(){
    ofSetColor( color);
    for (int i=0; i<walk.size(); i++){ // loop though all the steps in the walk, drawing a point at each one
        ofDrawCircle(walk[i], radius[i]);
    }
}

	

void ofApp::audioOut(ofSoundBuffer & buffer){
	//pan = 0.5f;
	float leftScale = 1 - pan;
	float rightScale = pan;

	// sin (n) seems to have trouble when n is very large, so we
	// keep phase in the range of 0-TWO_PI like this:
	while (phase > TWO_PI){
		phase -= TWO_PI;
	}

	if ( bNoise == true){
		// ---------------------- noise --------------
		for (size_t i = 0; i < buffer.getNumFrames(); i++){
			lAudio[i] = buffer[i*buffer.getNumChannels()    ] = ofRandom(0, 1) * volume * leftScale;
			rAudio[i] = buffer[i*buffer.getNumChannels() + 1] = ofRandom(0, 1) * volume * rightScale;
		}
	} else {
		phaseAdder = 0.95f * phaseAdder + 0.05f * phaseAdderTarget;
		for (size_t i = 0; i < buffer.getNumFrames(); i++){
			phase += phaseAdder;
			float sample = sin(phase);
			lAudio[i] = buffer[i*buffer.getNumChannels()    ] = sample * volume * leftScale;
			rAudio[i] = buffer[i*buffer.getNumChannels() + 1] = sample * volume * rightScale;
		}
	}

}
