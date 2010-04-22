/*

 */

#ifndef __dsp_CASPSRUnpackerCUDA_h
#define __dsp_CASPSRUnpackerCUDA_h

#include<stdint.h>
//#include "dsp/HistUnpacker.h"

void caspsr_unpack (const uint64_t ndat,
		    float scale,
		    const unsigned char* stagingBufGPU,
		    float* pol0, float* pol1);
  

#endif
