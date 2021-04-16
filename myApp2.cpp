//배경색 칠하기//////////////////////////////////////////
// sb6.h 헤더 파일을 포함시킨다.
#include <sb6.h>
#include <vmath.h>

// sb6::application을 상속받는다.
class my_application : public sb6::application
{
private:
	//VAO(Vertex Array Object): 버텍스 페치 스페이지를 나타내는 객체, OpenGL의 파이프라인의 입력과 관련된 모든 상태유지
	GLuint rendering_program; // GLuint:VAO객체저장변수
	GLuint vertex_array_object;

public:
	GLuint compile_shaders(){
		//(쉐이더 사용하기)
		//1.쉐이더 객체를 생성한다.
		GLuint vertex_shader;
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);

		GLuint fragment_shader;
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

		//2. 쉐이더 소스코드를 쉐이더 객체로 전달한다.
		/*const GLchar * vertex_shader_source[] =
		{
			"#version 430 core                       \n"
			"                                        \n"
			"void main(void)                         \n"
			"{                                       \n"
			"    gl_Position=vec4(0.0,0.0,0.5,1.0);  \n"
			"}                                       \n"
		};*/

		static const GLchar * vertex_shader_source[] = 
		{
			"#version 430 core                                          \n"
			"                                                           \n"
			"void main(void)                                            \n"
			"{                                                          \n"
			"const vec4 vertices[3] = vec4[3](vec4(0.25,-0.25,0.5,1.0), \n"
			"                              vec4(-0.25, 0.25, 0.5, 1.0), \n"
			"                              vec4(0.25, 0.25, 0.5, 1.0)); \n"
			"    gl_Position = vertices[gl_VertexID];                   \n"
			"}                                                          \n"
		};

		static const GLchar * fragment_shader_source[] = {
			"#version 430 core                       \n"
			"                                        \n"
			"out vec4 color;                         \n"
			"                                        \n"
			"void main(void)                         \n"
			"{                                       \n"
			"    color=vec4(1.0,0.8,0.0,1.0);        \n"
			"}                                       \n"
		};
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);

		//3. 쉐이더 객체의 소스코드를 컴파일한다.
		glCompileShader(vertex_shader);
		glCompileShader(fragment_shader);
		
		//4. 프로그램 객체를 생성한다.
		GLuint program;
		program = glCreateProgram();
		
		//5. 쉐이더 객체를 프로그램 객체에 어태치시킨다.
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);

		//6. 프로그램 객체에 어태치된 모든 쉐이더 객체를 링크한다.
		glLinkProgram(program);

		//7. 쉐이더 객체를 삭제한다.
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}

	//애플리케이션 초기화 가상함수 : 쉐이더 및 프로그램 재컴파일을 안하도록 startup에서 프로그램 객체를 저장
	virtual void startup(){
		rendering_program = compile_shaders();
		glGenVertexArrays(1, &vertex_array_object); //VAO객체 생성
		glBindVertexArray(vertex_array_object); //VAO객체를 파이프라인에 바인딩
	}

	//렌더링 virtual 함수를 작성해서 오버라이딩한다.
	//currentTime은 앱이 시작한 이후의 경과시간(초):애니메이션 위한 값으로 활용가능
	virtual void render(double currentTime)
	{
		const GLfloat red[] = { (float)sin(currentTime)* 0.5f + 0.5f,
			(float)cos(currentTime)* 0.5f + 0.5f,
			0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, red);

		//렌더링 위해 생성한 프로그램 객체를 사용하도록 한다.
		glUseProgram(rendering_program);
		//점을 하나 그린다.
		glPointSize(100.0f);
		//glDrawArrays(GL_POINTS, 0, 1);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	virtual void shutdown(){
		//애플리케이션이 종료될 때 호출되는 가상함수
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program);
	}

	
};

// DECLARE_MAIN의 하나뿐인 인스턴스
DECLARE_MAIN(my_application)
