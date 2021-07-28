#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

//int main(void)
//{
//	GLFWwindow* window;
//	if (!glfwInit())
//		return -1;
//	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//	if (!window)
//	{
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	while (!glfwWindowShouldClose(window))
//	{
//		glClear(GL_COLOR_BUFFER_BIT);
//		glBegin(GL_TRIANGLES);
//		glVertex2f(0, 0);
//		glVertex2f(0, 1);
//		glVertex2f(1, 0);
//		glEnd();
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//	glfwTerminate();
//	return 0;
//}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window,GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

//float vertices[] =
//{
//	//// 第一个三角形
//	//0.5f, 0.5f, 0.0f,   // 右上角
//	//0.5f, -0.5f, 0.0f,  // 右下角
//	//-0.5f, 0.5f, 0.0f,  // 左上角
//	//// 第二个三角形
//	//0.5f, -0.5f, 0.0f,  // 右下角
//	//-0.5f, -0.5f, 0.0f, // 左下角
//	//-0.5f, 0.5f, 0.0f   // 左上角
//	 0.5f,  0.5f, 0.0f,   // 右上角
//	 0.5f, -0.5f, 0.0f,  // 右下角
//	-0.5f, -0.5f, 0.0f, // 左下角
//	-0.5f,  0.5f, 0.0f   // 左上角
//};
//unsigned int indices[] = 
//{ 
//	// 注意索引从0开始! 
//	0, 1, 3, // 第一个三角形
//	1, 2, 3,  // 第二个三角形
//	0, 1, 2
//};



const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"ourColor = aColor;\n"
"}\n"
;

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(ourColor,1.0f);\n"
"\n"
"}\n"
;
const char* fragmentShaderSource2 =
"#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"FragColor = ourColor;\n"
"\n"
"}\n"
;
//
//static unsigned int CompileShader(const unsigned int type,const std::string& source)
//{
//	const char* src = source.c_str();
//	unsigned int shader = glCreateShader(type);
//	glShaderSource(shader, 1, &src, nullptr);
//	glCompileShader(shader);
//	return shader;
//}
//
//static unsigned int CreateShader(const std::string& vertexShaderSource,const std::string& fragmentShaderSource)
//{
//	unsigned int shaderProgram;
//	shaderProgram = glCreateProgram();
//	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
//	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER,fragmentShaderSource);
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	return shaderProgram;
//}

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(960, 540, "Fust", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Open Window Failed!!!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Init GLEW Failed!!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glViewport(0, 0, 960, 540);


	/*unsigned int VAOO, VBOO, EBOO;
	glGenVertexArrays(1, &VAOO);
	glGenBuffers(1, &VBOO);
	glGenBuffers(1, &EBOO);
	glBindVertexArray(VAOO);
	glBindBuffer(GL_ARRAY_BUFFER, VBOO);
	glBufferData(GL_ARRAY_BUFFER, 1, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 1, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);*/
	
	/*
	//顶点数组对象
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//顶点缓冲对象
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//索引缓冲对象
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);
	*/

	float firstTriangle[] = 
	{
	-0.9f, -0.5f, 0.0f,  // left 
	-0.0f, -0.5f, 0.0f,  // right
	-0.45f, 0.5f, 0.0f,  // top 
	};
	float secondTriangle[] = 
	{
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	};

	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	//unsigned int VBO, VAO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//glBindVertexArray(VAO);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);
	//// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	/*unsigned int VAO[2], VBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);*/

	//顶点着色器
	/*unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);*/

	////片元（片段）着色器 
	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	//unsigned int fragmentShader2;
	//fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	//glCompileShader(fragmentShader2);

	//unsigned int shaderProgram2;
	//shaderProgram2 = glCreateProgram();
	//glAttachShader(shaderProgram2, vertexShader);
	//glAttachShader(shaderProgram2, fragmentShader2);
	//glLinkProgram(shaderProgram2);

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader2);

	//着色器程序
	/*unsigned int shaderProgram = CreateShader(vertexShaderSource, fragmentShaderSource);
	unsigned int shaderProgram2 = CreateShader(vertexShaderSource,fragmentShaderSource2);*/
	//shaderProgram = glCreateProgram();
	////添加着色器
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	////链接着色器
	//glLinkProgram(shaderProgram);
	////删除着色器对象
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;


	float positions[] =
	{
		100.0f,100.0f,0.0f,0.0f,   // 0
		200.0f,100.0f,1.0f,0.0f,   // 1
		200.0f,200.0f,1.0f,1.0f,   // 2
		100.0f,200.0f,0.0f,1.0f   // 3
	};
	//float positions[] =
	//{
	//	-0.5f,-0.5f,0.0f,0.0f,   // 0
	//	 0.5f,-0.5f,1.0f,0.0f,   // 1
	//	 0.5f, 0.5f,1.0f,1.0f,   // 2
	//	-0.5f, 0.5f,0.0f,1.0f   // 3
	//};

	unsigned int indices[] =
	{
		0,1,2,
		2,3,0
	};

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	//glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);

	Shader shader("res/Shaders/Basic.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
	shader.SetUniformMat4f("u_MVP", proj);

	Texture texture("res/textures/Doraemon.png");
	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	Renderer renderer;

	float r = 0.0f;
	float increment = 0.05f;

	//glUseProgram(shaderProgram);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		shader.Bind();
		shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

		renderer.Draw(va,ib,shader);

		if (r>1.0f)
		{
			increment = -0.05f;
		}
		else if(r<0.0f)
		{
			increment = 0.05f;
		}
		r += increment;

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//uniform
	/*	glUseProgram(shaderProgram2);
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram2, "ourColor");
		glUniform4f(vertexColorLocation, 0, greenValue, 0, 1);*/

		//glUseProgram(shaderProgram);

		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		//使用着色器程序
		//glUseProgram(shaderProgram);

	/*	glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);*/
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		//glUseProgram(shaderProgram);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBindVertexArray(0);
		//glBindVertexArray(VAOO);
		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		//glDrawArrays(GL_TRIANGLES, 0, 6);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	/*glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);*/
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	//glDeleteVertexArrays(1, &VAOO);
	//glDeleteBuffers(1, &VBOO);
	//glDeleteBuffers(1, &EBOO);

	//glDeleteProgram(shaderProgram);
	//glDeleteProgram(shaderProgram2);


	glfwTerminate();
	return 0;
}

