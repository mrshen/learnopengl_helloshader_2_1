#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "my_shader.h"

#include <iostream>
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

// 第一个三角形
float vertices_orange[] = {
	-.25f, .5f, 0.0f,
	-.5f, .0f, 0.0f,
	.0f, 0.0f, 0.0f
};
// 第二个三角形
float vertices_yellow[] = {
	.25f, 0.5f, 0.0f,
	0.0f, .0f, 0.0f,
	.5f, .0f, 0.0f
};

void framebuffer_cb(GLFWwindow*, int, int);
void input_process(GLFWwindow*);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "create window fail!" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// process func address with glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "glad fail!" << endl;
		glfwTerminate();
		return -1;
	}
	// set frame_buffer callback
	glfwSetFramebufferSizeCallback(window, framebuffer_cb);

	// build and compile our shader program
	// ------------------------------------
	// vertex shader program
	MyShader shaderOrange = MyShader(
		"D:\\shaders\\triangle_orange_shader\\simple_triangle_vertex.vs",
		"D:\\shaders\\triangle_orange_shader\\simple_triangle_fragment.fs"
	);

	MyShader shaderYellow = MyShader(
		"D:\\shaders\\triangle_yellow_shader\\simple_triangle_vertex.vs",
		"D:\\shaders\\triangle_yellow_shader\\simple_triangle_fragment.fs"
	);
	
	GLuint VAO[2];
	glGenVertexArrays(2, VAO);

	GLuint VBO[2];
	glGenBuffers(2, VBO);

	// first triangle data binding
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_orange), vertices_orange, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// second triangle data binding
	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_yellow), vertices_yellow, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		input_process(window);

		glClearColor(0.0f, 0.0f, 0.5f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderOrange.use();
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		shaderYellow.use();
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	//glDeleteBuffers(1, &EBO);

	// terminate
	glfwTerminate();
	return 0;
}

void framebuffer_cb(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void input_process(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}