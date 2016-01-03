

#pragma once

#ifndef _GUTL_TYPE_H_
#define _GUTL_TYPE_H_

namespace gutl{


typedef 
enum _PROJECTION_TYPE{
	
	GGL_ORTOGONAL,
	GGL_PERSPECTIVE,
	GGL_NULL

}PROJECTION_TYPE;


//New types ...
typedef float scalar_t; // the scalar data type

typedef 
struct _Vector4
{
	scalar_t x;
	scalar_t y;
	scalar_t z;
	scalar_t w;

}Vector4;




//macros definiciones
#define SQUARE(x) (x)*(x)


}

#endif