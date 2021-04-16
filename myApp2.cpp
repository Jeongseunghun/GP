//���� ĥ�ϱ�//////////////////////////////////////////
// sb6.h ��� ������ ���Խ�Ų��.
#include <sb6.h>
#include <vmath.h>

// sb6::application�� ��ӹ޴´�.
class my_application : public sb6::application
{
private:
	//VAO(Vertex Array Object): ���ؽ� ��ġ ���������� ��Ÿ���� ��ü, OpenGL�� ������������ �Է°� ���õ� ��� ��������
	GLuint rendering_program; // GLuint:VAO��ü���庯��
	GLuint vertex_array_object;

public:
	GLuint compile_shaders(){
		//(���̴� ����ϱ�)
		//1.���̴� ��ü�� �����Ѵ�.
		GLuint vertex_shader;
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);

		GLuint fragment_shader;
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

		//2. ���̴� �ҽ��ڵ带 ���̴� ��ü�� �����Ѵ�.
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

		//3. ���̴� ��ü�� �ҽ��ڵ带 �������Ѵ�.
		glCompileShader(vertex_shader);
		glCompileShader(fragment_shader);
		
		//4. ���α׷� ��ü�� �����Ѵ�.
		GLuint program;
		program = glCreateProgram();
		
		//5. ���̴� ��ü�� ���α׷� ��ü�� ����ġ��Ų��.
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);

		//6. ���α׷� ��ü�� ����ġ�� ��� ���̴� ��ü�� ��ũ�Ѵ�.
		glLinkProgram(program);

		//7. ���̴� ��ü�� �����Ѵ�.
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}

	//���ø����̼� �ʱ�ȭ �����Լ� : ���̴� �� ���α׷� ���������� ���ϵ��� startup���� ���α׷� ��ü�� ����
	virtual void startup(){
		rendering_program = compile_shaders();
		glGenVertexArrays(1, &vertex_array_object); //VAO��ü ����
		glBindVertexArray(vertex_array_object); //VAO��ü�� ���������ο� ���ε�
	}

	//������ virtual �Լ��� �ۼ��ؼ� �������̵��Ѵ�.
	//currentTime�� ���� ������ ������ ����ð�(��):�ִϸ��̼� ���� ������ Ȱ�밡��
	virtual void render(double currentTime)
	{
		const GLfloat red[] = { (float)sin(currentTime)* 0.5f + 0.5f,
			(float)cos(currentTime)* 0.5f + 0.5f,
			0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, red);

		//������ ���� ������ ���α׷� ��ü�� ����ϵ��� �Ѵ�.
		glUseProgram(rendering_program);
		//���� �ϳ� �׸���.
		glPointSize(100.0f);
		//glDrawArrays(GL_POINTS, 0, 1);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	virtual void shutdown(){
		//���ø����̼��� ����� �� ȣ��Ǵ� �����Լ�
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program);
	}

	
};

// DECLARE_MAIN�� �ϳ����� �ν��Ͻ�
DECLARE_MAIN(my_application)
