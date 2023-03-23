#pragma once
#include <Runtime/World/SceneAspect.h>

namespace Portakal
{
	class CommandList;
	class SpriteCamera;
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

		int myInt;
	private:
		Array<SpriteCamera*> mCameras;
		CommandList* mCmdList;
	};

	START_GENERATE_TYPE(SpriteRendererAspect);
	START_TYPE_PROPERTIES(SpriteRendererAspect);
	REGISTER_BASE_TYPE(SceneAspect);
	REGISTER_FIELD(SpriteRendererAspect, myInt, int, AccessSpecifier::Public);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(SpriteRendererAspect);
	END_GENERATE_TYPE(SpriteRendererAspect);
}