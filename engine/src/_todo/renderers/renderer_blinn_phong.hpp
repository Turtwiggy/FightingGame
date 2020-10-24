#pragma once

//NOTE: this file contains blur and bloom effects

//unsigned int Renderer::hdr_fbo()
//{
//    // configure floating point framebuffer
//    // ------------------------------------
//    unsigned int hdrFBO;
//    glGenFramebuffers(1, &hdrFBO);
//    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
//    return hdrFBO;
//}
//
//std::array<unsigned int, 2> Renderer::hdr_colour_buffer(int width, int height, unsigned int hdr_fbo)
//{
//    // create 2 floating point color buffers (1 for normal rendering, other for brightness treshold values)
//    unsigned int colorBuffers[2];
//    glGenTextures(2, colorBuffers);
//    for (unsigned int i = 0; i < 2; i++)
//    {
//        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//        // attach texture to framebuffer
//        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
//    }
//    // create and attach depth buffer (renderbuffer)
//    unsigned int rboDepth;
//    glGenRenderbuffers(1, &rboDepth);
//    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
//    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
//    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
//    glDrawBuffers(2, attachments);
//    // finally check if framebuffer is complete
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        std::cout << "Framebuffer not complete!" << std::endl;
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//    std::array<unsigned int, 2> color_buffer_array;
//    color_buffer_array[0] = colorBuffers[0];
//    color_buffer_array[1] = colorBuffers[1];
//    return color_buffer_array;
//}

//void hdr_bloom_init()
//{
//    //// configure (floating point) framebuffers
//    //// ---------------------------------------
//    //s_Data.hdr_fbo = hdr_fbo();
//    //s_Data.hdr_colour_buffers = hdr_colour_buffer(screen_width, screen_height, s_Data.hdr_fbo);
//
//    //// ping-pong-framebuffer for blurring
//    //unsigned int pingpongFBO[2];
//    //unsigned int pingpongColorbuffers[2];
//    //glGenFramebuffers(2, pingpongFBO);
//    //glGenTextures(2, pingpongColorbuffers);
//    //for (unsigned int i = 0; i < 2; i++)
//    //{
//    //    glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
//    //    glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
//    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, screen_width, screen_height, 0, GL_RGBA, GL_FLOAT, NULL);
//    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
//    //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//    //    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
//    //    // also check if framebuffers are complete (no need for depth buffer)
//    //    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//    //        std::cout << "Framebuffer not complete!" << std::endl;
//    //}
//    //s_Data.pingpong_fbo[0] = pingpongFBO[0];
//    //s_Data.pingpong_fbo[1] = pingpongFBO[1];
//    //s_Data.pingpong_colour_buffers[0] = pingpongColorbuffers[0];
//    //s_Data.pingpong_colour_buffers[1] = pingpongColorbuffers[1];
//
//    //// lighting info
//    //// -------------
//    //// positions
//    //std::vector<glm::vec3> lightPositions;
//    //lightPositions.push_back(glm::vec3(0.0f, 0.5f, 1.5f));
//    //lightPositions.push_back(glm::vec3(-4.0f, 0.5f, -3.0f));
//    //lightPositions.push_back(glm::vec3(3.0f, 0.5f, 1.0f));
//    //lightPositions.push_back(glm::vec3(-.8f, 2.4f, -1.0f));
//    //s_Data.light_positions = lightPositions;
//    //// colors
//    //std::vector<glm::vec3> lightColors;
//    //lightColors.push_back(glm::vec3(5.0f, 5.0f, 5.0f));
//    //lightColors.push_back(glm::vec3(10.0f, 0.0f, 0.0f));
//    //lightColors.push_back(glm::vec3(0.0f, 0.0f, 15.0f));
//    //lightColors.push_back(glm::vec3(0.0f, 5.0f, 0.0f));
//    //s_Data.light_colours = lightColors;
//
//    //// shader configuration
//    //// --------------------
//    //s_Data.object_shader.use();
//    //s_Data.object_shader.setInt("texture_diffuse1", 0);
//    //s_Data.blur_shader.use();
//    //s_Data.blur_shader.setInt("image", 0);
//    //s_Data.hdr_bloom_final_shader.use();
//    //s_Data.hdr_bloom_final_shader.setInt("scene", 0);
//    //s_Data.hdr_bloom_final_shader.setInt("bloomBlur", 1);
//}

//void hdr_bloom_draw()
//{
//    //   // 1. render scene into floating point framebuffer
//    //// -----------------------------------------------
//    //   glBindFramebuffer(GL_FRAMEBUFFER, s_Data.hdr_fbo);
//    //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    //   s_Data.object_shader.use();
//    //   s_Data.object_shader.setMat4("view_projection", view_projection);
//    //   s_Data.object_shader.setVec3("viewPos", desc.camera.Position);
//    //   glActiveTexture(GL_TEXTURE0);
//    //   glBindTexture(GL_TEXTURE_2D, s_Data.wood_texture);
//    //   // set lighting uniforms
//    //   for (unsigned int i = 0; i < s_Data.light_positions.size(); i++)
//    //   {
//    //       s_Data.object_shader.setVec3("lights[" + std::to_string(i) + "].Position", s_Data.light_positions[i]);
//    //       s_Data.object_shader.setVec3("lights[" + std::to_string(i) + "].Color", s_Data.light_colours[i]);
//    //   }
//
//    //   // create one large cube that acts as the floor
//    //   model = glm::mat4(1.0f);
//    //   model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0));
//    //   model = glm::scale(model, glm::vec3(12.5f, 0.5f, 12.5f));
//    //   s_Data.object_shader.setMat4("model", model);
//    //   renderCube(s_Data.stats.DrawCalls);
//
//    //   // then create multiple cubes as the scenery
//    //   glBindTexture(GL_TEXTURE_2D, s_Data.second_texture);
//
//    //   model = glm::mat4(1.0f);
//    //   model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0));
//    //   model = glm::scale(model, glm::vec3(0.5f));
//    //   s_Data.object_shader.setMat4("model", model);
//    //   //state.cubes[0]->model->draw(s_Data.object_shader, s_Data.stats.DrawCalls);
//    //   renderCube(s_Data.stats.DrawCalls);
//    //   model = glm::mat4(1.0f);
//    //   model = glm::translate(model, glm::vec3(2.0f, 0.0f, 1.0));
//    //   model = glm::scale(model, glm::vec3(0.5f));
//    //   s_Data.object_shader.setMat4("model", model);
//    //   renderCube(s_Data.stats.DrawCalls);
//    //   model = glm::mat4(1.0f);
//    //   model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 2.0));
//    //   model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
//    //   s_Data.object_shader.setMat4("model", model);
//    //   renderCube(s_Data.stats.DrawCalls);
//    //   model = glm::mat4(1.0f);
//    //   model = glm::translate(model, glm::vec3(0.0f, 2.7f, 4.0));
//    //   model = glm::rotate(model, glm::radians(23.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
//    //   model = glm::scale(model, glm::vec3(1.25));
//    //   s_Data.object_shader.setMat4("model", model);
//    //   renderCube(s_Data.stats.DrawCalls);
//    //   model = glm::mat4(1.0f);
//    //   model = glm::translate(model, glm::vec3(-2.0f, 1.0f, -3.0));
//    //   model = glm::rotate(model, glm::radians(124.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
//    //   s_Data.object_shader.setMat4("model", model);
//    //   renderCube(s_Data.stats.DrawCalls);
//    //   model = glm::mat4(1.0f);
//    //   model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
//    //   model = glm::scale(model, glm::vec3(0.5f));
//    //   s_Data.object_shader.setMat4("model", model);
//    //   renderCube(s_Data.stats.DrawCalls);
//
//
//
//    //   // show all the light sources as bright cubes
//    //   s_Data.light_positions[0] = state.cubes[0]->transform.Position;
//
//    //   s_Data.light_shader.use();
//    //   s_Data.light_shader.setMat4("view_projection", view_projection);
//    //   for (unsigned int i = 0; i < s_Data.light_positions.size(); i++)
//    //   {
//    //       model = glm::mat4(1.0f);
//    //       model = glm::translate(model, glm::vec3(s_Data.light_positions[i]));
//    //       model = glm::scale(model, glm::vec3(0.25f));
//    //       s_Data.light_shader.setMat4("model", model);
//    //       s_Data.light_shader.setVec3("lightColor", s_Data.light_colours[i]);
//    //       renderCube(s_Data.stats.DrawCalls);
//    //   }
//    //   glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//    //   // 2. blur bright fragments with two-pass Gaussian Blur 
//    //   // --------------------------------------------------
//    //   bool horizontal = true, first_iteration = true;
//    //   unsigned int amount = 10;
//    //   s_Data.blur_shader.use();
//    //   s_Data.blur_shader.setInt("blur_x", amount / 2);
//    //   s_Data.blur_shader.setInt("blur_y", amount / 2);
//    //   for (unsigned int i = 0; i < amount; i++)
//    //   {
//    //       glBindFramebuffer(GL_FRAMEBUFFER, s_Data.pingpong_fbo[horizontal]);
//    //       s_Data.blur_shader.setInt("horizontal", horizontal);
//    //       glBindTexture(GL_TEXTURE_2D, first_iteration ? s_Data.hdr_colour_buffers[1] : s_Data.pingpong_colour_buffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
//    //       renderQuad();
//    //       horizontal = !horizontal;
//    //       if (first_iteration)
//    //           first_iteration = false;
//    //   }
//    //   glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//    //   // 3. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
//    //   // --------------------------------------------------------------------------------------------------------------------------
//    //   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    //   s_Data.hdr_bloom_final_shader.use();
//    //   glActiveTexture(GL_TEXTURE0);
//    //   glBindTexture(GL_TEXTURE_2D, s_Data.hdr_colour_buffers[0]);
//    //   glActiveTexture(GL_TEXTURE1);
//    //   glBindTexture(GL_TEXTURE_2D, s_Data.pingpong_colour_buffers[!horizontal]);
//    //   s_Data.hdr_bloom_final_shader.setInt("bloom", desc.hdr);
//    //   s_Data.hdr_bloom_final_shader.setFloat("exposure", desc.exposure);
//    //   renderQuad();
//    //   //std::cout << "bloom: " << (desc.hdr ? "on" : "off") << "| exposure: " << desc.exposure << std::endl;
//}
//
