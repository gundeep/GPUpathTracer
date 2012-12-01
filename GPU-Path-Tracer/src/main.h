// CIS565 CUDA Raytracer: A parallel raytracer for Patrick Cozzi's CIS565: GPU Computing at the University of Pennsylvania
// Written by Yining Karl Li, Copyright (c) 2012 University of Pennsylvania
// This file includes code from:
//       Rob Farber for CUDA-GL interop, from CUDA Supercomputing For The Masses: http://www.drdobbs.com/architecture-and-design/cuda-supercomputing-for-the-masses-part/222600097
//       Varun Sampath and Patrick Cozzi for GLSL Loading, from CIS565 Spring 2012 HW5 at the University of Pennsylvania: http://cis565-spring-2012.github.com/
//       Yining Karl Li's TAKUA Render, a massively parallel pathtracing renderer: http://www.yiningkarlli.com

#ifndef MAIN_H
#define MAIN_H

#ifdef __APPLE__
	#include <GL/glfw.h>
#else
	#include <GL/glew.h>
	#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <cuda_runtime.h>
#include <cutil_inline.h>
#include <cutil_gl_inline.h>
#include <cuda_gl_interop.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "glslUtility.h"
#include "sceneStructs.h"
#include "glm/glm.hpp"
#include "image.h"
#include "raytraceKernel.h"
#include "utilities.h"
#include "scene.h"
#include "obj.h"
#include "objloader.h"

//#include "Utility_AO.h"



using namespace std;
//-------------------------------
//----------Ambient Occlusion Stuff-----------
//-------------------------------

//float FARP = 1000.0f;
//float	NEARP = 1.0f;
//namespace quad_attributes {
//	enum {
//		POSITION,
//		TEXCOORD
//	};
//}
//
//typedef struct {
//	unsigned int vertex_array;
//	unsigned int vbo_indices;
//	unsigned int num_indices;
//	//Don't need these to get it working, but needed for deallocation
//	unsigned int vbo_data;
//} device_mesh2_t;
//
//
//typedef struct {
//	glm::vec3 pt;
//	glm::vec2 texcoord;
//} vertex2_t;
//
//enum Display {
//	DISPLAY_DEPTH = 0,
//	DISPLAY_NORMAL = 1,
//	DISPLAY_POSITION = 2,
//	DISPLAY_OCCLUSION = 3,
//	DISPLAY_TOTAL = 4
//}	;
//
//enum Occlusion {
//	OCCLUSION_NONE = 0,
//	OCCLUSION_REGULAR_SAMPLES = 1,
//	OCCLUSION_POISSON_SS_SAMPLES = 2,
//	OCCLUSION_WORLD_SPACE_SAMPLES = 3
//};


//-------------------------------
//----------Mesh/Obj Loader-----------
//-------------------------------

obj *mesh;
float* vbo;
float* nbo;
int nbosize;
int vbosize;
float* cbo;
int cbosize;
int* ibo;
int ibosize;


//-------------------------------
//----------PATHTRACER-----------
//-------------------------------

scene* renderScene;
camera* renderCam;
int targetFrame;
int iterations;
bool finishedRender;
bool singleFrameMode;

//-------------------------------
//------------GL STUFF-----------
//-------------------------------

GLuint positionLocation = 0;
GLuint texcoordsLocation = 1;
const char *attributeLocations[] = { "Position", "Tex" };
GLuint pbo = (GLuint)NULL;
GLuint displayImage;

//-------------------------------
//----------CUDA STUFF-----------
//-------------------------------

int width=800; int height=800;

//-------------------------------
//-------------MAIN--------------
//-------------------------------

int main(int argc, char** argv);

//-------------------------------
//---------RUNTIME STUFF---------
//-------------------------------

void runCuda();

#ifdef __APPLE__
	void display();
#else
	void display();
	void keyboard(unsigned char key, int x, int y);
#endif

//-------------------------------
//----------SETUP STUFF----------
//-------------------------------

#ifdef __APPLE__
	void init();
#else
	void init(int argc, char* argv[]);
#endif

void initPBO(GLuint* pbo);
void initCuda();
void initTextures();
void initVAO();
GLuint initShader(const char *vertexShaderPath, const char *fragmentShaderPath);

//-------------------------------
//---------CLEANUP STUFF---------
//-------------------------------

void cleanupCuda();
void deletePBO(GLuint* pbo);
void deleteTexture(GLuint* tex);
void shut_down(int return_code);

#endif