#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(24);
    ofBackground(0);
    
    // eyes setup
    #if DEMO
    demo = Eye(ofGetWidth()/2, ofGetHeight()/2, 200);
    #else
    for(int i=0; i<EYE_NUM; ++i){
        eyes[i] = Eye(ofRandomWidth(), ofRandomHeight(), ofRandom(20,50));
    }
    #endif
    
    
    #if USE_KINECT
    // kinect setup
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    // opencv setup
    current_image.allocate(kinect.width, kinect.height);
    pre_image.allocate(kinect.width, kinect.height);
    diff_image.allocate(kinect.width, kinect.height);
    binary_image.allocate(kinect.width, kinect.height);
    #endif
    Eye::init();
}

//--------------------------------------------------------------
void ofApp::update(){
    #if USE_KINECT
    // kinect update
    kinect.update();
    
    if(kinect.isFrameNew()){
        current_image.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        current_image.mirror(0, true);
        diff_image.absDiff(current_image, pre_image);
        diff_image.blurGaussian();
        diff_image.threshold(30);
        pre_image = current_image;
        
        finder.findContours(diff_image, INSENSITIVITY, kinect.width*kinect.height, 1, false);
        if(finder.nBlobs > 0){
            int x = finder.blobs[0].centroid.x;
            int y = finder.blobs[0].centroid.y;
            obj_pos = ofVec3f(
                finder.blobs[0].centroid.x,
                finder.blobs[0].centroid.y,
                kinect.getDistanceAt(x, y)*FARTHER_UNIT
            );
            obj_pos *= (float)ofGetWidth()/kinect.width;
        }
    }
    #endif
    
    //set where eyes looking at
    Eye::setLookAt(obj_pos.x, obj_pos.y, obj_pos.z);
    
    // eyes update
    #if DEMO
    demo.update();
    #else
    for(int i=0; i<EYE_NUM; ++i){
        eyes[i].update();
    }
    #endif
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    
    #if USE_KINECT && DEBUG
    // draw camera image
    diff_image.draw(20,20);
    finder.draw(20,20);
    #endif

    //draw eyes
    #if DEMO
    demo.draw();
    #else
    for(int i=0; i<EYE_NUM; ++i){
        eyes[i].draw();
    }
    #endif
    
    // draw informations
    #if DEBUG
    ofSetColor(255, 0, 0);
    stringstream info;
    info << "fps: " << ofGetFrameRate();
    ofDrawBitmapString(info.str(), 50, 50);
    #endif
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
