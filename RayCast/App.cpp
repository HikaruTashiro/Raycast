/* @file App.cpp
* @author Jonas Edward Tashiro
* * @brief
* @version 1.0
* @date 2023-01-22
*
* @copyright Copyright (c) 2022
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "includes/imgui/imgui.h"
#include "includes/imgui/imgui_impl_glfw.h"
#include "includes/imgui/imgui_impl_opengl3.h"
#include <iostream>
#include <math.h>
#include <chrono>
#include "Render/Shader.h"
#include "Render/VAO.h"
#include "Render/VBO.h"
#include "Render/EBO.h"
#include "Render/Raycast.h"
#include "World.cpp"
#include "Global.h"

void Initialize_GLFW();
void Initialize_GLEW();
void Initialize_ImGui();
void Cleanup_OpenGL();
void Cleanup_ImGui();
void display();


int main(void)
{
    Initialize_GLFW();
    Initialize_ImGui();

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT , "Raycast", NULL, NULL);
    if(window == NULL)
    {
        std::cout<<"Failed to Initialize Window\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    Initialize_GLEW();

    Shader shader("./GLSL/vertShader.glsl","./GLSL/fragShader.glsl");
    shader.activateShader();

    int wall_size[SCREEN_WIDTH];
    GLfloat vertices[SCREEN_WIDTH * 4];
    ray_cast(wall_size, map, player_x, player_y, angle_direction);
    projection_to_screen(vertices, wall_size);

    //for (int i = 0; i < SCREEN_WIDTH; i++)
    //    std::cout << wall_size[i] << '\n';

    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));
    vao.LinkVBO(vbo, 0);

    auto time_i = std::chrono::system_clock::now();
    auto time_f = std::chrono::system_clock::now();
    float time_dif;
    std::chrono::duration<float> elapsedTime; 

    while (!glfwWindowShouldClose(window))
    {
        time_f = std::chrono::system_clock::now();
        elapsedTime = time_f - time_i;
        time_i = time_f;
        time_dif = elapsedTime.count();
        display();
        walk(player_x, player_y, angle_direction, time_dif);
        rotate(angle_direction, time_dif);
        ray_cast(wall_size, map, player_x, player_y, angle_direction);
        projection_to_screen(vertices, wall_size);
        //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        vbo.access_subData(vertices, sizeof(vertices));

        glfwPollEvents();                     
        glfwSwapBuffers(window);
    }                                         

    vao.Unbind();
    vbo.Unbind();
    vao.Delete();
    vbo.Delete();
    shader.deleteShader();
    Cleanup_ImGui();
    Cleanup_OpenGL();

    return 0;
}

void display()
{
    // Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Draw primitives, number of indices, datatype of indices, index of indices
    glDrawArrays(GL_LINES, 0, SCREEN_WIDTH * 2);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //ImGui::Begin("Angle");
    //ImGui::SliderFloat("Change Angle",&angle_direction,-180.0f,180.0f);
    //if(ImGui::Button("positive x_axis"))
    //    player_x += 32.0f;
    //if(ImGui::Button("negative x_axis"))
    //    player_x -= 32.0f;
    //if(ImGui::Button("positive y_axis"))
    //    player_y += 32.0f;
    //if(ImGui::Button("negative y_axis"))
    //    player_y -= 32.0f;
    //ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Initialize_GLFW()
{
    if (!glfwInit())
    {
        std::cout << "Failed to Initialize GLFW\n";
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
}

void Initialize_GLEW()
{
    /*Initialize GLEW Library*/
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void Initialize_ImGui()
{
    /*ImGUI Initialization*/
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
}

void Cleanup_OpenGL()
{
    glfwTerminate();
}

void Cleanup_ImGui()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
