#include "ofApp.h"
#include "ofAppReceive.h"


//--------------------------------------------------------------
void ofApp::getMessage(ofxOscMessage m){
    // both the arguments are int32's
    mouseX = m.getArgAsInt32(0);
    mouseY = m.getArgAsInt32(1);
    mouseID = m.getArgAsInt32(2);
    for(int i = 0 ;i < NUM_PEOPLE; i++){
        if (mouseID==peopleid[i]) {
            peoplestate[i]++;
            break;
        }
        if(peoplestate[i]){
            continue;
        }else{
            peoplex[i]=mouseX;
            peopley[i]=mouseY;
            peopleid[i]=mouseID;
            peoplestate[i]=1;
            break;
        }
    }
}
//--------------------------------------------------------------
void ofApp::getMessage1(ofxOscMessage m){
    int mousenum;
    mousenum = m.getNumArgs();
    for (int j=0 ; j < mousenum/3 ; j++){
        mouseX = m.getArgAsInt32(0+j*3);
        mouseY = m.getArgAsInt32(1+j*3);
        mouseID = m.getArgAsInt32(2+j*3);
        for(int i = 0 ;i < NUM_PEOPLE; i++){
            if (mouseID==peopleid[i]) {
                peoplestate[i]++;
                break;
            }
            if(peoplestate[i]){
                continue;
            }else{
                peoplex[i]=mouseX;
                peopley[i]=mouseY;
                peopleid[i]=mouseID;
                peoplestate[i]=1;
                break;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::getMessage2(ofxOscMessage m){
    int mousenum;
    mousenum = m.getNumArgs();
    for (int j=0 ; j < mousenum/4 ; j++){
        //叩かれた座標
        mouseX = m.getArgAsInt32(0+j*3);
        mouseY = m.getArgAsInt32(1+j*3);
        //物体検出id
        mouseID = m.getArgAsInt32(2+j*3);
        //平均動きからのズレ
        mouseStd = m.getArgAsInt32(j+mousenum/4*3);
        clap clap_buf;
        clap_buf.clapx = mouseX;
        clap_buf.clapy = mouseY;
        clap_buf.clapid = mouseID;
        clap_buf.clapStd = mouseStd;
        claps.push_back(clap_buf);
    }
}

//--------------------------------------------------------------
void ofApp::getMessage22(ofxOscMessage m){
    int msgnum;
    msgnum = m.getNumArgs();
    if(msgnum==2){
        velx_ave = m.getArgAsInt32(0);
        vely_ave = m.getArgAsInt32(1);
    }
}
