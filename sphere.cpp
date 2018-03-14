// ==========================================================================
// $Id: sphere.cpp,v 1.2 2018/02/17 03:21:09 jlang Exp $
// Simple structure for data
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
// $Log: sphere.cpp,v $
// Revision 1.2  2018/02/17 03:21:09  jlang
// Simplified shape hierarchy for simplifying modifications
//
// Revision 1.1  2018/01/28 05:45:57  jlang
// Switch to core
//
//
// ==========================================================================
#include "sphere.h"
#pragma float_control(precise, off, push)
#pragma float_control(precise, pop)

Sphere::Sphere() : RenderShape() {
  // 42 vertices
  d_vertex.insert(d_vertex.end(), {
      0, 0.8506508, 0.5257311, 
	0, 0.8506508, -0.5257311, 
	0, -0.8506508, 0.5257311, 
	0, -0.8506508, -0.5257311, 
	0.8506508, 0.5257311, 0, 
	0.8506508, -0.5257311, 0, 
	-0.8506508, 0.5257311, 0, 
	-0.8506508, -0.5257311, 0, 
	0.5257311, 0, 0.8506508, 
	-0.5257311, 0, 0.8506508, 
	0.5257311, 0, -0.8506508, 
	-0.5257311, 0, -0.8506508
	});
  // 80 faces
  d_index.insert(d_index.end(), {
    1, 0, 4, 
	0, 1, 6, 
	2, 3, 5, 
	3, 2, 7, 
	4, 5, 10, 
	5, 4, 8, 
	6, 7, 9, 
	7, 6, 11, 
	8, 9, 2, 
	9, 8, 0, 
	10, 11, 1, 
	11, 10, 3, 
	0, 8, 4, 
	0, 6, 9, 
	1, 4, 10, 
	1, 11, 6, 
	2, 5, 8, 
	2, 9, 7, 
	3, 10, 5, 
	3, 7, 11
    });

  d_normal.insert(d_normal.end(), {
	  1,0,0,
	  1,0,0,
	  1,0,0,
	  1,0,0,
	  0,0,1,
	  0,0,1,
	  0,0,1,
	  0,0,1,
	  1,0,0,
	  1,0,0,
	  1,0,0,
	  1,0,0
  });

  // direct specification with all faces unrolled
  // - not supplied
}

