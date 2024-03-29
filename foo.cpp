// Headers
#include <GL/glew.h>
#include <GL/glfw.h>
#include <iostream>

// Shader sources
const char* vertexSource =
"#version 150\n"
"in vec2 position;"
"in vec3 color;"
"out vec3 Color;"
"void main() {"
"	Color = color;"
"	gl_Position = vec4( position, 0.0, 1.0 );"
"}";
const char* fragmentSource =
"#version 150\n"
"in vec3 Color;"
"out vec4 outColor;"
"void main() {"
"	outColor = vec4( Color, 1.0 );"
"}";

int main()
{
	glfwInit();
    glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
    glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 2 );
    glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    
    glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, GL_TRUE );
    glfwOpenWindow( 800, 600, 0, 0, 0, 0, 0, 0, GLFW_WINDOW );
    glfwSetWindowTitle( "OpenGL" );
	
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();
    
	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
    
	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers( 1, &vbo );
    
	float vertices[] = {
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
	};
    
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    
	// Create an element array
	GLuint ebo;
	glGenBuffers( 1, &ebo );
    
	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};
    
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );
    
	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexSource, NULL );
	glCompileShader( vertexShader );
    
	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragmentSource, NULL );
	glCompileShader( fragmentShader );
    
	// Link the vertex and fragment shader into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader( shaderProgram, vertexShader );
	glAttachShader( shaderProgram, fragmentShader );
	glBindFragDataLocation( shaderProgram, 0, "outColor" );
	glLinkProgram( shaderProgram );
	glUseProgram( shaderProgram );
    
	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation( shaderProgram, "position" );
	glEnableVertexAttribArray( posAttrib );
	glVertexAttribPointer( posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), 0 );
    
	GLint colAttrib = glGetAttribLocation( shaderProgram, "color" );
	glEnableVertexAttribArray( colAttrib );
	glVertexAttribPointer( colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( float ), (void*)( 2 * sizeof( float ) ) );
    
	while ( glfwGetWindowParam(GLFW_OPENED) )
	{
        if ( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS )
            break;
        
		// Clear the screen to black
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT );
		
		// Draw a rectangle from the 2 triangles using 6 indices
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
        
		// Swap buffers
        glfwSwapBuffers();
	}
    
	glDeleteProgram( shaderProgram );
	glDeleteShader( fragmentShader );
	glDeleteShader( vertexShader );
    
	glDeleteBuffers( 1, &ebo );
	glDeleteBuffers( 1, &vbo );
    
	glDeleteVertexArrays( 1, &vao );
}
