#include "camera.hpp"

namespace fightingengine {

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 Camera::get_view_matrix() const
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    glm::mat4 Camera::get_view_projection_matrix(int width, int height) const
    {
        glm::mat4 projection = glm::perspective(glm::radians(Zoom), (float)width / (float)height, 0.001f, 100.0f);
        glm::mat4 view = get_view_matrix();
        return projection * view;
    }

    glm::mat4 Camera::get_inverse_projection_view_matrix(float width, float height)
    {
        glm::mat4 projection = glm::perspective(glm::radians(Zoom), width / height, 0.001f, 100.0f);
        glm::mat4 view = get_view_matrix();
        return glm::inverse(projection * view);
    }

    // Compute the world direction vector based on the given X and Y coordinates in normalized-device space
    glm::vec3 Camera::get_eye_ray(float x, float y, float width, float height)
    {
        glm::vec4 temp(x, y, 0.0f, 1.0f);

        glm::mat4 inverse_projection_view = get_inverse_projection_view_matrix(width, height);

        glm::vec4 ray = inverse_projection_view * temp;
        ray /= ray.w;
        ray.x -= Position.x;
        ray.y -= Position.y;
        ray.z -= Position.z;

        return glm::vec3(ray.x, ray.y, ray.z);
    }


    void Camera::update(float delta_time)
    {
        float velocity = MovementSpeed * delta_time;

        //if (state.forward_pressed && state.backward_pressed)
        //{
        //    //do nothing
        //}
        //else if (state.forward_pressed)
        //{
        //    Position += Front * velocity;
        //}
        //else if (state.backward_pressed) {
        //    Position += -(Front * velocity);
        //}

        //if (state.left_pressed && state.right_pressed)
        //{
        //    //do nothing
        //}
        //else if (state.left_pressed)
        //{
        //    Position += -(Right * velocity);
        //}
        //else if (state.right_pressed) {
        //    Position += Right * velocity;
        //}

        //if (state.up_pressed && state.down_pressed)
        //{
        //    //do nothing
        //}
        //else if (state.up_pressed)
        //{
        //    Position += Up * velocity;
        //}
        //else if (state.down_pressed) {
        //    Position += -(Up * velocity);
        //}
    }

    //void Camera::process_events(const SDL_Event& evnt)
    //{
    //    //int mouse_x, mouse_y;
    //    //SDL_GetMouseState(&mouse_x, &mouse_y);

    //    switch (evnt.type)
    //    {
    //    case SDL_MOUSEWHEEL:
    //        process_mouse_scroll(evnt.wheel.y);
    //        break;
    //    case SDL_MOUSEMOTION:
    //        float xrel = evnt.motion.xrel;
    //        float yrel = evnt.motion.yrel;
    //        //printf("mousePos x: %f y: %f", xrel, yrel);

    //        process_mouse_movement(xrel, yrel);
    //        break;
    //    }
    //}

    // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void Camera::process_mouse_movement(float xoffset, float yoffset, bool constrainPitch)
    {
        xoffset *= CameraSensitivity;
        yoffset *= CameraSensitivity;

        Yaw += xoffset;
        Yaw = glm::mod(Yaw + xoffset, 360.0f);

        Pitch += (yoffset * -1);

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // Update Front, Right and Up Vectors using the updated Euler angles
        update_camera_vectors();
    }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void Camera::process_mouse_scroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

    // calculates the front vector from the Camera's (updated) Euler Angles
    void Camera::update_camera_vectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }

};