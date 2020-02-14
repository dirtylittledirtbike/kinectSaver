#pragma once


#include "ofMain.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    
    
    
    ofxKinectV2 kinect;
    bool takeSnapshot = false;
    
    ofTexture rgbTexture;
    ofPixels rgbPixels;
    
};
