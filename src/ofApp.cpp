/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */

#include "ofApp.h"
//#include "maximilian.h"/* include the lib */
#include "time.h"
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>


//--------------------------------------------------------------
void ofApp::setup(){
    
    /* This is stuff you always need.*/
      
    //samples from http://freesound.org
    normSamp.load(ofToDataPath("voice_.wav"));
    
    ofEnableAlphaBlending();
    ofSetupScreen();
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    
    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    
    
    ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
      ofBackground(0,0,0);
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */


   // processSound(normSamp);

    recordingOn = false;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    

    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
}
int myrandom (int i) { return std::rand()%i;}

maxiSample ofApp::processSound(maxiSample recording){
    
    maxiSample out;
    maxiRecorder rec;
    maxiFilter band;
    
    out = recording;
    double frequencyValues = 44100*0.8;
    float buffer1[(int)frequencyValues];
    double lengthSamp = out.getLength();
    double sampChunks = lengthSamp/frequencyValues;
    vector<int>order;
    order.resize((int)sampChunks);
    for(int i = 0; i < sampChunks; i++){
        order[i] = i;
    }
    
    std::random_shuffle ( order.begin(), order.end(),myrandom);
    
    
    rec.setup(ofToDataPath("newRecording.wav"));
    rec.startRecording();
    for(double i = 0 ; i < sampChunks; i++){
        double pos =  ofMap(order[i],0,sampChunks,0.1,1.0);
       // double pos = ofMap(i, 0, sampChunks, 0.1, 1.0);
        out.setPosition(pos);
        for(double playing = 0; playing<frequencyValues; playing++){
            buffer1[(int)playing]=out.playOnce()*10.0;
        }
            rec.passData(buffer1,frequencyValues);
    }
    
    rec.stopRecording();
    rec.saveToWav();

    
    
    return out;
}

void ofApp::processSoundVec(){
    
    maxiSample out;
    maxiRecorder rec;
    maxiFilter band;
    
    double frequencyValues = 44100*0.8;
    float buffer1[(int)frequencyValues];
    double lengthSamp = recorder.size();
    double sampChunks = lengthSamp/frequencyValues;
    vector<int>order;
    order.resize((int)sampChunks);
    for(int i = 0; i < sampChunks; i++){
        order[i] = i;
    }
    
    std::random_shuffle ( order.begin(), order.end(),myrandom);
    
    
    rec.setup(ofToDataPath("newRecording.wav"));
    rec.startRecording();
    for(double i = 0 ; i < sampChunks; i++){
        double pos = order[i]*frequencyValues;
        for(double playing = 0; playing<frequencyValues; playing++){
            buffer1[(int)playing]=recorder[playing+pos];
        }
        rec.passData(buffer1,frequencyValues);
    }
    
    rec.stopRecording();
    rec.saveToWav();

    
}


//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    
    for (int i = 0; i < bufferSize; i++){
        
        
        
    }
  
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    // samples are "interleaved"
    if(recordingOn){
        for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
            recorder.push_back(input[i*nChannels]);
        }
        bufferCount++;
    }
}

void ofApp::setupRecording(){
    if(recorder.size() > 0){
        recorder.clear();
    }
    bufferCount = 1;
    recordingOn =! recordingOn;
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key =='a'){
        recButton  =! recButton;
        if(recButton){
            setupRecording();
        } else {
            processSoundVec();
        }
    }
   }

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}


void ofApp::exit(){
}



//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
