#pragma once

// c++ standard lib headers
#include <vector>

// other library
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>

namespace fightingengine {

class InputManager
{
public:
  InputManager();

  void new_frame();

  // keyboard

  const Uint8* get_keyboard_state() const;

  void add_button_down(SDL_Keycode button);
  [[nodiscard]] bool get_key_down(SDL_Keycode button) const;
  [[nodiscard]] bool get_key_held(SDL_Scancode button) const;

  // mouse

  void add_mouse_down(SDL_MouseButtonEvent& mouse_e);
  [[nodiscard]] bool get_mouse_lmb_held() const;
  [[nodiscard]] bool get_mouse_rmb_held() const;
  [[nodiscard]] bool get_mouse_mmb_held() const;

  void set_mousewheel_y(const float amount);
  [[nodiscard]] float get_mousewheel_y() const;

private:
  // Keyboard state
  // down and up reset every frame
  std::vector<SDL_Keycode> down;
  const Uint8* state;

  float mousewheel_y;
};

}