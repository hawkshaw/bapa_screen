#include "ofApp.h"

#define DRAWMODE 2

//--------------------------------------------------------------
void ofApp::setup(){
	// listen on the given port
	//cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	current_msg_string = 0;
	mouseX = 0;
	mouseY = 0;
	mouseButtonState = "";
    //ofSetBackgroundAuto(false);
	ofBackground(0, 0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){

	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        
		// check for mouse moved message
		if(m.getAddress() == "/mouse/position"){
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
        string address_buf;
        address_buf = ofToString(m.getAddress())+":"+ofToString(m.getNumArgs());
        ofDrawBitmapString(address_buf, 0, 0);
        
        if(m.getAddress() == "/mouse/position1"){
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
        if(m.getAddress() == "/mouse/position2"){
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
        if(m.getAddress() == "/mouse/position22"){
            int msgnum;
            msgnum = m.getNumArgs();
            if(msgnum==2){
                velx_ave = m.getArgAsInt32(0);
                vely_ave = m.getArgAsInt32(1);
            }
        }

	}
    for (int i=0; i < NUM_PEOPLE; i++) {
        if(peoplestate[i]){
            if(peoplestate[i]==peoplestate_1f[i]){
                peoplekillcount[i]++;
            }else{
                peoplekillcount[i]=0;
            }
            if(peoplekillcount[i] > 100){
                peoplekillcount[i]=0;
                peoplestate[i]=0;
            }
            peoplestate_1f[i]=peoplestate[i];
        }
    }
}


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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
