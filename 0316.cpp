#include <sb6.h>
#include <vmath.h>

class my_application : public sb6::application
{
public:
	GLuint compile_shaders(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		static const GLchar * vertex_shader_source[] =
		{
			"# version 430 core                                     \n"
			"                                                \n"
			"void main(void)                                    \n"
			"{                                                \n"
			"   const vec4 vertices[12]=vec4[12](vec4(0.0, 0.0, 0.5, 1.0),  \n"
			"                           vec4(0.5, 0.0, 0.5, 1.0),           \n"
			"                           vec4(0.5, 0.5, 0.5, 1.0),           \n"

			"                           vec4(0.0, 0.0, 0.5, 1.0),           \n"
			"                           vec4(-0.5, 0.0, 0.5, 1.0),          \n"
			"                           vec4(-0.5, -0.5, 0.5, 1.0),         \n"

			"                           vec4(0.0, 0.0, 0.5, 1.0),           \n"
			"                           vec4(0, 0.5, 0.5, 1.0),             \n"
			"                           vec4(-0.5, 0.5, 0.5, 1.0),          \n"

			"                           vec4(0.0, 0.0, 0.5, 1.0),           \n"
			"                           vec4(0.5, -0.5, 0.5, 1.0),          \n"
			"                           vec4(0.0, -0.5, 0.5, 1.0));          \n"


			"                                                 \n"
			"   gl_Position   = vertices[gl_VertexID];                      \n"
			"}                                                 \n"
		};

		static const GLchar * fragment_shader_source[] =
		{
			"#version 430 core                                    \n"
			"out vec4 color;                                    \n"
			"void main(void)                                    \n"
			"{                                                \n"
			"   color = vec4(0.0, 0.8, 1.0, 1.0);                     \n"
			"}                                                \n"
		};

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		program = glCreateProgram();


		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;

	}

	GLuint compile_shaders2(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		static const GLchar * vertex_shader_source[] =
		{
			"# version 430 core                                     \n"
			"                                                \n"
			"void main(void)                                    \n"
			"{                                                \n"
			"   const vec4 vertices[6]= vec4[6](vec4(0.02, 0.0, 0.5, 1.0),   \n"
			"                           vec4(-0.02, 0.0, 0.5, 1.0),          \n"
			"                           vec4(0.02, -2.0, 0.5, 1.0),          \n"

			"                           vec4(0.02, -2.0, 0.5, 1.0),          \n"
			"                           vec4(-0.02, -2.0, 0.5, 1.0),         \n"
			"                           vec4(-0.02, 0.0, 0.5, 1.0));         \n"

			"   gl_Position   = vertices[gl_VertexID];                      \n"
			"}                                                 \n"
		};

		static const GLchar * fragment_shader_source[] =
		{
			"#version 430 core                                    \n"
			"out vec4 color;                                    \n"
			"void main(void)                                    \n"
			"{                                                \n"
			"   color = vec4(1.0, 0.2, 0.2, 1.0);                     \n"
			"}                                                \n"
		};

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		program = glCreateProgram();


		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;

	}

	virtual void startup(){
		rendering_program = compile_shaders();
		rendering_program2 = compile_shaders2();
		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);
	}

	virtual void shutdown()
	{
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program);
	}
	
	virtual void render(double currentTime)
	{
		const GLfloat red[] = { (float)sin(currentTime) * 0.5f + 0.5f,
			(float)cos(currentTime) * 0.5f + 0.5f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, red);

		glUseProgram(rendering_program2);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glUseProgram(rendering_program);

		glDrawArrays(GL_TRIANGLES, 0, 12);


	}
private:
	GLuint rendering_program;
	GLuint rendering_program2;
	GLuint vertex_array_object;
};


DECLARE_MAIN(my_application)