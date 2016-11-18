#pragma once

#include "ofMain.h"
#include "VectorMap.cpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void updateVectorField();
        void MakePerlinNoise(int  n_xres,  int  n_yres,  unsigned char*  pNoise);
    ofImage imageToShow;
    VectorMap* vectorMap;
    ofShader myShader;
    
    float*			pVectr;
    unsigned char*	pImage;
    unsigned char*	pNoise;
    unsigned char*	whiteNoise;
    float*			p_LUT0, *p_LUT1;
    int             n_xres,n_yres;
    bool showvecf;
};
