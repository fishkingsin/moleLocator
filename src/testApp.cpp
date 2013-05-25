#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofEnableAlphaBlending();
    ofSetLogLevel(OF_LOG_VERBOSE);
    defaultXML.loadFile("config.plist");
    mole.loadImage("mole01.png");
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

                            int x = defaultXML.getValue("integer", 0 , 0);
                            int y = defaultXML.getValue("integer", 0 , 1);
                            string _id = defaultXML.getValue("string", "id");
                            ofLogVerbose("postion ") << i << " =  "  << x<< " , " <<y;
                            Draggable * d = new Draggable();
                            d->setPos(x-mole.width*0.5, y-mole.height*0.5);
                            d->content = &mole;
                            d->_id = _id    ;

                            d->enableAllEvents();
                            draggable.push_back(d);
                            
#ifdef  ISDEBUG
                            defaultXML.setValue("integer", ofRandom(0,320),0);
                            defaultXML.setValue("integer", ofRandom(0,480),1);
#endif
                            defaultXML.popTag();
                        }
#ifdef  ISDEBUG
                        defaultXML.setValue("string", "blablablablablabla");
#endif
                        defaultXML.popTag();
                    }
                }
                
                defaultXML.popTag();
            }
            defaultXML.popTag();
        }
        defaultXML.popTag();
    }
#ifdef  ISDEBUG
    defaultXML.saveFile("config.plist");
#endif

//    gui1 = new ofxUICanvas(0,480,100,480);
//    gui1->addButton("Load", false, 44, 44);
//    gui1->addButton("Save", false, 44, 44);
//    ofAddListener(gui1->newGUIEvent,this,&testApp::guiEvent);
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
		}
    }
}
//--------------------------------------------------------------
void testApp::processOpenFileSelection(ofFileDialogResult openFileResult){
	
	ofLogVerbose("getName(): "  + openFileResult.getName());
	ofLogVerbose("getPath(): "  + openFileResult.getPath());
	
	ofFile file (openFileResult.getPath());
	filepath = openFileResult.getPath();
	if (file.exists()){
		//Limiting this example to one image so we delete previous ones
        image.clear();
		
		ofLogVerbose("The file exists - now checking the type via file extension");
		string fileExtension = ofToUpper(file.getExtension());
        ofLogVerbose("File Name") << file.getBaseName();
		originalFileBaseName = file.getBaseName();
		//We only want images
		if (fileExtension == "PNG" || fileExtension == "JPG") {
			image.loadImage(openFileResult.getPath());

		}
	}
	
}
//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    if(image.isAllocated())
    {
        ofPushStyle();
        ofSetColor(255);
        image.draw(0,0);
        ofPopStyle();
    }
    for(int i=0; i < draggable.size(); i++)
    {
        draggable[i]->draw();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key=='l')
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

    }
    else if(key=='s')
    {
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
                                defaultXML.setValue("integer", int(draggable[i]->x+draggable[i]->width*0.5),0);
                                
                                defaultXML.setValue("integer", int(draggable[i]->y+draggable[i]->height*0.5),1);
                                
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
        ofFileDialogResult saveFileResult = ofSystemSaveDialog(originalFileBaseName + "." + ofToLower(originalFileExtension), "Save your file");
		if (saveFileResult.bSuccess){
            defaultXML.saveFile(saveFileResult.filePath);
            //			processedImages[0].saveImage(saveFileResult.filePath);
		}
    }
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