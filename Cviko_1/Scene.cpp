#include "Scene.h"

#include <cstdlib> // for rand()
#include <ctime>   // for srand()


Scene::Scene(Camera* _camera) : camera(_camera)
{
	srand(static_cast<unsigned int>(time(0)));
}

Scene::~Scene()
{
	delete& objects;
}

void Scene::CrateScene() {
	camera->setCamera(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.05f, 45.0f, -90.f, 0.f, 0.08f);

	Light* light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 0);
	lights.push_back(light);

	ShaderProgram* shaderProgram = new ShaderProgram(camera, light);
	shaderProgram->init_shader("Shaders/lambert_vertex.glsl", "Shaders/lambert_fragment.glsl");
	camera->addObserver(shaderProgram);
	light->addObserver(shaderProgram);
	shaderPrograms.push_back(shaderProgram);

	Model* sphere_model = new Model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));
	
	DrawableObject* object1 = new DrawableObject(camera);
	object1->init_model(sphere_model);
	object1->init_shader(shaderProgram);
	object1->addTranslation(0.4f, -0.5f, 0.f);
	object1->addScale(0.1f, 0.1f, 0.1f);
	object1->addRotation(0.02f, 1.f, 0.f, 0.f);
	object1->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	objects.push_back(object1);

	Model* tree_model = new Model(std::vector<float>(tree, tree + sizeof(tree) / sizeof(tree[0])));
	models.push_back(tree_model);
	DrawableObject* object2 = new DrawableObject(camera);
	object2->init_model(tree_model);
	object2->init_shader(shaderProgram);
	object2->addTranslation(-0.4f, -0.8f, 0.f);
	object2->addScale(0.3f, 0.3f, 0.3f);
	object2->addRotation(0.05, 0.f, 1.f, 0.f);
	object2->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	objects.push_back(object2);

	Model* bush_model = new Model(std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(bushes[0])));
	models.push_back(bush_model);
	DrawableObject* object3 = new DrawableObject(camera);
	object3->init_model(bush_model);
	object3->init_shader(shaderProgram);
	object3->addTranslation(0.5f, 0.6f, 0.f);
	object3->addScale(0.4f, 0.4f, 0.4f);
	object3->addRotation(0.025f, 0.f, 0.f, 1.f);
	object3->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	objects.push_back(object3);

	/*
	object1->setModel("models/cube.obj");
	object1->setTexture("textures/brick.jpg");
	object1->setShader("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
	*/

}

void Scene::CreateForestScene(int numTrees, int numBushes) {
	camera->setCamera(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.05f, 60.0f, -90.f, 0.f, 0.08f);
	Light* light = new Light(glm::vec3(10.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 10);
	lights.push_back(light);

	ShaderProgram* shaderProgram = new ShaderProgram(camera, light);
	shaderProgram->init_shader("Shaders/blin_phong_vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	camera->addObserver(shaderProgram);
	light->addObserver(shaderProgram);
	shaderPrograms.push_back(shaderProgram);



	//plain
	Model* plain_model = new Model(std::vector<float>(plain, plain + sizeof(plain) / sizeof(plain[0])));
	models.push_back(plain_model);
	
	DrawableObject* plain = new DrawableObject(camera);
	plain->init_model(plain_model);
	plain->init_shader(shaderProgram);
	plain->addScale(5, 5, 5);
	plain->setColor(glm::vec4(0.659f, 0.408f, 0.165f, 1.0f));
	objects.push_back(plain);



	//tree
	Model* tree_model = new Model(std::vector<float>(tree, tree + sizeof(tree) / sizeof(tree[0])));
	models.push_back(tree_model);


	//bushes
	Model* bush_model = new Model(std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(bushes[0])));
	models.push_back(bush_model);





	for (int i = 0; i < numTrees; ++i) {
		DrawableObject* tree = new DrawableObject(camera);
		tree->init_model(tree_model);
		tree->init_shader(shaderProgram);
		RandomTransform(tree, i);
		tree->setColor(glm::vec4(1.0f, 0.f, 0.f, 1.0f));
		objects.push_back(tree);
	}

	for (int i = 0; i < numBushes; ++i) {
		DrawableObject* bush = new DrawableObject(camera);
		bush->init_model(bush_model);
		bush->init_shader(shaderProgram);
		RandomTransform(bush, i);
		bush->setColor(glm::vec4(0.0f, 1.f, 0.f, 1.0f));
		objects.push_back(bush);
	}

	
}

void Scene::CreateLightTestScene()
{
	camera->setCamera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.01f, 60.0, -90.0f, -90.0f, 0.05f);

	Light* light = new Light(glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 1);
	lights.push_back(light);


	ShaderProgram* shaderProgram = new ShaderProgram(camera, light);
	shaderProgram->init_shader("Shaders/phong_vertex.glsl", "Shaders/phong_fragment.glsl");
	camera->addObserver(shaderProgram);
	light->addObserver(shaderProgram);
	shaderPrograms.push_back(shaderProgram);

	Model* sphere_model = new Model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));
	models.push_back(sphere_model);

	DrawableObject* sphere_1 = new DrawableObject(camera);
	sphere_1->init_model(sphere_model);
	sphere_1->init_shader(shaderProgram);
	sphere_1->addTranslation(-0.3f, 0.f, 0.f);
	sphere_1->addScale(0.1f, 0.1f, 0.1f);
	sphere_1->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	objects.push_back(sphere_1);

	DrawableObject* sphere_2 = new DrawableObject(camera);
	sphere_2->init_model(sphere_model);
	sphere_2->init_shader(shaderProgram);
	sphere_2->addTranslation(0.3f, 0.f, 0.f);
	sphere_2->addScale(0.1f, 0.1f, 0.1f);
	sphere_2->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	objects.push_back(sphere_2);

	DrawableObject* sphere_3 = new DrawableObject(camera);
	sphere_3->init_model(sphere_model);
	sphere_3->init_shader(shaderProgram);
	sphere_3->addTranslation(0.f, 0.f, -0.3f);
	sphere_3->addScale(0.1f, 0.1f, 0.1f);
	sphere_3->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	objects.push_back(sphere_3);

	DrawableObject* sphere_4 = new DrawableObject(camera);
	sphere_4->init_model(sphere_model);
	sphere_4->init_shader(shaderProgram);
	sphere_4->addTranslation(0.f, 0.f, 0.3f);
	sphere_4->addScale(0.1f, 0.1f, 0.1f);
	sphere_4->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	objects.push_back(sphere_4);


	
}

void Scene::CreateFourShaderLightsScene()
{
	camera->setCamera(glm::vec3(-0.4f, 0.1f, 0.6f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.01f, 60.0, -65.0f, -5.f, 0.1f);
	Light* light = new Light(glm::vec3(-0.4f, 0.1f, 0.6f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 40);
	lights.push_back(light);
	
	Model* sphere_model = new Model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));
	models.push_back(sphere_model);



	
	//light
	ShaderProgram* shaderProgram_light = new ShaderProgram(camera, light);
	shaderPrograms.push_back(shaderProgram_light);
	shaderProgram_light->init_shader("Shaders/constant_vertex.glsl", "Shaders/constant_fragment.glsl");
	camera->addObserver(shaderProgram_light);
	light->addObserver(shaderProgram_light);


	DrawableObject* light_sphere = new DrawableObject(camera);
	light_sphere->init_model(sphere_model);
	light_sphere->init_shader(shaderProgram_light);
	light_sphere->addTranslation(-0.35f, 0.1f, 0.6f);
	light_sphere->addScale(0.01f, 0.01f, 0.01f);
	light_sphere->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	objects.push_back(light_sphere);




	//bush
	ShaderProgram* shaderProgram_bush = new ShaderProgram(camera, light);
	shaderProgram_bush->init_shader("Shaders/lambert_vertex.glsl", "Shaders/lambert_fragment.glsl");
	camera->addObserver(shaderProgram_bush);
	light->addObserver(shaderProgram_bush);
	shaderPrograms.push_back(shaderProgram_bush);

	Model* bushes_model = new Model(std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(bushes[0])));
	models.push_back(bushes_model);

	DrawableObject* bush_object = new DrawableObject(camera);
	bush_object->init_model(bushes_model);
	bush_object->init_shader(shaderProgram_bush);
	bush_object->addTranslation(-0.4f, -0.1f, 0.f);
	bush_object->addScale(0.3f, 0.3f, 0.3f);
	bush_object->setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	objects.push_back(bush_object);
	



	//suzi
	ShaderProgram* shaderProgram_suzi = new ShaderProgram(camera, light);
	shaderProgram_suzi->init_shader("Shaders/lambert_vertex.glsl", "Shaders/lambert_fragment.glsl");
	camera->addObserver(shaderProgram_suzi);
	light->addObserver(shaderProgram_suzi);
	shaderPrograms.push_back(shaderProgram_suzi);

	Model* suzi_smooth_model = new Model(std::vector<float>(suziSmooth, suziSmooth + sizeof(suziSmooth) / sizeof(suziSmooth[0])));
	models.push_back(suzi_smooth_model);

	DrawableObject* suzi_object = new DrawableObject(camera);
	suzi_object->init_model(suzi_smooth_model);
	suzi_object->init_shader(shaderProgram_suzi);
	suzi_object->addTranslation(-0.13f, 0.f, 0.f);
	suzi_object->addScale(0.1f, 0.1f, 0.1f);
	suzi_object->setColor(glm::vec4(0.631f, 0.412f, 0.106f, 1.0f));
	objects.push_back(suzi_object);
	



	//gift
	ShaderProgram* shaderProgram_gift = new ShaderProgram(camera, light);
	shaderProgram_gift->init_shader("Shaders/phong_vertex.glsl", "Shaders/phong_fragment.glsl");
	camera->addObserver(shaderProgram_gift);
	light->addObserver(shaderProgram_gift);
	shaderPrograms.push_back(shaderProgram_gift);

	Model* gift_model = new Model(std::vector<float>(gift, gift + sizeof(gift) / sizeof(gift[0])));
	models.push_back(gift_model);

	DrawableObject* gift_object = new DrawableObject(camera);
	gift_object->init_model(gift_model);
	gift_object->init_shader(shaderProgram_gift);
	gift_object->addTranslation(0.13f, -0.1f, 0.f);
	gift_object->addScale(0.4f, 0.4f, 0.4f);
	gift_object->setColor(glm::vec4(1.f, 0.f, 0.f, 1.0f));
	objects.push_back(gift_object);
	
	



	//sphere
	ShaderProgram* shaderProgram_sphere = new ShaderProgram(camera, light);
	shaderProgram_sphere->init_shader("Shaders/blin_phong_vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	camera->addObserver(shaderProgram_sphere);
	light->addObserver(shaderProgram_sphere);
	shaderPrograms.push_back(shaderProgram_sphere);

	DrawableObject* sphere_object = new DrawableObject(camera);
	sphere_object->init_model(sphere_model);
	sphere_object->init_shader(shaderProgram_sphere);
	sphere_object->addTranslation(0.4f, 0.f, 0.f);
	sphere_object->addScale(0.1f, 0.1f, 0.1f);
	sphere_object->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	objects.push_back(sphere_object);

}

void Scene::CreateMultipleLightsScene()
{
	camera->setCamera(glm::vec3(-0.4f, 0.1f, 0.6f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.01f, 45.0, -65.0f, -5.f, 0.1f);
	Light* light = new Light(glm::vec3(-0.4f, 0.1f, 0.6f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 40);


	Model* sphere_model = new Model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));
	models.push_back(sphere_model);
}

void Scene::RandomTransform(DrawableObject* object, int i) {

	float x = static_cast<float>(rand() % 10 - 5) / 10.0f;
	//float y = static_cast<float>(rand() % 10 - 9) / 10.0f;
	float z = static_cast<float>(rand() % 100 - 50) / 10.0f;

	float x_my = (i - 25) / 5.0f;
	object->addTranslation(x_my, 0, z);

	// Random rotation (0, 0.3)
	float random_rotate = rand() % 360;
	object->addRotation(random_rotate, 0.f, 1.f, 0.f);


	// Random scale (0.1, 0.5)
	float scale = static_cast<float>(rand() % 30 + 1) / 100.0f;
	object->addScale(scale, scale, scale);
}



void Scene::DrawScene() {

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Draw();
	}
}

void Scene::ClearScene() {
	camera->clearLinkShaders();
	for (Light* light : lights) {
		light->clearLinkShaders();
	}
	lights.clear();

	
	for (Model* model : models) {
		delete model;
	}
	models.clear();
	

	for (DrawableObject* obj : objects) {
		delete obj;
	}
	objects.clear();

	for (ShaderProgram* prg : shaderPrograms) {
		delete prg;
	}
	shaderPrograms.clear();
}

void Scene::SwitchScene(int sceneId) {
	ClearScene();

	if (sceneId == 1) {
		CrateScene();
	}
	else if (sceneId == 2) {
		CreateForestScene(50, 50);
	}
	else if (sceneId == 3) {
		CreateLightTestScene();
	}
	else if (sceneId == 4) {
		CreateFourShaderLightsScene();
	}
}