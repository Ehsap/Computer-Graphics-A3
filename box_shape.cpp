// ==========================================================================
// $Id: box_shape.cpp,v 1.3 2018/03/08 16:23:07 jlang Exp $
// Simple shape for interactions
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
// $Log: box_shape.cpp,v $
// Revision 1.3  2018/03/08 16:23:07  jlang
// Update to reflect shape hierarchy
//
// Revision 1.3  2018/03/05 03:18:41  jlang
// Updated to render_shape
//
// Revision 1.8  2018/02/26 23:54:14  jlang
// Update for render shape
//
// Revision 1.7  2018/01/27 20:12:18  jlang
// separated box from instanced attributes, defined shape interface
//
// Revision 1.6  2016/03/08 17:48:16  jlang
// Check in for 2016
//
// Revision 1.5  2014/10/03 23:00:17  jlang
// Switch to radians, correct GLSL version.
//
// Revision 1.4  2014/02/10 20:43:03  jlang
// Created skeleton programs.
//
// Revision 1.3  2014/02/07 22:44:45  jlang
// Merged version between laptop and desktop
//
// Revision 1.2  2014/02/06 23:30:05  jlang
// Instanced rendering with drawElements working - needs better way to pass translation limits.
//
// Revision 1.1  2014/02/03 03:38:45  jlang
// Draft lab check in
//
// Revision 1.1  2014/01/18 16:43:12  jlang
// Created solution for lab1 in OpenGL 4
//
// Revision 1.1  2011/01/15 00:23:37  jlang
// Created lab1 including skeleton
//
//
// ==========================================================================
#include "box_shape.h"
#define GLM_ENABLE_EXPERIMENTAL

BoxShape::BoxShape() : RenderShape() {
	// Duplicate vertices to get unique pairs of position and normal
  d_vertex.insert(d_vertex.end(), {
			// -x face
			-0.5f, -0.5f, -0.5f, // 0
				-0.5f, -0.5f,  0.5f, // 1
				-0.5f,  0.5f, -0.5f, // 2
				-0.5f,  0.5f,  0.5f, // 3
				// y face
				-0.5f,  0.5f, -0.5f, // 2
				-0.5f,  0.5f,  0.5f, // 3
				0.5f,  0.5f, -0.5f, // 6
				0.5f,  0.5f,  0.5f, // 7
				// x face
				0.5f,  0.5f, -0.5f, // 6
				0.5f,  0.5f,  0.5f, // 7
				0.5f, -0.5f, -0.5f, // 4
				0.5f, -0.5f,  0.5f, // 5
				// -z face
				-0.5f,  0.5f, -0.5f, // 2
				0.5f,  0.5f, -0.5f, // 6
				-0.5f, -0.5f, -0.5f, // 0
				0.5f, -0.5f, -0.5f, // 4
				// -y face
				-0.5f, -0.5f, -0.5f, // 0
				0.5f, -0.5f, -0.5f, // 4
				-0.5f, -0.5f,  0.5f, // 1
				0.5f, -0.5f,  0.5f, // 5
				// z-face
				-0.5f, -0.5f,  0.5f, // 1
				0.5f, -0.5f,  0.5f, // 5
				-0.5f,  0.5f,  0.5f, // 3
				0.5f,  0.5f,  0.5f  // 7
				});
	
  d_normal.insert(d_normal.end(), {
			// -x face
			-1.0f,  0.0f,  0.0f, // 0
				-1.0f,  0.0f,  0.0f, // 1
				-1.0f,  0.0f,  0.0f, // 2
				-1.0f,  0.0f,  0.0f, // 3
				// y face
				0.0f,  1.0f,  0.0f, // 2
				0.0f,  1.0f,  0.0f, // 3
				0.0f,  1.0f,  0.0f, // 6
				0.0f,  1.0f,  0.0f, // 7
				// x face
				1.0f,  0.0f,  0.0f, // 6
				1.0f,  0.0f,  0.0f, // 7
				1.0f,  0.0f,  0.0f, // 4
				1.0f,  0.0f,  0.0f, // 5
				// -z face
				0.0f,  0.0f, -1.0f, // 2
				0.0f,  0.0f, -1.0f, // 6
				0.0f,  0.0f, -1.0f, // 0
				0.0f,  0.0f, -1.0f, // 4
				// -y face
				0.0f, -1.0f,  0.0f, // 0
				0.0f, -1.0f,  0.0f, // 4
				0.0f, -1.0f,  0.0f, // 1
				0.0f, -1.0f,  0.0f, // 5
				// z-face
				0.0f,  0.0f,  1.0f, // 1
				0.0f,  0.0f,  1.0f, // 5
				0.0f,  0.0f,  1.0f, // 3
				0.0f,  0.0f,  1.0f  // 7
				});

	
  d_index.insert(d_index.end(), {
			0,1,2,3,     // -x
				d_restart,
				4,5,6,7,     // +y
				d_restart,
				8,9,10,11,   // +x
				d_restart,
				12,13,14,15, // -z
				d_restart,
				16,17,18,19, // -y
				d_restart,
				20,21,22,23  // +z
				});

  // direct specification
    d_vertex_direct.insert(d_vertex_direct.end(), {
	-0.5f, -0.5f, -0.5f, // 0
	  -0.5f, -0.5f,  0.5f, // 1
	  -0.5f,  0.5f, -0.5f, // 2
	  
	  -0.5f, -0.5f,  0.5f, // 1
	  -0.5f,  0.5f, -0.5f, // 2
	  -0.5f,  0.5f,  0.5f, // 3
	  
	  -0.5f,  0.5f, -0.5f, // 2
	  -0.5f,  0.5f,  0.5f, // 3
	  0.5f,  0.5f, -0.5f, // 6
 
	  -0.5f,  0.5f,  0.5f, // 3
	  0.5f,  0.5f, -0.5f, // 6
	  0.5f,  0.5f,  0.5f, // 7
	  
	  0.5f,  0.5f, -0.5f, // 6
	  0.5f,  0.5f,  0.5f, // 7
	  0.5f, -0.5f, -0.5f, // 4
	  
	  0.5f,  0.5f,  0.5f, // 7
	  0.5f, -0.5f, -0.5f, // 4
	  0.5f, -0.5f,  0.5f, // 5
	  //---------------------------
	  -0.5f,  0.5f, -0.5f, // 2
	  0.5f,  0.5f, -0.5f, // 6
	  -0.5f, -0.5f, -0.5f, // 0
  
	  0.5f,  0.5f, -0.5f, // 6
	  -0.5f, -0.5f, -0.5f, // 0
	  0.5f, -0.5f, -0.5f, // 4
  
	  -0.5f, -0.5f, -0.5f, // 0
	  0.5f, -0.5f, -0.5f, // 4
	  -0.5f, -0.5f,  0.5f, // 1

	  0.5f, -0.5f, -0.5f, // 4
	  -0.5f, -0.5f,  0.5f, // 1
	  0.5f, -0.5f,  0.5f, // 5

	  -0.5f, -0.5f,  0.5f, // 1
	  0.5f, -0.5f,  0.5f, // 5
	  -0.5f,  0.5f,  0.5f, // 3

	  0.5f, -0.5f,  0.5f, // 5
	  -0.5f,  0.5f,  0.5f, // 3
	  0.5f,  0.5f,  0.5f // 7
	  });
}
