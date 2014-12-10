#pragma once


#define USE_KINECT TRUE
#define DEMO FALSE
#define DEBUG FALSE
#define EYE_NUM 100
#define FARTHER_UNIT 0.02
#define INSENSITIVITY 1000

#include "ofMain.h"
#include "Eye.h"

#if USE_KINECT
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#endif

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    Eye demo;
    Eye eyes[EYE_NUM];
    
    #if USE_KINECT
    ofxKinect kinect;
    ofxCvGrayscaleImage pre_image;
    ofxCvGrayscaleImage current_image;
    ofxCvGrayscaleImage diff_image;
    ofxCvGrayscaleImage binary_image;
    ofxCvContourFinder finder;
    
    ofVec3f obj_pos;
    #endif
};
