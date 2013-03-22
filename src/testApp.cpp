#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    
    fingerMovie.loadMovie("movies/welcome.mov");  //load welcome screen
	fingerMovie.play();
    
    blur.setup(fingerMovie.getWidth(), fingerMovie.getHeight(), 4, .2, 4);  //blur welcome screen
    
    gameplay.loadMovie("movies/gameplay.mov");  //load gameplay screen
    
    gameover.loadMovie("movies/gameover.mov"); //load gameover screen
    
    thinkGear.setup();
    ofAddListener(thinkGear.attentionChangeEvent, this, &testApp::attentionListener);  //updates whatever get from the function
    
    alert.loadImage("images/aler.jpg");
   
    attention = 0.0;
    
    currBlur = 0.0;
    
    notStart = true; // default screen is welcome screen
    inPlay = false;  // default screen is not game playing screen
    isOver = false;  // game is not over
    firstPlaySeq = false; //opening sequence played at least once
    overplaySeq = false;
    attentionlow = false;
    displayAlert = false;
    counter=1;
    
}

//--------------------------------------------------------------
void testApp::update(){
    fingerMovie.update();
    blur.setScale(ofMap(attention, 0.0, 100.0, 4, 1));
    blur.setRotation(ofMap(attention, 0, 100.0, -PI, PI));
    
    thinkGear.update();
    if (fingerMovie.getPosition() > 0.9){ // make sure the welcome screen fully loops
        firstPlaySeq = true;
        notStart = true;
        isOver = false;
    }
    
    if (firstPlaySeq == false) {
        notStart = true;
        isOver = false;
        fingerMovie.update();
        blur.setScale(ofMap(attention, 0.0, 100.0, 4, 1));
        blur.setRotation(ofMap(attention, 0, 100.0, -PI, PI));
    }
    else {
        if (attention < 63 && attention >= 0){
            isOver = false;
            fingerMovie.update();
            blur.setScale(ofMap(attention, 0.0, 63.0, 4, 1));
            blur.setRotation(ofMap(attention, 0, 63.0, -PI, PI));
        }
        else {
            fingerMovie.close();
            notStart = false;
            isOver = false;
            inPlay = true;
            gameplay.update();
            
        }
    }// ending else for firstPlaySeq
    
    
    
    if (inPlay){
        isOver = false;
        gameplay.update();
        cout<<attention<<endl;
        if (attention < 70 && attention >=0 && counter==1){
            attentionlow = true;
            gameplay.setPaused(true);
            lastTime = ofGetElapsedTimef();
            counter++;
            
        }
        
            if(attentionlow){
                float diff = ofGetElapsedTimef() - lastTime;
                if (diff < 2000 && attention < 70 && attention >=0){
                    gameplay.setPaused(true);
                    displayAlert = true;
                    isOver = false;
                }
                
                if(diff > 2000 && diff < 5000 && attention > 70){
                    counter=1;
                    gameplay.setPaused(false);
                    displayAlert=false;
                    gameplay.update();
                    isOver = false;
                }
                
                if (diff > 5000 && attention < 70) {
                    isOver=true;
                    gameover.update();
                    gameplay.close();
                    inPlay=false;
                    attentionlow = false;
                    displayAlert=false;
                }
                
                if(displayAlert){
                    gameplay.setPaused(true);
                    isOver = false;

              }
        
        
    }
        if(isOver){
        gameplay.close();
        gameover.update();
    }
        
        if (gameover.getPosition() > 0.9){ // make sure the welcome screen fully loops
            overplaySeq = true;
            notStart = true;
            isOver = false;
            inPlay = false;
            
        }
        
        if (overplaySeq == false) {
            isOver = true;
            gameover.update();
        } else {
            gameover.close();
            fingerMovie.update();
            notStart = true;
            firstPlaySeq = false; 
        }

    
    
    }

}


//--------------------------------------------------------------
void testApp::draw(){
    
 
    ofSetWindowTitle("Attention = " + ofToString(attention));
    
    if (firstPlaySeq == false){
        blur.draw();
        blur.begin();
        fingerMovie.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
        fingerMovie.play();
        blur.end();
    }
    else {
        if (attention < 63 && attention >= 0) {
            blur.draw();
            blur.begin();
            fingerMovie.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
            fingerMovie.play();
            
            blur.end();
        }
    }
    
    
    if (inPlay){
            gameplay.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
            gameplay.play();
        if(attentionlow){
            alert.draw(100, 100, 100);
            ofDrawBitmapString("watch out", 100,100);
            
        }
    }
        
    if (isOver) {
        gameplay.close();
        gameover.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
        gameover.play();
    }
    
    
    




    

}




void testApp::attentionListener(float &param)
{
    attention = param;
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