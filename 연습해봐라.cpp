//배경색 칠하기//////////////////////////////////////////
// sb6.h 헤더 파일을 포함시킨다.
#include <sb6.h>
#include <vmath.h>

// sb6::application을 상속받는다.
class my_application : public sb6::application
{
public:
	GLuint compile_shaders(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		static const GLchar* vertex_shader_source[] =
		{
			"#version 430 core                                                \n"
			"layout (location = 0) in vec3 pos;                                \n"
			"layout (location = 1) in vec3 color;                            \n"
			"uniform mat4 rotMat;                                            \n"
			"out vec3 vsColor;                                                \n"
			"void main(void)                                                \n"
			"{                                                                \n"
			"    gl_Position = rotMat*vec4(pos.x, pos.y, pos.z, 1.0);        \n"
			"    vsColor = color;                                            \n"
			"}                                                                \n"
		};

		static const GLchar* fragment_shader_source[] =
		{
			"#version 430 core                                                \n"
			"in vec3 vsColor;                                                \n"
			"out vec4 fragcolor;                                            \n"
			"void main(void)                                                \n"
			"{                                                                \n"
			"    fragcolor = vec4(vsColor,1.0);                                \n"
			"}                                                                \n"
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

	virtual void startup() {
		rendering_program = compile_shaders();
		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);

		GLfloat vertices[] = {
			//앞
			0.25f, -0.25f, 0.5f, 1.0f, 0.0f, 0.0f,
			-0.25f, 0.25f, 0.5f, 1.0f, 0.0f, 0.0f,
			0.25f, 0.25f, 0.5f, 1.0f, 0.0f, 0.0f,

			-0.25f, -0.25f, 0.5f, 1.0f, 0.0f, 0.0f,
			-0.25f, 0.25f, 0.5f, 1.0f, 0.0f, 0.0f,
			0.25f, -0.25f, 0.5f, 1.0f, 0.0f, 0.0f,

			//뒤
			0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.25f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.25f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f,

			-0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.25f, 0.25f, 0.0f, 0.0f, 0.0f, 1.0f,

			//우
			0.25f, 0.25f, 0.5f, 1.0f, 0.0f, 1.0f,
			0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.25f, -0.25f, 0.5f, 1.0f, 0.0f, 1.0f,

			0.25f, -0.25f, 0.5f, 1.0f, 0.0f, 1.0f,
			0.25f, 0.25f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 1.0f,
			//왼
			-0.25f, 0.25f, 0.5f, 0.0f, 1.0f, 0.0f,
			-0.25f, -0.25f, 0.5f, 0.0f, 1.0f, 0.0f,
			-0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f,

			-0.25f, -0.25f, 0.5f, 0.0f, 1.0f, 0.0f,
			-0.25f, -0.25f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 0.0f,

			//상
			-0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.25f, 0.25f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.25f, 0.25f, 0.5f, 0.0f, 1.0f, 1.0f,

			0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.25f, 0.25f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.25f, 0.25f, 0.0f, 0.0f, 1.0f, 1.0f,

			//하
			-0.25f, -0.25f, 0.0f, 1.0f, 1.0f, 0.0f,
			-0.25f, -0.25f, 0.5f, 1.0f, 1.0f, 0.0f,
			0.25f, -0.25f, 0.5f, 1.0f, 1.0f, 0.0f,

			0.25f, -0.25f, 0.0f, 1.0f, 1.0f, 0.0f,
			-0.25f, -0.25f, 0.0f, 1.0f, 1.0f, 0.0f,
			0.25f, -0.25f, 0.5f, 1.0f, 1.0f, 0.0f,


		};

		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CW);
	}

	virtual void shutdown()
	{
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program);
	}
	// 렌더링 virtual 함수를 작성해서 오버라이딩한다.
	virtual void render(double currentTime)
	{
		const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, black);

		glUseProgram(rendering_program);

		vmath::mat4 transM = vmath::translate(vmath::vec3((float)sin(currentTime), 0.0f, (float)cos(currentTime) * 0.3f));
		float angle = currentTime * 150;
		vmath::mat4 rotateM = vmath::rotate(angle, 0.0f, 1.0f, 0.0f);
		vmath::vec3 eye(0.0, 1.0, -2.0);
		vmath::vec3 center(0.0, 0.0, 0.0);
		vmath::vec3 up(0.0, 1.0, 0.0);
		vmath::mat4 lookAt = vmath::lookat(eye, center, up);
		vmath::mat4 projM = vmath::perspective((float)cos(currentTime) * 20.0f + 50.0f, info.windowWidth / info.windowHeight, 0.1f, 1000.0f);

		GLint rotMatLocation = glGetUniformLocation(rendering_program, "rotMat");

		glUniformMatrix4fv(rotMatLocation, 1, GL_FALSE, projM * lookAt * transM * rotateM);

		glBindVertexArray(vertex_array_object);

		glDrawArrays(GL_TRIANGLES, 0, 36);


	}
private:
	GLuint rendering_program;
	GLuint vertex_array_object;
};

// DECLARE_MAIN의 하나뿐인 인스턴스
DECLARE_MAIN(my_application)