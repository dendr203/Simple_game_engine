#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::CrateScene() {
	// Create a scene with 3 objects
	DrawableObject* object1 = new DrawableObject();
	object1->init_sphere();
	transformation.scale(0.1f, 0.1f, 0.1f);
	transformation.translate(-5.0f, 0.0f, -5.0f);
	object1->setTransformation(transformation);
	objects.push_back(object1);


	transformation.clearModelMatrix();
	DrawableObject* object2 = new DrawableObject();
	object2->init_tree();
	transformation.scale(0.1f, 0.1f, 0.1f);
	transformation.translate(5.0f, 0.0f, 5.0f);
	object2->setTransformation(transformation);
	objects.push_back(object2);


	/*
	object1->setModel("models/cube.obj");
	object1->setTexture("textures/brick.jpg");
	object1->setShader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
	*/
}

void Scene::AddObject(DrawableObject* object) {
	objects.push_back(object);
}

void Scene::DrawScene(int angle) {
	for (int i = 0; i < objects.size(); i++)
	{
		transformation.rotate(angle, 0.0f, 1.0f, 0.0f);
		objects[i]->setTransformation(transformation);
		objects[i]->Draw();
	}
}