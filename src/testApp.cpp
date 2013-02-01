#include "testApp.h"

#define RECONNECT_TIME 400

//--------------------------------------------------------------
void testApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	// initialize app
	ofSetFrameRate(30);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
	ofSetBackgroundAuto(false);
    
	client.setup("settings.xml", this);
	
    // set the random seed
	ofSeedRandom(1);
    
    // add a "randomly" placed ball
    Ball* ball = new Ball(ofRandom(0, client.getMWidth()), ofRandom(0, client.getMHeight()), client.getMWidth(), client.getMHeight(),ofRandom(-5,5),ofRandom(-5,5));
    balls.push_back(ball);
    
	// start client
    client.start();
	
	
	player.setup();
	totalFrames = player.player.getTotalNumFrames();

	//	fingerMovie.setSynchronousSeeking(true);
	currentFrame = 0;
}

//--------------------------------------------------------------
void testApp::update(){
	
//	if(client.isRendering())
	{
	player.update(client.getFrameCount());
		player.updateTexture();
	}

//	if (fingerMovie.isLoaded()) {
		os.str("");
//
//		int frameDiff = currentFrame-fingerMovie.getCurrentFrame();
		os <<"FPS "<<client.getFPS() << endl;
//		os <<"Curent Frame "<< currentFrame << endl;
//		os <<"Movie Frame " << fingerMovie.getCurrentFrame() << endl;
//		os <<"Famediff " << frameDiff << endl;
//		//
//		float speed = 1+((frameDiff*1.0f)/25.0);
//		os <<"Speed " << speed << endl;
//		if(abs(frameDiff)<15 && abs(frameDiff)>1)
//		{
//			float diff = ofGetElapsedTimef() -  timeCount;
//			if(diff>5)
//			{
//				os <<"Set Speed "<<endl;
//				
//				fingerMovie.setSpeed(speed);
//				timeCount = ofGetElapsedTimef();
//			}
//		}
//		
//		else if(abs(frameDiff)>15)
//		{
////			fingerMovie.setPaused(true);
//			fingerMovie.setFrame(currentFrame);
////			fingerMovie.setPaused(false);
//		}
//		else
//		{
//			fingerMovie.setSpeed(1);
//		}
//
//	}
	
}

//--------------------------------------------------------------
void testApp::draw(){
//	ofSetColor(255);
	
}

//--------------------------------------------------------------
void testApp::frameEvent() {
    // clear the screen
    ofBackground(255, 255, 255);
//	currentFrame = client.getFrameCount()%totalFrames;
	ofSetColor(255);
	
	player.tex.draw(0, 0, client.getMWidth(),client.getMHeight());

	
	

	
//    if (fingerMovie.isLoaded()) {
//		
//		fingerMovie.update();
//		
//
//		
//		ofSetColor(255);
//		
//		
//		
//        fingerMovie.draw(0, 0, client.getMWidth(),client.getMHeight());
		ofDrawBitmapString(os.str(), client.getXoffset()+20,20);
//			}
    // move and draw all the balls
    for (int i = 0; i < balls.size(); i++) {
        balls[i]->calc();
        balls[i]->draw();
    }
    
    // read any incoming messages
    if (client.messageAvailable()) {
        vector<string> msg = client.getDataMessage();
        vector<string> xy = ofSplitString(msg[0], ",");
        float x = ofToInt(xy[0]);
        float y = ofToInt(xy[1]);
		float xd = ofToFloat(xy[2]);
		float yd = ofToFloat(xy[3]);
        Ball* ball = new Ball(x, y, client.getMWidth(), client.getMHeight(),xd,yd);
        balls.push_back(ball);
    }
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
void testApp::mousePressed(int x, int y, int button) {
    // never include a ":" when broadcasting your message
    x += client.getXoffset();
    y += client.getYoffset();
    client.broadcast(ofToString(x) + "," + ofToString(y) + "," +ofToString(ofRandom(-5,5)) + "," +ofToString(ofRandom(-5,5)));
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}
