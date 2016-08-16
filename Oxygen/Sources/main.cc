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
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
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
        GLSL(in vec3 in_position; in vec3 in_color; in vec2 in_texcoord;

             out vec3 color; out vec2 texcoord;

             uniform mat4 mvp;

             void main() {
                 gl_Position = mvp * vec4(in_position, 1.0);
                 color = in_color;
                 texcoord = in_texcoord;
             });
    char buffer[512];
    shader vertexShader = shader(vertexSource, GL_VERTEX_SHADER);
    GLint status = vertexShader.compile(buffer, 512);
    handleShaderCompileErrors(status, buffer);

    // Fragment Shader
    const char* fragmentSource = GLSL(

        in vec3 color; in vec2 texcoord;

        out vec4 outColor;

        uniform sampler2D texsamp; uniform sampler2D destroysamp;

        void main() {
            vec4 texColor = texture(texsamp, texcoord);
            vec4 destroyColor = texture(destroysamp, texcoord);
            outColor = vec4(color, 1.0) * mix(texColor, destroyColor, 0.5);
        });
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
                                    8 * sizeof(float), 0);

    shaderProgram.setAttributeArray("in_color", 3, GL_FLOAT, GL_FALSE,
                                    8 * sizeof(float),
                                    (void*) (3 * sizeof(float)));

    shaderProgram.setAttributeArray("in_texcoord", 2, GL_FLOAT, GL_FALSE,
                                    8 * sizeof(float),
                                    (void*) (6 * sizeof(float)));

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    std::string path = assetsDirectoryPath + "/textures/pumpkin.png";
    texture pumpkinTexture = texture(path.c_str(), GL_TEXTURE0);
    glUniform1i(shaderProgram.getUniformLocation("texsamp"), 0);

    glGenerateMipmap(GL_TEXTURE_2D);

    path = assetsDirectoryPath + "/textures/destroy.png";
    texture destroyTexture = texture(path.c_str(), GL_TEXTURE1);
    glUniform1i(shaderProgram.getUniformLocation("destroysamp"), 1);

    glGenerateMipmap(GL_TEXTURE_2D);

    glm::mat4 model;
    model =
        glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::mat4 view =
        glm::lookAt(glm::vec3(1.5f, 1.5f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 proj =
        glm::perspective(glm::radians(75.0f), 800.0f / 800.0f, 0.1f, 100.0f);

    glm::mat4 mvp = proj * view * model;

    glUniformMatrix4fv(shaderProgram.getUniformLocation("mvp"), 1, GL_FALSE,
                       glm::value_ptr(mvp));

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

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return EXIT_SUCCESS;
}
