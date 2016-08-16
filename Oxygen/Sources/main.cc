// Oxygen - main.cc
//
// Copyright (C) Jack Maloney 2016
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

// Local Headers
#include "glitter.h"
#include "oxygen.h"

// System Headers
#include <GLFW/glfw3.h>
#include <glad/glad.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

using namespace oxygen;

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Please specify assets directory. " << std::endl
                  << argv[0] << " <asset-dir>" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string assetsDirectoryPath = std::string(argv[1]);
    std::cout << "Assets Directory: " << assetsDirectoryPath << std::endl;

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow =
        glfwCreateWindow(mWidth, mHeight, "Oxygen", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    vao vertexArrayObject;
    vertexArrayObject.bind();

    // Buffer Vertices
    GLuint vbo;
    glGenBuffers(1, &vbo);
    // clang-format off
    GLfloat vertices[] = {
        // Top (side 0) facing positive y
        0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 0.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 1.0f, 0.0f, 1.0f,
        1.0f,  1.0f, 1.0f, 0.0f, 1.0f,
        0.0f,  1.0f, 1.0f, 1.0f, 1.0f,
        0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
        
        // Front (side 1) facing positive z
        0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        
        // Right (side 2) facing positive x
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        
        // Back (side 3) facing negative z
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        
        // Left (side 4) facing negative x
        0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        
        // Bottom (side 5) facing negative y
        0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
        1.0f,  0.0f, 0.0f, 0.0f, 0.0f,
        1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
        1.0f,  0.0f, 1.0f, 0.0f, 1.0f,
        0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
        0.0f,  0.0f, 0.0f, 1.0f, 0.0f,
    };
    // clang-format on

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /*
        GLuint ebo;
        glGenBuffers(1, &ebo);
        GLuint elements[] = {0, 1, 2, 2, 3, 0};
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
                     GL_STATIC_DRAW);
    */
    // Vertex Shader
    const char* vertexSource =
        GLSL(in vec3 in_position; in vec2 in_texcoord;

             out vec2 texcoord;

             uniform mat4 model; uniform mat4 view; uniform mat4 proj;

             void main() {
                 gl_Position = proj * view * model * vec4(in_position, 1.0);
                 texcoord = in_texcoord;
             });
    char buffer[512];
    shader vertexShader = shader(vertexSource, GL_VERTEX_SHADER);
    GLint status = vertexShader.compile(buffer, 512);
    handleShaderCompileErrors(status, buffer);

    // Fragment Shader
    const char* fragmentSource = GLSL(

        in vec2 texcoord;

        out vec4 outColor;

        uniform sampler2D texsamp;

        void main() { outColor = texture(texsamp, texcoord); });
    shader fragmentShader = shader(fragmentSource, GL_FRAGMENT_SHADER);
    status = fragmentShader.compile(buffer, 512);
    handleShaderCompileErrors(status, buffer);

    program shaderProgram = program();
    shaderProgram.addShader(vertexShader);
    shaderProgram.addShader(fragmentShader);
    status = shaderProgram.link(buffer, 512);
    shaderProgram.use();
    handleShaderCompileErrors(status, buffer);

    shaderProgram.setAttributeArray("in_position", 3, GL_FLOAT, GL_FALSE,
                                    5 * sizeof(float), 0);

    shaderProgram.setAttributeArray("in_texcoord", 2, GL_FLOAT, GL_FALSE,
                                    5 * sizeof(float),
                                    (void*) (3 * sizeof(float)));

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::string path = assetsDirectoryPath + "/textures/coal.png";
    texture coalTexture = texture(path.c_str(), GL_TEXTURE0);
    glGenerateMipmap(GL_TEXTURE_2D);

    path = assetsDirectoryPath + "/textures/destroy.png";
    texture destroyTexture = texture(path.c_str(), GL_TEXTURE1);
    glGenerateMipmap(GL_TEXTURE_2D);

    path = assetsDirectoryPath + "/textures/grass.png";
    texture grassTexture = texture(path.c_str(), GL_TEXTURE2);
    glGenerateMipmap(GL_TEXTURE_2D);

    path = assetsDirectoryPath + "/textures/hay.png";
    texture hayTexture = texture(path.c_str(), GL_TEXTURE3);
    glGenerateMipmap(GL_TEXTURE_2D);

    path = assetsDirectoryPath + "/textures/pumpkin.png";
    texture pumpkinTexture = texture(path.c_str(), GL_TEXTURE4);
    glGenerateMipmap(GL_TEXTURE_2D);

    path = assetsDirectoryPath + "/textures/sandstone.png";
    texture sandstoneTexture = texture(path.c_str(), GL_TEXTURE5);
    glGenerateMipmap(GL_TEXTURE_2D);

    glm::mat4 view =
        glm::lookAt(glm::vec3(25.0f, 11.5f, 11.5f), glm::vec3(8.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 proj =
        glm::perspective(glm::radians(75.0f), 800.0f / 800.0f, 0.1f, 100.0f);

    glUniformMatrix4fv(shaderProgram.getUniformLocation("view"), 1, GL_FALSE,
                       glm::value_ptr(view));
    glUniformMatrix4fv(shaderProgram.getUniformLocation("proj"), 1, GL_FALSE,
                       glm::value_ptr(proj));

    std::cout << glGetError() << std::endl;

    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(mWindow, true);
        }

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (int l = 0; l < 16; l++) {
            glm::mat4 m =
                glm::translate(glm::mat4(), glm::vec3(0.0, 0.0, l * -1));
            for (int k = 0; k < 16; k++) {
                m = glm::translate(m, glm::vec3(1.0f, 0.0f, 0.0f));
                glUniformMatrix4fv(shaderProgram.getUniformLocation("model"), 1,
                                   GL_FALSE, glm::value_ptr(m));
                GLint texsamp = shaderProgram.getUniformLocation("texsamp");

                // pumpkin
                glUniform1i(texsamp, 4);
                glDrawArrays(GL_TRIANGLES, 0, 6);

                // grass
                glUniform1i(texsamp, 2);
                glDrawArrays(GL_TRIANGLES, 6, 6);

                // coal
                glUniform1i(texsamp, 0);
                glDrawArrays(GL_TRIANGLES, 12, 6);

                // sandstone
                glUniform1i(texsamp, 5);
                glDrawArrays(GL_TRIANGLES, 18, 6);

                // hay
                glUniform1i(texsamp, 3);
                glDrawArrays(GL_TRIANGLES, 24, 6);

                // destroy
                glUniform1i(texsamp, 1);
                glDrawArrays(GL_TRIANGLES, 30, 6);
            }
        }

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return EXIT_SUCCESS;
}
