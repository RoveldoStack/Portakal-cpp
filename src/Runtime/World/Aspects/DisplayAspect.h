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
		DisplayAspect() : mMaxDisplayCount(8) {}
		~DisplayAspect() = default;

		FORCEINLINE RenderTargetResource* GetDefaultDisplay() const noexcept;
		FORCEINLINE RenderTargetResource* GetDisplay(const unsigned int index) const noexcept;
		FORCEINLINE Array<RenderTargetResource*> GetDisplays() const noexcept;
		FORCEINLINE unsigned int GetMaxDisplayCount() const noexcept { return mMaxDisplayCount; }

		void SelectDisplay(const unsigned int index, RenderTargetResource* pRenderTarget);
		void RegisterDisplay(RenderTargetResource* pRenderTarget);
		void RemoveDisplay(RenderTargetResource* pRenderTarget);
	private:
		virtual void InitializeCore() override;
		virtual void ExecuteCore() override;
		virtual void FinalizeCore() override;
	private:
		const unsigned int mMaxDisplayCount;
		Array<RenderTargetResource*> mDisplays;

		// Inherited via SceneAspect
		virtual bool RegisterComponentCore(Component* pComponent) override;
		virtual void RemoveComponentCore(Component* pComponent) override;
	};


#include "DisplayAspect.reflect.h"
}