#define GLEW_STATIC
#include <iostream>
#include <windows.h>

#include <glew.h>
#include <gl/GL.h>
#include <wglew.h>
#include <glfw3.h>

using namespace std;

int main() {

	glfwInit();
	if (glfwInit == GL_FALSE) {
		cout << "Failed to initialize GLFW" << endl;
		return -1;
	}

	//Задается минимальная требуемая версия OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	//Установка профайла для которого создается контекст
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "dz", nullptr, nullptr);

	if (window == nullptr)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << "Failed to initialize GLEW" << endl;
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	/////////////////////////////////////////////////////////////////////////////////////////////
	//GLfloat vertices[] = { -0.9f, -0.9f, 0.9f, 0.9f };


	///////////////////////////////////////////////////////////////////////////////////////

	// Игровой цикл
	while (glfwWindowShouldClose(window) == FALSE)
	{

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_LINE, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	glfwTerminate();
	return 0;

}