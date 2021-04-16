
// sb6.h 헤더 파일을 포함시킨다.
#include <sb6.h>
#include <vmath.h>

// sb6::application을 상속받는다.
class my_application : public sb6::application
{
public:
	// 쉐이더 컴파일한다.
	GLuint compile_shaders_pinwheel(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		// 버텍스 쉐이더 소스 코드
		static const GLchar * vertex_shader_source[] =
		{
			"#version 430 core                                       \n"
			"                                                   \n"
			"layout (location = 0) in vec4 color1;                          \n"
			"layout (location = 1) in vec4 color2;                          \n"
			"layout (location = 2) in vec4 color3;                          \n"
			"layout (location = 3) in float time;                        \n"
			"out vec4 vs_color;                                        \n"
			"void main(void)                                       \n"
			"{                                                   \n"
			"   const vec4 vertices[12] = vec4[12](vec4(0.0, 0.0, 0.5, 1.0),   \n"
			"                              vec4(-0.5, 0.5, 0.5, 1.0),   \n"
			"                              vec4(0.0, 0.5, 0.5, 1.0),   \n"
			"                              vec4(0.0, 0.0, 0.5, 1.0),   \n"
			"                              vec4(-0.5, -0.5, 0.5, 1.0),   \n"
			"                              vec4(-0.5, 0.0, 0.5, 1.0),   \n"
			"                              vec4(0.0, 0.0, 0.5, 1.0),   \n"
			"                              vec4(0.5, -0.5, 0.5, 1.0),   \n"
			"                              vec4(0.0, -0.5, 0.5, 1.0),   \n"
			"                              vec4(0.0, 0.0, 0.5, 1.0),   \n"
			"                              vec4(0.5, 0.5, 0.5, 1.0),   \n"
			"                              vec4(0.5, 0.0, 0.5, 1.0));   \n"
			"   const vec4 colors[3] = vec4[3](color1, color2, color3);      \n"
			"   mat4 wM = mat4(1.0);                                    \n"
			"   wM[0][0] =cos(radians(time));                           \n"
			"   wM[1][0] =-sin(radians(time));                          \n"
			"   wM[0][1] =sin(radians(time));                           \n"
			"   wM[1][1] =cos(radians(time));                           \n"
			"   gl_Position = wM*vertices[gl_VertexID];                     \n"
			"   vs_color = colors[gl_VertexID%3];                     \n"
			"}                                                   \n"
		};

		// 프래그먼트 쉐이더 소스 코드
		static const GLchar * fragment_shader_source[] =
		{
			"#version 430 core                          \n"
			"                                           \n"
			"in vec4 vs_color;                      \n"
			"out vec4 color;                            \n"
			"                                           \n"
			"void main(void)                            \n"
			"{                                          \n"
			"    color = vs_color;//vec4(0.0, 0.8, 1.0, 1.0);      \n"
			"}                                          \n"
		};

		// 버텍스 쉐이더를 생성하고 컴파일한다.
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		// 프래그먼트 쉐이더를 생성하고 컴파일한다.
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		// 프로그램을 생성하고 쉐이더를 Attach시키고 링크한다.
		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		// 이제 프로그램이 쉐이더를 소유하므로 쉐이더를 삭제한다.
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}

	GLuint compile_shaders_stick(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		// 버텍스 쉐이더 소스 코드
		static const GLchar * vertex_shader_source[] =
		{
			"#version 430 core                                       \n"
			"                                                   \n"
			"void main(void)                                       \n"
			"{                                                   \n"
			"   const vec4 vertices[6] = vec4[6](vec4(0.02, 0.0, 0.5, 1.0),   \n"
			"                              vec4(-0.02, 0.0, 0.5, 1.0),   \n"
			"                              vec4(-0.02, -1.0, 0.5, 1.0),   \n"
			"                              vec4(0.02, 0.0, 0.5, 1.0),   \n"
			"                              vec4(-0.02, -1.0, 0.5, 1.0),   \n"
			"                              vec4(0.02, -1.0, 0.5, 1.0));   \n"
			"   gl_Position = vertices[gl_VertexID];                     \n"
			"}                                                   \n"
		};

		// 프래그먼트 쉐이더 소스 코드
		static const GLchar * fragment_shader_source[] =
		{
			"#version 430 core                          \n"
			"                                           \n"
			"out vec4 color;                            \n"
			"                                           \n"
			"void main(void)                            \n"
			"{                                          \n"
			"    color = vec4(1.0, 0.0, 1.0, 1.0);      \n"
			"}                                          \n"
		};

		// 버텍스 쉐이더를 생성하고 컴파일한다.
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		// 프래그먼트 쉐이더를 생성하고 컴파일한다.
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		// 프로그램을 생성하고 쉐이더를 Attach시키고 링크한다.
		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		// 이제 프로그램이 쉐이더를 소유하므로 쉐이더를 삭제한다.
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}

	// 애플리케이션 초기화 수행한다.
	virtual void startup()
	{
		rendering_program_pinwheel = compile_shaders_pinwheel();
		rendering_program_stick = compile_shaders_stick();
		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);
	}

	// 애플리케이션 끝날 때 호출된다.
	virtual void shutdown()
	{
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program_pinwheel);
		glDeleteProgram(rendering_program_stick);
	}

	// 렌더링 virtual 함수를 작성해서 오버라이딩한다.
	virtual void render(double currentTime)
	{
		const GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
		const GLfloat red[] = { (float)sin(currentTime) * 0.5f + 0.5f,
			(float)cos(currentTime) * 0.5f + 0.5f,
			0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, black);

		const GLfloat c1[] = { (float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 0.25f, 1.0f };
		const GLfloat c2[] = { (float)cos(currentTime) * 0.5f + 0.5f, (float)sin(currentTime) * 0.5f + 0.5f, 0.25f, 1.0f };
		const GLfloat c3[] = { 0.25f, (float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 1.0f };

		glUseProgram(rendering_program_stick);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// 렌더링위해 생성한 프로그램 객체를 사용하도록 한다.
		glUseProgram(rendering_program_pinwheel);

		glVertexAttrib4fv(0, c1);
		glVertexAttrib4fv(1, c2);
		glVertexAttrib4fv(2, c3);
		glVertexAttrib1f(3, currentTime * 100);

		// 삼각형을 하나 그린다.
		glDrawArrays(GL_TRIANGLES, 0, 12);
	}

private:
	GLuint rendering_program_pinwheel, rendering_program_stick;
	GLuint vertex_array_object;
};

// DECLARE_MAIN의 하나뿐인 인스턴스
DECLARE_MAIN(my_application)


