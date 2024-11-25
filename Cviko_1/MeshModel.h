#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Model.h"
#include "Texture.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TextureCoords;
    glm::vec3 Tangent;
};


class MeshModel : public Model
{
public:
	MeshModel(const std::string& filename, Texture* texture, float tex_scale);
	~MeshModel();

	void draw_model() override;
	float getScale();
	int getUnitID();

private:
	Texture* texture;
	float tex_scale;
};

