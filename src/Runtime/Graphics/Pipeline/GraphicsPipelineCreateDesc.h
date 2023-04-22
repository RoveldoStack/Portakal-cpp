#pragma once
#include <Runtime/Graphics/Pipeline/Blending/BlendingStateDesc.h>
#include <Runtime/Graphics/Pipeline/DepthStencil/DepthStencilStateDesc.h>
#include <Runtime/Graphics/Pipeline/Rasterizer/RasterizerStateDesc.h>
#include <Runtime/Graphics/Pipeline/Rasterizer/MeshTopology.h>
#include <Runtime/Graphics/Pipeline/Output/OutputDesc.h>
#include <Runtime/Graphics/Pipeline/Input/InputLayoutDesc.h>
#include <Runtime/Graphics/Pipeline/Resource/ResourceStateDesc.h>

namespace Portakal
{
	class Shader;

	/// <summary>
	/// Required information to create graphics pipeline
	/// </summary>
	struct PORTAKAL_API GraphicsPipelineCreateDesc
	{
		/// <summary>
		/// The blending state
		/// </summary>
		BlendingStateDesc BlendingState;

		/// <summary>
		/// The depth stencil state
		/// </summary>
		DepthStencilStateDesc DepthStencilState;

		/// <summary>
		/// The rasterizer state
		/// </summary>
		RasterizerStateDesc RasterizerState;

		/// <summary>
		/// Mesh topology of the input
		/// </summary>
		MeshTopology MeshTopology;

		/// <summary>
		/// The shader set
		/// </summary>
		Array<Shader*> Shaders;

		/// <summary>
		/// Input layout of the vertex buffer
		/// </summary>
		InputLayoutDesc InputLayout;

		/// <summary>
		/// The resource state 
		/// </summary>
		ResourceStateDesc ResourceState;

		/// <summary>
		/// The output description
		/// </summary>
		OutputDesc OutputDesc;
	};
}