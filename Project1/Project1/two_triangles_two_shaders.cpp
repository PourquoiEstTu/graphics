#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

//vertex shader source program
const char *vertShaderSrc = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

//fragment shader source program
const char *fragShaderSrc = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(1.0f, 0.3f, 0.7f, 1.0f);\n"
    "}\0";

const char *fragShaderSrc1 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    " FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\0";

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
	float vertices1[] = {
		//first triangle
		-0.7f, -0.5f, 0.0f, //leftmost point
		-0.1f, -0.5f, 0.0f,  //point touching other triangle
		-0.4f, 0.5f, 0.0f, //topmost point
		//second triangle
		0.7f, -0.5f, 0.0f,
		0.1f, -0.5f, 0.0f,
		0.4f, 0.5f, 0.0f
	};
    //pretty easy to render two triangles with two arrays as well
    // float vertices2[] = {
	// 	//second triangle
	// 	0.7f, -0.5f, 0.0f,
	// 	0.1f, -0.5f, 0.0f,
	// 	0.4f, 0.5f, 0.0f
    // };

	//vertex buffer objects
	unsigned int vbo1, vbo2;
	glGenBuffers(1, &vbo1);
    glGenBuffers(1, &vbo2);
	// glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
	// 				GL_STATIC_DRAW);

	//vertex shader
	unsigned int vertShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
	glCompileShader(vertShader);

	//check vertex shader compilation
	int success;
	char infolog[512];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" 
			<< infolog << std::endl;
	}

	//fragment shader
	unsigned int fragShader, fragShader1;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    fragShader1 = glCreateShader(GL_FRAGMENT_SHADER);

    //fragShader
	glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
	glCompileShader(fragShader);
    //fragShader1
	glShaderSource(fragShader1, 1, &fragShaderSrc1, NULL);
	glCompileShader(fragShader1);

	//check fragment shader compilation
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" 
			<< infolog << std::endl;
	}
	glGetShaderiv(fragShader1, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" 
			<< infolog << std::endl;
	}

	//shader program object
	unsigned int shaderProgram, shaderProgram1;
	shaderProgram = glCreateProgram();
	shaderProgram1 = glCreateProgram();

    //shaderProgram setup
	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

    //shaderProgram setup
	glAttachShader(shaderProgram1, vertShader);
	glAttachShader(shaderProgram1, fragShader1);
	glLinkProgram(shaderProgram1);

    //check if shader program object compiled
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" 
			<< infolog << std::endl;
    }

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	glDeleteShader(fragShader1);

	//vertex array object
	unsigned int vao1, vao2;
	glGenVertexArrays(1, &vao1);
    glGenVertexArrays(1, &vao2);

    //instructions for vao1
	glBindVertexArray(vao1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1,
                    GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
							(void*)0);
	glEnableVertexAttribArray(0);

    //instructions for vao1
	glBindVertexArray(vao2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1,
                    GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
							(void*)0);
	glEnableVertexAttribArray(0);

	//render loop
	while (!glfwWindowShouldClose(window)) 
	{
		processInput(window);

		//render commands
        glUseProgram(shaderProgram);
        //render first triangle
		glBindVertexArray(vao1);
		glDrawArrays(GL_TRIANGLES, 0, 3);
        //render second 
        glUseProgram(shaderProgram1);
		glBindVertexArray(vao2);
		glDrawArrays(GL_TRIANGLES, 3, 3);

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
}