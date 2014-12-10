//
//  Eye.cpp
//  WatchingEyes2D
//
//  Created by 南部 晃史 on 2014/12/08.
//
//

#include "Eye.h"

ofImage Eye::lids[IMAGE_NUM];
ofImage Eye::base;
ofImage Eye::pupil;
ofVec3f Eye::object_pos;
int Eye::last_look_object_millis;
bool Eye::bLookObject;

Eye::Eye(int x, int y, int size){
    this->size = size;
    pos = ofVec3f(x, y, 0);
    counter = 0;
    bFlash = false;
    vel = ofVec3f(ofRandom(1), ofRandom(1)).normalize()*ofRandom(-1, 1);
}

void Eye::init(){
    for(int i=0; i<IMAGE_NUM; ++i){
        stringstream filename;
        filename << "mabataki_1/mabataki_" << ofToString(i, 5, '0') << ".png";
        lids[i].loadImage(filename.str());
    }
    base.loadImage("sirome_1.png");
    pupil.loadImage("kurome_1.png");
    
}

void Eye::setLookAt(int x, int y, int z){
    // dont overwrite object position if eye looking and object is other place
    bool bLooking = (ofGetElapsedTimeMillis() - last_look_object_millis < 3000);
    bool bNearObject = (ofVec3f(x,y,z)-object_pos).lengthSquared() < 30;
    bLookObject = !bLooking || !bNearObject;
    if(!bLooking || !bNearObject){
        object_pos = ofVec3f(x, y, z);
        last_look_object_millis = ofGetElapsedTimeMillis();
    }
}

void Eye::update(){
    // update eye position
    pos += vel;
    if(pos.x > ofGetWidth()+size){
        pos.x = -size;
    }else if(pos.x < -size){
        pos.x = ofGetWidth()+size;
    }
    if(pos.y > ofGetHeight()+size){
        pos.y = -size;
    }else if(pos.y < -size){
        pos.y = ofGetHeight()+size;
    }
    
    // flashing
    if(ofRandom(1)<0.01){
        bFlash = true;
    }
    if(bFlash){
        ++counter;
        if (counter == IMAGE_NUM) {
            counter = 0;
            bFlash = false;
        }
    }
    
    // set look_at
    if(bLookObject){
        target_look_at = object_pos;
    }else{
        if(ofRandom(1)<0.01){
            target_look_at = ofVec3f(ofRandomWidth(), ofRandomHeight(), ofRandom(100,1000));
        }
    }
    
    // move pupil
    look_at = look_at * (1 - PUPIL_SPEED) + target_look_at * PUPIL_SPEED;
    pupil_diff = look_at - pos;
    pupil_diff.normalize();
    pupil_diff.z = 0;
    float R = ofDist(pos.x, pos.y, look_at.x, look_at.y);
    pupil_diff *= MIN(R*size/look_at.z, size/2-size*0.3);
}

void Eye::draw(){
    ofSetRectMode(OF_RECTMODE_CENTER);
    base.draw(pos.x, pos.y, size, size);
    pupil.draw(pos.x+pupil_diff.x, pos.y+pupil_diff.y, size, size);
    lids[counter].draw(pos.x, pos.y, size, size);
    ofSetRectMode(OF_RECTMODE_CORNER);
}

void Eye::startFlashing(){
    bFlash = true;
}