#pragma once
#include <Runtime/Application/Application.h>
namespace Portakal
{
	class Window;
	class GraphicsDevice;
	class CommandBuffer;

	class PORTAKAL_API EditorPlayerApplication : public Application
	{
	public:
		virtual bool Tick() override;
		virtual void Initialize() override;
	private:
		Array<ApplicationModule*> _tickableModules;
		Array<ApplicationModule*> _eventableModules;
		Array<ApplicationModule*> _validationModules;
		GraphicsDevice* _defaultDevice;
		Window* _defaultWindow;
		CommandBuffer* _cmdBuffer;
	};
}