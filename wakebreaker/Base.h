#ifndef _BASE_H_
#define _BASE_H_

#include <math.h>
#include <stdio.h>
#include <string.h>

#include <stdint.h>

#include <math.h>
#include <time.h>
#include "GLES/gl.h"
#include "GLES/egl.h"

#pragma warning (disable : 4244 4100)

typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed int int32;
typedef unsigned int uint32;
typedef int64_t int64;


#define SAFE_DELETE(p) { if(p) { delete p; p = NULL; } }
#define SAFE_ARRAY_DELETE(p) { if(p) { delete [] p; p = NULL; } }
#define PIX 205887
#define TWOPIX 411775



#endif
