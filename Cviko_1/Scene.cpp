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


void Scene::CreateForestScene(int numTrees, int numBushes) {
	camera->setCamera(glm::vec3(6.f, 5.f, 7.f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.05f,
		60.0f, -130.f, -30.f, 0.08f);
	Light* light = new Light(glm::vec3(10.0f, 5.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 32);
	lights.push_back(light);


	//light
	ShaderProgram* shaderProgram_light = new ShaderProgram(camera);
	shaderProgram_light->addLight(light);
	shaderProgram_light->init_shader("Shaders/constant_vertex.glsl", "Shaders/constant_fragment.glsl");
	camera->addObserver(shaderProgram_light);
	light->addObserver(shaderProgram_light);
	shaderPrograms.push_back(shaderProgram_light);

	Model* sphere_model = new Model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));
	models.push_back(sphere_model);

	DrawableObject* light_sphere = new DrawableObject(camera);
	light_sphere->init_model(sphere_model);
	light_sphere->init_shader(shaderProgram_light);
	light_sphere->addTranslation(glm::vec3(light->getPosition().x, light->getPosition().y, light->getPosition().z));
	light_sphere->addScale(glm::vec3(0.5f, 0.5f, 0.5f));
	light_sphere->setColor(glm::vec4(light->getColor().x, light->getColor().y, light->getColor().z, 1.0f));
	objects.push_back(light_sphere);


	

	ShaderProgram* shaderProgram = new ShaderProgram(camera);
	shaderProgram->addLight(light);
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
	plain->addScale(glm::vec3(500, 500, 500));
	plain->setColor(glm::vec4(0.659f, 0.408f, 0.165f, 1.0f));
	objects.push_back(plain);



	//tree
	Model* tree_model = new Model(std::vector<float>(tree, tree + sizeof(tree) / sizeof(tree[0])));
	models.push_back(tree_model);


	//bushes
	Model* bush_model = new Model(std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(bushes[0])));
	models.push_back(bush_model);


	DrawableObject* tree_rotate = new DrawableObject(camera);
	tree_rotate->init_model(tree_model);
	tree_rotate->init_shader(shaderProgram);
	tree_rotate->addTranslation(glm::vec3(5.f, 3.f, 0.f));
	tree_rotate->addScale(glm::vec3(0.5, 0.5f, 0.5f));
	tree_rotate->setColor(glm::vec4(1.0f, 1.f, 1.f, 1.0f));
	tree_rotate->addDynamicRotation(45.f, glm::vec3(0.f, 0.f, 1.f));
	objects.push_back(tree_rotate);



	for (int i = 0; i < numTrees; ++i) {
		DrawableObject* tree = new DrawableObject(camera);
		tree->init_model(tree_model);
		tree->init_shader(shaderProgram);
		RandomTransform(tree, 100.f);
		tree->setColor(glm::vec4(1.0f, 0.f, 0.f, 1.0f));
		objects.push_back(tree);
	}

	for (int i = 0; i < numBushes; ++i) {
		DrawableObject* bush = new DrawableObject(camera);
		bush->init_model(bush_model);
		bush->init_shader(shaderProgram);
		RandomTransform(bush, 30.f);
		bush->setColor(glm::vec4(0.0f, 1.f, 0.f, 1.0f));
		objects.push_back(bush);
	}

	
}

void Scene::RandomTransform(DrawableObject* object, float scale_base) {


	float x = (rand() % 500 - 250) / 10.0f;
	float z = static_cast<float>(rand() % 500 - 250) / 10.0f;
	object->addTranslation(glm::vec3(x, 0, z));

	// Random rotation
	float random_rotate = rand() % 360;
	object->addRotation(random_rotate, glm::vec3(0.f, 1.f, 0.f));


	// Random scale
	float scale = static_cast<float>(rand() % 30 + 1) / scale_base;
	object->addScale(glm::vec3(scale, scale, scale));
}


void Scene::CreateLightTestScene()
{
	camera->setCamera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		0.01f, 60.0, -89.9f, -89.9f, 0.05f);

	Light* light = new Light(glm::vec3(0.0f, 0.1f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 1);
	lights.push_back(light);

	Light* light_2 = new Light(glm::vec3(-2.f, 0.f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 32);
	lights.push_back(light_2);


	Model* sphere_model = new Model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));
	models.push_back(sphere_model);

	//light
	ShaderProgram* shaderProgram_light = new ShaderProgram(camera);
	//shaderProgram_light->addLight(light);
	//shaderProgram_light->addLight(light_2);
	shaderProgram_light->init_shader("Shaders/constant_vertex.glsl", "Shaders/constant_fragment.glsl");
	camera->addObserver(shaderProgram_light);
	//light->addObserver(shaderProgram_light);
	//light_2->addObserver(shaderProgram_light);
	shaderPrograms.push_back(shaderProgram_light);


	DrawableObject* light_sphere_1 = new DrawableObject(camera);
	light_sphere_1->init_model(sphere_model);
	light_sphere_1->init_shader(shaderProgram_light);
	light_sphere_1->addTranslation(glm::vec3(light->getPosition().x, light->getPosition().y, light->getPosition().z));
	light_sphere_1->addScale(glm::vec3(0.01f, 0.01f, 0.01f));
	light_sphere_1->setColor(glm::vec4(light->getColor().x, light->getColor().y, light->getColor().z, 1.0f));
	objects.push_back(light_sphere_1);


	DrawableObject* light_sphere_2 = new DrawableObject(camera);
	light_sphere_2->init_model(sphere_model);
	light_sphere_2->init_shader(shaderProgram_light);
	light_sphere_2->addTranslation(glm::vec3(light_2->getPosition().x, light_2->getPosition().y, light_2->getPosition().z));
	light_sphere_2->addScale(glm::vec3(0.01f, 0.01f, 0.01f));
	light_sphere_2->setColor(glm::vec4(light_2->getColor().x, light_2->getColor().y, light_2->getColor().z, 1.0f));
	//objects.push_back(light_sphere_2);



	
	//spheres
	ShaderProgram* shaderProgram = new ShaderProgram(camera);
	shaderProgram->addLight(light);
	//shaderProgram->addLight(light_2);
	shaderProgram->init_shader("Shaders/blin_phong_vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	camera->addObserver(shaderProgram);
	light->addObserver(shaderProgram);
	shaderPrograms.push_back(shaderProgram);


	DrawableObject* sphere_1 = new DrawableObject(camera);
	sphere_1->init_model(sphere_model);
	sphere_1->init_shader(shaderProgram);
	sphere_1->addTranslation(glm::vec3(-0.3f, 0.f, 0.f));
	sphere_1->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	sphere_1->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	objects.push_back(sphere_1);

	DrawableObject* sphere_2 = new DrawableObject(camera);
	sphere_2->init_model(sphere_model);
	sphere_2->init_shader(shaderProgram);
	sphere_2->addTranslation(glm::vec3(0.3f, 0.f, 0.f));
	sphere_2->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	sphere_2->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	objects.push_back(sphere_2);

	DrawableObject* sphere_3 = new DrawableObject(camera);
	sphere_3->init_model(sphere_model);
	sphere_3->init_shader(shaderProgram);
	sphere_3->addTranslation(glm::vec3(0.f, 0.f, -0.3f));
	sphere_3->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	sphere_3->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	objects.push_back(sphere_3);

	DrawableObject* sphere_4 = new DrawableObject(camera);
	sphere_4->init_model(sphere_model);
	sphere_4->init_shader(shaderProgram);
	sphere_4->addTranslation(glm::vec3(0.f, 0.f, 0.3f));
	sphere_4->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	sphere_4->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	objects.push_back(sphere_4);


	
}

void Scene::CreateFourShaderLightsScene()
{
	camera->setCamera(glm::vec3(-0.4f, 0.1f, 0.6f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		0.01f, 60.0, -65.0f, -5.f, 0.1f);
	Light* light = new Light(glm::vec3(-0.4f, 0.1f, 0.6f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 40);
	lights.push_back(light);
	
	Model* sphere_model = new Model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));
	models.push_back(sphere_model);



	
	//light
	ShaderProgram* shaderProgram_light = new ShaderProgram(camera);
	shaderProgram_light->addLight(light);
	shaderProgram_light->init_shader("Shaders/constant_vertex.glsl", "Shaders/constant_fragment.glsl");
	camera->addObserver(shaderProgram_light);
	light->addObserver(shaderProgram_light);
	shaderPrograms.push_back(shaderProgram_light);


	DrawableObject* light_sphere_1 = new DrawableObject(camera);
	light_sphere_1->init_model(sphere_model);
	light_sphere_1->init_shader(shaderProgram_light);
	light_sphere_1->addTranslation(glm::vec3(light->getPosition().x, light->getPosition().y, light->getPosition().z));
	light_sphere_1->addScale(glm::vec3(0.01f, 0.01f, 0.01f));
	light_sphere_1->setColor(glm::vec4(light->getColor().x, light->getColor().y, light->getColor().z, 1.0f));
	objects.push_back(light_sphere_1);




	//bush
	ShaderProgram* shaderProgram_bush = new ShaderProgram(camera);
	shaderProgram_bush->addLight(light);
	shaderProgram_bush->init_shader("Shaders/lambert_vertex.glsl", "Shaders/lambert_fragment.glsl");
	camera->addObserver(shaderProgram_bush);
	light->addObserver(shaderProgram_bush);
	shaderPrograms.push_back(shaderProgram_bush);

	Model* bushes_model = new Model(std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(bushes[0])));
	models.push_back(bushes_model);

	DrawableObject* bush_object = new DrawableObject(camera);
	bush_object->init_model(bushes_model);
	bush_object->init_shader(shaderProgram_bush);
	bush_object->addTranslation(glm::vec3(-0.4f, -0.1f, 0.f));
	bush_object->addScale(glm::vec3(0.3f, 0.3f, 0.3f));
	bush_object->setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
	objects.push_back(bush_object);
	



	//suzi
	ShaderProgram* shaderProgram_suzi = new ShaderProgram(camera);
	shaderProgram_suzi->addLight(light);
	shaderProgram_suzi->init_shader("Shaders/lambert_vertex.glsl", "Shaders/lambert_fragment.glsl");
	camera->addObserver(shaderProgram_suzi);
	light->addObserver(shaderProgram_suzi);
	shaderPrograms.push_back(shaderProgram_suzi);

	Model* suzi_smooth_model = new Model(std::vector<float>(suziSmooth, suziSmooth + sizeof(suziSmooth) / sizeof(suziSmooth[0])));
	models.push_back(suzi_smooth_model);

	DrawableObject* suzi_object = new DrawableObject(camera);
	suzi_object->init_model(suzi_smooth_model);
	suzi_object->init_shader(shaderProgram_suzi);
	suzi_object->addTranslation(glm::vec3(-0.13f, 0.f, 0.f));
	suzi_object->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	suzi_object->setColor(glm::vec4(0.631f, 0.412f, 0.106f, 1.0f));
	objects.push_back(suzi_object);
	



	//gift
	ShaderProgram* shaderProgram_gift = new ShaderProgram(camera);
	shaderProgram_gift->addLight(light);
	shaderProgram_gift->init_shader("Shaders/phong_vertex.glsl", "Shaders/phong_fragment.glsl");
	camera->addObserver(shaderProgram_gift);
	light->addObserver(shaderProgram_gift);
	shaderPrograms.push_back(shaderProgram_gift);

	Model* gift_model = new Model(std::vector<float>(gift, gift + sizeof(gift) / sizeof(gift[0])));
	models.push_back(gift_model);

	DrawableObject* gift_object = new DrawableObject(camera);
	gift_object->init_model(gift_model);
	gift_object->init_shader(shaderProgram_gift);
	gift_object->addTranslation(glm::vec3(0.13f, -0.1f, 0.f));
	gift_object->addScale(glm::vec3(0.4f, 0.4f, 0.4f));
	gift_object->setColor(glm::vec4(1.f, 0.f, 0.f, 1.0f));
	objects.push_back(gift_object);
	
	



	//sphere
	ShaderProgram* shaderProgram_sphere = new ShaderProgram(camera);
	shaderProgram_sphere->addLight(light);
	shaderProgram_sphere->init_shader("Shaders/blin_phong_vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	camera->addObserver(shaderProgram_sphere);
	light->addObserver(shaderProgram_sphere);
	shaderPrograms.push_back(shaderProgram_sphere);

	DrawableObject* sphere_object = new DrawableObject(camera);
	sphere_object->init_model(sphere_model);
	sphere_object->init_shader(shaderProgram_sphere);
	sphere_object->addTranslation(glm::vec3(0.4f, 0.f, 0.f));
	sphere_object->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	sphere_object->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	objects.push_back(sphere_object);

}

void Scene::CreateMultipleLightsScene()
{
	camera->setCamera(glm::vec3(0.f, 0.f, 0.9f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		0.01f, 45.0, -90.f, 0.f, 0.1f);
	Light* light_white = new Light(glm::vec3(-0.8f, 0.f, 0.f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 32);
	Light* light_red = new Light(glm::vec3(0.8f, 0.f, 0.f), glm::vec3(1.0f, 0.f, 0.f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 32);
	lights.push_back(light_white);
	lights.push_back(light_red);

	Model* sphere_model = new Model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));
	models.push_back(sphere_model);


	//lights
	ShaderProgram* shaderProgram_light = new ShaderProgram(camera);
	//shaderProgram_light->addLight(light_white);
	//shaderProgram_light->addLight(light_red);
	shaderProgram_light->init_shader("Shaders/constant_vertex.glsl", "Shaders/constant_fragment.glsl");
	camera->addObserver(shaderProgram_light);
	//light_white->addObserver(shaderProgram_light);
	//light_red->addObserver(shaderProgram_light);
	shaderPrograms.push_back(shaderProgram_light);

	DrawableObject* light_sphere_red = new DrawableObject(camera);
	light_sphere_red->init_model(sphere_model);
	light_sphere_red->init_shader(shaderProgram_light);
	light_sphere_red->addTranslation(glm::vec3(light_red->getPosition().x, light_red->getPosition().y, light_red->getPosition().z));
	light_sphere_red->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	light_sphere_red->setColor(glm::vec4(light_red->getColor().x, light_red->getColor().y, light_red->getColor().z, 1.0f));
	objects.push_back(light_sphere_red);

	DrawableObject* light_sphere_white = new DrawableObject(camera);
	light_sphere_white->init_model(sphere_model);
	light_sphere_white->init_shader(shaderProgram_light);
	light_sphere_white->addTranslation(glm::vec3(light_white->getPosition().x, light_white->getPosition().y, light_white->getPosition().z));
	light_sphere_white->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	light_sphere_white->setColor(glm::vec4(light_white->getColor().x, light_white->getColor().y, light_white->getColor().z, 1.0f));
	objects.push_back(light_sphere_white);




	ShaderProgram* shaderProgram_sphere = new ShaderProgram(camera);
	shaderProgram_sphere->addLight(light_red);
	shaderProgram_sphere->addLight(light_white);
	shaderProgram_sphere->init_shader("Shaders/blin_phong_vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	camera->addObserver(shaderProgram_sphere);
	light_red->addObserver(shaderProgram_sphere);
	shaderPrograms.push_back(shaderProgram_sphere);

	DrawableObject* light_red_sphere = new DrawableObject(camera);
	light_red_sphere->init_model(sphere_model);
	light_red_sphere->init_shader(shaderProgram_sphere);
	light_red_sphere->addTranslation(glm::vec3(0.f, 0.f, 0.f));
	light_red_sphere->addScale(glm::vec3(0.3f, 0.3f, 0.3f));
	light_red_sphere->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	objects.push_back(light_red_sphere);


}





void Scene::DrawScene(float deltaTime) {

	for (DrawableObject* object : objects)
	{
		object->updateTime(deltaTime);
		object->Draw();
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
		obj->clearTransformations();
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
		CreateForestScene(500, 1000);
	}
	else if (sceneId == 2) {
		CreateLightTestScene();
	}
	else if (sceneId == 3) {
		CreateFourShaderLightsScene();
	}
	else if (sceneId == 4) {
		CreateMultipleLightsScene();
	}
}