#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


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

	//three 3d coords
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	//pg. 30
	//vertex shader program
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	//pg. 28-29
	//identifier for vertex buffer object 
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	//binds VBO buffer to buffer object type GL_ARRAY_BUFFER
	//any buffer calls to this type will now act on VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//copies vertex data to buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//pg. 31
	unsigned int vertexShader;
	//creates a vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//attach shader src code (vertexShaderSource string) to
	//  shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//test if shader has compiled
	int success;
	char infolog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::VERTEXCOMPILATION_FAILED\n"
			<< infolog << std::endl;
	}

	//pg. 32 - creating fragment shader
	//src code for shader
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		" FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	//code is the same as creating the vertex shader except for
	//  the arg passed to glCreateShader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//pg. 32-33 - creating a shader program object
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	//attach compiled shaders from above to program object
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// linking the shaders (to the program object)*
	//   *not fully sure about description above
	glLinkProgram(shaderProgram);

	//makes every shader and rendering call after this fcn call use
	//  the shaders in shaderProgram 
	glUseProgram(shaderProgram);

	//feels similar to deallocating shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);


		//check and call events and swap buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//free() but for glfw
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//pg. 24
void processInput(GLFWwindow* window)
{
	//check whether user has pressed esc
	//  if the user has, then the window close
	//  property is set to true and make the render
	//  loop terminate
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
