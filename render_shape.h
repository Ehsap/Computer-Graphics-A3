// ==========================================================================
// $Id: render_shape.h,v 1.4 2018/03/05 03:19:23 jlang Exp $
// Simple sphere based on icosahedron approximation. Based on box_shape 1.6.
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
// $Log: render_shape.h,v $
// Revision 1.4  2018/03/05 03:19:23  jlang
// Added normals to render shape
//
// Revision 1.3  2018/02/26 23:55:55  jlang
// Update for render shape
//
// Revision 1.2  2018/02/17 03:21:06  jlang
// Simplified shape hierarchy for simplifying modifications
//
// Revision 1.1  2018/01/28 05:45:57  jlang
// Switch to core
//
//
// ==========================================================================
#ifndef CSI4130_SPHERE_SHAPE_H_
#define CSI4130_SPHERE_SHAPE_H_


#include <vector>

#include <cassert>

// gl types
#include <GL/glew.h>
//#if WIN32
//#include <gl/wglew.h>
//#else
//#include <GL/glext.h>
//#endif

// glm types
#include <glm/glm.hpp>

#include "shape.h"
#include "attributes.h"

class RenderShape : public Shape, public Attributes {
 protected:
  // index-based rendering
  GLushort d_restart = 0xFFFF; //-32768;
  // Vertex coordinates
  std::vector<GLfloat> d_vertex;
	std::vector<GLfloat> d_normal;
  std::vector<GLushort> d_index;
  // direct specification with all faces unrolled
  std::vector<GLfloat> d_vertex_direct;
  
 public:
  
  inline RenderShape(int _nColors = 12, int _nTfms = 12,
  		     glm::vec3 _minP = glm::vec3(-1.0f,-1.0f,-1.0f),
  		     glm::vec3 _maxP = glm::vec3( 1.0f, 1.0f, 1.0f));
  /*
  inline ~RenderShape() {
    if (d_vertex) delete[] d_vertex;
    if (d_index) delete[] d_index;
    if (d_vertex_direct) delete[] d_vertex_direct;
  }
  */
  
  // indexed drawing
  inline int getNPoints() const;
  inline glm::vec3 getVertex( int _num ) const;
	inline glm::vec3 getNormal( int _num ) const;
  inline int getNIndices() const;
  inline GLushort getIndex( int _num ) const;


	inline GLushort getRestart() const;

  inline const GLfloat* getVertices() const;
	inline const GLfloat* getNormals() const;
  inline const GLushort* getIndicies() const;
	
  // direct drawing
  inline int getNTriangles() const;
  inline const GLfloat* getVertexDirect() const;
  
  // instanced drawing
  inline int getNColors() const;
  inline int getNTransforms() const;
  
  
 private:
  // no copy or assignment
  RenderShape(const RenderShape& _oSphere );
  RenderShape& operator=( const RenderShape& _oSphere );
};


RenderShape::RenderShape( int _nColors, int _nTfms,
			  glm::vec3 _minP, glm::vec3 _maxP ) :
Attributes( _nColors, _nTfms, _minP, _maxP ) {
}

int RenderShape::getNPoints() const {
  return d_vertex.size();
}


glm::vec3 RenderShape::getVertex( int _num ) const {
  assert( _num < d_vertex.size() );
  return glm::vec3(d_vertex[_num*3],d_vertex[_num*3+1],d_vertex[_num*3+2]);
}


glm::vec3 RenderShape::getNormal( int _num ) const {
  assert( _num < d_normal.size() );
  return glm::vec3(d_normal[_num*3],d_normal[_num*3+1],d_normal[_num*3+2]);
}


int RenderShape::getNIndices() const {
  return d_index.size();
}

GLushort RenderShape::getIndex( int _num ) const {
  assert( _num < d_index.size() );
  return d_index[_num];
}

GLushort RenderShape::getRestart() const {
  return d_restart;
}

const GLfloat* RenderShape::getVertices() const {
  return d_vertex.data();
}

const GLfloat* RenderShape::getNormals() const {
  return d_normal.data();
}

const GLushort* RenderShape::getIndicies() const {
  return d_index.data();
}


const GLfloat* RenderShape::getVertexDirect() const {
  return d_vertex_direct.data();
}


int RenderShape::getNTriangles() const {
  return d_vertex_direct.size()/3/3; // d_nTriangles and number of coords;
}

int RenderShape::getNColors() const {
  return getAttribNColors();
};


int RenderShape::getNTransforms() const {
  return getAttribNTransforms();
}


#endif
