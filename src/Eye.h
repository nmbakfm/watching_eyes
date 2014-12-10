//
//  Eye.h
//  WatchingEyes2D
//
//  Created by 南部 晃史 on 2014/12/08.
//
//

#ifndef __WatchingEyes2D__Eye__
#define __WatchingEyes2D__Eye__

#include "ofMain.h"

#define IMAGE_NUM 23
#define PUPIL_SPEED 0.1

class Eye {
private:
    ofVec3f pos;
    ofVec3f look_at;
    ofVec3f pupil_diff;
    ofVec3f vel;
    ofVec3f target_look_at;
    static ofVec3f object_pos;
    static ofImage lids[IMAGE_NUM];
    static ofImage base;
    static ofImage pupil;
    static bool bLookObject;
    int size;
    int counter;
    bool bFlash;
    static int last_look_object_millis;
public:
    Eye(){};
    Eye(int x, int y, int size);
    static void init();
    static void setLookAt(int x, int y, int z);
    void update();
    void draw();
    void startFlashing();
};

#endif /* defined(__WatchingEyes2D__Eye__) */
