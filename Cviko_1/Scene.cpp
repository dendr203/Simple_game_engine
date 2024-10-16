#include "Scene.h"

#include <cstdlib> // Pro rand()
#include <ctime>   // Pro srand()

const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"out vec3 frag_pos;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"	  frag_pos = vp;"
"}";

const char* vertex_shader_with_color =
"#version 330\n"
"layout(location=0) in vec4 position;\n"  // Pozice vrcholu
"layout(location=1) in vec4 color;\n"     // Barva vrcholu
"out vec4 vertex_color;\n"                // Pøeposíláme barvu do fragment shaderu
"void main () {\n"
"    gl_Position = position;\n"
"    vertex_color = color;\n"
"}";

const char* vertex_shader_trans =
"#version 330 core\n"
"layout(location = 0) in vec3 vp;\n"  // Deklarace vstupní pozice vrcholu
"layout(location = 1) in vec4 color;\n"  // Deklarace vstupní barvy
"uniform mat4 modelMatrix;\n"  // Uniformní promìnná pro transformaèní matici
"out vec4 vertex_color;\n"  // Výstupní promìnná pro barvu vrcholu
"void main() {\n"
"    gl_Position = modelMatrix * vec4(vp, 1.0);\n"  // Výpoèet pozice vrcholu
"    vertex_color = color;\n"  // Pøedání barvy do fragment shaderu
"}";

const char* vertex_shader_camera =
"#version 330\n"
"uniform mat4 modelMatrix;"
"uniform mat4 projectMatrix;"
"uniform mat4 viewMatrix;"
"out vec3 vertexColor;"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vn;"
"void main () {"
"     vertexColor=vn;"
"     gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
"}";



const char* fragment_shader =
"#version 330\n"
"in vec3 frag_pos;"
"out vec4 frag_colour;"
"void main () {"
"	  vec3 color = (frag_pos + vec3(0.5));"
"     frag_colour = vec4 (color, 1.0);"
"}";

const char* fragment_shader_with_color =
"#version 330\n"
"in vec4 vertex_color;\n"  // Pøijímáme barvu z vertex shaderu
"out vec4 frag_colour;\n"
"void main () {\n"
"    frag_colour = vertex_color;\n"  // Nastavujeme výslednou barvu
"}";

const char* fragment_shader_better =
"#version 330\n"
"in vec4 vertex_color;\n"  // Pøijímáme barvu z vertex shaderu
"out vec4 frag_colour;\n"
"void main () {\n"
"    frag_colour = vertex_color + 1;\n"  // Nastavujeme výslednou barvu
"}";

const char* fragment_shader_green =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.0, 0.9, 0.0, 1.0);"
"}";

const char* fragment_shader_camera =
"#version 330\n"
"out vec4 frag_colour;"
"in vec3 vertexColor;"
"void main () {"
"     frag_colour = vec4(vertexColor, 0.0);"
"}";



Scene::Scene(Camera* _camera)
{
	srand(static_cast<unsigned int>(time(0)));
	camera = _camera;
}

Scene::~Scene() {}

void Scene::CrateScene() {
	
	DrawableObject* object1 = new DrawableObject();
	object1->init_sphere();
	object1->init_shader(vertex_shader_trans, fragment_shader_better);
	object1->translate(0.4f, -0.5f, 0.f);
	object1->scale(0.1f, 0.1f, 0.1f);
	object1->rotateAngle = 0.02f;
	object1->rotateX = 1.f;
	objects.push_back(object1);

	DrawableObject* object2 = new DrawableObject();
	object2->init_tree();
	object2->init_shader(vertex_shader_trans, fragment_shader_with_color);
	object2->translate(-0.4f, -0.8f, 0.f);
	object2->scale(0.3f, 0.3f, 0.3f);
	object2->rotateAngle = 0.05f;
	object2->rotateY = 1.f;
	objects.push_back(object2);

	DrawableObject* object3 = new DrawableObject();
	object3->init_bushes();
	object3->init_shader(vertex_shader_trans, fragment_shader_green);
	object3->translate(0.5f, 0.6f, 0.f);
	object3->scale(0.4f, 0.4f, 0.4f);
	object3->rotateAngle = 0.025f;
	object3->rotateZ = 1.f;
	objects.push_back(object3);
	
	/*
	object1->setModel("models/cube.obj");
	object1->setTexture("textures/brick.jpg");
	object1->setShader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
	*/
}

void Scene::CreateForestScene(int numTrees, int numBushes) {
	


	for (int i = 0; i < numTrees; ++i) {
		DrawableObject* tree = new DrawableObject();
		tree->init_tree();
		tree->init_shader(vertex_shader_camera, fragment_shader_camera);
		RandomTransform(tree, i);
		objects.push_back(tree);
	}

	for (int i = 0; i < numBushes; ++i) {
		DrawableObject* bush = new DrawableObject();
		bush->init_bushes();
		bush->init_shader(vertex_shader_camera, fragment_shader_camera);
		RandomTransform(bush, i);
		objects.push_back(bush);
	}
}

void Scene::CreateCameraBaseScene() {
	DrawableObject* object1 = new DrawableObject();
	object1->init_sphere();
	object1->init_shader(vertex_shader_camera, fragment_shader_camera);
	object1->scale(0.5f, 0.5f, 0.5f);
	//object1->rotateAngle = 0.1f;
	//object1->rotateX = 1.f;
	objects.push_back(object1);
}

void Scene::RandomTransform(DrawableObject* object, int i) {
	
	float x = static_cast<float>(rand() % 10 - 5) / 10.0f;
	//float y = static_cast<float>(rand() % 10 - 9) / 10.0f;
	float z = static_cast<float>(rand() % 10 - 9) / 10.0f;
	
	float help = (i - 5) / 2.0f;
	printf("x: %f\n", help);
	printf("y: %f\n", z);
	object->translate(help, -0.7, z);

	// Random rotation (0, 0.3)
	/*
	object->rotateAngle = rand() % 3 / 10.0f;
	int axis = rand() % 3;
	switch (axis) {
	case 0: // Rotation around X axis
		object->rotateX = 1.f;
		break;
	case 1: // Rotation around Y axis
		object->rotateY = 1.f;
		break;
	case 2: // Rotation around Z axis
		object->rotateZ = 1.f;
		break;
	}
	*/

	// Random scale (0.1, 0.5)
	float scale = static_cast<float>(rand() % 30 + 1) / 100.0f;
	printf("scale %f\n", scale);
	object->scale(scale, scale, scale);
}



void Scene::DrawScene() {

	//glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 viewMatrix = camera->getViewMatrix();
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 1000.0f / 800.0f, 0.1f, 100.0f);

	for (int i = 0; i < objects.size(); i++)
	{
		//objects[i]->rotate(objects[i]->rotateAngle, objects[i]->rotateX, objects[i]->rotateY, objects[i]->rotateZ);
		objects[i]->Draw(viewMatrix, projectionMatrix);
	}
}

void Scene::ClearScene() {
	for (DrawableObject* obj : objects) {
		delete obj;
	}
	objects.clear();
}

void Scene::SwitchScene(int sceneId) {
	ClearScene();

	if (sceneId == 1) {
		CrateScene();
	}
	else if (sceneId == 2) {
		CreateForestScene(10, 5);
	}
}