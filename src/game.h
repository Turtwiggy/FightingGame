#pragma once

#include "3d/camera.hpp"
#include "game_state.hpp"
#include "graphics/renderer.h"
#include "gui.hpp"
#include "util/profiler.hpp"
#include "util/circular_buffer.h"
#include "util/resource_manager.hpp"
#include "input/input_manager.h"
#include "window/game_window.h"

//placeholder systems
//#include "physics/physics_example.hpp""
//#include "audio/audio_player.hpp"
//#include "networking/networking_common.hpp"
//#include "networking/network_settings.hpp"
//#include "networking/chat_client.hpp"
//#include "networking/chat_server.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
//#include <entt/entt.hpp>

#include <string>
#include <vector>
#include <memory>
#include <thread>

namespace fightinggame
{
    class Game
    {
    public:
        bool process_events(Renderer& r, GameWindow& g_window, Gui& gui, Camera& camera, InputManager& input_manager);
        void run();

        float get_average_fps() { return fps_buffer.average(); }

    private:
        void tick(float delta_time, GameState& state, float timer);    //update game logic
        void fixed_tick(float fixed_delta_time);

        void render
        (
            Profiler& profiler,
            GameState& state,
            Renderer& r,
            Camera& c,
            Gui& g,
            GameWindow& window,
            FGObject& cube
        );
        void shutdown(Renderer& r, GameWindow& w);

    private:
        static Game* sInstance;
        bool running = true;
        bool fullscreen = false;
        float timer = 0.0f;

        //delta time metrics
        double FPS = 144.0;
        Uint32 MILLISECONDS_PER_FRAME = (Uint32)(1000 / FPS);
        //float SECONDS_PER_FRAME = 1.f / FPS;
        CircularBuffer fps_buffer;

        int FIXED_TICKS_PER_SECOND = 1;
        float SECONDS_PER_FIXED_TICK = 1.f / FIXED_TICKS_PER_SECOND;
        float seconds_since_last_game_tick = 0;

        unsigned int start = 0;
        unsigned int prev = 0;
        unsigned int now = 0;

        //physics
        //physics_simulation _physics;

        //audio
        //audio_player audio;

        //networking
        //std::unique_ptr<std::thread> _networking_thread;
        //network_settings net_set;
        //net_set.addrServer.Clear();
        //net_set.addrServer.ParseString("127.0.0.1");
        //net_set.addrServer.m_port = net_set.port;
    };
}
