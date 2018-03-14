// ==========================================================================
// $Id: lit_boxes.fs,v 1.4 2016/03/12 03:34:41 jlang Exp $
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
// $Log: lit_boxes.fs,v $
// Revision 1.4  2016/03/12 03:34:41  jlang
// Fixed spot light
//
// Revision 1.3  2014/10/24 21:45:40  jlang
// Added error checking to guard against optimezed out uniforms and attributes
//
// Revision 1.2  2014/10/18 14:13:56  jlang
// Added core. Runs with OpenGL 3.3 but material block arrays need 4.0 to work correctly.
//
// Revision 1.1  2014/03/01 22:26:07  jlang
// Created lab 6 with material parameters and use of ubo
//
// Revision 1.1  2014/02/24 16:45:59  jlang
// Lab 5 post
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
// Revision 1.1  2014/02/03 03:38:45  jlang
// Draft lab check in
//
// ==========================================================================
#version 400 core

in vec4 colorVertFrag; 
in vec3 normalFrag; 
in vec3 eyeFrag; 
in vec3 lightFrag; 

out vec4 color;

struct LightSource {
  vec4 ambient;  
  vec4 diffuse;
  vec4 specular;
  // spot light
  // v is the vector to the vertex
  // if dir*v < cos(cutoff) then (dir * v)^N 
  vec3 spot_direction;
  float spot_exponent;
  float spot_cutoff;
  // attentuation 1/(k_c + k_l r + k_q r^2) 
  // r is the distance of a vertex from the light source
  float constant_attenuation;
  float linear_attenuation;
  float quadratic_attenuation;
};
 
uniform LightSource lights[2];

struct Material {
  vec4 emissive;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};

layout (std140) uniform MaterialBlock {
  uniform Material materials[4];	       
};


void main() {
  vec3 NVec = normalize(normalFrag);
  vec3 LVec = normalize(lightFrag);
  vec3 EVec = normalize(eyeFrag);

  float distanceLight = length(lightFrag.xyz);

  float attenuation = 1.0 / 
    (lights[0].constant_attenuation +
     lights[0].linear_attenuation * distanceLight +
     lights[0].quadratic_attenuation * distanceLight * distanceLight);

  // ambient term
  vec4 ambient =  colorVertFrag * lights[0].ambient;

  // diffuse term
  float dotNL = max(0.0,dot(NVec,LVec));
  vec4 diffuse = colorVertFrag * lights[0].diffuse * dotNL;

  // spot light
  float spot_attenuation = 1.0;
  float dotSV = dot(-LVec,normalize(lights[0].spot_direction));
  if ( dotSV < cos(radians(lights[0].spot_cutoff))) {
    spot_attenuation = 0.0;
  } else {
    spot_attenuation = pow(dotSV,lights[0].spot_exponent);
  }

  // color
  color = ambient + 
  	 attenuation * spot_attenuation * diffuse;
}
