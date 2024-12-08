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



//Daylight forrest scene
void Scene::CreateForestScene_blud(int numTrees, int numBushes)
{
	CreateSkybox();

	camera->setCamera(glm::vec3(6.f, 5.f, 7.f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.10f,
		60.0f, -130.f, -30.f, 0.08f);


	SpotLight* spotlight_1 = new SpotLight(0, glm::vec3(-5.0f, +50.0f, -5.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 5.f, 10.f);
	lights.push_back(spotlight_1);


	DirectionalLight* dir_light = new DirectionalLight(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	lights.push_back(dir_light);
	

	PointLight* blud_1 = new PointLight(glm::vec3(-10.f, 1.f, -10.f), glm::vec3(1.f, 1.f, 1.f), 0.1f, 0.3f, 0.032f);
	PointLight* blud_2 = new PointLight(glm::vec3(-10.f, 1.f, 10.f), glm::vec3(1.f, 1.f, 1.f), 0.1f, 0.3f, 0.032f);
	PointLight* blud_3 = new PointLight(glm::vec3(10.f, 1.f, 10.f), glm::vec3(1.f, 1.f, 1.f), 0.1f, 0.3f, 0.032f);
	PointLight* blud_4 = new PointLight(glm::vec3(10.f, 1.f, -10.f), glm::vec3(1.f, 1.f, 1.f), 0.1f, 0.3f, 0.032f);
	PointLight* blud_5 = new PointLight(glm::vec3(5.f, 1.f, 5.f), glm::vec3(1.f, 1.f, 1.f), 0.1f, 0.3f, 0.032f);
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


	
	//tree, bush plain
	ShaderProgram* shaderProgram = new ShaderProgram(camera);
	shaderProgram->addLight(spotlight_1);
	shaderProgram->addLight(blud_1);
	shaderProgram->addLight(blud_2);
	shaderProgram->addLight(blud_3);
	shaderProgram->addLight(blud_4);
	shaderProgram->addLight(blud_5);
	shaderProgram->addLight(dir_light);
	shaderProgram->init_shader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	camera->addObserver(shaderProgram);
	shaderPrograms.push_back(shaderProgram);


	//plain
	Texture* plain_texture = new Texture("Textures/grass.png", GL_TEXTURE1);
	textures.push_back(plain_texture);

	MeshModel* plain_model = new MeshModel("Models/teren.obj", plain_texture, 1);
	models.push_back(plain_model);
	
	DrawableObject* plain = new DrawableObject(nullptr, true);
	plain->init_model(plain_model);
	plain->init_shader(shaderProgram);
	//plain->addScale(glm::vec3(30, 30, 30));
	plain->setColor(glm::vec4(1.f, 1.f, 1.f, 1.0f));
	plain->setMaterial(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.01f, 0.01f, 0.01f), 32.0f);
	objects.push_back(plain);



	//tree
	Texture* tree_texture = new Texture("Textures/tree.png", GL_TEXTURE2);
	textures.push_back(tree_texture);

	MeshModel* tree_model = new MeshModel("Models/tree.obj", tree_texture, 1);
	models.push_back(tree_model);


	//bushes
	Model* bush_model = new Model(std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(bushes[0])));
	models.push_back(bush_model);



	for (int i = 0; i < numTrees; ++i) {
		DrawableObject* tree = new DrawableObject();
		tree->init_model(tree_model);
		tree->init_shader(shaderProgram);
		RandomTransform(tree, 100.f);
		tree->setColor(glm::vec4(1.0f, 1.f, 1.f, 1.0f));
		tree->setMaterial(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f), 32.0f);
		objects.push_back(tree);
		if (i % 3 == 0)
		{
			tree->addDynamicRotation(45.f, glm::vec3(0.f, 1.f, 0.f));
		}
	}

	for (int i = 0; i < numBushes; ++i) {
		DrawableObject* bush = new DrawableObject();
		bush->init_model(bush_model);
		bush->init_shader(shaderProgram);
		RandomTransform(bush, 5.f);
		bush->setColor(glm::vec4(0.0f, 1.f, 0.f, 1.0f));
		bush->setMaterial(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f), 32.0f);
		objects.push_back(bush);
	}




	Texture* house_texture = new Texture("Textures/house.png", GL_TEXTURE3);
	textures.push_back(house_texture);

	MeshModel* house_model = new MeshModel("Models/house.obj", house_texture, 1);
	models.push_back(house_model);

	DrawableObject* house = new DrawableObject();
	house->init_model(house_model);
	house->init_shader(shaderProgram);
	house->setColor(glm::vec4(1.f, 1.f, 1.f, 1.0f));
	house->addTranslation(glm::vec3(-5.f, 0.f, -5.f));
	house->addScale(glm::vec3(0.7f, 0.7f, 0.7f));
	house->addRotation(45.f, glm::vec3(0.f, 1.f, 0.f));
	//house->addDynamicRotation(45.f, glm::vec3(0.f, 1.f, 0.f));
	//house->setMaterial(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f), 32.0f);
	objects.push_back(house);



	Texture* zombie_texture = new Texture("Textures/zombie.png", GL_TEXTURE4);
	textures.push_back(zombie_texture);

	MeshModel* zombie_model = new MeshModel("Models/zombie.obj", zombie_texture, 1);
	models.push_back(zombie_model);


	glm::mat4x3 controlPoints = glm::mat4x3(
		glm::vec3(-5.0f, 0.0f, 0.0f), 
		glm::vec3(-1.5f, 0.0f, 5.0f),
		glm::vec3(1.5f, 0.0f, -5.0f),
		glm::vec3(5.0f, 0.0f, 0.0f)
	);

	BezierCurve* bezierCurve = new BezierCurve(controlPoints, 0.25f);

	DrawableObject* zombie = new DrawableObject(bezierCurve);
	zombie->init_model(zombie_model);
	zombie->init_shader(shaderProgram);
	zombie->addTranslation(glm::vec3(25.f, 0.f, 0.f));
	zombie->setColor(glm::vec4(1.f, 1.f, 1.f, 1.0f));
	//zombie->addDynamicRotation(45.f, glm::vec3(0.f, 1.f, 0.f));
	//zombie->setMaterial(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f), 32.0f);
	objects.push_back(zombie);


	Texture* login_texture = new Texture("Textures/wooden_fence.png", GL_TEXTURE5);
	textures.push_back(login_texture);

	MeshModel* login_model = new MeshModel("Models/login_final.obj", login_texture, 1);
	models.push_back(login_model);

	DrawableObject* login_object = new DrawableObject();
	login_object->init_model(login_model);
	login_object->init_shader(shaderProgram);
	login_object->addTranslation(glm::vec3(15.f, 5.f, 0.f));
	login_object->setColor(glm::vec4(1.f, 1.f, 1.f, 1.0f));
	login_object->setMaterial(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f), 32.0f);
	objects.push_back(login_object);


	Texture* mario_texture = new Texture("Textures/Mario.png", GL_TEXTURE6);
	textures.push_back(mario_texture);

	MeshModel* mario_model = new MeshModel("Models/mario.obj", mario_texture, 1);
	models.push_back(mario_model);

	DrawableObject* mario_object = new DrawableObject();
	mario_object->init_model(mario_model);
	mario_object->init_shader(shaderProgram);
	mario_object->addTranslation(glm::vec3(30.f, 0.f, -10.f));
	mario_object->setColor(glm::vec4(1.f, 1.f, 1.f, 1.0f));
	mario_object->addDynamicRotation(5, glm::vec3(0.f, 1.f, 0.f));
	mario_object->setMaterial(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.9f, 0.9f, 0.9f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
	objects.push_back(mario_object);


}

void Scene::RandomTransform(DrawableObject* object, float scale_base) {


	float x = (rand() % 500 - 250) / 10.0f;
	float z = static_cast<float>(rand() % 500 - 250) / 10.0f;
	object->addTranslation(glm::vec3(x, 0, z));



	// Random scale
	float scale = static_cast<float>(rand() % 25 + 1) / scale_base;
	object->addScale(glm::vec3(scale, scale, scale));


}


//Dark forrest scene
void Scene::CreateForestScene_bat(int numTrees, int numBushes)
{
	camera->setCamera(glm::vec3(6.f, 5.f, 7.f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.05f,
		60.0f, -130.f, -30.f, 0.08f);


	glm::mat4x3 controlPoints = glm::mat4x3(
		glm::vec3(-25.0f, 5.0f, 0.0f),
		glm::vec3(-11.5f, 5.0f, 25.0f),
		glm::vec3(11.5f, 5.0f, -25.0f),
		glm::vec3(25.0f, 5.0f, 0.0f)
	);

	BezierCurve* bezierCurve = new BezierCurve(controlPoints, 0.001f);

	SpotLight* spotlight = new SpotLight(0, glm::vec3(10.0f, 10.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 1.0f, .0f), 20.f, 40.f, bezierCurve);
	lights.push_back(spotlight);

	SpotLight* battery = new SpotLight(1, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 15.f, 30.f);
	lights.push_back(battery);


	//tree, bush plain
	ShaderProgram* shaderProgram = new ShaderProgram(camera);
	shaderProgram->addLight(spotlight);
	shaderProgram->addLight(battery);
	shaderProgram->init_shader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	camera->addObserver(shaderProgram);
	shaderPrograms.push_back(shaderProgram);


	//plain
	Texture* plain_texture = new Texture("Textures/grass.png", GL_TEXTURE1);
	textures.push_back(plain_texture);

	MeshModel* plain_model = new MeshModel("Models/teren.obj", plain_texture, 1);
	models.push_back(plain_model);

	DrawableObject* plain = new DrawableObject(nullptr, true);
	plain->init_model(plain_model);
	plain->init_shader(shaderProgram);
	plain->setColor(glm::vec4(1.f, 1.f, 1.f, 1.0f));
	plain->setMaterial(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.01f, 0.01f, 0.01f), 32.0f);
	objects.push_back(plain);




	//light
	ShaderProgram* shaderProgram_light = new ShaderProgram(camera);
	shaderProgram_light->addLight(spotlight);
	shaderProgram_light->init_shader("Shaders/vertex.glsl", "Shaders/constant_fragment.glsl");
	camera->addObserver(shaderProgram_light);
	shaderPrograms.push_back(shaderProgram_light);

	Model* sphere_model = new Model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));
	models.push_back(sphere_model);

	DrawableObject* light_sphere = new DrawableObject(bezierCurve);
	light_sphere->init_model(sphere_model);
	light_sphere->init_shader(shaderProgram_light);
	light_sphere->addScale(glm::vec3(0.5f, 0.5f, 0.5f));
	light_sphere->setColor(glm::vec4(spotlight->getColor().x, spotlight->getColor().y, spotlight->getColor().z, 1.0f));
	light_sphere->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 32.0f);
	objects.push_back(light_sphere);




	//tree
	Texture* tree_texture = new Texture("Textures/tree.png", GL_TEXTURE2);
	textures.push_back(tree_texture);

	MeshModel* tree_model = new MeshModel("Models/tree.obj", tree_texture, 1);
	models.push_back(tree_model);


	//bushes
	Model* bush_model = new Model(std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(bushes[0])));
	models.push_back(bush_model);



	for (int i = 0; i < numTrees; ++i) {
		DrawableObject* tree = new DrawableObject();
		tree->init_model(tree_model);
		tree->init_shader(shaderProgram);
		RandomTransform(tree, 100.f);
		tree->setColor(glm::vec4(1.0f, 1.f, 1.f, 1.0f));
		tree->setMaterial(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
		objects.push_back(tree);
		if (i % 3 == 0)
		{
			tree->addDynamicRotation(45.f, glm::vec3(0.f, 1.f, 0.f));
		}
	}

	for (int i = 0; i < numBushes; ++i) {
		DrawableObject* bush = new DrawableObject();
		bush->init_model(bush_model);
		bush->init_shader(shaderProgram);
		RandomTransform(bush, 5.f);
		bush->setColor(glm::vec4(0.0f, 1.f, 0.f, 1.0f));
		bush->setMaterial(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
		objects.push_back(bush);
	}




	Texture* house_texture = new Texture("Textures/house.png", GL_TEXTURE3);
	textures.push_back(house_texture);

	MeshModel* house_model = new MeshModel("Models/house.obj", house_texture, 1);
	models.push_back(house_model);

	DrawableObject* house = new DrawableObject();
	house->init_model(house_model);
	house->init_shader(shaderProgram);
	house->setColor(glm::vec4(1.f, 1.f, 1.f, 1.0f));
	house->addTranslation(glm::vec3(-5.f, 0.f, -5.f));
	house->addScale(glm::vec3(0.7f, 0.7f, 0.7f));
	house->addRotation(45.f, glm::vec3(0.f, 1.f, 0.f));
	//house->addDynamicRotation(45.f, glm::vec3(0.f, 1.f, 0.f));
	house->setMaterial(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f), 32.0f);
	objects.push_back(house);
}


//marios
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
	shaderPrograms.push_back(shaderProgram_light);


	DrawableObject* light_sphere_1 = new DrawableObject();
	light_sphere_1->init_model(sphere_model);
	light_sphere_1->init_shader(shaderProgram_light);
	light_sphere_1->addTranslation(glm::vec3(pointlight->getPosition().x, pointlight->getPosition().y, pointlight->getPosition().z));
	light_sphere_1->addScale(glm::vec3(0.01f, 0.01f, 0.01f));
	light_sphere_1->setColor(glm::vec4(pointlight->getColor().x, pointlight->getColor().y, pointlight->getColor().z, 1.0f));
	light_sphere_1->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(light_sphere_1);



	
	

	Texture* mario_texture = new Texture("Textures/Mario.png", GL_TEXTURE1);
	textures.push_back(mario_texture);

	MeshModel* mario_model = new MeshModel("Models/mario.obj", mario_texture, 1);
	models.push_back(mario_model);


	

	DrawableObject* mario_object = new DrawableObject();
	mario_object->init_model(mario_model);
	mario_object->init_shader(shaderProgram_light);
	mario_object->addTranslation(glm::vec3(-0.4f, 0.f, 0.f));
	mario_object->setColor(glm::vec4(1.f, 1.f, 1.f, 1.0f));
	mario_object->addScale(glm::vec3(0.03f, 0.03f, 0.03f));
	mario_object->addDynamicRotation(5, glm::vec3(0.f, 1.f, 0.f));
	mario_object->setMaterial(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
	objects.push_back(mario_object);


	ShaderProgram* shaderProgram_lambert = new ShaderProgram(camera);
	shaderProgram_lambert->addLight(pointlight);
	shaderProgram_lambert->init_shader("Shaders/vertex.glsl", "Shaders/lambert_fragment.glsl");
	camera->addObserver(shaderProgram_lambert);
	shaderPrograms.push_back(shaderProgram_lambert);

	DrawableObject* mario_object_1 = new DrawableObject();
	mario_object_1->init_model(mario_model);
	mario_object_1->init_shader(shaderProgram_lambert);
	mario_object_1->addTranslation(glm::vec3(-0.15f, 0.f, 0.f));
	mario_object_1->setColor(glm::vec4(1.f, 1.f, 1.f, 1.0f));
	mario_object_1->addScale(glm::vec3(0.03f, 0.03f, 0.03f));
	mario_object_1->addDynamicRotation(5, glm::vec3(0.f, 1.f, 0.f));
	mario_object_1->setMaterial(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
	objects.push_back(mario_object_1);
	


	ShaderProgram* shaderProgram_phong = new ShaderProgram(camera);
	shaderProgram_phong->addLight(pointlight);
	shaderProgram_phong->init_shader("Shaders/vertex.glsl", "Shaders/phong_fragment.glsl");
	camera->addObserver(shaderProgram_phong);
	shaderPrograms.push_back(shaderProgram_phong);

	DrawableObject* mario_object_2 = new DrawableObject();
	mario_object_2->init_model(mario_model);
	mario_object_2->init_shader(shaderProgram_phong);
	mario_object_2->addTranslation(glm::vec3(0.05f, 0.f, 0.f));
	mario_object_2->setColor(glm::vec4(1.f, 1.f, 1.f, 1.0f));
	mario_object_2->addScale(glm::vec3(0.03f, 0.03f, 0.03f));
	mario_object_2->addDynamicRotation(5, glm::vec3(0.f, 1.f, 0.f));
	mario_object_2->setMaterial(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
	objects.push_back(mario_object_2);



	ShaderProgram* shaderProgram_blin = new ShaderProgram(camera);
	shaderProgram_blin->addLight(pointlight);
	shaderProgram_blin->init_shader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	camera->addObserver(shaderProgram_blin);
	shaderPrograms.push_back(shaderProgram_blin);

	DrawableObject* mario_object_3 = new DrawableObject();
	mario_object_3->init_model(mario_model);
	mario_object_3->init_shader(shaderProgram_blin);
	mario_object_3->addTranslation(glm::vec3(0.3f, 0.f, 0.f));
	mario_object_3->setColor(glm::vec4(1.f, 1.f, 1.f, 1.0f));
	mario_object_3->addScale(glm::vec3(0.03f, 0.03f, 0.03f));
	mario_object_3->addDynamicRotation(5, glm::vec3(0.f, 1.f, 0.f));
	mario_object_3->setMaterial(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
	objects.push_back(mario_object_3);

}

//koule
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
	shaderPrograms.push_back(shaderProgram_light);

	DrawableObject* light_sphere_red = new DrawableObject();
	light_sphere_red->init_model(sphere_model);
	light_sphere_red->init_shader(shaderProgram_light);
	light_sphere_red->addTranslation(glm::vec3(spotlight_red->getPosition().x, spotlight_red->getPosition().y, spotlight_red->getPosition().z));
	light_sphere_red->addScale(glm::vec3(0.1f, 0.1f, 0.1f));
	light_sphere_red->setColor(glm::vec4(spotlight_red->getColor().x, spotlight_red->getColor().y, spotlight_red->getColor().z, 1.0f));
	light_sphere_red->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(light_sphere_red);
	

	DrawableObject* light_sphere_white = new DrawableObject();
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
	shaderPrograms.push_back(shaderProgram_sphere);

	DrawableObject* sphere_1 = new DrawableObject();
	sphere_1->init_model(sphere_model);
	sphere_1->init_shader(shaderProgram_sphere);
	sphere_1->addTranslation(glm::vec3(0.8f, 0.f, -0.5f));
	sphere_1->addScale(glm::vec3(0.3f, 0.3f, 0.3f));
	sphere_1->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	sphere_1->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(sphere_1);

	DrawableObject* sphere_2 = new DrawableObject();
	sphere_2->init_model(sphere_model);
	sphere_2->init_shader(shaderProgram_sphere);
	sphere_2->addTranslation(glm::vec3(-0.8f, 0.f, -0.5f));
	sphere_2->addScale(glm::vec3(0.3f, 0.3f, 0.3f));
	sphere_2->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	sphere_2->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(sphere_2);

	Model* background_model = new Model(std::vector<float>(plain, plain + sizeof(plain) / sizeof(plain[0])));
	models.push_back(background_model);

	DrawableObject* background = new DrawableObject();
	background->init_model(background_model);
	background->init_shader(shaderProgram_sphere);
	background->addTranslation(glm::vec3(0.f, 0.f, -1.f));
	background->addScale(glm::vec3(10.f, 10.f, 10.f));
	background->addRotation(90, glm::vec3(1.f, 0.f, 0.f));
	background->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	background->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f);
	objects.push_back(background);

}


void Scene::CreateTexturedScene()
{
	CreateSkybox();

	camera->setCamera(glm::vec3(0.f, 0.f, 2.f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
		0.1f, 45.0, -90.f, 0.f, 0.1f);

	SpotLight* spotlight_white = new SpotLight(0, glm::vec3(0.f, 0.f, 2.f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 30.f, 35.f);
	lights.push_back(spotlight_white);

	ShaderProgram* shaderProgram = new ShaderProgram(camera);
	shaderProgram->addLight(spotlight_white);
	shaderProgram->init_shader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	camera->addObserver(shaderProgram);
	shaderPrograms.push_back(shaderProgram);


	Texture* texture = new Texture("Textures/wooden_fence.png", GL_TEXTURE1);
	textures.push_back(texture);
	TexturedModel* tex_model = new TexturedModel(std::vector<float>(plain_textured, plain_textured + sizeof(plain_textured) / sizeof(plain_textured[0])), texture);
	models.push_back(tex_model);

	DrawableObject* textured_object = new DrawableObject();
	textured_object->init_model(tex_model);
	textured_object->init_shader(shaderProgram);
	textured_object->addTranslation(glm::vec3(-2.f, 0.f, -1.f));
	textured_object->addScale(glm::vec3(1.f, 1.f, 1.f));
	textured_object->addRotation(90, glm::vec3(0.f, -1.f, 0.f));
	textured_object->addRotation(90, glm::vec3(0.f, 0.f, -1.f));
	textured_object->addDynamicRotation(10, glm::vec3(0.f, -1.f, 0.f));
	textured_object->setColor(glm::vec4(1, 1, 1, 1.0));
	textured_object->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
	objects.push_back(textured_object);


	Texture* texture_2 = new Texture("Textures/grass.png", GL_TEXTURE2);
	textures.push_back(texture_2);
	TexturedModel* tex_model_2 = new TexturedModel(std::vector<float>(plain_textured, plain_textured + sizeof(plain_textured) / sizeof(plain_textured[0])), texture_2);
	models.push_back(tex_model_2);

	DrawableObject* textured_object_2 = new DrawableObject();
	textured_object_2->init_model(tex_model_2);
	textured_object_2->init_shader(shaderProgram);
	textured_object_2->addTranslation(glm::vec3(2.f, 0.f, -1.f));
	textured_object_2->addScale(glm::vec3(1.f, 1.f, 1.f));
	textured_object_2->addRotation(90, glm::vec3(0.f, -1.f, 0.f));
	textured_object_2->addRotation(90, glm::vec3(0.f, 0.f, -1.f));
	textured_object_2->addDynamicRotation(10, glm::vec3(0.f, 1.f, 0.f));
	textured_object_2->setColor(glm::vec4(1, 1, 1, 1.0));
	textured_object_2->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
	objects.push_back(textured_object_2);



	Model* background_model = new Model(std::vector<float>(plain, plain + sizeof(plain) / sizeof(plain[0])));
	models.push_back(background_model);

	DrawableObject* background = new DrawableObject();
	background->init_model(background_model);
	background->init_shader(shaderProgram);
	background->addTranslation(glm::vec3(0.f, 0.f, -3.f));
	background->addScale(glm::vec3(5.f, 5.f, 5.f));
	background->addRotation(90, glm::vec3(1.f, 0.f, 0.f));
	background->setColor(glm::vec4(0.385, 0.647, 0.812, 1.0));
	background->setMaterial(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.2f, 0.2f, 0.2f), 32.0f);
	objects.push_back(background);
	
}



void Scene::CreateSkybox()
{
	const float skycube[108] = {
		// Pøední stìna
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,

		// Zadní stìna
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		 // Levá stìna
		 -1.0f, -1.0f, -1.0f,
		 -1.0f, -1.0f,  1.0f,
		 -1.0f,  1.0f,  1.0f,
		 -1.0f, -1.0f, -1.0f,
		 -1.0f,  1.0f,  1.0f,
		 -1.0f,  1.0f, -1.0f,

		 // Pravá stìna
		  1.0f, -1.0f, -1.0f,
		  1.0f,  1.0f, -1.0f,
		  1.0f,  1.0f,  1.0f,
		  1.0f, -1.0f, -1.0f,
		  1.0f,  1.0f,  1.0f,
		  1.0f, -1.0f,  1.0f,

		  // Horní stìna
		  -1.0f,  1.0f, -1.0f,
		  -1.0f,  1.0f,  1.0f,
		   1.0f,  1.0f,  1.0f,
		  -1.0f,  1.0f, -1.0f,
		   1.0f,  1.0f,  1.0f,
		   1.0f,  1.0f, -1.0f,

		   // Spodní stìna
		   -1.0f, -1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
			1.0f, -1.0f,  1.0f,
		   -1.0f, -1.0f, -1.0f,
			1.0f, -1.0f,  1.0f,
		   -1.0f, -1.0f,  1.0f
	};



	ShaderProgram* shaderProgram_skybox = new ShaderProgram(camera);
	shaderProgram_skybox->init_shader("Shaders/skybox_vertex.glsl", "Shaders/skybox_fragment.glsl");
	camera->addObserver(shaderProgram_skybox);
	shaderPrograms.push_back(shaderProgram_skybox);


	Texture* skybox_texture = new Texture(
		"Textures/posx.jpg", "Textures/negx.jpg",
		"Textures/posy.jpg", "Textures/negy.jpg",
		"Textures/posz.jpg", "Textures/negz.jpg",
		 GL_TEXTURE0);
	textures.push_back(skybox_texture);
	
	TexturedModel* skybox_model = new TexturedModel(std::vector<float>(skycube, skycube + sizeof(skycube) / sizeof(skycube[0])), skybox_texture, 10, 1);
	models.push_back(skybox_model);


	DrawableObject* skybox = new DrawableObject();
	skybox->init_model(skybox_model, 1);
	skybox->init_shader(shaderProgram_skybox);
	objects.push_back(skybox);
}

void Scene::DrawSkybox(float deltaTime)
{
	for (DrawableObject* object : objects)
	{
		if (object->is_Skybox() == 1)
		{
			glDepthMask(GL_FALSE);						//zákaz zápisu do depth bufferu
			glDepthFunc(GL_LEQUAL);						//fragmenty projdou hloubkovým testem, pokud mají hloubku menší nebo rovnu aktuální hodnotì (vykreslí se na pozdají)
			object->DrawSkybox(skyboxFollowCamera);
			glDepthMask(GL_TRUE);
			glDepthFunc(GL_LESS);						//další objekty musí mít hloubku menší než maximum v depth bufferu
		}
	}
}

void Scene::DrawScene(float deltaTime)
{
	for (DrawableObject* object : objects)
	{
		if (object->is_Skybox() != 1)
		{
			glStencilFunc(GL_ALWAYS, object->getID(), 0xFF);
			object->Draw(deltaTime);
		}
	}
}


void Scene::ClearScene() {
	camera->clearLinkShaders();
	lights.clear();

	
	for (Model* model : models) {
		delete model;
	}
	models.clear();

	for (Texture* texture : textures) {
		delete texture;
	}
	textures.clear();
	
	
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
		CreateForestScene_blud(50, 50);
	}
	else if (sceneId == 2) {
		CreateForestScene_bat(50, 50);
	}
	else if (sceneId == 3) {
		CreateFourShaderLightsScene();
	}
	else if (sceneId == 4) {
		CreateMultipleLightsScene();
	}
	else if (sceneId == 5)
	{
		CreateTexturedScene();
	}
}

void Scene::DeleteSelectedOBJ(int id) {
	for (int i = 0; i < objects.size(); ++i) {
		if (objects[i]->getID() == id) {
			objects.erase(objects.begin() + i);
			break;
		}
	}
}

void Scene::addTree(const glm::vec3& position) {
	
	ShaderProgram* shaderProgram = new ShaderProgram(camera);
	for(Light* light : lights)
	{
		shaderProgram->addLight(light);
	}
	shaderProgram->init_shader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	camera->addObserver(shaderProgram);
	shaderPrograms.push_back(shaderProgram);

	
	Texture* tree_texture = new Texture("Textures/tree.png", GL_TEXTURE10);
	textures.push_back(tree_texture);

	MeshModel* tree_model = new MeshModel("Models/tree.obj", tree_texture, 1);
	models.push_back(tree_model);




	DrawableObject* tree = new DrawableObject();
	tree->init_model(tree_model);
	tree->init_shader(shaderProgram);
	tree->addTranslation(position);

	// Random rotation
	float random_rotate = rand() % 360;
	tree->addRotation(random_rotate, glm::vec3(0.f, 1.f, 0.f));


	// Random scale
	float scale = static_cast<float>(rand() % 9 + 1) / 50;
	tree->addScale(glm::vec3(scale, scale, scale));


	tree->setColor(glm::vec4(1.f, 1.f, 1.f, 1.0f));
	tree->setMaterial(glm::vec3(0.01f, 0.01f, 0.01f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.1f, 0.1f, 0.1f), 32.0f);
	objects.push_back(tree);
}