#include "ofApp.h"
#include "LICHeader.h"
//--------------------------------------------------------------
void ofApp::setup(){
    n_xres = SQUARE_FLOW_FIELD_SZ;
    n_yres = SQUARE_FLOW_FIELD_SZ;
    p_LUT0 = (float*		 ) malloc( sizeof(float        ) * DISCRETE_FILTER_SIZE);
    p_LUT1 = (float*		 ) malloc( sizeof(float        ) * DISCRETE_FILTER_SIZE);
    pVectr = (float*         ) malloc( sizeof(float        ) * n_xres * n_yres * 2 );
    pImage = (unsigned char* ) malloc( sizeof(unsigned char) * n_xres * n_yres     );
    pNoise = (unsigned char* ) malloc( sizeof(unsigned char) * n_xres * n_yres     );
    whiteNoise = (unsigned char* ) malloc( sizeof(unsigned char) * n_xres * n_yres     );
    
    SyntheszSaddle(n_xres, n_yres, pVectr);
    NormalizVectrs(n_xres, n_yres, pVectr);
    MakeWhiteNoise(n_xres, n_yres, pNoise);
    GenBoxFiltrLUT(DISCRETE_FILTER_SIZE, p_LUT0, p_LUT1);
    FlowImagingLIC(n_xres, n_yres, pVectr, pNoise, pImage, p_LUT0, p_LUT1, LOWPASS_FILTR_LENGTH);

    ofImage trump;
    trump.load("trump.jpg");
    pNoise = trump.getPixels();
//    imageToShow = new ofImage();
    imageToShow.allocate(n_xres, n_xres, OF_IMAGE_GRAYSCALE);
    imageToShow.setFromPixels(pImage, n_xres, n_xres, OF_IMAGE_GRAYSCALE);
    
//
//    for(int  j = 0;	 j < SQUARE_FLOW_FIELD_SZ;  j ++)
//    for(int  i = 0;	 i < SQUARE_FLOW_FIELD_SZ;  i ++)
//    {
//        cout<<(image[j * 400 + i]);
//    }
}

//--------------------------------------------------------------
void ofApp::update(){
    updateVectorField();
//    MakeWhiteNoise(n_xres, n_yres, pNoise);
    MakePerlinNoise(n_xres, n_yres, pNoise);
    FlowImagingLIC(n_xres, n_yres, pVectr, pNoise, pImage, p_LUT0, p_LUT1, min(ofGetElapsedTimef()*3,LOWPASS_FILTR_LENGTH));
    imageToShow.setFromPixels(pImage, n_xres, n_xres, OF_IMAGE_GRAYSCALE);
    imageToShow.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    cout<<ofGetFrameNum()<<endl;
    imageToShow.draw(0, 0,400,400);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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

void ofApp::updateVectorField(){
    for(int  j = 0;  j < n_yres;  j ++)
        for(int  i = 0;  i < n_xres;  i ++)
        {
            int	 index = (  (n_yres - 1 - j) * n_xres + i  )  <<  1;
            //        pVectr[index    ] = - ( j / (n_yres - 1.0f) - 0.5f );
            //        pVectr[index + 1] =     i / (n_xres - 1.0f) - 0.5f;
            //
            float y_textCoord = j / (n_yres - 1.0f);
            float x_textCoord = i / (n_xres - 1.0f);
            // float rad = atan((y_textCoord - 0.5)/(x_textCoord-0.5));
            
            pVectr[index    ] = y_textCoord- 0.5;
            pVectr[index + 1] = x_textCoord- 0.5;
        }
}

void ofApp::MakePerlinNoise(int  n_xres,  int  n_yres,  unsigned char*  pNoise)
{
    for(int  j = 0;   j < n_yres;  j ++)
        for(int  i = 0;   i < n_xres;  i ++)
        {
            pNoise[j * n_xres + i] =  whiteNoise[j * n_xres + i] + int((ofNoise(float(i)/n_xres, ofGetElapsedTimef())-0.5)*255);
        }
}

