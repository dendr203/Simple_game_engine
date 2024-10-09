#include "Application.h"


int main(void)
{
	Application* app = new Application();
	app->initialization(); //OpenGL inicialization

	//Loading scene
	app->createModels();
	//app->createShaders();
	app->run(); //Rendering 


}