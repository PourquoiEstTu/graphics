#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

/* void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


int main() {
	//initialization stuffs, pg. 20
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//create window object, pg. 21
	GLFWwindow* window = glfwCreateWindow(800, 600, "PINK RECTANGLE", NULL, NULL);
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

	//pg. 37-38 EBOs
	//three 3d coords
	float vertices[] = {
		0.5f, 0.5f, 0.0f,   //top right
		0.5f, -0.5f, 0.0f,  //bottom right 
		-0.5f, -0.5f, 0.0f, //bottom left 
		-0.5f, 0.5f, 0.0f   //top left
	};
	//indices an element buffer object uses to tell 
	//  opengl which coords to draw from vertices[] 
	//  in what order
	unsigned int indices[] = { //we always start from 0
		0, 1, 3, //first triangle
		1, 2, 3  //second triangle  
	};
	
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, 
					GL_STATIC_DRAW);

	//pg. 30
	//vertex shader program
	const char* vertexShaderSource = "#version 330 core\n"
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
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		" FragColor = vec4(1.0f, 0.3f, 0.7f, 1.0f);\n"
		"}\0";

	//create fragmentShader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//pg. 32-33 - creating a shader program object
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//pg. 35-36 creating vertex array objects (VAO)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//pg. 34 - specifiying which parts of our input data (the vertices
	//  array) goes to which vertex attribute in the vertex shader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
		(void*)0);
	//pg. 35
	glEnableVertexAttribArray(0);

	//pg. 40 - works both inside and outside render loop
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		//rendering commands
		//makes every shader and rendering call after this fcn call use
	    //  the shaders in shaderProgram 
		glUseProgram(shaderProgram);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
} */