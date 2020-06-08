#include "game.h"

#include "gui.hpp"
#include "graphics/render_command.h"
#include "3d/assimp_obj_loader.h"

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>
#include "imgui.h"
#include "SDL2/SDL.h"
#include <GL/glew.h>
#include "boost/filesystem.hpp"
#include <cstdint>
#include <string>
#include <filesystem>

using namespace fightinggame;

const std::string kBuildStr = "1";
//const std::string kBuildStr(kGitSHA1Hash, 8);
const std::string kWindowTitle = "fightinggame";

game* game::sInstance = nullptr;

bool game::process_window_input_down(const SDL_Event& event, game_window& window)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_ESCAPE:

        return false;
    case SDLK_f:
        window.SetFullscreen(!fullscreen);

        int width, height;
        window.GetSize(width, height);

        m_width = width;
        m_height = height;
        std::cout << "screen size toggled, w: " << m_width << " h: " << m_height << std::endl;
        render_command::SetViewport(0, 0, m_width, m_height);
        
        fullscreen = !fullscreen;

        break;
    case SDLK_m:
        window.ToggleMouseCaptured();
        break;
    }

    return true;
}

bool game::process_events(profiler& p, renderer& r, game_window& g, Gui& gui, Camera& c)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        // If gui captures this input, do not propagate
        if (!gui.ProcessEventSdl2(e, r.get_imgui_context()))
        {
            //Update camera when mouse is grabbed
            if(g.IsInputGrabbed())
                c.ProcessEvents(e);

            //Other window events
            if (e.type == SDL_QUIT) {
                return false;
            }
            else if (e.type == SDL_WINDOWEVENT
                && e.window.event == SDL_WINDOWEVENT_CLOSE
                && e.window.windowID == SDL_GetWindowID(g.GetHandle()))
                return false;

            switch (e.type)
            {
            case SDL_KEYDOWN:
                return process_window_input_down(e, g);
            }
        }
    }
    return true;
}

//Called X ticks per second
void game::tick(float delta_time, game_state& state)
{
    //printf("ticking frame %i game state time: %f \n", _frameCount, delta_time);

    state.cube_pos = glm::vec3(0.0, 0.0, 0.0);
}

void game::render(profiler& profiler, game_state& state, renderer& r, Camera& c, Gui& g, game_window& window, Model& model)
{
    {
        profiler.Begin(profiler::Stage::NewFrame);
        r.new_frame(window.GetHandle());
        profiler.End(profiler::Stage::NewFrame);
    }

    {
        profiler.Begin(profiler::Stage::SceneDraw);
        renderer::draw_scene_desc drawDesc
        ( 
            model
        );
        drawDesc.view_id = graphics::render_pass::Main;
        drawDesc.height = m_height;
        drawDesc.width = m_width;
        drawDesc.camera = c;

        r.draw_pass(drawDesc);
        profiler.End(profiler::Stage::SceneDraw);
    }

    {
        profiler.Begin(profiler::Stage::GuiLoop);
        if (g.Loop(*this, r.get_imgui_context(), profiler))
        {
            running = false;
            return;
        }
        profiler.End(profiler::Stage::GuiLoop);
    }

    {
        profiler.Begin(profiler::Stage::RenderFrame);
        r.end_frame(window.GetHandle());
        profiler.End(profiler::Stage::RenderFrame);
    }
}

void game::run()
{
    sInstance = this;

    //todo init spdlogger

    //Profiler
    profiler profile;
    printf("profiler taking up: %s bytes \n", std::to_string(sizeof(profiler)));

    //Window
    game_window window =  game_window
    (
        kWindowTitle + " [" + kBuildStr + "]",
        m_width,
        m_height, 
        display_mode::Windowed
    );
    printf("game window taking up: %s bytes \n", std::to_string(sizeof(game_window)));

    //Camera
    Camera cam = Camera(glm::vec3(0.0f, 0.0f, 10.0f));
    printf("camera taking up: %s bytes \n", std::to_string(sizeof(Camera)));

    //_camera = std::make_unique<Camera>();
    //auto aspect = _window ? _window->GetAspectRatio() : 1.0f;
    //_camera->SetProjectionMatrixPerspective(70.0f, aspect, 1.0f, 65536.0f)

    //Renderer
    renderer rend = renderer(window, false);
    printf("renderer taking up: %s bytes \n", std::to_string(sizeof(renderer)));

    //ImGui Gui (harhar)
    Gui gui;
    printf("Gui taking up: %s bytes \n", std::to_string(sizeof(Gui)));

    //Temp obj loader - should be moved in future
    std::filesystem::path current_dir = std::filesystem::current_path();
    current_dir.append("res/models/lizard_wizard/lizard_wizard.obj");
    Model tempModel = Model(current_dir.generic_u8string());
    printf("Model taking up: %s bytes \n", std::to_string(sizeof(Model)));

    _frameCount = 0;
    while (running)
    {
        //Update Profiler
        profile.Frame();
        profile.Begin(profiler::Stage::UpdateLoop);

        // input
        // -----
        profile.Begin(profiler::Stage::SdlInput);
        running = process_events(profile, rend, window, gui, cam);
        if (!running) { shutdown(rend, window);  return; }
        profile.End(profiler::Stage::SdlInput);

        // Delta Time
        // ----------
        ImGuiIO& io = ImGui::GetIO();
        float delta_time = io.DeltaTime;
        //printf("delta_time %f \n", delta_time);
        _timeSinceLastUpdate += delta_time;

        // Update Systems
        // --------------
        cam.Update(delta_time);

        // Game Logic Tick
        // ---------------
        while (_timeSinceLastUpdate >= timePerFrame)
        {
            state_previous = state_current;

            tick(timePerFrame, state_current ); //this update's state_current

            _timeSinceLastUpdate -= timePerFrame;
        }

        // Rendering
        // ---------
        render(profile, state_current, rend, cam, gui, window, tempModel);

        //lerp between game states
        //const float alpha = _timeSinceLastUpdate / timePerFrame;
        //game_state state_lerped = state_current * alpha + state_previous * ( 1.0 - alpha );
        //render(window, new_state, net_set);

        _frameCount += 1;
        state_current.frame = _frameCount;

        float curr_fps = 1.0f / delta_time;
        printf("curr_fps: %f", curr_fps );
        average_fps.add_next( curr_fps  );
        //printf("frame count: %i \n", _frameCount);
        profile.End(profiler::Stage::UpdateLoop);

    }

    //end
    //shutdown(_renderer, _window);
}

void game::shutdown(renderer& r, game_window& w)
{
    running = false;

    r.shutdown();
    w.Close();
}
