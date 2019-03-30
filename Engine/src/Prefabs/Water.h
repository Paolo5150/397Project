#pragma once
#include "..\GameObject\Component.h"
#include "..\Components\MeshRenderer.h"

#include "..\Graphics\Layers.h"
#include "..\Graphics\FrameBuffer.h"
#include "..\Core\CameraPerspective.h"



class Water : public GameObject
{
public:

	Water(Texture2D* normalMap, Texture2D* distortion);
	Water();

	~Water();
	void Update() override;
	FrameBuffer* refractionBuffer;
	FrameBuffer* reflectionBuffer;
	CameraPerspective* mainCamera;
	void OnPreRender(Camera& camera, Shader* currentShader = nullptr) ;

private:
	bool ResizeFrameBuffers(Event* e);
	CameraPerspective* waterCamera;
	MeshRenderer* meshRenderer;
	Material* material;
	float timer;
	void Initialize(Texture2D* normalMap = nullptr, Texture2D* distortion = nullptr);



};

