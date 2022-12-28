#pragma once
#include <Portakal/Window/WindowCreateDesc.h>


namespace Portakal
{
	/// <summary>
	/// Represents a OS window
	/// </summary>
	class PORTAKAL_API Window
	{
	public:
		Window* CreateWindow(const WindowCreateDesc& desc);

		virtual ~Window();

		FORCEINLINE std::string GetTitle() const noexcept { return _title; }
		FORCEINLINE unsigned int GetWidth() const noexcept { return _width; }
		FORCEINLINE unsigned int GetHeight() const noexcept { return _height; }
		FORCEINLINE unsigned int GetPositionX() const noexcept { return _positionX; }
		FORCEINLINE unsigned int GetPositionY() const noexcept { return _positionY; }

		void SetTitle(const std::string& title);
		void SetSize(const unsigned int width, const unsigned int height);
		void SetPosition(const unsigned int x, const unsigned int y);
	protected:
		Window(const WindowCreateDesc& desc) : _title(desc.Name),_width(desc.Width),_height(desc.Height),_positionX(desc.PositionX),_positionY(desc.PositionY) {}

		FORCEINLINE virtual void SetTitleCore(const std::string& title) = 0;
		FORCEINLINE virtual void SetSizeCore(const unsigned int width, const unsigned int height) = 0;
		FORCEINLINE virtual void SetPositionCore(const unsigned int x, const unsigned int y) = 0;
	private:
		std::string _title;
		unsigned int _width;
		unsigned int _height;
		unsigned int _positionX;
		unsigned int _positionY;
	};
}