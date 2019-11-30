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

	//�������� ����������� ��������� ������ OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	//��������� �������� ��� �������� ��������� ��������
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//���������� ����������� ��������� ������� ����
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

	GLfloat treug[] = {
		// �������           // �����
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ������ ������ ����
		-0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   // ������ ����� ����
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    // ������� ����

		-0.9f,  0.9f, 0.0f,  1.0f, 0.0f, 0.0f,   
		-0.9f, -0.9f, 0.0f,  0.0f, 0.0f, 0.0f,   //�����

		 0.9f,  0.9f, 0.0f,  0.0f, 0.0f, 0.0f    //�����
	};

	//��������� ������
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *vertexShaderSource = R"(
		#version 450 core
		layout (location = 0) in vec3 position; // ������������� ������� ���������� � ������������ � 0
		layout (location = 1) in vec3 color;    // � ������� ���������� � ������ � 1

		out vec3 ourColor; // �������� ���� �� ����������� ������

		void main()
		{
			gl_Position = vec4(position, 1.0);
			ourColor = color; // ������������� �������� �����, ���������� �� ��������� ������
		};)";

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //����������� �������� ��� ������� � ������� �������
	glCompileShader(vertexShader); //�����������

	//����������� ������
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar *fragmentShaderSource = R"(#version 450 core
		in vec3 ourColor;
		out vec4 color;

		void main()
		{
			color = vec4(ourColor, 1.0f);
		};)";

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//������ ���������� �������
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//������ ���������� ������
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(treug), treug, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
		
	//��������� ���������
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

///////////////////////////////////////////////////////////////////////////////////////

	// ������� ����
	while (glfwWindowShouldClose(window) == FALSE)
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glLineWidth(5);
		glDrawArrays(GL_LINES, 3, 2);
		glPointSize(10);
		glDrawArrays(GL_POINTS, 5, 1);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glfwTerminate();
	return 0;
}