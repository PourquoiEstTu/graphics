#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/* void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
	//initialization stuffs, pg. 20
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//create window object, pg. 21
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//tells glfw to make the context of our window the main context
	//  of the current thread, pg. 21
	glfwMakeContextCurrent(window);

	//checks if GLAD is initialized
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//set size of rendering window, pg. 21
	glViewport(0, 0, 800, 600);

	//resizes the viewport everytime the user resizes the window, pg. 22
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//render loop, so window doesnt close immediately
	//  it keeps running until we tell it to stop
	//  more detail on functions on pg. 22-23
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		//rendering commands
		// //pg. 24-25
		// //changes colour of screen (?)
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// //acc prints colour to buffer/window
		glClear(GL_COLOR_BUFFER_BIT);
		

		//check and call events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//free() but for glfw
	//  deletes all resources allocated by glfw
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//pg. 24
void processInput(GLFWwindow *window) 
{
	//check whether user has pressed esc
	//  if the user has, then the window close
	//  property is set to true and make the render
	//  loop terminate
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
} */
