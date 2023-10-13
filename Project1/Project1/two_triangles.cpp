#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

/* void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
	//init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Two Triangles",
											NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//set up buffers
	/*if they're right next to each other, then an 
	 *  EBO can be used for the one shared vertex
	 */
	/*float vertices[] = {
		//first triangle
		-0.7f, -0.5f, 0.0f, //leftmost point
		-0.1f, -0.5f, 0.0f,  //point touching other triangle
		-0.4f, 0.5f, 0.0f, //topmost point
		//second triangle
		0.7f, -0.5f, 0.0f,
		0.1f, -0.5f, 0.0f,
		0.4f, 0.5f, 0.0f
		/* //smaller inside triangles just cuz lol
		-0.35f, -0.25f, 0.0f,
		-0.2f, -0.25f, 0.0f,
		-0.2f, -0.4f, 0.0f */ /*
	};

	//vertex buffer object
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
					GL_STATIC_DRAW);

	//vertex shader
	const char *vertShaderSrc = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	unsigned int vertShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
	glCompileShader(vertShader);

	//check vertex shader compilation
	int success;
	char vertinfolog[512];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertShader, 512, NULL, vertinfolog);
		std::cout << "ERROR::SHADER::VERTEXCOMPILATION_FAILED\n" 
			<< vertinfolog << std::endl;
	}

	//fragment shader
	const char *fragShaderSrc = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		" FragColor = vec4(1.0f, 0.3f, 0.7f, 1.0f);\n"
		"}\0";
	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
	glCompileShader(fragShader);

	//check fragment shader compilation
	char fraginfolog[512];
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, fraginfolog);
		std::cout << "ERROR::SHADER::FRAGMENTCOMPILATION_FAILED\n" 
			<< fraginfolog << std::endl;
	}

	//shader program object
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	//vertex array object
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//vertex attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
							(void*)0);
	glEnableVertexAttribArray(0);

	//render loop
	while (!glfwWindowShouldClose(window)) 
	{
		processInput(window);

		//render commands
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
} */
