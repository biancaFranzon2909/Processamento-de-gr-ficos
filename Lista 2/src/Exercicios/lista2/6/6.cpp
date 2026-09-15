#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

struct Vertex {
    GLfloat x, y, z;
    GLfloat r, g, b;
};

const GLuint WIDTH = 800, HEIGHT = 600;
vector<Vertex> g_vertices;
GLuint g_VBO, g_VAO;
vec3 g_currentTriangleColor;
int g_clickCount = 0;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
int setupShader();
void setupGeometry();

const GLchar *vertexShaderSource = R"glsl(
 #version 400
 layout (location = 0) in vec3 position;
 layout (location = 1) in vec3 color;
 uniform mat4 projection;
 out vec3 vertColor;
 void main()
 {
     gl_Position = projection * vec4(position, 1.0);
     vertColor = color;
 }
)glsl";

const GLchar *fragmentShaderSource = R"glsl(
 #version 400
 in vec3 vertColor;
 out vec4 color;
 void main()
 {
     color = vec4(vertColor, 1.0);
 }
)glsl";

int main()
{
    srand((unsigned int)time(NULL));

    glfwInit();
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Exercício 6 - Triângulos no Clique", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;

    GLuint shaderID = setupShader();
    setupGeometry();

    glUseProgram(shaderID);

    mat4 projection = ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f);
    GLint projLoc = glGetUniformLocation(shaderID, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));

    // Cor inicial para o primeiro triângulo
    g_currentTriangleColor = vec3((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(g_VAO);

        glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
        glBufferData(GL_ARRAY_BUFFER, g_vertices.size() * sizeof(Vertex), g_vertices.data(), GL_DYNAMIC_DRAW);

        int numVerticesToDraw = (g_vertices.size() / 3) * 3;
        if (numVerticesToDraw > 0)
        {
            glDrawArrays(GL_TRIANGLES, 0, numVerticesToDraw);
        }

        if (g_vertices.size() % 3 != 0)
        {
            glPointSize(8.0f);
            glDrawArrays(GL_POINTS, numVerticesToDraw, g_vertices.size() - numVerticesToDraw);
        }

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &g_VAO);
    glDeleteBuffers(1, &g_VBO);
    glfwTerminate();
    return 0;
}

// Clique do Mouse
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        // Adiciona o novo vértice com a cor atual
        Vertex v;
        v.x = (GLfloat)xpos;
        v.y = (GLfloat)ypos;
        v.z = 0.0f;
        v.r = g_currentTriangleColor.r;
        v.g = g_currentTriangleColor.g;
        v.b = g_currentTriangleColor.b;

        g_vertices.push_back(v);
        g_clickCount++;

        cout << "Vértice criado em: (" << xpos << ", " << ypos << ")" << endl;

        // A cada 3 vértices, sorteia uma nova cor para o PRÓXIMO triângulo
        if (g_clickCount % 3 == 0)
        {
            g_currentTriangleColor = vec3(
                (rand() % 80 + 20) / 100.0f,
                (rand() % 80 + 20) / 100.0f,
                (rand() % 80 + 20) / 100.0f
            );
            cout << "Triângulo " << (g_clickCount / 3) << " concluído!" << endl;
        }
    }
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void setupGeometry()
{
    glGenBuffers(1, &g_VBO);
    glGenVertexArrays(1, &g_VAO);

    glBindVertexArray(g_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, g_VBO);

    // Atributo 0: Posição (x, y, z)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, x));
    glEnableVertexAttribArray(0);

    // Atributo 1: Cor (r, g, b)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, r));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

int setupShader()
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}