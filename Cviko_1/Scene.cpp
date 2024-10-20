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



Scene::Scene() : camera(nullptr), viewMatrix(0), projectionMatrix(0)
{
	srand(static_cast<unsigned int>(time(0)));	
}

Scene::~Scene()
{
	delete &objects;
}

void Scene::init_cameraScene(Camera* _camera)
{
	camera = _camera;
}

void Scene::CrateScene() {
	
	DrawableObject* object1 = new DrawableObject(camera);
	//object1->init_sphere();
	object1->init_shader(vertex_shader_camera, fragment_shader_camera);
	object1->translate(0.4f, -0.5f, 0.f);
	object1->scale(0.1f, 0.1f, 0.1f);
	object1->rotateAngle = 0.02f;
	object1->rotateX = 1.f;
	objects.push_back(object1);

	DrawableObject* object2 = new DrawableObject(camera);
	//object2->init_tree();
	object2->init_shader(vertex_shader_camera, fragment_shader_camera);
	object2->translate(-0.4f, -0.8f, 0.f);
	object2->scale(0.3f, 0.3f, 0.3f);
	object2->rotateAngle = 0.05f;
	object2->rotateY = 1.f;
	objects.push_back(object2);

	DrawableObject* object3 = new DrawableObject(camera);
	//object3->init_bushes();
	object3->init_shader(vertex_shader_camera, fragment_shader_camera);
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
	
	Model* plain_model = new Model();
	plain_model->init_model(std::vector<float>(plain, plain + sizeof(plain) / sizeof(plain[0])));

	Model* tree_model = new Model();
	tree_model->init_model(std::vector<float>(tree, tree + sizeof(tree) / sizeof(tree[0])));

	Model* bush_model = new Model();
	bush_model->init_model(std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(bushes[0])));

	//create plain here next for ground
	DrawableObject* plain = new DrawableObject(camera);
	plain->init_model(plain_model);
	plain->init_shader(vertex_shader_camera, fragment_shader_camera);
	plain->scale(5, 5, 5);
	objects.push_back(plain);



	for (int i = 0; i < numTrees; ++i) {
		DrawableObject* tree = new DrawableObject(camera);
		tree->init_model(tree_model);
		tree->init_shader(vertex_shader_camera, fragment_shader_camera);
		RandomTransform(tree, i);
		objects.push_back(tree);
	}

	for (int i = 0; i < numBushes; ++i) {
		DrawableObject* bush = new DrawableObject(camera);
		bush->init_model(bush_model);
		bush->init_shader(vertex_shader_camera, fragment_shader_camera);
		RandomTransform(bush, i);
		objects.push_back(bush);
	}
}

void Scene::RandomTransform(DrawableObject* object, int i) {
	
	float x = static_cast<float>(rand() % 10 - 5) / 10.0f;
	//float y = static_cast<float>(rand() % 10 - 9) / 10.0f;
	float z = static_cast<float>(rand() % 100 - 50) / 10.0f;
	
	float x_my = (i - 25) / 5.0f;
	object->translate(x_my, 0, z);

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
	object->scale(scale, scale, scale);
}



void Scene::DrawScene() {

	for (int i = 0; i < objects.size(); i++)
	{
		//objects[i]->rotate(objects[i]->rotateAngle, objects[i]->rotateX, objects[i]->rotateY, objects[i]->rotateZ);
		objects[i]->Draw(camera->getViewMatrix(), camera->getProjectionMatrix());
	}
}

void Scene::ClearScene() {
	for (DrawableObject* obj : objects) {
		delete obj;
	}
	objects.clear();
	camera->clearLinkShaders();
}

void Scene::SwitchScene(int sceneId) {
	ClearScene();

	if (sceneId == 1) {
		CrateScene();
	}
	else if (sceneId == 2) {
		CreateForestScene(50, 50);
	}
}