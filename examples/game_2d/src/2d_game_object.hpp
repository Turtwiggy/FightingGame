#pragma once

// other project headers
#include <SDL2/SDL_scancode.h>
#include <glm/glm.hpp>

// your includes
#include "engine/maths_core.hpp"
#include "spritemap.hpp"

namespace game2d {

enum class CollisionLayer
{
  NoCollision = 0,
  Bullet = 1,
  Player = 2,
  Enemy = 3,
  Obstacle = 4,

  Count = 5
};

static const std::vector<bool> GAME_COLL_MATRIX = {
  false, // NoCollision_NoCollision_0_0
  false, // bullet_NoCollision_1_0
  false, // Player_NoCollision_2_0
  false, // Enemy_NoCollision_3_0
  false, // Obstacle_NoCollision_4_0

  false, // bullet_bullet_1_1
  false, // player_bullet_2_1
  true,  // enemy_bullet_3_1
  true,  // Obstacle_bullet_4_1

  false, // player_player_2_2
  true,  // enemy_player_3_2
  true,  // Obstacle_player_4_2

  false, // enemy_enemy_3_3
  true,  // Obstacle_enemy_4_3

  false, // Obstacle_Obstacle_4_4
};

struct KeysAndState
{
  bool use_keyboard = false;

  // keyboard
  SDL_Scancode w = SDL_SCANCODE_W;
  SDL_Scancode s = SDL_SCANCODE_S;
  SDL_Scancode a = SDL_SCANCODE_A;
  SDL_Scancode d = SDL_SCANCODE_D;
  SDL_Scancode key_boost = SDL_SCANCODE_LSHIFT;
  SDL_Scancode key_pause = SDL_SCANCODE_P;
  SDL_Scancode key_camera_up = SDL_SCANCODE_UP;
  SDL_Scancode key_camera_down = SDL_SCANCODE_DOWN;
  SDL_Scancode key_camera_left = SDL_SCANCODE_LEFT;
  SDL_Scancode key_camera_right = SDL_SCANCODE_RIGHT;
  SDL_Scancode key_camera_follow_player = SDL_SCANCODE_Q;

  // controller
  float l_analogue_x = 0.0f;
  float l_analogue_y = 0.0f;
  float r_analogue_x = 0.0f;
  float r_analogue_y = 0.0f;

  // common
  float angle_around_player = 0.0f;
  bool pause_pressed = false;
  bool shoot_pressed = false;
  bool boost_pressed = false;
};

enum class AiBehaviour
{
  MOVEMENT_DIRECT,
  MOVEMENT_ARC_ANGLE,
};

//
// If this game ever has more than 1 million entities,
// reconsider this structure. Until then, lets gooooo.
//

struct GameObject2D
{
  static inline uint32_t global_int_counter = 0;
  uint32_t id = 0;

  bool active = true;
  bool do_render = true;
  bool do_lifecycle_timed = false;
  bool do_lifecycle_health = true;
  bool do_physics = true;
  bool flag_for_delete = false;

  // render
  int tex_slot = 0;
  sprite::type sprite = sprite::type::SQUARE;
  glm::vec2 pos = { 0.0f, 0.0f }; // in pixels, centered
  float angle_radians = 0.0f;
  glm::vec4 colour = { 1.0f, 0.0f, 0.0f, 1.0f };
  glm::vec2 render_size = { 20.0f, 20.0f };

  // physics
  glm::vec2 physics_size = render_size;
  CollisionLayer collision_layer = CollisionLayer::NoCollision;
  std::vector<glm::ivec2> in_grid_cell;

  // game: movement
  float speed_current = 50.0f;
  float speed_default = 50.0f;
  glm::vec2 velocity = { 0.0f, 0.0f };
  float velocity_boost_modifier = 5.0f;
  float shift_boost_time = 10.0f;
  float shift_boost_time_left = shift_boost_time;

  // ai: hacky behaviour
  // could probably use a list of "prioritized" ai instead. will do that on 3+ ai needed.
  AiBehaviour ai_original = AiBehaviour::MOVEMENT_DIRECT;
  AiBehaviour ai_current = AiBehaviour::MOVEMENT_DIRECT;
  float approach_theta_degrees = 0.0f;

  // game: shooting
  float bullet_seconds_between_spawning = 0.15f;
  float bullet_seconds_between_spawning_left = 0.0f;

  // game: lifecycle timed
  float time_alive_left = 5.0f;

  // game: lifecycle health
  int hits_able_to_be_taken = 3;
  int hits_taken = 0;
  bool invulnerable = false;

  // game: extra
  std::string name = "DEFAULT";

  GameObject2D() { id = ++GameObject2D::global_int_counter; }
};

// util

[[nodiscard]] glm::vec2
gameobject_in_worldspace(const GameObject2D& camera, const GameObject2D& go);

[[nodiscard]] bool
gameobject_off_screen(glm::vec2 pos, glm::vec2 size, const glm::ivec2& screen_size);

namespace gameobject {

// logic

void
update_position(GameObject2D& obj, float delta_time_s);

// entities

GameObject2D
create_bullet(sprite::type sprite, int tex_slot, glm::vec4 colour);

GameObject2D
create_camera();

GameObject2D
create_enemy(sprite::type sprite, int tex_slot, glm::vec4 colour, fightingengine::RandomState& rnd);

GameObject2D
create_tree(int tex_slot);

GameObject2D
create_player(sprite::type sprite, int tex_slot, glm::vec4 colour, glm::vec2 screen);

GameObject2D
create_kennynl_texture(int tex_slot);

} // namespace gameobject

} // namespace game2d
