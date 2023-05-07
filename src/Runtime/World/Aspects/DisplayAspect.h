#pragma once
#include <Runtime/World/SceneAspect.h>

namespace Portakal
{
	class RenderTarget;
	class PORTAKAL_API DisplayAspect : public SceneAspect
	{
		GENERATE_CLASS(DisplayAspect);
	public:
		DisplayAspect() = default;
		~DisplayAspect() = default;

		FORCEINLINE RenderTarget* GetDefaultDisplay() const noexcept;
		FORCEINLINE RenderTarget* GetDisplay(const unsigned int index) const noexcept;
		FORCEINLINE Array<RenderTarget*> GetDisplays() const noexcept;

		void RegisterDisplay(RenderTarget* pTarget);
		void RemoveDisplay(RenderTarget* pTarget);
	private:
		virtual void OnInitialize() override;
		virtual void OnExecute() override;
		virtual void OnFinalize() override;
	private:
		Array<RenderTarget*> mDisplays;
	};


#include "DisplayAspect.reflect.h"
}