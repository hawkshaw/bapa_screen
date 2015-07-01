#include "ofApp.h"
#include "ofAppReceive.h"
#include "ofAppDraw.h"

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
            getMessage(m);
        }
        string address_buf;
        address_buf = ofToString(m.getAddress())+":"+ofToString(m.getNumArgs());
        ofDrawBitmapString(address_buf, 0, 0);
        
        if(m.getAddress() == "/mouse/position1"){
            getMessage1(m);
        }
        if(m.getAddress() == "/mouse/position2"){
            getMessage2(m);
        }
        if(m.getAddress() == "/mouse/position22"){
            getMessage22(m);
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
