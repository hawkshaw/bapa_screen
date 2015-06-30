#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofAppReceive.h"
#include "ofAppDraw.h"

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 20
#define NUM_PEOPLE 120

class ofApp : public ofBaseApp {
	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void getMessage(ofxOscMessage m);
        void getMessage1(ofxOscMessage m);
        void getMessage2(ofxOscMessage m);
        void getMessage22(ofxOscMessage m);

    
		ofTrueTypeFont font;
		ofxOscReceiver receiver;

		int current_msg_string;
		string msg_strings[NUM_MSG_STRINGS];
		float timers[NUM_MSG_STRINGS];
        int peoplex[NUM_PEOPLE];
        int peopley[NUM_PEOPLE];
        int peoplestate[NUM_PEOPLE];
        int peoplestate_1f[NUM_PEOPLE];
        int peoplekillcount[NUM_PEOPLE];
        int peopleid[NUM_PEOPLE];
		int mouseX, mouseY,mouseID,mouseStd;
		string mouseButtonState;
    
        ofImage receivedImage;
        class clap{
            public:
                int clapx,clapy;
                int clapid;
                int clapsend;
                int clapStd;
        };
        std::vector<clap> claps;
        int velx_ave,vely_ave;
};
