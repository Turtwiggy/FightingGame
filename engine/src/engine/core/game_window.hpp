#pragma once

//c++ standard lib headers
#include <cstdint>
#include <memory>
#include <string>

//other library headers
#include <SDL2/SDL.h>
#undef main //thanks SDL2?

namespace fightingengine
{
	enum class display_mode
	{
		Windowed,
		Fullscreen,
		Borderless
	};

	class GameWindow
	{
		struct SDLDestroyer
		{
			void operator()(SDL_Window* window) const { SDL_DestroyWindow(window); }
		};

	public:
		GameWindow(const std::string& title, const SDL_DisplayMode& display, display_mode displaymode);
		GameWindow(const std::string& title, int width, int height, display_mode displaymode);

		[[nodiscard]] SDL_Window* GetHandle() const;

		[[nodiscard]] bool IsOpen() const;
		[[nodiscard]] float GetBrightness() const;
		void SetBrightness(const float bright);
		[[nodiscard]] uint32_t GetID() const;
		[[nodiscard]] uint32_t GetFlags() const;


		void SetTitle(const std::string& str);
		[[nodiscard]] std::string GetTitle() const;
		[[nodiscard]] float GetAspectRatio() const;

		void Show();
		void Hide();
		void Close();

		void SetPosition(int x, int y);
		void GetPosition(int& x, int& y) const;
		void SetSize(int width, int height);
		void GetSize(int& width, int& height) const;
		void SetMinimumSize(int width, int height);
		void GetMinimumSize(int& width, int& height) const;
		void SetMaximumSize(int width, int height);
		void GetMaximumSize(int& width, int& height) const;

		void Minimise();
		void Maximise();
		void Restore();
		void Raise();

		void SetBordered(const bool b);
		void SetFullscreen(const bool f);
		[[nodiscard]] bool IsFullscreen() const;
        void ToggleFullscreen();

		//Mouse
		void SetMousePosition(int x, int y);
		[[nodiscard]] bool IsInputGrabbed() const;
		void CaptureMouse();
		void ReleaseMouse();

        [[nodiscard]] SDL_GLContext& get_gl_context();
        [[nodiscard]] std::string get_glsl_version() const;

	private:
		std::unique_ptr<SDL_Window, SDLDestroyer> _window;

        SDL_GLContext gl_context;

		//only possible with c++20
		//constexpr std::string glsl_version = "#version 430";
		const std::string glsl_version = "#version 430";
    };
}
