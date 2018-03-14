// ==========================================================================
// $Id: material.h,v 1.3 2014/10/18 14:03:56 jlang Exp $
// Light example for hierachical modeling
// Modified code from solar2.cpp created by Francisco Javier Ovalle Martinez
// inspired by the OpenGL programming guide by Shreiner et al.
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
// Creator: Jochen Lang
// Email:   jlang@site.uottawa.ca
// ==========================================================================
// $Log: material.h,v $
// Revision 1.3  2014/10/18 14:03:56  jlang
// Added extra checks in setLights and switched to radians.
//
// Revision 1.2  2014/03/02 01:56:19  jlang
// Tested on windows with OpenGL 3.3
//
// Revision 1.1  2014/03/01 22:26:07  jlang
// Created lab 6 with material parameters and use of ubo
//
// Revision 1.2  2014/02/22 19:51:39  jlang
// Drawing with indexed materials and 1 light source
//
// Revision 1.1  2014/02/17 18:52:57  jlang
// Draft lab5
//
// Revision 1.1  2011/03/06 03:46:54  jlang
// Created lab 7
//
// Revision 1.2  2011/02/26 22:12:24  jlang
// Completed Lab 6
//
// Revision 1.1  2011/02/26 03:53:14  jlang
// Created skeleton for lighting lab
//
// ==========================================================================
#include <cassert>
#include <sstream>
#include <string>

// gl types
#include <GL/glew.h>
// glm types
#define GLM_FORCE_RADIAN
#include <glm/glm.hpp>


namespace CSI4130 {

struct Material {
  glm::vec4 d_emissive;
  glm::vec4 d_ambient;
  glm::vec4 d_diffuse;
  glm::vec4 d_specular;
  GLfloat d_shininess;

Material() : d_emissive(0.0, 0.0, 0.0, 1.0),
    d_ambient( 0.2f, 0.2f, 0.2f, 1.0f ), 
    d_diffuse( 0.8f, 0.8f, 0.8f, 1.0f ), 
    d_specular( 0.0f, 0.0f, 0.0f, 1.0f ),
    d_shininess( 1.0f ) {}
};
 

class MaterialArray {
  const static int STRIDE = 20; // 5*4

  std::vector<Material> d_materials;
    
public:
  int getSize() {
    return STRIDE * sizeof(float) * d_materials.size();
  }

  Material get( int i ) {
    assert(i < d_materials.size());
    return d_materials[i];
  }

  void set( int _i, const Material& _ls) {
    assert(_i < d_materials.size());
    d_materials[_i] = _ls;
    return;
  }

  void append( const Material& _ls) {
    d_materials.push_back(_ls);
    return;
  }

  void setMaterial( GLuint program, int _m ) {
    assert( _m < d_materials.size());
    GLint locMaterial = -1;
    std::string varName("materials[");
    std::ostringstream os;
    os << varName << _m;
    varName = os.str();
    locMaterial = glGetUniformLocation(program, (varName + "].emissive").c_str());
    glProgramUniform4fv(program, locMaterial, 1, glm::value_ptr(d_materials[_m].d_emissive));
    locMaterial = glGetUniformLocation(program, (varName + "].ambient").c_str());
    glProgramUniform4fv(program, locMaterial, 1, glm::value_ptr(d_materials[_m].d_ambient));
    locMaterial = glGetUniformLocation(program, (varName + "].diffuse").c_str());
    glProgramUniform4fv(program, locMaterial, 1, glm::value_ptr(d_materials[_m].d_diffuse));
    locMaterial = glGetUniformLocation(program, (varName + "].specular").c_str());
    glProgramUniform4fv(program, locMaterial, 1, glm::value_ptr(d_materials[_m].d_specular));
    locMaterial = glGetUniformLocation(program, (varName + "].shininess").c_str());
    glProgramUniform1f(program, locMaterial, d_materials[_m].d_shininess);
    return;
  }

  void setMaterials( GLuint program ) {
    int maxMaterial = d_materials.size();
    for ( int m=0; m<maxMaterial; ++m )  {
      setMaterial(program, m );
    }
    return;
  }


  void setMaterialsUBO( GLuint _ubo ) {
    glBindBuffer(GL_UNIFORM_BUFFER, _ubo);
    // We will send our data one material at a time
    int mId = 0;
    // cerr <<  "Overall size: " << STRIDE * d_materials.size() << endl;
    for ( std::vector<Material>::const_iterator iter = d_materials.begin();
	  iter != d_materials.end(); ++iter )  {
      Material m = *iter;
      // cerr << "Offset: " << mId*STRIDE*sizeof(float) << " Size: " << sizeof(Material) << endl;
      glBufferSubData(GL_UNIFORM_BUFFER, mId*STRIDE*sizeof(float), sizeof(Material), reinterpret_cast<const GLvoid*>(&m) );
      ++mId;
      errorOut();
    }
    // glBindBuffer(GL_UNIFORM_BUFFER, 0);
    return;
  }

};





}; // end namespace
