#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/GraphicsDeviceObject.h>
namespace Portakal
{
	/// <summary>
	/// Required information to create commitable resource table
	/// </summary>
	struct PORTAKAL_API ResourceTableCreateDesc
	{
		/// <summary>
		/// The resources
		/// </summary>
		Array<GraphicsDeviceObject*> Buffers;
		Array<GraphicsDeviceObject*> Textures;
		Array<GraphicsDeviceObject*> Samplers;
	};
}