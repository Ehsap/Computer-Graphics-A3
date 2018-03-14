// ==========================================================================
// $Id: attributes.cpp,v 1.1 2018/02/17 03:21:05 jlang Exp $
// Attributes class to augment shape. Based on box_shape 1.6.
// ==========================================================================
// (C)opyright:
//
//   Jochen Lang
//   EECS, University of Ottawa
//   800 King Edward Ave.
//   Ottawa, On., K1N 6N5
//   Canada.
//   http://www.eecs.uottawa.ca
//
// Creator: jlang (Jochen Lang)
// Email:   jlang@uottawa.ca
// ==========================================================================
// $Log: attributes.cpp,v $
// Revision 1.1  2018/02/17 03:21:05  jlang
// Simplified shape hierarchy for simplifying modifications
//
//
// ==========================================================================
#include <iostream>

#define _USE_MATH_DEFINES
#define GLM_ENABLE_EXPERIMENTAL

#include <cmath>
#include<math.h>

#include "attributes.h"
// matrix manipulation
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

void Attributes::createColors() {
  // create a jet color map

  int step = d_nColors/4;
  int step2 = step/2;

  for (int i = 0; i < step2; ++i ) {
    d_colors[i].r = 0.0f;
    d_colors[i].g = 0.0f;
    d_colors[i].b = 0.5f + (i*0.5f)/step2;
    d_colors[i].a = 1.0f;
  }
  for (int i = step2; i < step+step2; ++i ) {
    d_colors[i].r = 0.0f;
    d_colors[i].g = static_cast<float>(i-step2)/step;
    d_colors[i].b = 1.0f;
    d_colors[i].a = 1.0f;
  }
  for (int i = step+step2; i<2*step+step2; ++i ) {
    d_colors[i].r = static_cast<float>(i-step-step2)/step;
    d_colors[i].g = 1.0f;
    d_colors[i].b = static_cast<float>(2*step+step2-i)/step;
    d_colors[i].a = 1.0f;
  }
  for (int i = 2*step+step2; i<3*step+step2; ++i ) {
    d_colors[i].r = 1.0f;
    d_colors[i].g = static_cast<float>(3*step+step2-i)/step;
    d_colors[i].b = 0.0f;
    d_colors[i].a = 1.0f;
  }
  for (int i = 3*step+step2; i<d_nColors; ++i ) {
    d_colors[i].r = static_cast<float>(d_nColors-i)/step + 0.5f;
    d_colors[i].g = 0.0f;
    d_colors[i].b = 0.0f;
    d_colors[i].a = 1.0f;
  }
  /*
  for (int i = 0; i < d_nColors; ++i ) {
    std::cerr << i << " [" << d_colors[i].r
    	<< " " << d_colors[i].g
      << " " << d_colors[i].b << "]" << std::endl;
  }
  */
  return;
}

void Attributes::createTransforms(glm::vec3 _minP, glm::vec3 _maxP) {
  glm::vec3 volume = _maxP - _minP;
  for (int i=0; i<d_nTfms; ++i) {
    glm::vec3 randVec;
    float len2;
    // make a unit vector
    do {
      randVec = glm::vec3(2.0f*randomUnit()-1.0f,
			  2.0f*randomUnit()-1.0f,
			  2.0f*randomUnit()-1.0f);
      len2 = glm::dot(randVec,randVec); 
    } while ( len2 > 1.0f );
    // Now normalize
    randVec *= 1.0f/sqrt(len2);
    // random angle -pi .. pi
    float angle = static_cast<float>(M_PI * ( 2.0 * randomUnit() -  1.0 ));
    d_tfms[i] = glm::rotate( angle, randVec );
    // Add a random vector scaled upto the viewing volume
    randVec.x = (randomUnit()-0.5f) * volume.x;
    randVec.y = (randomUnit()-0.5f) * volume.y;
    randVec.z = (randomUnit()-0.5f) * volume.z;
    d_tfms[i] = glm::translate( d_tfms[i], randVec );
  }
  return;
}
