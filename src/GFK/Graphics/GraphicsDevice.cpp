#include <GFK/Graphics/GraphicsDevice.hpp>
#include <GFK/Graphics/Color.hpp>
#include <GFK/Graphics/PackedColor.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <GFK/Graphics/Shader.hpp>
#include <iostream>

namespace gfk
{

// Render scene
void display(GLuint &vao);

// Initialize the data to be rendered
void initialize(GLuint &vao);

GLuint vao;

// Render scene
void display(GLuint &vao) {
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 12);
}

void initialize(GLuint &vao) {
	// Use a Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 4 triangles to be rendered
	GLfloat vertices_position[24] = {
		0.0, 0.0,
		0.5, 0.0,
		0.5, 0.5,

		0.0, 0.0,
		0.0, 0.5,
		-0.5, 0.5,

		0.0, 0.0,
		-0.5, 0.0,
		-0.5, -0.5,		

		0.0, 0.0,
		0.0, -0.5,
		0.5, -0.5,
	};

	// Create a Vector Buffer Object that will store the vertices on video memory
	GLuint vbo;
	glGenBuffers(1, &vbo);

	// Allocate space and upload the data from CPU to GPU
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_position), vertices_position, GL_STATIC_DRAW);	

	//GLuint shaderProgram = create_program("vertShader.vs", "fragShader.fs");

	Shader shader = Shader::CreateFromFile("vertShader.vs", "fragShader.fs");

	// Get the location of the attributes that enters in the vertex shader
	GLint position_attribute = glGetAttribLocation(shader.GetGLShaderID(), "position");

	// Specify how the data for position can be accessed
	glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable the attribute
	glEnableVertexAttribArray(position_attribute);
	std::cout << "Initialized VAO" << std::endl;
}

GraphicsDevice::GraphicsDevice()
{
	
}

GraphicsDevice::~GraphicsDevice()
{

}

void GraphicsDevice::Initialize()
{
	std::cout << "OpenGL - " << glGetString( GL_VERSION ) << std::endl;

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
	}

	std::cout << "Initialized GLEW" << std::endl;

	initialize(vao);
}

void GraphicsDevice::SetClearColor(const gfk::Color &color)
{
	glClearColor(color.R, color.G, color.B, color.A);
}

void GraphicsDevice::SetClearColor(const gfk::PackedColor &color)
{
	glClearColor(color.GetR(), color.GetG(), color.GetB(), color.GetA());
}

void GraphicsDevice::SetDepthClearValue(float depth)
{
	glClearDepth(depth);
}

void GraphicsDevice::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	display(vao);
}

void GraphicsDevice::ClearDepth()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void GraphicsDevice::ClearColor()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsDevice::ResizeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
}

}
