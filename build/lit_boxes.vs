// ==========================================================================
// $Id: lit_boxes.vs,v 1.2 2014/10/18 14:13:56 jlang Exp $
// Draw boxes with instancing
// ==========================================================================
// (C)opyright:
//
//   Jochen Lang
//   EECS, University of Ottawa
//   800 King Edward Ave.
//   Ottawa, On., K1N 6N5
//   Canada.
//   http://www.site.uottawa.ca
//
// Creator: jlang (Jochen Lang)
// Email:   jlang@site.uottawa.ca
// ==========================================================================
// $Log: lit_boxes.vs,v $
// Revision 1.2  2014/10/18 14:13:56  jlang
// Added core. Runs with OpenGL 3.3 but material block arrays need 4.0 to work correctly.
//
// Revision 1.1  2014/03/01 22:26:07  jlang
// Created lab 6 with material parameters and use of ubo
//
// Revision 1.3  2014/02/23 02:18:41  jlang
// Make sure material index is flat.
//
// Revision 1.2  2014/02/22 19:51:39  jlang
// Drawing with indexed materials and 1 light source
//
// Revision 1.1  2014/02/17 18:52:57  jlang
// Draft lab5
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
// ==========================================================================
#version 330 core

layout (location=0) in vec4 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec4 color;

layout (location = 3) in mat4 ModelMatrix;	

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

uniform vec4 lightPosition[2];

out vec4 colorVertFrag; // Pass the color on to rasterization
out vec3 normalFrag; // Pass the normal to rasterization
out vec3 eyeFrag; // Pass an eye vector along
out vec3 lightFrag; // Pass a light vector along


void main() {

  // map the vertex position into clipping space 
  mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
  // postion in camera coordinates
  vec4 posVec = ModelViewMatrix * position;
  eyeFrag = -posVec.xyz;  

  // light vector in camera coordinates
  // Check for directional lighting	
  if ( lightPosition[0].w > 0.0 ) {
    lightFrag = lightPosition[0].xyz - posVec.xyz;
  } else {
    lightFrag = lightPosition[0].xyz;
  }

  // assume Modelview matrix has no non-uniform scaling or shearing 
  normalFrag = mat3(ModelViewMatrix) * normal;

  gl_Position = ProjectionMatrix * posVec;

  colorVertFrag = color;
}
