#include "Axis.h"

Axis::Axis() : GameObject("Axis")
{
	std::vector<Vertex> vsRight;
	vsRight.push_back(Vertex(0.8f, 0.8f, 0.0f));
	vsRight.push_back(Vertex(1.0f, 0.8, 0.0f));

	std::vector<Vertex> vsUp;
	vsUp.push_back(Vertex(0.8f, 0.8f, 0.0f));
	vsUp.push_back(Vertex(0.8f, 1.0f, 0.0f));

	std::vector<Vertex> vsFront;
	vsFront.push_back(Vertex(0.8f, 0.8f, 0.0f));
	vsFront.push_back(Vertex(0.8f, 0.8f, 1.0f));

	LineRenderer* lu = new LineRenderer(vsUp);
	lu->SetColor(0, 1, 0);
	LineRenderer* lr = new LineRenderer(vsRight);
	lr->SetColor(1, 0, 0);


	LineRenderer* lf = new LineRenderer(vsFront);
	lf->SetColor(0, 0, 1);


	AddComponent(lu);
	AddComponent(lr);
	AddComponent(lf);

}