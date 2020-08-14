#pragma once

#include "engine/core/game_window.h"
#include "engine/core/data_structures/circular_buffer.h"
#include "engine/core/input_manager.h"
#include "engine/imgui/imgui_setup.h"
#include "engine/debug/profiler.hpp"

#include <memory>
#include <string>

namespace fightingengine {

    class Application
    {
    public:
        Application(const std::string& name = "Fighting Engine (Default)", int width = 1080, int height = 720);
        virtual ~Application();
        void shutdown();

        float get_delta_time();
        void frame_begin();
        void frame_end(float delta_time);
        void poll(); 
        void gui_begin();
        void gui_end();

        bool is_running() { return running; }

        InputManager& get_input() { return input_manager; }
        ImGui_Manager& get_imgui() { return imgui_manager; }
        GameWindow& get_window() { return *window; }

        float get_average_fps() { return fps_buffer.average(); }

    private:

        //window events
        void on_window_close();
        void on_window_resize(int w, int h);

    private:
        std::unique_ptr<GameWindow> window;
        //std::unique_ptr<Renderer> renderer;
        //Profiler profiler;
        InputManager input_manager;
        ImGui_Manager imgui_manager;

        bool running = true;
        bool fullscreen = false;
        bool minimized = false;

         //FPS settings
        double FPS = 144.0;
        Uint32 MILLISECONDS_PER_FRAME = (Uint32)(1000 / FPS);
        CircularBuffer<float, 100> fps_buffer;

        //Game's fixed tick
        int FIXED_TICKS_PER_SECOND = 1;
        float SECONDS_PER_FIXED_TICK = 1.f / FIXED_TICKS_PER_SECOND;
        float seconds_since_last_game_tick = 0;

        //Delta time
        unsigned int start = 0;
        unsigned int prev = 0;
        unsigned int now = 0;
        float time_since_launch = 0.0f;
    };
}