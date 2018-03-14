// ==========================================================================
// $Id: shape.h,v 1.1 2018/01/28 05:45:57 jlang Exp $
// Shape interface. Code is based on box_shape 1.5
// ==========================================================================
// (C)opyright:
//
//   Jochen Lang
//   SITE, University of Ottawa
//   800 King Edward Ave.
//   Ottawa, On., K1N 6N5
//   Canada.
//   http://www.site.uottawa.ca
//
// Creator: jlang (Jochen Lang)
// Email:   jlang@site.uottawa.ca
// ==========================================================================
// $Log: shape.h,v $
// Revision 1.1  2018/01/28 05:45:57  jlang
// Switch to core
//
// ==========================================================================
#ifndef CSI4130_SHAPE_H_
#define CSI4130_SHAPE_H_

// gl types
#include <GL/glew.h>
//#if WIN32
//#include <gl/wglew.h>
//#else
//#include <GL/glext.h>
//#endif

// glm types
#include <glm/glm.hpp>

struct Shape {
	// indexed drawing
  virtual int getNPoints() const = 0;
  virtual glm::vec3 getVertex( int _num ) const = 0;
  virtual int getNIndices() const = 0;
  virtual GLushort getIndex( int _num ) const = 0;
  virtual GLushort getRestart() const = 0;

  // direct drawing
  virtual int getNTriangles() const = 0;
	  
  // instanced drawing
  virtual int getNTransforms() const = 0;
  virtual int getNColors() const = 0;
};

#endif
