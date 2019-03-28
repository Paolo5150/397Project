#pragma once
#include "..\GameObject\Component.h"
#include "..\Components\MeshRenderer.h"

#include "..\Graphics\Layers.h"
#include "..\Graphics\FrameBuffer.h"
#include "..\Core\CameraPerspective.h"



class Water : public GameObject
{
public:
	static float heightPlane;
	static int heightPlaneActive;
	Water(Texture2D* normalMap, Texture2D* distortion);
	~Water();
	void Update() override;
	FrameBuffer* refractionBuffer;
	FrameBuffer* reflectionBuffer;
	CameraPerspective* mainCamera;
	void OnPreRender(Camera& camera, Shader* currentShader = nullptr) override;

private:

	CameraPerspective* waterCamera;
	MeshRenderer* meshRenderer;
	Material* material;
	float timer;



};

