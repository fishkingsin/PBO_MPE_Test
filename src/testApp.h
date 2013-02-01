#pragma once

#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "mpeClientTCP.h"
#include "Ball.h"
#include "ofPBO.h"
class PBOPlayer
{
public:
	ofPBO pbo;
	bool updateTex;
	ofTexture tex;
	ofQTKitPlayer player;
	void setup()
	{
//		ofDisableTextureEdgeHack();
		string path = "/Volumes/data_RAID/Downloads/Videos/test/";
		ofDirectory dir;
		dir.allowExt("mp4");
		dir.allowExt("avi");
		dir.allowExt("mov");
		dir.allowExt("m4v");
		dir.listDir(path);
		player.setPixelFormat(OF_PIXELS_RGB);
		ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_PIXELS_ONLY;
		player.loadMovie(path+"IMG_1891.MOV", decodeMode);
//		player.loadMovie(dir.getPath(int(ofRandom(dir.getFiles().size()))), decodeMode);
		
		tex.allocate(player.getPixelsRef());
		pbo.allocate(tex,1);
		player.play();
		player.setPaused(true);
		updateTex = false;
	}
	void update(int frame)
	{
		player.update();
		player.setFrame(frame%player.getTotalNumFrames());
		if(player.isFrameNew()){

			
			pbo.loadData(player.getPixelsRef());
			updateTex = true;
		}
	}
	void updateTexture()
	{
		if(updateTex){
			pbo.updateTexture();
			updateTex = false;
		}
	}
	void draw(float x, float y, float w, float h)
	{
//		if(updateTex){
//			pbo.updateTexture();
//			updateTex = false;
//		}
		tex.draw(x,y,w,h);
	}
	void draw()
	{
		if(updateTex){
			pbo.updateTexture();
			updateTex = false;
		}
		tex.draw(0,0);
	}
};
class testApp : public ofBaseApp, public mpeClientListener {
    
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
    
    void frameEvent();
    
private:
    mpeClientTCP  client;
    vector<Ball*> balls;
    PBOPlayer player;
	int totalFrames , currentFrame;
	ostringstream os;

	float timeCount;
};

#endif



