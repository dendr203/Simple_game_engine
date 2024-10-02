#pragma once
#include "Model.h"



class Square : public Model
{
public:
	Square();

	void Init(const char* vertex_shader, const char* fragment_shader) override;


private:
	float points[18];
	int size = 18 * sizeof(float);

};

