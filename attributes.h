// ==========================================================================
// $Id: attributes.h,v 1.1 2018/02/17 03:21:05 jlang Exp $
// Attribute class to extend shape capabilities. Code is based on box_shape 1.5
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
// $Log: attributes.h,v $
// Revision 1.1  2018/02/17 03:21:05  jlang
// Simplified shape hierarchy for simplifying modifications
//
// ==========================================================================
#ifndef CSI4130_ATTRIBUTES_H_
#define CSI4130_ATTRIBUTES_H_

#include <cassert>
#include <cstdlib> // Needed in windows for rand

// gl types
#include <GL/glew.h>
//#if WIN32
//#include <gl/wglew.h>
//#else
//#include <GL/glext.h>
//#endif

// glm types
#include <glm/glm.hpp>


class Attributes {
 protected:
  int d_nColors;
  int d_nTfms;

 public:
  // vertex attributes
  glm::vec4* d_colors;
  glm::mat4* d_tfms;
  
 public:
  inline Attributes(int _nColors = 12, int _nTfms = 12,  
		    glm::vec3 _minP = glm::vec3(-1.0f,-1.0f,-1.0f),
		    glm::vec3 _maxP = glm::vec3( 1.0f, 1.0f, 1.0f));
  virtual inline ~Attributes();
    
  // instanced drawing
  inline int getAttribNTransforms() const;
  inline int getAttribNColors() const;

  // Call to change viewing volume
  inline void updateTransforms( int _nTfms, 
				glm::vec3 _minP = glm::vec3(-1.0f,-1.0f,-1.0f),
				glm::vec3 _maxP = glm::vec3( 1.0f, 1.0f, 1.0f));
  
  inline void updateColors( int _nColors );

 private:
  void createColors();
  void createTransforms(glm::vec3 _minP, glm::vec3 _maxP);

  static inline float randomUnit();
	
  // no copy or assignment
  Attributes(const Attributes& _oAttributes );
  Attributes& operator=( const Attributes& _oAttributes );
};

Attributes::Attributes( int _nColors, int _nTfms,
		    glm::vec3 _minP, glm::vec3 _maxP ) : 
d_nColors(_nColors), d_nTfms(_nTfms) {
  d_colors = new glm::vec4[d_nColors];
  createColors();
  d_tfms = new glm::mat4[d_nTfms];
  createTransforms(_minP,_maxP);
}


Attributes::~Attributes() {
  delete[] d_colors;
  delete[] d_tfms;
}

int Attributes::getAttribNColors() const {
  return d_nColors;
}

int Attributes::getAttribNTransforms() const {
  return d_nTfms;
}

inline void Attributes::updateTransforms( int _nTfms, 
	  glm::vec3 _minP, glm::vec3 _maxP ) { 
	if ( d_nTfms != _nTfms ) {
		delete[] d_tfms;
		d_nTfms = _nTfms;
	  d_tfms = new glm::mat4[d_nTfms];	
	}
  createTransforms(_minP,_maxP);
}

inline void Attributes::updateColors( int _nColors ) {
	if ( d_nColors != _nColors ) { 
		delete[] d_colors;
		d_nColors = _nColors; 
	  d_colors = new glm::vec4[d_nColors];
	}  
	createColors();
}

inline float Attributes::randomUnit() {
  return static_cast<float>(rand())/RAND_MAX; 
}



#endif
