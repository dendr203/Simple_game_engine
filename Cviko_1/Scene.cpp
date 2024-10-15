#include "Scene.h"

#include <cstdlib> // Pro rand()
#include <ctime>   // Pro srand()


Scene::Scene()
{
	srand(static_cast<unsigned int>(time(0)));
}

Scene::~Scene() {}

void Scene::CrateScene() {
	
	DrawableObject* object1 = new DrawableObject();
	object1->init_sphere();
	object1->translate(0.4f, -0.5f, 0.f);
	object1->scale(0.1f, 0.1f, 0.1f);
	object1->rotateAngle = 0.02f;
	object1->rotateX = 1.f;
	objects.push_back(object1);

	DrawableObject* object2 = new DrawableObject();
	object2->init_tree();
	object2->translate(-0.4f, -0.8f, 0.f);
	object2->scale(0.3f, 0.3f, 0.3f);
	object2->rotateAngle = 0.05f;
	object2->rotateY = 1.f;
	objects.push_back(object2);

	DrawableObject* object3 = new DrawableObject();
	object3->init_bushes();
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
	// Vytvoøení náhodného lesa
	for (int i = 0; i < numTrees; ++i) {
		DrawableObject* tree = new DrawableObject();
		tree->init_tree();
		RandomTransform(tree);
		objects.push_back(tree);
	}

	for (int i = 0; i < numBushes; ++i) {
		DrawableObject* bush = new DrawableObject();
		bush->init_bushes();
		RandomTransform(bush);
		objects.push_back(bush);
	}
}

void Scene::CreateCameraBaseScene() {
	DrawableObject* object1 = new DrawableObject();
	object1->init_sphere();
	object1->scale(0.2f, 0.2f, 0.2f);
	object1->rotateAngle = 0.1f;
	object1->rotateX = 1.f;
	objects.push_back(object1);
}

void Scene::RandomTransform(DrawableObject* object) {
	// Náhodná pozice v rozsahu (-10, 10) na ose x a z, a na y v rozsahu (-1, 0)
	float x = static_cast<float>(rand() % 10 - 5) / 10.0f;
	float y = static_cast<float>(rand() % 10 - 9) / 10.0f;
	float z = static_cast<float>(rand() % 10 - 9) / 10.0f;
	object->translate(x, y, z);

	// Náhodná rotace v rozsahu (0, 360) na ose y
	object->rotateAngle = rand() % 3 / 10.0f;
	int axis = rand() % 3; // 0 = X, 1 = Y, 2 = Z
	switch (axis) {
	case 0: // Rotace kolem osy X
		object->rotateX = 1.f;
		break;
	case 1: // Rotace kolem osy Y
		object->rotateY = 1.f;
		break;
	case 2: // Rotace kolem osy Z
		object->rotateZ = 1.f;
		break;
	}

	// Náhodné škálování v rozsahu (0.1, 0.5)
	float scale = static_cast<float>(rand() % 2 + 1) / 10.0f;
	object->scale(scale, scale, scale);
}


void Scene::AddObject(DrawableObject* object) {
	objects.push_back(object);
}

void Scene::DrawScene() {
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->rotate(objects[i]->rotateAngle, objects[i]->rotateX, objects[i]->rotateY, objects[i]->rotateZ);
		objects[i]->Draw();
	}
}

void Scene::ClearScene() {
	// Uvolnìní pamìti pro všechny objekty ve scénì
	for (DrawableObject* obj : objects) {
		delete obj;
	}
	objects.clear();
}

void Scene::SwitchScene(int sceneId) {
	ClearScene(); // Vyèistíme pøedchozí scénu

	if (sceneId == 1) {
		// Normální scéna s pevnì danými objekty
		CrateScene();
	}
	else if (sceneId == 2) {
		// Scéna s lesem
		CreateForestScene(10, 5); // Vytvoøíme scénu s 10 stromy a 5 keøi
	}
}