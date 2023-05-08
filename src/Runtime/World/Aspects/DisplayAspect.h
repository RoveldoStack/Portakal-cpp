#pragma once
#include <Runtime/World/SceneAspect.h>

namespace Portakal
{
	class RenderTargetResource;
	PCLASS();
	class PORTAKAL_API DisplayAspect : public SceneAspect
	{
		GENERATE_CLASS(DisplayAspect);
	public:
		DisplayAspect() = default;
		~DisplayAspect() = default;

		FORCEINLINE RenderTargetResource* GetDefaultDisplay() const noexcept;
		FORCEINLINE RenderTargetResource* GetDisplay(const unsigned int index) const noexcept;
		FORCEINLINE Array<RenderTargetResource*> GetDisplays() const noexcept;

		void RegisterDisplay(RenderTargetResource* pTarget);
		void RemoveDisplay(RenderTargetResource* pTarget);
	private:
		virtual void OnInitialize() override;
		virtual void OnExecute() override;
		virtual void OnFinalize() override;
	private:
		Array<RenderTargetResource*> mDisplays;
	};


#include "DisplayAspect.reflect.h"
}