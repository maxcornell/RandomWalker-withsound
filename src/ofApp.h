/*
 Project Title: randomWalker
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */


#pragma once

#include "ofMain.h"

class walker {
    // walker class that contains vector of points and color and radius of each step
    ofPoint xyPoint;
    vector<ofPoint> walk;
    ofColor color;
        
public:
    walker();
    ~walker();
    void update();
    void draw();
    vector<int> radius;


    };

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    walker walker; // create a wallker object

    //sound
    ofSoundStream soundStream;

		float 	pan;
		int		sampleRate;
		bool 	bNoise;
		float 	volume;

		vector <float> lAudio;
		vector <float> rAudio;
		
		//------------------- for the simple sine wave synthesis
		float 	targetFrequency;
		float 	phase;
		float 	phaseAdder;
		float 	phaseAdderTarget;


	void audioOut(ofSoundBuffer & buffer);

};


