//
//  VectorMap.cpp
//  lineIntergralConvolution
//
//  Created by Scofield on 11/16/16.
//
//

#include <stdio.h>
#include "ofMain.h"
#include <vector>
#include "math.h"

class VectorMap{
public:
    int xRes;
    int yRes;
    ofVec2f center;
    vector<ofVec2f> ankors;// polar coordinate
    float* angleArrayForCenters;
    float* vectors;
    
    VectorMap(int _xRes, int _yRes, ofVec2f _center, vector<ofVec2f> _ankors){
        xRes = _xRes;
        yRes = _yRes;
        center = _center;
        ankors = _ankors;
        angleArrayForCenters = (float*) malloc( sizeof(float) * xRes * yRes);
        vectors = (float*) malloc( sizeof(float) * xRes * yRes * 2 );
    }
    
    void calculateAngles(){
        for(int  j = 0;  j < xRes;  j ++)
            for(int  i = 0;  i < yRes;  i ++){
                float y_textCoord = j / (yRes - 1.0f);
                float x_textCoord = i / (xRes - 1.0f);
                int	 index = (  j * yRes + i  );
                
                // Calculate Theta
                float theta = calculateTheta(x_textCoord,y_textCoord);
                float radius = sqrt(y_textCoord*y_textCoord + x_textCoord*x_textCoord);
                
                float ankorIndex = whichAnkorsBetween(ofVec2f(theta,radius),ankors);
                float radiusRef, amt, tempTheta;
                
                if (ankorIndex != -1){
                    
                    if (ankorIndex != 3){
                        amt = (theta-ankors[ankorIndex].x)/(ankors[ankorIndex+1].x-ankors[ankorIndex].x);
                        radiusRef = lerp(ankors[ankorIndex].y , ankors[ankorIndex+1].y, amt,1.0);
                        tempTheta = lerp(ankors[ankorIndex].x , ankors[ankorIndex+1].x , amt , radius/radiusRef);
                    }else{
                        float deltaAngle = theta-ankors[ankorIndex].x;
                        if (deltaAngle < 0) deltaAngle = deltaAngle + 2*PI;
                        float sumDeltaAngle = ankors[0].x - ankors[ankorIndex].x + 2*PI;
                        amt = deltaAngle/sumDeltaAngle;
                        
                        radiusRef = lerp(ankors[ankorIndex].y , ankors[0].y, amt,1.0);
                        tempTheta = lerp(ankors[ankorIndex].x , ankors[0].x + 2*PI, amt , radius/radiusRef);
                        if (tempTheta > 2*PI){
                            tempTheta = tempTheta - 2*PI;
                        }
                    }
                }
                
                tempTheta = tempTheta+ PI/2;
                angleArrayForCenters[index] = tempTheta;
                
                vectors[index*2] = cos(tempTheta);
                vectors[index*2 + 1] = sin(tempTheta);
                
            }
    }
    
    float calculateTheta(float x, float y ){
        
        float tempTheta;
        float thetaFraction = (y - center.y)/(x - center.x);
//        if(thetaFraction > 10000000000){
//            tempTheta = PI/2;
//        }else if (thetaFraction < -10000000000){
//            tempTheta = -PI/2;
//        }else{
            if (x < center.x) {
                tempTheta = atan(thetaFraction) + PI;
                
            }else{
                tempTheta = atan(thetaFraction);
                if (tempTheta < 0)  tempTheta = tempTheta + 2 * PI;
            }
//        }
        return tempTheta;
    }
    
    float lerp(float n1, float n2, float amt, float exp){
        return (n2-n1)*pow(amt,exp) + n1;
    }
    
    int whichAnkorsBetween(ofVec2f p, vector<ofVec2f> ankors){
        if (ankors.size() != 4)
            return -1;
        else{
            for (int i = 0 ; i < 3 ; i++){
                if (p.x > ankors[i+1].x) continue;
                else if (p.x > ankors[i].x){
                    return i;
                }
            }
            return 3;
        }
        
    }
    
//    void getVector(int i, int j){
//        int	 index = (  (xRes - 1 - j) * yRes + i  )  <<  1;
//        return ofVec2f(vectors[index],vectors[index+1]);
//    }
//    
//    void setVector(int i, int j, ofVec2f targetVector){
//        int	 index = (  (xRes - 1 - j) * yRes + i  )  <<  1;
//        vectors[index]   = targetVector.x;
//        vectors[index+1] = targetVector.y;
//    }
    
//    void generateVectors(){
//        for(int  j = 0;  j < xRes;  j ++)
//            for(int  i = 0;  i < yRes;  i ++)
//            {
//                int	 index = (  (xRes - 1 - j) * yRes + i  )  <<  1;
//                
//                float y_textCoord = j / (yRes - 1.0f);
//                float x_textCoord = i / (xRes - 1.0f);
//                // float rad = atan((y_textCoord - 0.5)/(x_textCoord-0.5));
//                
//                float vecXSum = 0 , vecYSum = 0;
//                int centerNum = centers.size();
//                for (int k = 0; k < centerNum;k++){
//                    vecYSum = vecYSum + (y_textCoord - (1-centers[k].y))*(y_textCoord - (1-centers[k].y));
//                    vecXSum = vecXSum + (x_textCoord - centers[k].x)*(x_textCoord - centers[k].x);
//                }
//                vectors[index    ] = vecYSum/centerNum;
//                vectors[index + 1] = vecXSum/centerNum;
//            }
//    }
    
};