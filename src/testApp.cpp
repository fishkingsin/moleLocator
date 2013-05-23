#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    defaultXML.loadFile("config.plist");
    string str;
    defaultXML.copyXmlToString(str);
    ofLogNotice("defaultXML") << str;
    if(defaultXML.pushTag("plist"))
    {
        if(defaultXML.pushTag("dict"))
        {
            if(defaultXML.pushTag("array"))
            {
                int numTag = defaultXML.getNumTags("dict");
                for(int i = 0 ; i< numTag ; i++)
                {
                    if(defaultXML.pushTag("dict",i))
                    {
                        if(defaultXML.pushTag("dict"))
                        {

//                            defaultXML.removeTag("key",0);
//                            defaultXML.removeTag("key",1);
//                            defaultXML.removeTag("integer",0);
//                            defaultXML.removeTag("integer",1);
                            int x = defaultXML.getValue("integer", 0 , 0);
                            int y = defaultXML.getValue("integer", 0 , 1);
                            ofLogVerbose("postion ") << i << " =  "  << x<< " , " <<y;
                            ofxDraggable * d = new ofxDraggable();
                            d->setPos(x, y);
                            d->setSize(100, 100);
                            d->enableAllEvents();
                            draggable.push_back(d);
                            
                            defaultXML.setValue("key", "x",0);
                            defaultXML.setValue("integer", (int)ofRandom(ofGetWidth()),0);
                            defaultXML.setValue("key", "y",1);
                            defaultXML.setValue("integer", (int)ofRandom(ofGetHeight()),1);
                            defaultXML.popTag();
                        }
                        defaultXML.popTag();
                    }
                }
                
                defaultXML.popTag();
            }
            defaultXML.popTag();
        }
        defaultXML.popTag();
    }
    defaultXML.saveFile("config.plist");

    gui1 = new ofxUICanvas();
    gui1->addButton("Load", false, 44, 44);
    gui1->addButton("Save", false, 44, 44);
    ofAddListener(gui1->newGUIEvent,this,&testApp::guiEvent);
    originalFileExtension = "plist";

}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
    if(name=="Load")
    {
     
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a jpg or png");
		
		//Check if the user opened a file
		if (openFileResult.bSuccess){
			
			ofLogVerbose("User selected a file");
			
			//We have a file, check it and process it
			processOpenFileSelection(openFileResult);
			
		}else {
			ofLogVerbose("User hit cancel");
		}
    }else if(name=="Save")
    {
        //
		ofFileDialogResult saveFileResult = ofSystemSaveDialog(originalFileBaseName + "." + ofToLower(originalFileExtension), "Save your file");
		if (saveFileResult.bSuccess){
            defaultXML.saveFile(saveFileResult.filePath);
//			processedImages[0].saveImage(saveFileResult.filePath);
		}
    }
}
//--------------------------------------------------------------
void testApp::processOpenFileSelection(ofFileDialogResult openFileResult){
	
	ofLogVerbose("getName(): "  + openFileResult.getName());
	ofLogVerbose("getPath(): "  + openFileResult.getPath());
	
	ofFile file (openFileResult.getPath());
	
	if (file.exists()){
		//Limiting this example to one image so we delete previous ones
//		processedImages.clear();
//		loadedImages.clear();
		
		ofLogVerbose("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());
        ofLogVerbose("File Name") << file.getBaseName();
		originalFileBaseName = file.getBaseName();
		//We only want images
		if (fileExtension == "PNG" || fileExtension == "JPG") {
			
			//Save the file extension to use when we save out
			
			
			//Load the selected image
/*			ofImage image;
			image.loadImage(openFileResult.getPath());
			if (image.getWidth()>ofGetWidth() || image.getHeight() > ofGetHeight())
			{
				image.resize(image.getWidth()/2, image.getHeight()/2);
			}
			loadedImages.push_back(image);
			
			//Make some short variables
			int w = image.getWidth();
			int h = image.getHeight();
			
			//Make a new image to save manipulation by copying the source
			ofImage processedImage = image;
			
			//Walk through the pixels
			for (int y = 0; y < h; y++){
				
				//Create a vector to store and sort the colors
				vector<ofColor> colorsToSort;
				
				for (int x = 0; x < w; x++){
					
					//Capture the colors for the row
					ofColor color = image.getColor(x, y);
					colorsToSort.push_back(color);
				}
				
				//Sort the colors for the row
				sort (colorsToSort.begin(), colorsToSort.end(), sortColorFunction);
				
				for (int x = 0; x < w; x++)
				{
					//Put the sorted colors back in the new image
					processedImage.setColor(x, y, colorsToSort[x]);
				}
			}
			//Store the processed image
			processedImages.push_back(processedImage);*/
		}
	}
	
}
//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}