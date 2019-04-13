#include "LineRenderer.h"
#include "..\Core\Core.h"
#include "..\Utils\AssetLoader.h"
#include "..\Core\Camera.h"



LineRenderer::~LineRenderer()
{

	delete vertexArray;
	delete vertexBuffer;

}
LineRenderer::LineRenderer(std::vector<Vertex> verts) : Renderer("LineRenderer"), vertices(verts)
{
	vertexArray = Core::Instance().GetGraphicsAPI().CreateVertexArray();
	vertexBuffer = Core::Instance().GetGraphicsAPI().CreateVertexBuffer();

	Material m;
	m.SetShader(AssetLoader::Instance().GetAsset<Shader>("ColorOnly"));

	SetMaterial(m);
	SetMaterial(m, NOLIGHT);
	SetMaterial(m, COLORONLY);

	Initialize();

}

void LineRenderer::SetColor(float r, float g, float b)
{
	GetMaterial().SetColor(r, g, b);
	GetMaterial(NOLIGHT).SetColor(r, g, b);
	GetMaterial(COLORONLY).SetColor(r, g, b);

}


void LineRenderer::OnPreRender(Camera& cam, Shader* currentShader )
{
	//Logger::LogError("Line renderer");
	glm::mat4 mvp = cam.GetProjectionMatrix() * cam.GetViewMatrix() * _parent->transform.GetMatrix();
	Shader::GetCurrentShader().SetMat4("u_mvp", mvp);
	Shader::GetCurrentShader().SetMat4("u_model", _parent->transform.GetMatrix());
	Shader::GetCurrentShader().SetMat4("u_view", cam.GetViewMatrix());
	Shader::GetCurrentShader().SetMat4("u_projection", cam.GetProjectionMatrix());
}


void LineRenderer::Initialize()
{

	vertexArray->Bind();

	SetVertices(vertices);


	//Position
	vertexArray->AddLayoutf(0, 3, false, sizeof(Vertex), 0);

	vertexArray->Unbind();
}

void LineRenderer::SetVertices(std::vector<Vertex> verts)
{
	vertices = verts;
	vertexBuffer->AddData(vertices);

}


void LineRenderer::Render(Camera& cam)
{
	vertexArray->RenderArrayLines(vertices.size());

}