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