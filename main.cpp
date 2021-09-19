﻿#define STB_IMAGE_IMPLEMENTATION
//Shao commented, above line is compulsory
#include <stdio.h>
#include <string.h>
#include <cmath>//Shao commented, not compulsory
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
//#include "CommonValues.h"//Shao commented, not compulsory
#include "Window.h"//Window.h is under reviewing
#include "Mesh.h"//Mesh.h is under reviewing
#include "Shader.h"//Shader.h under reviewing
#include "Camera.h"//Camere.h under reviewing
#include "Texture.h"//Texture.h under reviewing
//#include "DirectionalLight.h"//This line is not compulsory 

#include "Material.h"//Waited to be review

#include "Model.h"//Waited to be review

#include "Skybox.h"//Waited to be review

const float toRadians = 3.14159265f / 180.0f;

GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
uniformSpecularIntensity = 0, uniformShininess = 0,
uniformDirectionalLightTransform = 0, uniformOmniLightPos = 0, uniformFarPlane = 0;//Need to be changed

Window mainWindow;
//std::vector<Mesh*> meshList;//Shao removed for making the sphere to be transperant

std::vector<Shader> shaderList;
Shader directionalShadowShader;//Wait to being removed
Shader omniShadowShader;//Wait to being removed

Camera camera;

Material shinyMaterial;
Material dullMaterial;

Model piper_pa18;
Model propeller;

Model Finger02;
Model Finger03;
Model Finger04;
Model Finger05;
Model Finger06;
Model Finger07;
Model Finger08;
Model Finger09;
Model Finger10;
Model Finger11;
Model Finger12;
Model Finger13;
Model Finger14;
Model Finger15;
Model Finger16;
Model Palm;//Shao added

DirectionalLight mainLight;//This line is not compulsory, but affects some below code
PointLight pointLights[MAX_POINT_LIGHTS];//This line is not compulsory but affects some below code
SpotLight spotLights[MAX_SPOT_LIGHTS];//This line is not compulsory but affects some below code

Skybox skybox;

unsigned int pointLightCount = 0;//This line is not compulsory but affects some below code
unsigned int spotLightCount = 0;//This line is not compulsory but affects some below code

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
//GLunit skyboxLocation;//How to solve this redline?

//float z;
glm::vec3 rotation(0.f);
//MyCamera;

// Vertex Shader
//static const char* vShader = "Shaders/shader-yuzhou.vert";
static const char* vShader = "Shaders/shader.vert";
// Fragment Shader
static const char* fShader = "Shaders/shader-test.frag";

//void processInput(GLFWwindow* window) {//Input control
//	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
//		rotation.x= rotation.x + 1;//+=
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, true);
//	}
//}//Control K+X

//void processInput() {//Input control
//	if(GLFW_KEY_UP) {
//		rotation.x = rotation.x + 10;//+=
//	}
//	if (GLFW_KEY_DOWN) {
//		rotation.x = rotation.x - 10;//+=
//	}
//	if (GLFW_KEY_LEFT) {
//		rotation.y = rotation.y + 10;//+=
//	}
//	if (GLFW_KEY_RIGHT) {
//		rotation.y = rotation.y - 10;//+=
//	}
//	//if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//	//	glfwSetWindowShouldClose(window, true);
//	//}
//}

void CreateShaders()
{

	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	directionalShadowShader.CreateFromFiles("Shaders/directional_shadow_map.vert", "Shaders/directional_shadow_map.frag");
	omniShadowShader.CreateFromFiles("Shaders/omni_shadow_map.vert", "Shaders/omni_shadow_map.geom", "Shaders/omni_shadow_map.frag");
	//Above two lines are not compulsory, but if they are removed, it shows small error.
}

void RenderScene()
{
	//glm::mat4 model(1.0f);//Removed 1.0f, no differences
	//Shao edited 02 this Chunk of code for loading the airplane.
	glm::mat4 model01;//model1 for the plane
	glm::mat4 model02;//model2 for the propeller
	glm::mat4 model03;
	glm::mat4 model04;
	glm::mat4 model05;
	glm::mat4 model06;
	glm::mat4 model07;
	glm::mat4 model08;
	glm::mat4 model09;
	glm::mat4 model10;
	glm::mat4 model11;
	glm::mat4 model12;
	glm::mat4 model13;
	glm::mat4 model14;
	glm::mat4 model15;
	glm::mat4 model16;
	//glm::vec3 rotation(0.f);//Refereicing from Youtube
	/*//Init Matrices, Shao referenced from https://youtu.be/uX3Iil0F51U
	glm::vec3 position(0.f);
	glm::vec3 rotation(0.f);
	glm::vec3 scale(1.f);
	//Added up to here, it makes no difference*/

	float angle = (float)glfwGetTime() * glm::radians(5.0f);
	float angle1 = 0.0f;
	if (angle > 60.0f * toRadians)
	{
		angle1 = (float)glfwGetTime()  * glm::radians(1.0f);
		if (angle1 > 60.0f * toRadians) {
			angle1 = 60.0f * toRadians;
		}
	}
	if (angle >= 70.0f * toRadians)
	{
		angle = 70.0f * toRadians;
	}
	
	

	//Shao removed this chunk of airplane code for making keyboard controling 
	model01 = glm::mat4(1.0f);
	model01 = glm::translate(model01, glm::vec3(0.0f, -2.0f, -4.0f));//The position of the airplane
	//model = glm::translate(model, glm::vec3(x, y, z));
	//model = glm::translate(model, glm::vec3(triOffset, 0.0f, -2.5f));//Added from Udemy-Projection
	
	model01 = glm::rotate(model01, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));//Shao edited for keyboard controlling rotation
	model01 = glm::rotate(model01, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));//Shao edited for keyboard controlling rotation
	model01 = glm::rotate(model01, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));//Shao edited for keyboard controlling rotation

	//rotation.x++;
	model01 = glm::rotate(model01, -90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));//Shao once removed static rotation
	model01 = glm::scale(model01, glm::vec3(1.0f, 0.2f, 1.0f));

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model01));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	Palm.RenderModel();


	//Loading the Finger Segments
	model02 = glm::mat4(1.0f);
	model02 = model02 * model01;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position
	model02 = glm::translate(model02, glm::vec3(-2.8f, 0.0f, 1.8f));
	model02 = glm::rotate(model02, 90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	model02 = glm::rotate(model02, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model02 = glm::rotate(model02, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	//model02 = glm::rotate(model02, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));//Shao edited
	
	model02 = glm::scale(model02, glm::vec3(.01f, .04f, .003f));//Previously was 0.006, so invisible
	//model02 = glm::rotate(model02, angle, glm::vec3(-1.0f, 0.0f, 0.0f));//rotating
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model02));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger02.RenderModel();
/*
	float angle2 = 0.0f;
	if (angle > 60.0f * toRadians)
	{
		angle2 = (float)glfwGetTime() * glm::radians(5.0f);
		if (angle2 > 40.0f * toRadians) {
			angle2 = 40.0f * toRadians;
		}
	}
*/
	model03 = glm::mat4(1.0f);
	model03 = model03 * model02;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position
	model03 = glm::translate(model03, glm::vec3(-2.8f, 0.0f, 100.0f));
	
	model03 = glm::rotate(model03, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	//model03 = glm::rotate(model03, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model03 = glm::rotate(model03, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model03));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger03.RenderModel();


	
	model04 = glm::mat4(1.0f);
	model04 = model04 * model03;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position
	
	model04 = glm::translate(model04, glm::vec3(-2.8f, 0.0f, 300.0f));
	
	model04 = glm::rotate(model04, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	model04 = glm::rotate(model04, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model04 = glm::rotate(model04, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model04));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger04.RenderModel();

	//*****************************************Little Finger Done Above************************************************************

	//Loading the Finger Segments
	model05 = glm::mat4(1.0f);
	model05 = model05 * model01;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position
	model05 = glm::translate(model05, glm::vec3(-2.8f, 0.0f, 0.6f));
	model05 = glm::rotate(model05, 90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	model05 = glm::rotate(model05, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model05 = glm::rotate(model05, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	//model05 = glm::rotate(model05, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));//Shao edited
	model05 = glm::scale(model05, glm::vec3(.01f, .05f, .003f));//Previously was 0.006, so invisible
	//model05 = glm::scale(model05, glm::vec3(1.01f, 0.02f, 1.003f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model05));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger05.RenderModel();


	//Loading the Finger Segments
	model07 = glm::mat4(1.0f);
	model07 = model07 * model05;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position
	model07 = glm::translate(model07, glm::vec3(-2.8f, 0.0f, -300.6f));
	model07 = glm::rotate(model07, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	model07 = glm::rotate(model07, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model07 = glm::rotate(model07, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	//model05 = glm::rotate(model05, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));//Shao edited
	//model07 = glm::rotate(model07, angle, glm::vec3(0.0f, 1.0f, 0.0f));//Shao edited
	model07 = glm::scale(model07, glm::vec3(1.0f, 1.0f, 1.0f));//Previously was 0.006, so invisible
	//model05 = glm::scale(model05, glm::vec3(1.01f, 0.02f, 1.003f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model07));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger07.RenderModel();

	//Loading the Finger Segments
	model06 = glm::mat4(1.0f);
	model06 = model06 * model05;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position
	model06 = glm::translate(model06, glm::vec3(-2.8f, 0.0f, -300.6f));
	model06 = glm::rotate(model06, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	//model06 = glm::rotate(model06, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model06 = glm::rotate(model06, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	//model05 = glm::rotate(model05, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));//Shao edited
	//model06 = glm::rotate(model06, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	model06 = glm::scale(model06, glm::vec3(1.0f, 1.0f, 1.0f));//Previously was 0.006, so invisible
	//model05 = glm::scale(model05, glm::vec3(1.01f, 0.02f, 1.003f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model06));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger06.RenderModel();
	
	//*****************************************Ring Finger Done Above************************************************************
	//Loading the Finger Segments
	model08 = glm::mat4(1.0f);
	model08 = model08 * model01;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position
	model08 = glm::translate(model08, glm::vec3(-2.8f, 0.0f, -.6f));
	model08 = glm::rotate(model08, 90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	model08 = glm::rotate(model08, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model08 = glm::rotate(model08, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	//model02 = glm::rotate(model02, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));//Shao edited
	model08 = glm::scale(model08, glm::vec3(.01f, .04f, .003f));//Previously was 0.006, so invisible
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model08));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger08.RenderModel();

	model09 = glm::mat4(1.0f);
	model09 = model09 * model08;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position
	model09 = glm::translate(model09, glm::vec3(-2.8f, 0.0f, 100.0f));
	model09 = glm::scale(model09, glm::vec3(1.0f, 1.0f, 1.0f));//Previously was 0.006, so invisible
	model09 = glm::rotate(model09, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	//model03 = glm::rotate(model03, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model09 = glm::rotate(model09, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	//model03 = glm::rotate(model03, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));//Shao edited

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model09));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger09.RenderModel();


	model10 = glm::mat4(1.0f);
	model10 = model10 * model09;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position

	model10 = glm::translate(model10, glm::vec3(-2.8f, 0.0f, 300.0f));
	model10 = glm::rotate(model10, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	model10 = glm::rotate(model10, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model10 = glm::rotate(model10, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model10 = glm::scale(model10, glm::vec3(1.0f, 1.0f, 1.0f));//Previously was 0.006, so invisible
	//model04 = glm::rotate(model04, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));//Shao edited

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model10));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger10.RenderModel();

	//*******************************************Middle Finger Done Above*****************************************************

	model11 = glm::mat4(1.0f);
	model11 = model11 * model01;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position
	model11 = glm::translate(model11, glm::vec3(-2.8f, 0.0f, -1.8f));
	model11 = glm::rotate(model11, 90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	model11 = glm::rotate(model11, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model11 = glm::rotate(model11, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	//model02 = glm::rotate(model02, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));//Shao edited
	model11 = glm::scale(model11, glm::vec3(.01f, .04f, .003f));//Previously was 0.006, so invisible
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model11));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger11.RenderModel();

	model12 = glm::mat4(1.0f);
	model12 = model12 * model11;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position
	model12 = glm::translate(model12, glm::vec3(-2.8f, 0.0f, 100.0f));
	model12 = glm::scale(model12, glm::vec3(1.0f, 1.0f, 1.0f));//Previously was 0.006, so invisible
	model12 = glm::rotate(model12, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	//model03 = glm::rotate(model03, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model12 = glm::rotate(model12, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	//model03 = glm::rotate(model03, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));//Shao edited

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model12));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger12.RenderModel();


	model13 = glm::mat4(1.0f);
	model13 = model13 * model12;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position

	model13 = glm::translate(model13, glm::vec3(-2.8f, 0.0f, 300.0f));
	model13 = glm::rotate(model13, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	model13 = glm::rotate(model13, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model13 = glm::rotate(model13, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model13 = glm::scale(model13, glm::vec3(1.0f, 1.0f, 1.0f));//Previously was 0.006, so invisible
	//model04 = glm::rotate(model04, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));//Shao edited

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model13));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger13.RenderModel();

	//*****************************************Index Finger Done Above***********************************************************

	model14 = glm::mat4(1.0f);
	model14 = model14 * model01;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position
	model14 = glm::translate(model14, glm::vec3(0.2f, 0.1f, -3.4f));
	model14 = glm::rotate(model14, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	//model14 = glm::rotate(model14, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	//model14 = glm::rotate(model14, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	//model02 = glm::rotate(model02, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));//Shao edited
	model14 = glm::scale(model14, glm::vec3(.01f, .04f, .003f));//Previously was 0.006, so invisible
	model14 = glm::rotate(model14, angle, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model14));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger14.RenderModel();

	
	model15 = glm::mat4(1.0f);
	model15 = model15 * model14;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position
	model15 = glm::translate(model15, glm::vec3(-2.8f, 0.0f, 100.0f));
	
	model15 = glm::rotate(model15, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	//model03 = glm::rotate(model03, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model15 = glm::rotate(model15, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model15 = glm::scale(model15, glm::vec3(.2f, 1.0f, 2.0f));//Previously was 0.006, so invisible
	//model15 = glm::rotate(model15, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));//Shao edited
	model15 = glm::rotate(model15, angle1, glm::vec3(0.0f, -1.0f, 0.0f));

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model15));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger15.RenderModel();

	/*
	model16 = glm::mat4(1.0f);
	model16 = model16 * model15;
	//glm::mat4(1.0f) = glm::mat4(1.0f) * model;
	//model2 = glm::translate(model2, glm::vec3(0.0f, -1.0f, -7.56f));//Original position
	model16 = glm::translate(model16, glm::vec3(-2.8f, 0.0f, 200.0f));

	model16 = glm::rotate(model16, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));//Rotate the 3D position of the propeller
	//model03 = glm::rotate(model03, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
	model16 = glm::rotate(model16, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
	model16 = glm::scale(model16, glm::vec3(1.0f, 1.0f, 1.0f));//Previously was 0.006, so invisible
	//model03 = glm::rotate(model03, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));//Shao edited

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model16));
	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	//propeller.RenderModel();
	Finger16.RenderModel();
	*/
	
}

//If directionalShadowMapPass is removed, it shows black screen, since it involves into shaders.
void DirectionalShadowMapPass(DirectionalLight* light)
{
	directionalShadowShader.UseShader();

	glViewport(0, 0, light->getShadowMap()->GetShadowWidth(), light->getShadowMap()->GetShadowHeight());

	light->getShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	uniformModel = directionalShadowShader.GetModelLocation();
	directionalShadowShader.SetDirectionalLightTransform(&light->CalculateLightTransform());

	directionalShadowShader.Validate();

	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//Above function need to be removed, I skip it first.
void OmniShadowMapPass(PointLight* light)
{
	omniShadowShader.UseShader();

	glViewport(0, 0, light->getShadowMap()->GetShadowWidth(), light->getShadowMap()->GetShadowHeight());

	light->getShadowMap()->Write();
	glClear(GL_DEPTH_BUFFER_BIT);

	uniformModel = omniShadowShader.GetModelLocation();
	uniformOmniLightPos = omniShadowShader.GetOmniLightPosLocation();
	uniformFarPlane = omniShadowShader.GetFarPlaneLocation();

	glUniform3f(uniformOmniLightPos, light->GetPosition().x, light->GetPosition().y, light->GetPosition().z);
	glUniform1f(uniformFarPlane, light->GetFarPlane());
	omniShadowShader.SetLightMatrices(light->CalculateLightTransform());

	omniShadowShader.Validate();

	RenderScene();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//Above function need to be removed, I skip it first.
void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	glViewport(0, 0, 1366, 768);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox.DrawSkybox(viewMatrix, projectionMatrix);

	shaderList[0].UseShader();

	uniformModel = shaderList[0].GetModelLocation();
	uniformProjection = shaderList[0].GetProjectionLocation();
	uniformView = shaderList[0].GetViewLocation();
	uniformModel = shaderList[0].GetModelLocation();
	uniformEyePosition = shaderList[0].GetEyePositionLocation();
	uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
	uniformShininess = shaderList[0].GetShininessLocation();

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

	//This chunk of the code is not compulsory for working on airplane
	shaderList[0].SetDirectionalLight(&mainLight);
	shaderList[0].SetPointLights(pointLights, pointLightCount, 3, 0);
	shaderList[0].SetSpotLights(spotLights, spotLightCount, 3 + pointLightCount, pointLightCount);
	shaderList[0].SetDirectionalLightTransform(&mainLight.CalculateLightTransform());

	mainLight.getShadowMap()->Read(GL_TEXTURE2);
	shaderList[0].SetTexture(1);
	shaderList[0].SetDirectionalShadowMap(2);

	glm::vec3 lowerLight = camera.getCameraPosition();
	lowerLight.y -= 0.3f;
	spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

	shaderList[0].Validate();

	RenderScene();
}

//void update(GLFWWindow* window, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)


int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	//CreateObjects();
	CreateShaders();
	//-45.0f is the camera perspective angle
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 0.5f, 0.5f);
	//Origially, the last 3 parameters are 0.0f, 5.0f, 0.5f  ,Parameters above reduce the sensitivity for controlling
//camera = Camera(glm::vec3(0.0f, -2.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 1.5f, 0.1f);
//Above line of the code is for testing the camera position matching with the airplane's position.                                           

	shinyMaterial = Material(4.0f, 256);
	dullMaterial = Material(0.3f, 4);

	//Shao edited 03 this Chunk of code for loading the airplane.
	//piper_pa18 = Model();//Shao eidted 03 for loading sphere.
	//piper_pa18.LoadModel("Models/Box/box.obj");

	Palm = Model();
	Palm.LoadModel("Models/Box/box.obj");

	propeller = Model();//Shao eidted 03 for loading sphere.
	propeller.LoadModel("Models/Pelican_Propeller/propeller.obj");

	Finger02 = Model();
	Finger02.LoadModel("Models/Arm/Arm02.obj");
	Finger03 = Model();
	Finger03.LoadModel("Models/Arm/Arm03.obj");
	Finger04 = Model();
	Finger04.LoadModel("Models/Arm/Arm04.obj");
	Finger05 = Model();
	Finger05.LoadModel("Models/Arm/Arm05.obj");
	Finger06 = Model();
	Finger06.LoadModel("Models/Arm/Arm06.obj");
	Finger07 = Model();
	Finger07.LoadModel("Models/Arm/Arm07.obj");
	Finger08 = Model();
	Finger08.LoadModel("Models/Arm/Arm08.obj");
	Finger09 = Model();
	Finger09.LoadModel("Models/Arm/Arm09.obj");
	Finger10 = Model();
	Finger10.LoadModel("Models/Arm/Arm10.obj");
	Finger11 = Model();
	Finger11.LoadModel("Models/Arm/Arm11.obj");
	Finger12 = Model();
	Finger12.LoadModel("Models/Arm/Arm12.obj");
	Finger13 = Model();
	Finger13.LoadModel("Models/Arm/Arm13.obj");
	Finger14 = Model();
	Finger14.LoadModel("Models/Arm/Arm14.obj");
	Finger15 = Model();
	Finger15.LoadModel("Models/Arm/Arm15.obj");
	Finger16 = Model();
	Finger16.LoadModel("Models/Arm/Arm16.obj");

	mainLight = DirectionalLight(2048, 2048,
		1.0f, 0.53f, 0.3f,
		0.1f, 0.9f,
		-10.0f, -12.0f, 18.5f);

	pointLights[0] = PointLight(1024, 1024,
		0.01f, 100.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 2.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;
	pointLights[1] = PointLight(1024, 1024,
		0.01f, 100.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f,
		-4.0f, 3.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;


	spotLights[0] = SpotLight(1024, 1024,
		0.01f, 100.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;
	spotLights[1] = SpotLight(1024, 1024,
		0.01f, 100.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, -1.5f, 0.0f,
		-100.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);
	//Helped from Zhang Shijun

	//
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime(); // SDL_GetPerformanceCounter();
		deltaTime = now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
		lastTime = now;

		// Get + Handle User Input
		glfwPollEvents();

		//Zhang Shijun
		//processInput();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);//Original code
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		if (mainWindow.getsKeys()[GLFW_KEY_UP])
		{
			rotation.x += 0.5;
		}

		if (mainWindow.getsKeys()[GLFW_KEY_DOWN]) {
			rotation.x -= 0.5;//+=
		}
		if (mainWindow.getsKeys()[GLFW_KEY_LEFT]) {
			rotation.y += 0.5;//+=
		}
		if (mainWindow.getsKeys()[GLFW_KEY_RIGHT]) {
			rotation.y -= 0.5;//+=
		}
		if (mainWindow.getsKeys()[GLFW_KEY_U]) {
			rotation.z += 0.5;//+=
		}
		if (mainWindow.getsKeys()[GLFW_KEY_O]) {
			rotation.z -= 0.5;//+=
		}

		if (mainWindow.getsKeys()[GLFW_KEY_L])
		{
			spotLights[0].Toggle();
			mainWindow.getsKeys()[GLFW_KEY_L] = false;
		}
		//updateInput(window, position, rotation, scale);//Shao edited for taking keyboard control of the air plane

		//If this loop is removed, it shows black screen
		DirectionalShadowMapPass(&mainLight);
		for (size_t i = 0; i < pointLightCount; i++)
		{
			OmniShadowMapPass(&pointLights[i]);//Shao reomved for turning off the spot light,remove this line or not, no difference, flashligh is depended line 458.
		}
		for (size_t i = 0; i < spotLightCount; i++)
		{
			OmniShadowMapPass(&spotLights[i]);//Shao reomved for turning off the spot light
		}

		RenderPass(camera.calculateViewMatrix(), projection);

		mainWindow.swapBuffers();
	}

	return 0;
}