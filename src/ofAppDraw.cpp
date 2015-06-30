#include "ofApp.h"
#include "ofAppReceive.h"
#include "ofAppDraw.h"

#define DRAWMODE 2

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    string buf;
    //buf = "listening for osc messages on port" + ofToString(PORT);
    //ofDrawBitmapString(buf, 10, 20);
    
    // draw mouse state
    buf = "mouse: " + ofToString(mouseX, 4) +  " " + ofToString(mouseY, 4);
    if(DRAWMODE==1)ofDrawBitmapString(buf, 430, 20);
    //ofDrawBitmapString(mouseButtonState, 580, 20);
    buf = "velx_ave: " + ofToString(velx_ave, 4);
    if(DRAWMODE==1)ofDrawBitmapString(buf, 560, 20);
    buf = "vely_ave: " + ofToString(vely_ave, 4);
    if(DRAWMODE==1)ofDrawBitmapString(buf, 680, 20);
    //for(int i = 0; i < NUM_MSG_STRINGS; i++){
    //	ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
    //}
    string clapbuf;
    for(int i = 0 ;i < NUM_PEOPLE; i++){
        if(peoplestate[i]){
            clapbuf = ofToString(peopleid[i])+":"+ofToString(peoplestate[i])+":"+ofToString(peoplekillcount[i]);
            if(DRAWMODE==1)ofDrawBitmapString(clapbuf, peoplex[i], peopley[i]);
        }
    }
    int clap_num;
    clap_num = claps.size();
    for(int i = 0; i<clap_num; i++){
        clapbuf = ofToString(claps[i].clapid)+":"+ofToString(claps[i].clapStd);
        if (claps[i].clapStd < 300) {
            ofSetColor(255,255,255);
        }else{
            ofSetColor(255,0,0);
        }
        if(DRAWMODE==1)ofDrawBitmapString(clapbuf, claps[i].clapx, claps[i].clapy );
        if(DRAWMODE==2)ofCircle(claps[i].clapx, claps[i].clapy , 10);
    }
    claps.clear();
}