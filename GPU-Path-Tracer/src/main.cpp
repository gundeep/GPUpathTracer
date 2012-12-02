// CIS565 CUDA Raytracer: A parallel raytracer for Patrick Cozzi's CIS565: GPU Computing at the University of Pennsylvania
// Written by Yining Karl Li, Copyright (c) 2012 University of Pennsylvania
// This file includes code from:
//       Rob Farber for CUDA-GL interop, from CUDA Supercomputing For The Masses: http://www.drdobbs.com/architecture-and-design/cuda-supercomputing-for-the-masses-part/222600097
//       Varun Sampath and Patrick Cozzi for GLSL Loading, from CIS565 Spring 2012 HW5 at the University of Pennsylvania: http://cis565-spring-2012.github.com/
//       Yining Karl Li's TAKUA Render, a massively parallel pathtracing renderer: http://www.yiningkarlli.com

#include "main.h"



//// ALL the Ambient Occlusion Stuff
//GLuint depthTexture = 0;
//GLuint normalTexture = 0;
//GLuint positionTexture = 0;
//GLuint FBO = 0;
//GLuint random_normal_tex;
//GLuint random_scalar_tex;
//
//GLuint ssao_prog;
//  void initSSAO()
//  {
//	Utility::shaders_t shaders = Utility::loadShaders("shaders/ssao.vert", "shaders/ssao.frag");
//    ssao_prog = glCreateProgram();
//	glBindAttribLocation(ssao_prog, quad_attributes::POSITION, "Position");
//	glBindAttribLocation(ssao_prog, quad_attributes::TEXCOORD, "Texcoord");
// 
//	Utility::attachAndLinkProgram(ssao_prog, shaders);
//  }
//
//  device_mesh2_t device_quad;
//void initQuad() {
//	vertex2_t verts [] = { {glm::vec3(-1,1,0),glm::vec2(0,1)},
//	{glm::vec3(-1,-1,0),glm::vec2(0,0)},
//	{glm::vec3(1,-1,0), glm::vec2(1,0)},
//	{glm::vec3(1,1,0),  glm::vec2(1,1)}};
//
//	unsigned short indices[] = { 0,1,2,0,2,3};
//
//	//Allocate vertex array
//	//Vertex arrays encapsulate a set of generic vertex attributes and the buffers they are bound too
//	//Different vertex array per mesh.
//	glGenVertexArrays(1, &(device_quad.vertex_array));
//    glBindVertexArray(device_quad.vertex_array);
//
//    
//	//Allocate vbos for data
//	glGenBuffers(1,&(device_quad.vbo_data));
//	glGenBuffers(1,&(device_quad.vbo_indices));
//    
//	//Upload vertex data
//	glBindBuffer(GL_ARRAY_BUFFER, device_quad.vbo_data);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
//    //Use of strided data, Array of Structures instead of Structures of Arrays
//	glVertexAttribPointer(quad_attributes::POSITION, 3, GL_FLOAT, GL_FALSE,sizeof(vertex2_t),0);
//	glVertexAttribPointer(quad_attributes::TEXCOORD, 2, GL_FLOAT, GL_FALSE,sizeof(vertex2_t),(void*)sizeof(glm::vec3));
//	glEnableVertexAttribArray(quad_attributes::POSITION);
//	glEnableVertexAttribArray(quad_attributes::TEXCOORD);
//
//    //indices
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, device_quad.vbo_indices);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLushort), indices, GL_STATIC_DRAW);
//    device_quad.num_indices = 6;
//	//Unplug Vertex Array
//    glBindVertexArray(0);
//}
//
//  enum Display display_type = DISPLAY_TOTAL;
//  enum Occlusion occlusion_type = OCCLUSION_NONE;
//void draw_quad() {
//
//    glUseProgram(ssao_prog);
//
//	glBindVertexArray(device_quad.vertex_array);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, device_quad.vbo_indices);
//
//    glEnable(GL_TEXTURE_2D);
//
//	glm::mat4 persp = glm::perspective(45.0f,1.0f,FARP,NEARP);
//    glm::vec4 test(-2,0,10,1);
//    glm::vec4 testp = persp * test;
//    glm::vec4 testh = testp / testp.w;
//    glm::vec2 coords = glm::vec2(testh.x, testh.y) / 2.0f + 0.5f;
//    glUniform1i(glGetUniformLocation(ssao_prog, "u_ScreenHeight"), height);
//    glUniform1i(glGetUniformLocation(ssao_prog, "u_ScreenWidth"), width);
//    glUniform1f(glGetUniformLocation(ssao_prog, "u_Far"), FARP);
//    glUniform1f(glGetUniformLocation(ssao_prog, "u_Near"), NEARP);
//    glUniform1i(glGetUniformLocation(ssao_prog, "u_OcclusionType"), occlusion_type);
//    glUniform1i(glGetUniformLocation(ssao_prog, "u_DisplayType"), display_type);
//    glUniformMatrix4fv(glGetUniformLocation(ssao_prog, "u_Persp"),1, GL_FALSE, &persp[0][0] );
//    
//	glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_2D, depthTexture);
//    glUniform1i(glGetUniformLocation(ssao_prog, "u_Depthtex"),0);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, normalTexture);
//    glUniform1i(glGetUniformLocation(ssao_prog, "u_Normaltex"),1);
//    glActiveTexture(GL_TEXTURE2);
//    glBindTexture(GL_TEXTURE_2D, positionTexture);
//    glUniform1i(glGetUniformLocation(ssao_prog, "u_Positiontex"),2);
//    glActiveTexture(GL_TEXTURE3);
//    glBindTexture(GL_TEXTURE_2D, random_normal_tex);
//    glUniform1i(glGetUniformLocation(ssao_prog, "u_RandomNormaltex"),3);
//    glActiveTexture(GL_TEXTURE4);
//    glBindTexture(GL_TEXTURE_2D, random_scalar_tex);
//    glUniform1i(glGetUniformLocation(ssao_prog, "u_RandomScalartex"),4);
//    
//    glDrawElements(GL_TRIANGLES, device_quad.num_indices, GL_UNSIGNED_SHORT,0);
//
//    glBindVertexArray(0);
//}
//int mouse_buttons = 0;
//int mouse_old_x = 0;
//int mouse_old_y = 0;
//void mouse(int button, int state, int x, int y)
//{
//    if (state == GLUT_DOWN) {
//        mouse_buttons |= 1<<button;
//    } else if (state == GLUT_UP) {
//        mouse_buttons = 0;
//    }
// 
//    mouse_old_x = x;
//    mouse_old_y = y;
//}
//Camera cam(glm::vec3(17,0,4),
//		   glm::normalize(glm::vec3(-1,0,0)),
//		   glm::normalize(glm::vec3(0,0,1)));
//
//void motion(int x, int y)
//{
//    float dx, dy;
//    dx = (float)(x - mouse_old_x);
//    dy = (float)(y - mouse_old_y);
// 
//    if (mouse_buttons & 1<<GLUT_RIGHT_BUTTON) {
//		cam.adjust(0,0,dx,0,0,0);;
//    }
//    else {
//        cam.adjust(-dx*0.2f,-dy*0.2f,0,0,0,0);
//    }
// 
//    mouse_old_x = x;
//    mouse_old_y = y;
//}
//void
//Camera::adjust(float dx, // look left right
//      float dy, //look up down
//      float dz,
//      float tx, //strafe left right
//      float ty,
//      float tz)//go forward) //strafe up down
//{
//
//	if (abs(dx) > 0) {
//		rx += dx;
//        rx = fmod(rx,360.0f);
//	}
//
//	if (abs(dy) > 0) {
//        ry += dy;
//        ry = clamp(ry,-70.0f, 70.0f);
//	}
//
//	if (abs(tx) > 0) {
//	//	glm::vec3 dir = glm::rotate_vector::rotate(start_dir,rx + 90,up);
//      //  glm::vec2 dir2(dir.x,dir.y);
//       // glm::vec2 mag = dir2 * tx;
//      //  pos += mag;	
//	}
//
//	if (abs(tz) > 0) {
//		//glm::vec3 dir = glm::gtx::rotate_vector::rotate(start_dir,rx,up);
//       // glm::vec2 dir2(dir.x,dir.y);
//       // glm::vec2 mag = dir2 * tz;
//       // pos += mag;
//	}
//}


//-------------------------------
//-------------MAIN--------------
//-------------------------------

int main(int argc, char** argv){

  #ifdef __APPLE__
	  // Needed in OSX to force use of OpenGL3.2 
	  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	  glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #endif

  // Set up pathtracer stuff
  bool loadedScene = false;
  finishedRender = false;

  targetFrame = 0;
  singleFrameMode = false;

  // Load scene file
  for(int i=1; i<argc; i++){
    string header; string data;
    istringstream liness(argv[i]);
    getline(liness, header, '='); getline(liness, data, '=');
    if(strcmp(header.c_str(), "scene")==0){
      renderScene = new scene(data);
      loadedScene = true;
    }else if(strcmp(header.c_str(), "frame")==0){
      targetFrame = atoi(data.c_str());
      singleFrameMode = true;
    }
	
  }

  if(!loadedScene){
    cout << "Error: scene file needed!" << endl;
    return 0;
  }

  // Set up camera stuff from loaded pathtracer settings
  iterations = 0;
  renderCam = &renderScene->renderCam;
  width = renderCam->resolution[0];
  height = renderCam->resolution[1];

  if(targetFrame>=renderCam->frames){
    cout << "Warning: Specified target frame is out of range, defaulting to frame 0." << endl;
    targetFrame = 0;
  }

  // Launch CUDA/GL

  #ifdef __APPLE__
	init();
  #else
	init(argc, argv);
  #endif

  initCuda();

  initVAO();
  initTextures();
  

  GLuint passthroughProgram;
  passthroughProgram = initShader("shaders/passthroughVS.glsl", "shaders/passthroughFS.glsl");

  glUseProgram(passthroughProgram);
  glActiveTexture(GL_TEXTURE0);

  //initSSAO();
  //initQuad();

  #ifdef __APPLE__
	  // send into GLFW main loop
	  while(1){
		display();
		if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS || !glfwGetWindowParam( GLFW_OPENED )){
				exit(0);
		}
	  }

	  glfwTerminate();
  #else
	  glutDisplayFunc(display);
	  glutKeyboardFunc(keyboard);
	 // glutMouseFunc(mouse);
	  //glutMotionFunc(motion);

	  glutMainLoop();
  #endif
  return 0;
}

//-------------------------------
//---------RUNTIME STUFF---------
//-------------------------------

void runCuda(){

  // Map OpenGL buffer object for writing from CUDA on a single GPU
  // No data is moved (Win & Linux). When mapped to CUDA, OpenGL should not use this buffer
  
  if(iterations<renderCam->iterations){
    uchar4 *dptr=NULL;
    iterations++;
    cudaGLMapBufferObject((void**)&dptr, pbo);  // hmm pbo is program buffer

	//////////////////////////////////////////  
    ///////pack geom and material arrays//////
	//////////////////////////////////////////

    geom* geoms = new geom[renderScene->objects.size()];
	obj* objs= new obj[renderScene->meshes.size()];
    material* materials = new material[renderScene->materials.size()];
    
    for(unsigned int i=0; i<renderScene->objects.size(); i++)
	{
      geoms[i] = renderScene->objects[i];
    }
	for(unsigned int k=0; k<renderScene->meshes.size(); k++)
	{
		
		objs[k]= renderScene->meshes[k];
		//objs[0].faces
		//cout<<"filling objs\n";
	}
    for(unsigned int j=0; j<renderScene->materials.size(); j++){
      materials[j] = renderScene->materials[j];
    }

	/////////////////////////////////////
	////////// Mesh Loading /////////////
	/////////////////////////////////////
	int number_of_faces;
	triangle* tri_faces;
	if (renderScene->meshes.size() >0)
	{
		vbo = renderScene->meshes[0].getVBO();
		vbosize = renderScene->meshes[0].getVBOsize();

		nbo = renderScene->meshes[0].getNBO();
		nbosize= renderScene->meshes[0].getNBOsize();	

		float newcbo[] = {0.0, 1.0, 0.0, 
						0.0, 0.0, 1.0, 
						1.0, 0.0, 0.0};
		cbo = newcbo;
		cbosize = 9;

		ibo = renderScene->meshes[0].getIBO();
		ibosize = renderScene->meshes[0].getIBOsize();

		vector<vector<int>>* temp_faces= renderScene->meshes[0].getFaces();
		//hack
		number_of_faces=ibosize/3;
		tri_faces= new triangle[number_of_faces];

		/*for(int i=0;i<108;i++)
		{
			cout<<vbo[i]<<"   \n";
			if((i+1)%3==0)
			{
				cout<<"\n";
			}
		}*/

		for( int i=0 ; i <number_of_faces ; i++)
		{
			// here P0 has the vertex index of 1 vertex of triangle
			tri_faces[i].p0=glm::vec3(vbo[i*9],vbo[i*9 +1 ],vbo[i*9 +2]);
			tri_faces[i].p1=glm::vec3(vbo[i*9 +3],vbo[i*9 +4],vbo[i*9 +5]);
			tri_faces[i].p2=glm::vec3(vbo[i*9 + 6],vbo[i*9 + 7],vbo[i*9 + 8]);


			tri_faces[i].n0=glm::vec3(nbo[i*9],    nbo[i*9 +1 ],nbo[i*9 +2]);
			tri_faces[i].n1=glm::vec3(nbo[i*9 +3], nbo[i*9 +4], nbo[i*9 +5]);
			tri_faces[i].n2=glm::vec3(nbo[i*9 + 6],nbo[i*9 + 7],nbo[i*9 + 8]);


			////// NOTE This line is hacky, just to save the normal

			tri_faces[i].n0=glm::normalize(tri_faces[i].n0+tri_faces[i].n1+tri_faces[i].n2);


			//tri_faces[i].p0 = glm::vec3(vbo[3*temp_faces[0][i][0]],vbo[3*temp_faces[0][i][0] + 1],vbo[3*(temp_faces[0][i][0]) + 2]);
			//tri_faces[i].p1 = glm::vec3(vbo[3*temp_faces[0][i][1]],vbo[3*temp_faces[0][i][1] + 1],vbo[3*(temp_faces[0][i][1]) + 2]);
			//tri_faces[i].p2 = glm::vec3(vbo[3*temp_faces[0][i][2]],vbo[3*temp_faces[0][i][2] + 1],vbo[3*(temp_faces[0][i][2]) + 2]);
			//cout<"ok";
			//tri_faces[i].p0= vbo[i*tri_faces[i].p0.x, i*tri_faces[i].p0.y,i*tri_faces[i].p0.z];
		}
	
		//vbo[temp_faces[0][0][0]
		/*for( int i=0 ; i <number_of_faces ; i++)
		{
		cout<<tri_faces[i].p0.x<<"	\n";
		cout<<tri_faces[i].p1.x<<"	\n";
		cout<<tri_faces[i].p2.x<<"	\n";
		}*/
	}

    
	// execute the kernel
    cudaRaytraceCore(dptr, renderCam, targetFrame, iterations, materials,
		renderScene->materials.size(), geoms, renderScene->objects.size(),
		vbo,nbo,cbo,vbosize,nbosize,cbosize,objs, renderScene->meshes.size(), number_of_faces, tri_faces,
		ibo,ibosize);
    
    // unmap buffer object
    cudaGLUnmapBufferObject(pbo);
  }else{

    if(!finishedRender){
      //output image file
      image outputImage(renderCam->resolution.x, renderCam->resolution.y);

      for(int x=0; x<renderCam->resolution.x; x++){
        for(int y=0; y<renderCam->resolution.y; y++){
          int index = x + (y * renderCam->resolution.x);
          outputImage.writePixelRGB(x,y,renderCam->image[index]);
        }
      }
      
      gammaSettings gamma;
      gamma.applyGamma = true;
      gamma.gamma = 1.0/2.2;
      gamma.divisor = renderCam->iterations;
      outputImage.setGammaSettings(gamma);
      string filename = renderCam->imageName;
      string s;
      stringstream out;
      out << targetFrame;
      s = out.str();
      utilityCore::replaceString(filename, ".bmp", "."+s+".bmp");
      utilityCore::replaceString(filename, ".png", "."+s+".png");
      outputImage.saveImageRGB(filename);
      cout << "Saved frame " << s << " to " << filename << endl;
      finishedRender = true;
      if(singleFrameMode==true){
        cudaDeviceReset(); 
        exit(0);
      }
    }
    if(targetFrame<renderCam->frames-1){

      //clear image buffer and move onto next frame
      targetFrame++;
      iterations = 0;
      for(int i=0; i<renderCam->resolution.x*renderCam->resolution.y; i++){
        renderCam->image[i] = glm::vec3(0,0,0);
      }
      cudaDeviceReset(); 
      finishedRender = false;
    }
  }
}

#ifdef __APPLE__

	void display(){
		runCuda();

		string title = "CIS565 Render | " + utilityCore::convertIntToString(iterations) + " Frames";
		glfwSetWindowTitle(title.c_str());

		glBindBuffer( GL_PIXEL_UNPACK_BUFFER, pbo);
		glBindTexture(GL_TEXTURE_2D, displayImage);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, 
			  GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glClear(GL_COLOR_BUFFER_BIT);   

		// VAO, shader program, and texture already bound
		glDrawElements(GL_TRIANGLES, 6,  GL_UNSIGNED_SHORT, 0);

		glfwSwapBuffers();
	}

#else

	void display(){
		runCuda();

		string title = "565Raytracer | " + utilityCore::convertIntToString(iterations) + " Frames";
		glutSetWindowTitle(title.c_str());

		glBindBuffer( GL_PIXEL_UNPACK_BUFFER, pbo);
		glBindTexture(GL_TEXTURE_2D, displayImage);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, 
			  GL_RGBA, GL_UNSIGNED_BYTE, NULL);

		glClear(GL_COLOR_BUFFER_BIT);   

		// VAO, shader program, and texture already bound
		glDrawElements(GL_TRIANGLES, 6,  GL_UNSIGNED_SHORT, 0);

		glutPostRedisplay();
		glutSwapBuffers();
	}

	void keyboard(unsigned char key, int x, int y)
	{
		std::cout << key << std::endl;
		switch (key) 
		{
		   case(27):
			   exit(1);
			   break;
			/*
			case('1'):
			  occlusion_type = OCCLUSION_NONE;
			  break;
			case('2'):
			  occlusion_type = OCCLUSION_REGULAR_SAMPLES;
			  break;
			case('6'):
			  display_type = DISPLAY_DEPTH;
			  break;
			case('7'):
			  display_type = DISPLAY_NORMAL;
			  break;
			case('8'):
			  display_type = DISPLAY_POSITION;
			  break;
			case('9'):
			  display_type = DISPLAY_OCCLUSION;
			  break;
			case('0'):
			  display_type = DISPLAY_TOTAL;
			  break;
			}*/
	}
}
	

#endif




//-------------------------------
//----------SETUP STUFF----------
//-------------------------------

#ifdef __APPLE__
	void init(){

		if (glfwInit() != GL_TRUE){
			shut_down(1);      
		}

		// 16 bit color, no depth, alpha or stencil buffers, windowed
		if (glfwOpenWindow(width, height, 5, 6, 5, 0, 0, 0, GLFW_WINDOW) != GL_TRUE){
			shut_down(1);
		}

		// Set up vertex array object, texture stuff
		initVAO();
		initTextures();
	}
#else
	void init(int argc, char* argv[]){
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowSize(width, height);
		glutCreateWindow("565Raytracer");

		// Init GLEW
		glewInit();
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			/* Problem: glewInit failed, something is seriously wrong. */
			std::cout << "glewInit failed, aborting." << std::endl;
			exit (1);
		}

		initVAO();
		initTextures();
	}
#endif

void initPBO(GLuint* pbo){
  if (pbo) {
    // set up vertex data parameter
    int num_texels = width*height;
    int num_values = num_texels * 4;
    int size_tex_data = sizeof(GLubyte) * num_values;
    
    // Generate a buffer ID called a PBO (Pixel Buffer Object)
    glGenBuffers(1,pbo);
    // Make this the current UNPACK buffer (OpenGL is state-based)
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, *pbo);
    // Allocate data for the buffer. 4-channel 8-bit image
    glBufferData(GL_PIXEL_UNPACK_BUFFER, size_tex_data, NULL, GL_DYNAMIC_COPY);
    cudaGLRegisterBufferObject( *pbo );
  }
}

void initCuda(){
  // Use device with highest Gflops/s
  cudaGLSetGLDevice( cutGetMaxGflopsDeviceId() );

  initPBO(&pbo);

  // Clean up on program exit
  atexit(cleanupCuda);

  runCuda();
}

void initTextures(){
    glGenTextures(1,&displayImage);
    glBindTexture(GL_TEXTURE_2D, displayImage);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_BGRA,
        GL_UNSIGNED_BYTE, NULL);
}

void initVAO(void){
    GLfloat vertices[] =
    { 
        -1.0f, -1.0f, 
         1.0f, -1.0f, 
         1.0f,  1.0f, 
        -1.0f,  1.0f, 
    };

    GLfloat texcoords[] = 
    { 
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
    };

    GLushort indices[] = { 0, 1, 3, 3, 1, 2 };

    GLuint vertexBufferObjID[3];
    glGenBuffers(3, vertexBufferObjID);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)positionLocation, 2, GL_FLOAT, GL_FALSE, 0, 0); 
    glEnableVertexAttribArray(positionLocation);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjID[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)texcoordsLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(texcoordsLocation);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferObjID[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

GLuint initShader(const char *vertexShaderPath, const char *fragmentShaderPath){
    GLuint program = glslUtility::createProgram(vertexShaderPath, fragmentShaderPath, attributeLocations, 2);
    GLint location;

    glUseProgram(program);
    
    if ((location = glGetUniformLocation(program, "u_image")) != -1)
    {
        glUniform1i(location, 0);
    }

    return program;
}

//-------------------------------
//---------CLEANUP STUFF---------
//-------------------------------

void cleanupCuda(){
  if(pbo) deletePBO(&pbo);
  if(displayImage) deleteTexture(&displayImage);
}

void deletePBO(GLuint* pbo){
  if (pbo) {
    // unregister this buffer object with CUDA
    cudaGLUnregisterBufferObject(*pbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, *pbo);
    glDeleteBuffers(1, pbo);
    
    *pbo = (GLuint)NULL;
  }
}

void deleteTexture(GLuint* tex){
    glDeleteTextures(1, tex);
    *tex = (GLuint)NULL;
}
 
void shut_down(int return_code){
  #ifdef __APPLE__
	glfwTerminate();
  #endif
  exit(return_code);
}
