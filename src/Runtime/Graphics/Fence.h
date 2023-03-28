#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/GraphicsDeviceObject.h>
namespace Portakal
{
	class PORTAKAL_API Fence : public GraphicsDeviceObject
	{
	public:
		// Inherited via GraphicsDeviceObject
		virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override { return GraphicsDeviceObjectType::Fence; }
		virtual void OnDestroy() override;

	};
}