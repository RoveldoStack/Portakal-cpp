#pragma once
#include <Runtime/Application/Application.h>
namespace Portakal
{
	class Window;
	class GraphicsDevice;
	class CommandList;

	class PORTAKAL_API EditorPlayerApplication : public Application
	{
	public:
		
	private:
		virtual void Tick() override;
		virtual void PreTick() override;
		virtual void PostTick() override;
		virtual void Initialize() override;
	private:
		Array<ApplicationModule*> _tickableModules;
		Array<ApplicationModule*> _eventableModules;
		Array<ApplicationModule*> _validationModules;
		GraphicsDevice* _defaultDevice;
		Window* _defaultWindow;
		CommandList* _cmdBuffer;
	};
}