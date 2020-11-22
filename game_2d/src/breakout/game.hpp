#pragma once

//c++ standard lib headers
#include <vector>

//other project headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//your project headers
#include "engine/graphics/texture.hpp"
#include "engine/graphics/render_command.hpp"
using namespace fightingengine;

namespace game2d 
{


struct Transform
{
    glm::vec2 position = { 0.0f, 0.0f }; //in pixels, centered
    float angle = 0.0f;                  //in degrees
    glm::vec2 scale = { 100.0f, 100.0f };
    glm::vec3 colour = { 1.0f, 1.0f, 1.0f };
};

struct GameObject
{
    Transform transform;
    glm::vec2 velocity = { 0.0f, 0.0f };
    Texture2D* texture;

    //gameobject flags... 
    //note: avoid adding these, or come up with a better system
    //more flags is a 2^n of configurations of testing to make sure everything
    bool is_solid = false;
    bool destroyed = false;

    GameObject( Texture2D* tex );
};

struct Ball 
{
    GameObject game_object;
    
    float radius = 1.0f;
    bool stuck = true;

    Ball( Texture2D* tex );
};
void reset_ball( Ball& ball );
void move_ball( Ball& ball, float delta_time_s, int window_width );

enum class GameState 
{
   GAME_ACTIVE,
   GAME_MENU,
   GAME_WIN
};


struct GameLevel
{
    std::vector<GameObject> bricks;
};

void load_level_from_file(std::vector<std::vector<int>>& layout, const std::string& path);

void init_level(GameLevel& level, const std::vector<std::vector<int>>& layout, int width, int height);


struct Breakout
{
    GameState state = GameState::GAME_ACTIVE;

    std::vector<GameLevel> levels;
};

void init_breakout_levels(std::vector<GameLevel>& breakout, int screen_width, int screen_height);


// ---- breakout game functions

void update_user_input();

void update_game_state();

} //namespace game2d