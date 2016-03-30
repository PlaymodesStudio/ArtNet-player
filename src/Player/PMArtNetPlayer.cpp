//
//  PMArtNetPlayer.cpp
//  ArtNet-player
//
//  Created by Eduard Frigola on 04/03/16.
//
//

#include "PMArtNetPlayer.h"


bool PMArtNetPlayer::setup(string videoFilename, const char* machineIP, const char* targetIP){
    setupBase();
    //buildOutputDevicesPanel();
    
    //header
    playHeader.setPosition(vidImageContainer.getX(), vidImageContainer.getBottom()+20);
    playHeader.setSize(vidImageContainer.getWidth(), 20);
    
    
    videoPlayer.setPixelFormat(OF_PIXELS_RGB); //set pixel type to NATIVE, although it has to be always rgb
    videoPlayer.load(videoFilename);  //load Video
    auto universes = videoPlayer.getPixels().getHeight();
    buildNodesPanel(3);
    videoPlayer.setLoopState(OF_LOOP_NORMAL);
    
    playHeader.setDuration(videoPlayer.getDuration());
    ofAddListener(playHeader.headerDragged, this, &PMArtNetPlayer::changePlayHead);
    
    artnet.setup(PM_ARTNET_PLAYER);
    artnet.setTargetIP(targetIP);
//    artnet.start();
}

void PMArtNetPlayer::update(){
    videoPlayer.update();

    artnet.sendDmx(videoPlayer.getPixels());
    playHeader.setHeaderPosition(videoPlayer.getPosition());
}

void PMArtNetPlayer::draw(int x, int y, int w, int h){
    videoPlayer.draw(vidImageContainer);
    drawBasicLayout();
    playHeader.draw();
}

void PMArtNetPlayer::changePlayHead(float &position){
    videoPlayer.setPosition(position);
}


void PMArtNetPlayer::mousePressed(int x, int y, int button){
    if(fileSelectorCustom.isInside(x, y))
        fileSelectorCustom.selectToOpen();
    playHeader.dragged(x, y);
}