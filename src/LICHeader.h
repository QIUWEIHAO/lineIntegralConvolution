//
//  LICHeader.h
//  lineIntergralConvolution
//
//  Created by Scofield on 11/15/16.
//
//

#ifndef LICHeader_h
#define LICHeader_h

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>


#define  SQUARE_FLOW_FIELD_SZ	1000
#define	 DISCRETE_FILTER_SIZE	2048
#define  LOWPASS_FILTR_LENGTH	40.00000f
#define	 LINE_SQUARE_CLIP_MAX	100000.0f
#define	 VECTOR_COMPONENT_MIN   0.050000f


void     SyntheszSaddle(int  n_xres,  int     n_yres,  float*   pVectr);
void	 NormalizVectrs(int  n_xres,  int     n_yres,  float*   pVectr);
void     GenBoxFiltrLUT(int  LUTsiz,  float*  p_LUT0,  float*   p_LUT1);
void     MakeWhiteNoise(int  n_xres,  int     n_yres,  unsigned char*  pNoise);
void	 FlowImagingLIC(int  n_xres,  int     n_yres,  float*   pVectr,   unsigned char*  pNoise,
                        unsigned char*  pImage,  float*  p_LUT0,  float*  p_LUT1,  float  krnlen);
void 	 WriteImage2PPM(int  n_xres,  int     n_yres,  unsigned char*  pImage,     char*  f_name);
unsigned char*    licMain();

#endif /* LICHeader_h */
