#include "Scene.h"

#include <cstdlib> // Pro rand()
#include <ctime>   // Pro srand()


//basic shader
const char* vertex_shader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"out vec3 frag_pos;"
"void main () {"
"     gl_Position = vec4 (vp, 1.0);"
"	  frag_pos = vp;"
"}";

const char* fragment_shader =
"#version 330\n"
"in vec3 frag_pos;"
"out vec4 frag_colour;"
"void main () {"
"	  vec3 color = (frag_pos + vec3(0.5));"
"     frag_colour = vec4 (color, 1.0);"
"}";


//colors
const char* vertex_shader_with_color =
"#version 330\n"
"layout(location=0) in vec4 position;\n"  // Pozice vrcholu
"layout(location=1) in vec4 color;\n"     // Barva vrcholu
"out vec4 vertex_color;\n"                // Pøeposíláme barvu do fragment shaderu
"void main () {\n"
"    gl_Position = position;\n"
"    vertex_color = color;\n"
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




//transformation
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

const char* fragment_shader_green =
"#version 330\n"
"out vec4 frag_colour;"
"void main () {"
"     frag_colour = vec4 (0.0, 0.9, 0.0, 1.0);"
"}";




//camera moovement
const char* vertex_shader_camera =
"#version 330\n"
"uniform mat4 modelMatrix;"
"uniform mat4 projectionMatrix;"
"uniform mat4 viewMatrix;"
"out vec3 vertexColor;"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 vn;"
"void main () {"
"     vertexColor=vn;"
"     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);"
"}";

const char* fragment_shader_camera =
"#version 330\n"
"out vec4 frag_colour;"
"in vec3 vertexColor;"
"void main () {"
"     frag_colour = vec4(vertexColor, 0.0);"
"}";




//constant idk dodìlat
const char* vertex_shader_light_constant =
"#version 400\n"

"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"

"layout(location = 0) in vec3 in_Position;"
"layout(location = 1) in vec3 in_Normal;"

"out vec4 ex_worldPosition;"
"out vec3 ex_worldNormal;"

"void main(void) {"
"	ex_worldPosition = modelMatrix * vec4(in_Position, 1.0f);"	//calculate world coordinates
"	mat4 normalMatrix = transpose(inverse(modelMatrix));"
"	ex_worldNormal = normalize(vec3(normalMatrix * vec4(in_Normal, 0.0)));" //calculate world normal in world coordinates
"	gl_Position = projectionMatrix * viewMatrix * ex_worldPosition;"
"}";


const char* fragment_shader_light_constant =
"#version 400\n"
"in vec4 ex_worldPosition;"
"in vec3 ex_worldNormal;"

"uniform vec3 lightColor;"
"uniform vec3 lightPosition;"
"uniform vec4 ambientLight;"

"out vec4 out_Color;"
"void main(void){"
"	vec3 lightDirection = lightPosition - vec3(ex_worldPosition);"

"	float dot_product = max(dot(normalize(lightDirection), normalize(ex_worldNormal)), 0.0);"
"	vec4 diffuse = dot_product * vec4(lightColor, 1.0);"	//better result

"	out_Color = vec4(0.385, 0.647, 0.812, 1.0);"
"}";




//lambert
const char* vertex_shader_light_lambert =
"#version 400\n"

"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"

"layout(location = 0) in vec3 in_Position;"
"layout(location = 1) in vec3 in_Normal;"

"out vec4 ex_worldPosition;"
"out vec3 ex_worldNormal;"

"void main(void) {"
"	ex_worldPosition = modelMatrix * vec4(in_Position, 1.0f);"	//calculate world coordinates
"	mat4 normalMatrix = transpose(inverse(modelMatrix));"		
"	ex_worldNormal = normalize(vec3(normalMatrix * vec4(in_Normal, 0.0)));" //calculate world normal in world coordinates
"	gl_Position = projectionMatrix * viewMatrix * ex_worldPosition;"
"}";

const char* fragment_shader_light_lambert =
"#version 400\n"
"in vec4 ex_worldPosition;"
"in vec3 ex_worldNormal;"

"uniform vec3 lightColor;"
"uniform vec3 lightPosition;"
"uniform vec4 ambientLight;"

"out vec4 out_Color;"
"void main(void){"
"	vec3 lightDirection = lightPosition - vec3(ex_worldPosition);"

"	float dot_product = max(dot(normalize(lightDirection), normalize(ex_worldNormal)), 0.0);"
"	vec4 diffuse = dot_product * vec4(lightColor, 1.0);"	//better result

"	vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);"
"	out_Color = (ambientLight + diffuse) * objectColor;"
"}";



//phong
const char* vertex_shader_light_phong =
"#version 400\n"

"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"uniform vec3 lightPosition;"

"layout(location = 0) in vec3 in_Position;"
"layout(location = 1) in vec3 in_Normal;"

"out vec4 ex_worldPosition;"
"out vec3 ex_worldNormal;"
"out vec3 ex_lightDirection;"
"out vec3 ex_viewDirection;"

"void main(void) {"
"   ex_worldPosition = modelMatrix * vec4(in_Position, 1.0f);"
"   mat4 normalMatrix = transpose(inverse(modelMatrix));"
"   ex_worldNormal = normalize(vec3(normalMatrix * vec4(in_Normal, 0.0)));"
"   gl_Position = projectionMatrix * viewMatrix * ex_worldPosition;"

"   ex_lightDirection = normalize(lightPosition - vec3(ex_worldPosition));"
"   vec3 cameraPosition = vec3(inverse(viewMatrix)[3]);" // Inver viewMatrix a get camera position
"   ex_viewDirection = normalize(cameraPosition - vec3(ex_worldPosition));"
"}";



const char* fragment_shader_light_phong =
"#version 400\n"
"in vec4 ex_worldPosition;"
"in vec3 ex_worldNormal;"
"in vec3 ex_lightDirection;"
"in vec3 ex_viewDirection;"

"uniform vec3 lightColor;"
"uniform vec4 ambientLight;"
"uniform float shininess;"

"out vec4 out_Color;"

"void main(void) {"
"   vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);"

	// Compute light direction and view direction
"   vec3 lightDir = normalize(ex_lightDirection);"
	// Diffuse light
"   float dot_product = max(dot(normalize(ex_worldNormal), ex_lightDirection), 0.0);"
"   vec4 diffuse = dot_product * vec4(lightColor, 1.0);"


"   vec3 reflectDir = normalize(reflect(-ex_lightDirection, normalize(ex_worldNormal)));"
	// Specular light
"   float spec = pow(max(dot(ex_viewDirection, reflectDir), 0.0), shininess);"
"   vec4 specular = vec4(lightColor, 1.0) * spec;"

"   out_Color = ambientLight + (diffuse * objectColor) + specular;"
"}";





//blinn-phong
const char* vertex_shader_light_blinn_phong =
"#version 400\n"

"uniform mat4 modelMatrix;"
"uniform mat4 viewMatrix;"
"uniform mat4 projectionMatrix;"
"uniform vec3 lightPosition;"

"layout(location = 0) in vec3 in_Position;"
"layout(location = 1) in vec3 in_Normal;"

"out vec4 ex_worldPosition;"
"out vec3 ex_worldNormal;"
"out vec3 ex_lightDirection;"
"out vec3 ex_viewDirection;"

"void main(void) {"
"   ex_worldPosition = modelMatrix * vec4(in_Position, 1.0f);"
"   mat4 normalMatrix = transpose(inverse(modelMatrix));"
"   ex_worldNormal = normalize(vec3(normalMatrix * vec4(in_Normal, 0.0)));"
"   gl_Position = projectionMatrix * viewMatrix * ex_worldPosition;"

"   ex_lightDirection = normalize(lightPosition - vec3(ex_worldPosition));"
"   vec3 cameraPosition = vec3(inverse(viewMatrix)[3]);" // Inver viewMatrix a get camera position
"   ex_viewDirection = normalize(cameraPosition - vec3(ex_worldPosition));"
"}";

const char* fragment_shader_light_blin_phong =
"#version 400\n"
"in vec4 ex_worldPosition;"
"in vec3 ex_worldNormal;"
"in vec3 ex_lightDirection;"
"in vec3 ex_viewDirection;"

"uniform vec3 lightColor;"
"uniform vec4 ambientLight;"
"uniform float shininess;"

"out vec4 out_Color;"

"void main(void) {"
"   vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);"

// Compute light direction and view direction
"   vec3 lightDir = normalize(ex_lightDirection);"
// Diffuse light
"   float dot_product = max(dot(normalize(ex_worldNormal), ex_lightDirection), 0.0);"
"   vec4 diffuse = dot_product * vec4(lightColor, 1.0);"

"	vec3 halfwayVec = normalize(ex_viewDirection + ex_lightDirection);"

"   vec3 reflectDir = normalize(reflect(-ex_lightDirection, normalize(ex_worldNormal)));"
// Specular light
"   float spec = pow(max(dot(ex_worldNormal, halfwayVec), 0.0), shininess);"
"   vec4 specular = vec4(lightColor, 1.0) * spec;"

"   out_Color = ambientLight + (diffuse * objectColor) + specular;"
"}";







Scene::Scene(Camera* _camera) : camera(_camera), shaderProgram(nullptr)
{
	srand(static_cast<unsigned int>(time(0)));
}

Scene::~Scene()
{
	delete& objects;
}

void Scene::CrateScene() {
	camera->setCamera(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.05, 45.0, -90.f, 0.f, 0.08f);

	Light* light = new Light(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 0);

	shaderProgram = new ShaderProgram(camera, light);
	shaderProgram->init_shader(vertex_shader_light_lambert, fragment_shader_light_lambert);
	camera->addObserver(shaderProgram);
	light->addObserver(shaderProgram);

	Model* sphere_model = new Model();
	sphere_model->init_model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));
	DrawableObject* object1 = new DrawableObject(camera);
	object1->init_model(sphere_model);
	object1->init_shader(shaderProgram);
	object1->translate(0.4f, -0.5f, 0.f);
	object1->scale(0.1f, 0.1f, 0.1f);
	object1->rotateAngle = 0.02f;
	object1->rotateX = 1.f;
	objects.push_back(object1);

	Model* tree_model = new Model();
	tree_model->init_model(std::vector<float>(tree, tree + sizeof(tree) / sizeof(tree[0])));
	DrawableObject* object2 = new DrawableObject(camera);
	object2->init_model(tree_model);
	object2->init_shader(shaderProgram);
	object2->translate(-0.4f, -0.8f, 0.f);
	object2->scale(0.3f, 0.3f, 0.3f);
	object2->rotateAngle = 0.05f;
	object2->rotateY = 1.f;
	objects.push_back(object2);

	Model* bush_model = new Model();
	bush_model->init_model(std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(bushes[0])));
	DrawableObject* object3 = new DrawableObject(camera);
	//object3->init_bushes();
	object3->init_model(bush_model);
	object3->init_shader(shaderProgram);
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

	shaderProgram->setMatrixUniform("projectionMatrix", camera->getProjectionMatrix());
}

void Scene::CreateForestScene(int numTrees, int numBushes) {
	camera->setCamera(glm::vec3(0.0f, 1.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.05, 45.0, -90.f, 0.f, 0.08f);

	Light* light = new Light(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 10);

	shaderProgram = new ShaderProgram(camera, light);
	shaderProgram->init_shader(vertex_shader_light_phong, fragment_shader_light_phong);
	camera->addObserver(shaderProgram);
	light->addObserver(shaderProgram);

	Model* plain_model = new Model();
	plain_model->init_model(std::vector<float>(plain, plain + sizeof(plain) / sizeof(plain[0])));

	Model* tree_model = new Model();
	tree_model->init_model(std::vector<float>(tree, tree + sizeof(tree) / sizeof(tree[0])));

	Model* bush_model = new Model();
	bush_model->init_model(std::vector<float>(bushes, bushes + sizeof(bushes) / sizeof(bushes[0])));

	//create plain here next for ground
	DrawableObject* plain = new DrawableObject(camera);
	plain->init_model(plain_model);
	plain->init_shader(shaderProgram);
	plain->scale(5, 5, 5);
	objects.push_back(plain);



	for (int i = 0; i < numTrees; ++i) {
		DrawableObject* tree = new DrawableObject(camera);
		tree->init_model(tree_model);
		tree->init_shader(shaderProgram);
		RandomTransform(tree, i);
		objects.push_back(tree);
	}

	for (int i = 0; i < numBushes; ++i) {
		DrawableObject* bush = new DrawableObject(camera);
		bush->init_model(bush_model);
		bush->init_shader(shaderProgram);
		RandomTransform(bush, i);
		objects.push_back(bush);
	}

	shaderProgram->setMatrixUniform("projectionMatrix", camera->getProjectionMatrix());
}

void Scene::CreateConstantTestScene()
{
	camera->setCamera(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.05f, 45.0, -90.0f, -90.0f, 0.08f);

	Light* light = new Light(glm::vec3(0.0f, 0.2f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 32);

	shaderProgram = new ShaderProgram(camera, light);
	shaderProgram->init_shader(vertex_shader_light_phong, fragment_shader_light_phong);
	camera->addObserver(shaderProgram);
	light->addObserver(shaderProgram);

	Model* sphere_model = new Model();
	sphere_model->init_model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));

	DrawableObject* sphere_1 = new DrawableObject(camera);
	sphere_1->init_model(sphere_model);
	sphere_1->init_shader(shaderProgram);
	sphere_1->translate(-0.3f, 0.f, 0.f);
	sphere_1->scale(0.1f, 0.1f, 0.1f);
	objects.push_back(sphere_1);

	DrawableObject* sphere_2 = new DrawableObject(camera);
	sphere_2->init_model(sphere_model);
	sphere_2->init_shader(shaderProgram);
	sphere_2->translate(0.3f, 0.f, 0.f);
	sphere_2->scale(0.1f, 0.1f, 0.1f);
	objects.push_back(sphere_2);

	DrawableObject* sphere_3 = new DrawableObject(camera);
	sphere_3->init_model(sphere_model);
	sphere_3->init_shader(shaderProgram);
	sphere_3->translate(0.f, 0.f, -0.3f);
	sphere_3->scale(0.1f, 0.1f, 0.1f);
	objects.push_back(sphere_3);

	DrawableObject* sphere_4 = new DrawableObject(camera);
	sphere_4->init_model(sphere_model);
	sphere_4->init_shader(shaderProgram);
	sphere_4->translate(0.f, 0.f, 0.3f);
	sphere_4->scale(0.1f, 0.1f, 0.1f);
	objects.push_back(sphere_4);


	shaderProgram->setMatrixUniform("projectionMatrix", camera->getProjectionMatrix());
}

void Scene::CreateFourShaderLightsScene()
{
	camera->setCamera(glm::vec3(-0.4f, 0.1f, 0.6f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.05f, 45.0, -60.0f, 0.f, 0.08f);
	Light* light = new Light(glm::vec3(-0.4f, 0.1f, 0.6f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.1f, 0.1f, 0.1f, 0.1f), 10);
	shaderProgram = new ShaderProgram(camera, light);


	Model* sphere_model = new Model();
	sphere_model->init_model(std::vector<float>(sphere, sphere + sizeof(sphere) / sizeof(sphere[0])));

	
	shaderProgram->init_shader(vertex_shader_light_blinn_phong, fragment_shader_light_blin_phong);
	camera->addObserver(shaderProgram);
	light->addObserver(shaderProgram);

	DrawableObject* light_sphere = new DrawableObject(camera);
	light_sphere->init_model(sphere_model);
	light_sphere->init_shader(shaderProgram);
	light_sphere->translate(-0.4f, 0.1f, 0.6f);
	light_sphere->scale(0.01f, 0.01f, 0.01f);
	objects.push_back(light_sphere);



	//ShaderProgram* shaderProgram_dva = new ShaderProgram(camera, light);
	//shaderProgram_dva->init_shader(vertex_shader_light_lambert, fragment_shader_light_lambert);
	//camera->addObserver(shaderProgram_dva);


	DrawableObject* sphere_1 = new DrawableObject(camera);
	sphere_1->init_model(sphere_model);
	sphere_1->init_shader(shaderProgram);
	sphere_1->translate(-0.35f, 0.f, 0.f);
	sphere_1->scale(0.1f, 0.1f, 0.1f);
	objects.push_back(sphere_1);

	DrawableObject* sphere_2 = new DrawableObject(camera);
	sphere_2->init_model(sphere_model);
	sphere_2->init_shader(shaderProgram);
	sphere_2->translate(-0.13f, 0.f, 0.f);
	sphere_2->scale(0.1f, 0.1f, 0.1f);
	objects.push_back(sphere_2);

	DrawableObject* sphere_3 = new DrawableObject(camera);
	sphere_3->init_model(sphere_model);
	sphere_3->init_shader(shaderProgram);
	sphere_3->translate(0.13f, 0.f, 0.f);
	sphere_3->scale(0.1f, 0.1f, 0.1f);
	objects.push_back(sphere_3);

	DrawableObject* sphere_4 = new DrawableObject(camera);
	sphere_4->init_model(sphere_model);
	sphere_4->init_shader(shaderProgram);
	sphere_4->translate(0.35f, 0.f, 0.f);
	sphere_4->scale(0.1f, 0.1f, 0.1f);
	objects.push_back(sphere_4);


	shaderProgram->setMatrixUniform("projectionMatrix", camera->getProjectionMatrix());
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
		objects[i]->Draw();
	}
}

void Scene::ClearScene() {
	for (DrawableObject* obj : objects) {
		delete obj;
	}
	objects.clear();
	camera->clearLinkShaders();


	for (Light* light : lights) {
		light->clearLinkShaders();
	}
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
		CreateConstantTestScene();
	}
	else if (sceneId == 4) {
		CreateFourShaderLightsScene();
	}
}