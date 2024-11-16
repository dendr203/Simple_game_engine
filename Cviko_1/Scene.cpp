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


void Scene::CreateForestScene_blud(int numTrees, int numBushes) {
	camera->setCamera(glm::vec3(6.f, 5.f, 7.f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.05f,
		60.0f, -130.f, -30.f, 0.08f);


	SpotLight* spotlight_1 = new SpotLight(0, glm::vec3(-20.0f, 10.0f, 20.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, .0f, .0f), 5.f, 10.f);
	lights.push_back(spotlight_1);

	SpotLight* spotlight_2 = new SpotLight(0, glm::vec3(-20.0f, 10.0f, -20.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), 10.f, 20.f);
	lights.push_back(spotlight_2);
	

	PointLight* blud_1 = new PointLight(glm::vec3(-10.f, 1.f, -5.f), glm::vec3(1.f, 1.f, 1.f), 0.1f, 0.3f, 0.032f);
	PointLight* blud_2 = new PointLight(glm::vec3(10.f, 1.f, 5.f), glm::vec3(1.f, 1.f, 1.f), 0.1f, 0.3f, 0.032f);
	PointLight* blud_3 = new PointLight(glm::vec3(-2.f, 1.f, 3.f), glm::vec3(1.f, 1.f, 1.f), 0.1f, 0.3f, 0.032f);
	PointLight* blud_4 = new PointLight(glm::vec3(5.f, 1.f, -3.f), glm::vec3(1.f, 1.f, 1.f), 0.1f, 0.3f, 0.032f);
	PointLight* blud_5 = new PointLight(glm::vec3(8.f, 1.f, 4.f), glm::vec3(1.f, 1.f, 1.f), 0.1f, 0.3f, 0.032f);
	lights.push_back(blud_1);
	lights.push_back(blud_2);
	lights.push_back(blud_3);
	lights.push_back(blud_4);
	lights.push_back(blud_5);


	//light
	ShaderProgram* shaderProgram_light = new ShaderProgram(camera);
	shaderProgram_light->init_shader("Shaders/vertex.glsl", "Shaders/constant_fragment.glsl");
	camera->addObserver(shaderProgram_light);
	shaderPrograms.push_back(shaderProgram_light);
	Model* sphere_model = new Model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));
	models.push_back(sphere_model);


	
	//tree, bush plain
	ShaderProgram* shaderProgram = new ShaderProgram(camera);
	shaderProgram->addLight(spotlight_1);
	shaderProgram->addLight(spotlight_2);
	shaderProgram->addLight(blud_1);
	shaderProgram->addLight(blud_2);
	shaderProgram->addLight(blud_3);
	shaderProgram->addLight(blud_4);
	shaderProgram->addLight(blud_5);
	shaderProgram->init_shader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	camera->addObserver(shaderProgram);
	spotlight_1->addObserver(shaderProgram);
	spotlight_2->addObserver(shaderProgram);
	blud_1->addObserver(shaderProgram);
	blud_2->addObserver(shaderProgram);
	blud_3->addObserver(shaderProgram);
	blud_4->addObserver(shaderProgram);
	blud_5->addObserver(shaderProgram);
	shaderPrograms.push_back(shaderProgram);


	//plain
	Model* plain_model = new Model(std::vector<float>(plain, plain + sizeof(plain) / sizeof(plain[0])));
	models.push_back(plain_model);
	
	DrawableObject* plain = new DrawableObject(camera);
	plain->init_model(plain_model);
	plain->init_shader(shaderProgram);
	plain->addScale(glm::vec3(500, 500, 500));
	plain->setColor(glm::vec4(0.659f, 0.408f, 0.165f, 1.0f));
	plain->setMaterial(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.1f, 0.1f, 0.1f), 32.0f);
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
	tree_rotate->setMaterial(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(tree_rotate);



	for (int i = 0; i < numTrees; ++i) {
		DrawableObject* tree = new DrawableObject(camera);
		tree->init_model(tree_model);
		tree->init_shader(shaderProgram);
		RandomTransform(tree, 100.f);
		tree->setColor(glm::vec4(1.0f, 0.f, 0.f, 1.0f));
		tree->setMaterial(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.4f, 0.4f, 0.4f), 32.0f);
		objects.push_back(tree);
		if (i % 3 == 0)
		{
			tree->addDynamicRotation(45.f, glm::vec3(0.f, 1.f, 0.f));
		}
	}

	for (int i = 0; i < numBushes; ++i) {
		DrawableObject* bush = new DrawableObject(camera);
		bush->init_model(bush_model);
		bush->init_shader(shaderProgram);
		RandomTransform(bush, 30.f);
		bush->setColor(glm::vec4(0.0f, 1.f, 0.f, 1.0f));
		bush->setMaterial(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.4f, 0.4f, 0.4f), 32.0f);
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


void Scene::CreateForestScene_bat(int numTrees, int numBushes)
{
	camera->setCamera(glm::vec3(6.f, 5.f, 7.f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.05f,
		60.0f, -130.f, -30.f, 0.08f);

	SpotLight* spotlight = new SpotLight(0, glm::vec3(10.0f, 10.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, .0f), 20.f, 40.f);
	lights.push_back(spotlight);

	SpotLight* battery = new SpotLight(1, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 10.f, 20.f);
	lights.push_back(battery);


	//light
	ShaderProgram* shaderProgram_light = new ShaderProgram(camera);
	shaderProgram_light->addLight(spotlight);
	shaderProgram_light->init_shader("Shaders/vertex.glsl", "Shaders/constant_fragment.glsl");
	camera->addObserver(shaderProgram_light);
	spotlight->addObserver(shaderProgram_light);
	shaderPrograms.push_back(shaderProgram_light);

	Model* sphere_model = new Model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));
	models.push_back(sphere_model);

	DrawableObject* light_sphere = new DrawableObject(camera);
	light_sphere->init_model(sphere_model);
	light_sphere->init_shader(shaderProgram_light);
	light_sphere->addTranslation(glm::vec3(spotlight->getPosition().x, spotlight->getPosition().y, spotlight->getPosition().z));
	light_sphere->addScale(glm::vec3(0.5f, 0.5f, 0.5f));
	light_sphere->setColor(glm::vec4(spotlight->getColor().x, spotlight->getColor().y, spotlight->getColor().z, 1.0f));
	light_sphere->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 32.0f);
	objects.push_back(light_sphere);




	//tree, bush plain
	ShaderProgram* shaderProgram = new ShaderProgram(camera);
	shaderProgram->addLight(spotlight);
	shaderProgram->addLight(battery);
	shaderProgram->init_shader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	camera->addObserver(shaderProgram);
	spotlight->addObserver(shaderProgram);
	battery->addObserver(shaderProgram);
	shaderPrograms.push_back(shaderProgram);


	//plain
	Model* plain_model = new Model(std::vector<float>(plain, plain + sizeof(plain) / sizeof(plain[0])));
	models.push_back(plain_model);

	DrawableObject* plain = new DrawableObject(camera);
	plain->init_model(plain_model);
	plain->init_shader(shaderProgram);
	plain->addScale(glm::vec3(500, 500, 500));
	plain->setColor(glm::vec4(0.659f, 0.408f, 0.165f, 1.0f));
	plain->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
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
	tree_rotate->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(tree_rotate);



	for (int i = 0; i < numTrees; ++i) {
		DrawableObject* tree = new DrawableObject(camera);
		tree->init_model(tree_model);
		tree->init_shader(shaderProgram);
		RandomTransform(tree, 100.f);
		tree->setColor(glm::vec4(1.0f, 0.f, 0.f, 1.0f));
		tree->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
		objects.push_back(tree);
		if (i % 3 == 0)
		{
			tree->addDynamicRotation(45.f, glm::vec3(0.f, 1.f, 0.f));
		}
	}

	for (int i = 0; i < numBushes; ++i) {
		DrawableObject* bush = new DrawableObject(camera);
		bush->init_model(bush_model);
		bush->init_shader(shaderProgram);
		RandomTransform(bush, 30.f);
		bush->setColor(glm::vec4(0.0f, 1.f, 0.f, 1.0f));
		bush->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
		objects.push_back(bush);
	}
}

void Scene::CreateFourShaderLightsScene()
{
	camera->setCamera(glm::vec3(-0.4f, 0.1f, 0.6f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		0.005f, 60.0, -65.0f, -5.f, 0.1f);

	PointLight* pointlight = new PointLight(glm::vec3(-0.4f, 0.1f, 0.6f), glm::vec3(1.0f, 1.0f, 1.0f), 0.1f, 0.3f, 0.032f);
	lights.push_back(pointlight);


	Model* sphere_model = new Model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));
	models.push_back(sphere_model);



	
	//light
	ShaderProgram* shaderProgram_light = new ShaderProgram(camera);
	shaderProgram_light->addLight(pointlight);
	shaderProgram_light->init_shader("Shaders/vertex.glsl", "Shaders/constant_fragment.glsl");
	camera->addObserver(shaderProgram_light);
	pointlight->addObserver(shaderProgram_light);
	shaderPrograms.push_back(shaderProgram_light);


	DrawableObject* light_sphere_1 = new DrawableObject(camera);
	light_sphere_1->init_model(sphere_model);
	light_sphere_1->init_shader(shaderProgram_light);
	light_sphere_1->addTranslation(glm::vec3(pointlight->getPosition().x, pointlight->getPosition().y, pointlight->getPosition().z));
	light_sphere_1->addScale(glm::vec3(0.01f, 0.01f, 0.01f));
	light_sphere_1->setColor(glm::vec4(pointlight->getColor().x, pointlight->getColor().y, pointlight->getColor().z, 1.0f));
	light_sphere_1->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(light_sphere_1);



	
	



	//suzi
	ShaderProgram* shaderProgram_suzi = new ShaderProgram(camera);
	shaderProgram_suzi->addLight(pointlight);
	shaderProgram_suzi->init_shader("Shaders/vertex.glsl", "Shaders/lambert_fragment.glsl");
	camera->addObserver(shaderProgram_suzi);
	pointlight->addObserver(shaderProgram_suzi);
	shaderPrograms.push_back(shaderProgram_suzi);

	Model* suzi_smooth_model = new Model(std::vector<float>(suziSmooth, suziSmooth + sizeof(suziSmooth) / sizeof(suziSmooth[0])));
	models.push_back(suzi_smooth_model);

	DrawableObject* suzi_object = new DrawableObject(camera);
	suzi_object->init_model(suzi_smooth_model);
	suzi_object->init_shader(shaderProgram_suzi);
	suzi_object->addTranslation(glm::vec3(-0.35f, 0.f, 0.f));
	suzi_object->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	suzi_object->setColor(glm::vec4(0.631f, 0.412f, 0.106f, 1.0f));
	suzi_object->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.1f, 0.1f, 0.1f), 32.0f);
	objects.push_back(suzi_object);
	


	DrawableObject* suzi_object_2 = new DrawableObject(camera);
	suzi_object_2->init_model(suzi_smooth_model);
	suzi_object_2->init_shader(shaderProgram_suzi);
	suzi_object_2->addTranslation(glm::vec3(-0.08f, 0.f, 0.f));
	suzi_object_2->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	suzi_object_2->setColor(glm::vec4(0.631f, 0.412f, 0.106f, 1.0f));
	suzi_object_2->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(suzi_object_2);



	DrawableObject* suzi_object_3 = new DrawableObject(camera);
	suzi_object_3->init_model(suzi_smooth_model);
	suzi_object_3->init_shader(shaderProgram_suzi);
	suzi_object_3->addTranslation(glm::vec3(0.20f, 0.f, 0.f));
	suzi_object_3->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	suzi_object_3->setColor(glm::vec4(0.631f, 0.412f, 0.106f, 1.0f));
	suzi_object_3->setMaterial(glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(suzi_object_3);
	





}

void Scene::CreateMultipleLightsScene()
{
	camera->setCamera(glm::vec3(0.f, 0.f, 2.f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		0.01f, 45.0, -90.f, 0.f, 0.1f);

	SpotLight* spotlight_white = new SpotLight(0, glm::vec3(-0.8f, 0.f, 0.9f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 30.f, 35.f);

	SpotLight* spotlight_red = new SpotLight(0, glm::vec3(0.8f, 0.f, 0.9f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), 30.f, 35.f);

	lights.push_back(spotlight_white);
	lights.push_back(spotlight_white);

	Model* sphere_model = new Model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));
	models.push_back(sphere_model);


	//lights
	ShaderProgram* shaderProgram_light = new ShaderProgram(camera);
	shaderProgram_light->addLight(spotlight_white);
	shaderProgram_light->addLight(spotlight_red);
	shaderProgram_light->init_shader("Shaders/vertex.glsl", "Shaders/constant_fragment.glsl");
	camera->addObserver(shaderProgram_light);
	spotlight_white->addObserver(shaderProgram_light);
	spotlight_white->addObserver(shaderProgram_light);
	shaderPrograms.push_back(shaderProgram_light);

	DrawableObject* light_sphere_red = new DrawableObject(camera);
	light_sphere_red->init_model(sphere_model);
	light_sphere_red->init_shader(shaderProgram_light);
	light_sphere_red->addTranslation(glm::vec3(spotlight_red->getPosition().x, spotlight_red->getPosition().y, spotlight_red->getPosition().z));
	light_sphere_red->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	light_sphere_red->setColor(glm::vec4(spotlight_red->getColor().x, spotlight_red->getColor().y, spotlight_red->getColor().z, 1.0f));
	light_sphere_red->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(light_sphere_red);
	

	DrawableObject* light_sphere_white = new DrawableObject(camera);
	light_sphere_white->init_model(sphere_model);
	light_sphere_white->init_shader(shaderProgram_light);
	light_sphere_white->addTranslation(glm::vec3(spotlight_white->getPosition().x, spotlight_white->getPosition().y, spotlight_white->getPosition().z));
	light_sphere_white->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	light_sphere_white->setColor(glm::vec4(spotlight_white->getColor().x, spotlight_white->getColor().y, spotlight_white->getColor().z, 1.0f));
	light_sphere_white->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(light_sphere_white);




	ShaderProgram* shaderProgram_sphere = new ShaderProgram(camera);
	shaderProgram_sphere->addLight(spotlight_red);
	shaderProgram_sphere->addLight(spotlight_white);
	shaderProgram_sphere->init_shader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	camera->addObserver(shaderProgram_sphere);
	spotlight_red->addObserver(shaderProgram_sphere);
	spotlight_white->addObserver(shaderProgram_sphere);
	shaderPrograms.push_back(shaderProgram_sphere);

	DrawableObject* sphere_1 = new DrawableObject(camera);
	sphere_1->init_model(sphere_model);
	sphere_1->init_shader(shaderProgram_sphere);
	sphere_1->addTranslation(glm::vec3(0.8f, 0.f, -0.5f));
	sphere_1->addScale(glm::vec3(0.3f, 0.3f, 0.3f));
	sphere_1->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	sphere_1->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(sphere_1);

	DrawableObject* sphere_2 = new DrawableObject(camera);
	sphere_2->init_model(sphere_model);
	sphere_2->init_shader(shaderProgram_sphere);
	sphere_2->addTranslation(glm::vec3(-0.8f, 0.f, -0.5f));
	sphere_2->addScale(glm::vec3(0.3f, 0.3f, 0.3f));
	sphere_2->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	sphere_2->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(sphere_2);

	Model* background_model = new Model(std::vector<float>(plain, plain + sizeof(plain) / sizeof(plain[0])));
	models.push_back(background_model);

	DrawableObject* background = new DrawableObject(camera);
	background->init_model(background_model);
	background->init_shader(shaderProgram_sphere);
	background->addTranslation(glm::vec3(0.f, 0.f, -1.f));
	background->addScale(glm::vec3(10.f, 10.f, 10.f));
	background->addRotation(90, glm::vec3(1.f, 0.f, 0.f));
	background->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	background->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(background);

}





void Scene::DrawScene(float deltaTime) {

	for (DrawableObject* object : objects)
	{
		object->Draw(deltaTime);
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
		CreateForestScene_blud(500, 1000);
	}
	else if (sceneId == 2) {
		CreateForestScene_bat(500, 1000);
	}
	else if (sceneId == 3) {
		CreateFourShaderLightsScene();
	}
	else if (sceneId == 4) {
		CreateMultipleLightsScene();
	}
}