#include "Collider.h"

void Collider::EngineUpdate()
{
	if (enableRender)
	{
		meshRenderer->EngineUpdate();
	}

	transform.Update();
}

void Collider::OnAttach(GameObject* go)
{
	InitializeMeshRenderer();
	transform.parent = &go->transform;
	meshRenderer->transform = &transform;
	meshRenderer->SetParent(go);

	meshRenderer->AddPreRenderCallback([](Camera& cam, Shader* s){		
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);	
	});


	meshRenderer->AddPostRenderCallback([](Camera& cam, Shader* s){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
	});
}

