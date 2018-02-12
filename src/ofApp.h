#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxMaxim.h"
#include "maxiGrains.h"
#include "ofxOsc.h"
#include <sys/time.h>

#define HOST "localhost"
#define RECEIVEPORT 12000
#define SENDPORT 6448

typedef hannWinFunctor grainPlayerWin;


class ofApp : public ofBaseApp{
    
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
    void init_band_arrays(float ***data_ptr, int dim_x, int dim_y);
    maxiSample processSound(maxiSample recording);
    void processSoundVec();
    void audioOut(float * output, int bufferSize, int nChannels);
    void audioIn(float * input, int bufferSize, int nChannels);
    void exit();
    void setupRecording();
    
    int		bufferSize;
    int		initialBufferSize; /* buffer size */
    int		sampleRate;

    
    
    double outputs[2];
    
    //processing sound
    maxiSample normSamp;
    
    //sound recording
    bool recordingOn;
    bool recButton;
    vector<float> recorder;
    double bufferCount;
};


