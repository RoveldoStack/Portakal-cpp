#pragma once
#include <Runtime/World/SceneAspect.h>

namespace Portakal
{
	class CommandList;
	class SpriteCamera;
	PCLASS();
	class PORTAKAL_API SpriteRendererAspect : public SceneAspect
	{
		GENERATE_CLASS(SpriteRendererAspect);
	public:
		SpriteRendererAspect() = default;
		~SpriteRendererAspect() = default;

		void RegisterCamera(SpriteCamera* pCamera);
		void RemoveCamera(SpriteCamera* pCamera);

		// Inherited via SceneAspect
		virtual void OnInitialize() override;

		virtual void OnExecute() override;

		virtual void OnFinalize() override;

	private:
		Array<SpriteCamera*> mCameras;
		CommandList* mCmdList;
	};

#include "SpriteRendererAspect.reflect.h"
}