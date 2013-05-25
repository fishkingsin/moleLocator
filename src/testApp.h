#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxUI.h"
#include "ofxDraggable.h"
class Draggable :public ofxDraggable
{
    public :
    void draw()
    {
        ofPushStyle();
        ofNoFill();
        ofSetColor(255,0,0);
        ofDrawBitmapString(_id, x+width*0.5,y+height*0.5);
        ofPopStyle();
        ofPushStyle();
        ofxDraggable::draw();
        ofPopStyle();        
    }
    string _id;
};
class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void guiEvent(ofxUIEventArgs &e);
    void processOpenFileSelection(ofFileDialogResult openFileResult);
    ofImage image;
    ofxUICanvas *gui1;
    
    ofxXmlSettings defaultXML;
    string originalFileExtension,originalFileBaseName;
    vector<Draggable*> draggable;
    ofImage mole;
    string filepath;
};
