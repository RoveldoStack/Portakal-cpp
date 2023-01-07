#pragma once
#include <Runtime/Graphics/BlendingStateDesc.h>
#include <Runtime/Graphics/DepthStencilStateDesc.h>
#include <Runtime/Graphics/RasterizerState.h>
#include <Runtime/Graphics/MeshTopology.h>
#include <Runtime/Graphics/OutputDesc.h>
#include <Runtime/Graphics/InputLayoutDesc.h>
#include <Runtime/Graphics/ResourceStateDesc.h>

namespace Portakal
{
	class Shader;

	struct PORTAKAL_API GraphicsPipelineCreateDesc
	{
		BlendingStateDesc BlendingState;
		DepthStencilStateDesc DepthStencilState;
		RasterizerStateDesc RasterizerState;
		MeshTopology MeshTopology;
		Array<Shader*> Shaders;
		InputLayoutDesc InputLayout;
		ResourceStateDesc ResourceState;
		OutputDesc OutputDesc;

	};
}