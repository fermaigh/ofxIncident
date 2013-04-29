#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    
    welcomescreen.loadMovie("movies/welcome.mov");
    welcomescreen.play();

    
    blur.setup(welcomescreen.getWidth(), welcomescreen.getHeight(), 4, .2, 4);
    gameplay.loadMovie("movies/gameplay.mov");
    gameover.loadMovie("movies/gameover.mov");
    
    
    thinkGear.setup();
    ofAddListener(thinkGear.attentionChangeEvent, this, &testApp::attentionListener);
    font.loadFont("font/RexBold.otf", 15);
    
    distAw = 0.0;
    prevAw = 0.0;
    currAw = 0.0;
    distMw = 0.0;
    prevMw = 0.0;
    currMw = 0.0;
    
    atChangeTime = 0.0;
    meChangeTime = 0.0;
    
    attention = 0.0;
    
    currBlur = 0.0;
    
    firstPlaySeq = false;
    welcome = true;
    over = false;
    danger = false;
    extreme = false;
    incident = false;
    
    startTime = 0;
    currentTime = 0;
    totalTime = 5;
    flip = true;
    
    counter= 1;
    threshold = 63;
    openThreshold = 30;
    
}

//--------------------------------------------------------------
void testApp::update(){
    thinkGear.update();
    float cur = ofGetElapsedTimef();
    float progress = cur - atChangeTime;
    progress = ofClamp(progress, 0.0, 1.0);
    if (progress == 0.0) prevAw = currAw;
    currAw = ofxTweenLite::tween(prevAw, distAw, progress, OF_EASE_SINE_INOUT);
    progress = cur - meChangeTime;
    progress = ofClamp(progress, 0.0, 1.0);
    if (progress == 0.0) prevMw = currMw;
    currMw = ofxTweenLite::tween(prevMw, distMw, progress, OF_EASE_SINE_INOUT);
    blur.setScale(ofMap(attention, 0.0, 100.0, 4, 1));
    blur.setRotation(ofMap(attention, 0, 100.0, -PI, PI));
    if (welcomescreen.getPosition() > 0.9){
        firstPlaySeq = true;
    }
    
    if (firstPlaySeq == false) {
        welcomescreen.update();
        blur.setScale(ofMap(attention, 0.0, 100.0, 4, 1));
        blur.setRotation(ofMap(attention, 0, 100.0, -PI, PI));
    }
    else {
        if (attention < openThreshold){
            welcomescreen.update();
            blur.setScale(ofMap(attention, 0.0, 63.0, 4, 1));
            blur.setRotation(ofMap(attention, 0, 63.0, -PI, PI));
        }
        else {
            welcome = false;
            incident = true;
            welcomescreen.close();
        }
    }
    
    if(incident == true){
      gameplay.update();
    if (attention < threshold){
        danger = true;
    }
    else {
        danger = false;
        extreme = false;
        flip = true;
    }
    
    if(danger == true && welcome == false){
        
        currentTime = ofGetElapsedTimef();
        
        if (flip == true){
            startTime = ofGetElapsedTimef();
            flip = false;
        }
        
        if (currentTime - startTime < totalTime){
            cout<<"current time:"<<endl;
            cout<<currentTime<<endl;
            cout<<"start time:"<<endl;
            cout<<startTime<<endl;
            extreme = true;
            transparency.loadImage("images/alert.png");
        }
        else {
            gameplay.close();
            gameover.update();
            over = true;
            cout<<"game over"<<endl;
        }
    }
    }
    
    if(over == true){
    
    if (gameover.getPosition() > 0.9){
        lastPlaySeq = true;
        cout<<"game over played once"<<endl;
    }
    
    if (lastPlaySeq == false) {
        gameover.update();
        cout<<"game over has not played once"<<endl;
    }
    else {
        gameover.close();
         ofExit();
        cout<<"game should closed"<<endl;
    }
    }
        
}




//--------------------------------------------------------------
void testApp::draw(){
    ofSetWindowTitle("Attention = " + ofToString(attention));
    if (firstPlaySeq == false){
        blur.draw();
        blur.begin();
        welcomescreen.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
        welcomescreen.play();
        blur.end();
    } else {
        if (attention < openThreshold) {
            blur.draw();
            blur.begin();
            welcomescreen.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
            welcomescreen.play();
            blur.end();
        }
    }    
    if (incident == true && welcome == false && extreme == true){
        ofEnableAlphaBlending();
        gameplay.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
        gameplay.play();
        float wave = sin(ofGetElapsedTimef());
        transparency.draw(ofGetWidth()/3 + (wave * 100), ofGetWidth()/3);
        ofDisableAlphaBlending();
    }
    else if (incident == true && welcome == false){
        gameplay.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
        gameplay.play();
    }
    
    if (over == true && lastPlaySeq == false) {
        gameover.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
        gameover.play();
    }
    
    ofPushMatrix();
    ofTranslate(0, 30);
    ofPushStyle();
    ofSetColor(ofColor::yellow);
    font.drawString("Attention", 10, ofGetHeight()/15 - 20);
    ofFill();
    ofRect(10, ofGetHeight()/20-10, currAw/10, 10);
    
    if (attention > 0.0)
    {
        ofSetColor(ofColor::yellow, ofMap(currAw, 0.0, ofGetWidth()/2, 50, 100));
        font.drawString(ofToString(attention), 100, ofGetHeight()/20 - 10);
    }
    ofPopStyle();
    ofPopMatrix();
}

void testApp::attentionListener(float &param)
{
    attention = param;
    distAw = ofMap(attention, 0.0, 100.0, 0, ofGetWidth());
    atChangeTime = ofGetElapsedTimef();
}
void testApp::keyPressed(int key){}
void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y ){}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){}
void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){}