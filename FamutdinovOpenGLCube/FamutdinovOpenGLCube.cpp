#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <conio.h>


float angle = 0;
float bias_X = 0;
float bias_Y = 0;
float bias_Z = 0;
float delta_bias = 0.1;

GLfloat light_position[] = {-0.5f, -0.5f, -1.0f, 0.0f};
GLfloat diffuse_color[] = {0.0f, 0.0f, 0.2f, 0.1f};

int main(void)
{
    //test commit
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 640, "Lab1", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    float vertices[] = { -0.5,-0.5,-0.5,-0.5,0.5,-0.5,0.5,0.5,-0.5,0.5,-0.5,-0.5,
                         -0.5,-0.5,-0.5,-0.5,-0.5,0.5,0.5,-0.5,0.5,0.5,-0.5,-0.5,
                         -0.5,-0.5,-0.5,-0.5,-0.5,0.5,-0.5,0.5,0.5,-0.5,0.5,-0.5,
                         -0.5,0.5,-0.5,-0.5,0.5,0.5,0.5,0.5,0.5,0.5,0.5,-0.5,
                         -0.5,-0.5,0.5,-0.5,0.5,0.5,0.5,0.5,0.5,0.5,-0.5,0.5,
                         0.5,-0.5,-0.5,0.5,0.5,-0.5,0.5,0.5,0.5,0.5,-0.5,0.5 };

    GLfloat colors[6][3] = {
     {1.0f, 0.0f, 0.0f},  // Красный
     {0.0f, 1.0f, 0.0f},  // Зелёный
     {0.0f, 0.0f, 1.0f},  // Синий
     {1.0f, 1.0f, 0.0f},  // Жёлтый
     {1.0f, 0.0f, 1.0f},  // Фиолетовый
     {0.0f, 1.0f, 1.0f}   // Голубой
    };


    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    /* Loop until the user closes the window */

    //glOrtho(-2,2, -2,2, -2,2);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glFrustum(-1, 1, -1, 1, 1, 100);

    while (!glfwWindowShouldClose(window))
    {
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);

        char key;
        if (angle > 360 or angle < -360) {
            angle = 0;
        }
        /* Render here */
        //glClearColor(0.0f, 0.4f, 0.6f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        glVertexPointer(3, GL_FLOAT, 0, &vertices);
        glEnableClientState(GL_VERTEX_ARRAY);

        if (_kbhit()) { // Проверяем, была ли нажата клавиша
            key = _getch();  // Получаем нажатую клавишу

            // поворот в одну сторону
            if (key == 'u' or key == 'U') {
                angle += 2;

            };

            // поворот в другую сторону
            if (key == 'i' or key == 'I') {
                angle -= 2;

            };

            if (key == 'j' or key == 'J') {
                bias_X -= delta_bias;

            };

            if (key == 'k' or key == 'K') {
                bias_X += delta_bias;

            };

            if (key == 'n'  or key == 'N') {
                bias_Y -= delta_bias;

            };

            if (key == 'm' or key == 'M') {
                bias_Y += delta_bias;

            };

            if (key == 'o' or key == 'O') {
                bias_Z -= delta_bias;

            };

            if (key == 'p' or key == 'P') {
                bias_Z += delta_bias;

            };
        };

        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        for (int i = 0; i < 6; i++) {
            glColor3fv(colors[i]);
            glPushMatrix();
            glTranslatef(bias_X, bias_Y, -4 + bias_Z);
            glRotatef(angle, 1.0f, 1.0f, 0);
            glDrawArrays(GL_QUADS, i * 4, 4);
            glPopMatrix();
        };

        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);

        glDisable(GL_LIGHT0);
        glDisableClientState(GL_VERTEX_ARRAY);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}