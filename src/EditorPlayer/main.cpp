#include <Runtime/Platform/PlatformMessage.h>
#include <Runtime/Window/Window.h>
int main(unsigned int argumentCount, const char** ppArguments)
{
	Portakal::WindowCreateDesc windowDesc = {};
	windowDesc.Name = "Portakal Editor Player";
	windowDesc.PositionX = 100;
	windowDesc.PositionY = 100;
	windowDesc.Width = 1024;
	windowDesc.Height = 1024;

	Portakal::Window* pWindow = Portakal::Window::Create(windowDesc);

	pWindow->Show();

	while (1)
	{
		pWindow->PollEvents();
	}
	return 0;
}