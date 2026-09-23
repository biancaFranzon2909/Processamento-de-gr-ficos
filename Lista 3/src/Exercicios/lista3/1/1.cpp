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

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
int setupShader();
void setupGeometry();

const GLuint WIDTH = 800, HEIGHT = 600;
vector<GLfloat> g_vertices;
vector<vec4> g_coresTriangulos;
GLuint g_VBO, g_VAO;
vec4 g_corAtual;

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
int setupShader();
void setupGeometry();

const GLchar *vertexShaderSource = R"glsl(
 #version 400
 layout (location = 0) in vec3 position;
 uniform mat4 projection;
 void main()
 {
     gl_Position = projection * vec4(position.x, position.y, position.z, 1.0);
 }
)glsl";

const GLchar *fragmentShaderSource = R"glsl(
 #version 400
 uniform vec4 inputColor;
 out vec4 color;
 void main()
 {
     color = inputColor;
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

    GLint colorLoc = glGetUniformLocation(shaderID, "inputColor");
    GLint projLoc = glGetUniformLocation(shaderID, "projection");

    mat4 projection = ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, value_ptr(projection));

    // Cor inicial para o primeiro triângulo
    g_corAtual = vec4((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1.0f);

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
        glBufferData(GL_ARRAY_BUFFER, g_vertices.size() * sizeof(GLfloat), g_vertices.data(), GL_DYNAMIC_DRAW);

        if (!g_vertices.empty()) {
            glBindBuffer(GL_ARRAY_BUFFER, g_VBO);
            glBufferData(GL_ARRAY_BUFFER, g_vertices.size() * sizeof(GLfloat), g_vertices.data(), GL_DYNAMIC_DRAW);

            
            int numTriangulos = g_coresTriangulos.size();
            for (int i = 0; i < numTriangulos; i++)
            {
                glUniform4f(colorLoc, g_coresTriangulos[i].r, g_coresTriangulos[i].g, g_coresTriangulos[i].b, 1.0f);
                glDrawArrays(GL_TRIANGLES, i * 3, 3);
            }

            int totalVertices = g_vertices.size() / 3;
            int pontosSobrando = totalVertices % 3;
            if (pontosSobrando > 0)
            {
                glPointSize(8.0f);
                glUniform4f(colorLoc, g_corAtual.r, g_corAtual.g, g_corAtual.b, 1.0f);
                glDrawArrays(GL_POINTS, numTriangulos * 3, pontosSobrando);
            }
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

        g_vertices.push_back((GLfloat)xpos);
        g_vertices.push_back((GLfloat)ypos);
        g_vertices.push_back(0.0f);

        cout << "Vértice criado em: (" << xpos << ", " << ypos << ")" << endl;

        // A cada 3 vértices, faz novo triângulo
        int totalVertices = g_vertices.size() / 3;
        if (totalVertices % 3 == 0)
        {
            // Guarda a cor utilizada para esse triângulo
            g_coresTriangulos.push_back(g_corAtual);

            // Sorteia uma nova cor para o PRÓXIMO triângulo
            g_corAtual = vec4((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1.0f);
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, (GLvoid *)0);
    glEnableVertexAttribArray(0);

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