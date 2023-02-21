#pragma once
#include <Runtime/World/SceneAspect.h>

namespace Portakal
{
	class CommandList;
	class PORTAKAL_API SpriteRendererAspect : public SceneAspect
	{
		GENERATE_CLASS(SpriteRendererAspect);
	public:
		SpriteRendererAspect() = default;
		~SpriteRendererAspect() = default;


		// Inherited via SceneAspect
		virtual void OnInitialize() override;

		virtual void OnExecute() override;

		virtual void OnFinalize() override;
	private:
		CommandList* mCmdList;
	};

	START_GENERATE_TYPE(SpriteRendererAspect);
	START_TYPE_PROPERTIES(SpriteRendererAspect);
	REGISTER_BASE_TYPE(SceneAspect);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(SpriteRendererAspect);
	END_GENERATE_TYPE(SpriteRendererAspect);
}