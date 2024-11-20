#pragma once
#include "Model.h"
#include "Texture.h"

class TexturedModel : public Model
{
public:
    TexturedModel(const std::vector<float>& vertices, Texture* texture, float tex_scale = 1.0, int is_skybox = 0);
	
	void init_skybox(const std::vector<float>& vertices);
    void draw_model() override;
	float getScale();
	int getUnitID();
private:
    Texture* texture;
	float tex_scale;

	void init_model(const std::vector<float>& verticies) override;
};


