#include <sb6.h>
#include <vmath.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class my_application : public sb6::application
{
public:
	// ���̴� �������Ѵ�.
	GLuint compile_shaders(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		// ���ؽ� ���̴� �ҽ� �ڵ�
		static const GLchar * vertex_shader_source[] =
		{
			"#version 430 core                                       \n"
			"                                                        \n"
			"layout(location=0)in vec3 pos;                          \n"
			"layout(location=1)in vec3 color;                        \n"
			"layout(location=2)in vec2 texCoord;                     \n"
			"													     \n"
			"uniform mat4 rotMat;                                    \n"
			"                                                        \n"
			"out vec3 vsColor;                                       \n"
			"out vec2 vsTexCoord;                                    \n"
			"                                                        \n"
			"void main(void)                                         \n"
			"{                                                       \n"
			" gl_Position = rotMat*vec4(pos.x, pos.y, pos.z, 1.0);   \n"
			"                                                        \n"
			" vsColor = color;                                       \n"
			" vsTexCoord = texCoord;                                 \n"
			"}                                                       \n"
		};
		static const GLchar * fragment_shader_source[] =
		{
			"#version 430 core                                   \n"
			"in vec3 vsColor;                                    \n"
			"in vec2 vsTexCoord;                                 \n"

			"uniform sampler2D texture1;                         \n"

			"out vec4 fragColor;                                 \n"
			"void main(void)                                     \n"
			"{                                                   \n"
			"   fragColor = texture(texture1, vsTexCoord);       \n"
			/*"   fragColor = texture(texture1, vsTexCoord) * vec4(vsColor,1.0);       \n"*/
			"}                                                   \n"
		};


		// ���ؽ� ���̴��� �����ϰ� �������Ѵ�.
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		// �����׸�Ʈ ���̴��� �����ϰ� �������Ѵ�.
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		// ���α׷��� �����ϰ� ���̴��� Attach��Ű�� ��ũ�Ѵ�.
		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		// ���� ���α׷��� ���̴��� �����ϹǷ� ���̴��� �����Ѵ�.
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;
	}


	// ���ø����̼� �ʱ�ȭ �����Ѵ�.
	virtual void startup()
	{
		rendering_program = compile_shaders();
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// �ﰢ�� ���� ��ġ�� �����Ѵ�.
		GLfloat vertices[] = {
			//3���� ��ġ         //�÷�            //�ؽ�ó ��ǥ
			0.25f, 0.25f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,         //���� ���
			-0.25f, 0.25f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,        //���� ���
			-0.25f, -0.25f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,       //���� �ϴ�
			0.25f, -0.25f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f         //���� �ϴ�
		
		};

		// �ﰢ������ �׸� �ε����� �����Ѵ�.
		GLuint indices[] = {
			0, 1, 2,  //ù��° �ﰢ��
			0, 2, 3   //�ι�° �ﰢ��
		};
	

		// VBO�� �����Ͽ� vertices ������ ����
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// VBO�� ����� �� ���ؽ� �Ӽ����� ����
		// ��ġ �Ӽ�(location =0)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// �÷� �Ӽ�(location =1)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// �ؽ�ó ��ǥ �Ӽ� (location =2)
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// EBO�� �����ϰ� indices ������ ����
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// VBO �� ���ؽ� �Ӽ��� �� ������ VBO�� VAO�� unbind�Ѵ�.
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//�ؽ�ó ��ü ����� ���ε�
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);


		// �ؽ�ó �̹��� �ε��ϱ�
		int width, height, nrChannels;
		unsigned char *data = stbi_load("../../src/_myApp_/wall.jpg", &width, &height, &nrChannels, 0);

		if (data){
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		stbi_image_free(data);


			// �ؽ�ó ���ø�/���͸� ����
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	}

	// ���ø����̼� ���� �� ȣ��ȴ�.
	virtual void shutdown()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteProgram(rendering_program);
	}

	// ������ virtual �Լ��� �ۼ��ؼ� �������̵��Ѵ�.
	virtual void render(double currentTime)
	{
		const GLfloat color[] = { (float)sin(currentTime) * 0.5 + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 0.0f, 1.0f };
		const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, black);

		// ���������� ������ ���α׷� ��ü�� ����ϵ��� �Ѵ�.
		glUseProgram(rendering_program);

		// z�࿡ ���� ȸ�� ����� �����.
		float angle = currentTime * 50;
		vmath::mat4 rm = vmath::mat4::identity();
		// "rotMat" uniform�� ���� ��ġ�� �����´�.
		GLint rotMatLocation = glGetUniformLocation(rendering_program, "rotMat");
		// "rotMat" uniform���� �����Ѵ�.
		glUniformMatrix4fv(rotMatLocation, 1, GL_FALSE, rm);

		// �ؽ�ó�� bind�Ѵ�.
		glUniform1i(glGetUniformLocation(rendering_program, "texture1"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// �̸� ������ VAO�� �׸��� ���� bind �Ѵ�.
		glBindVertexArray(VAO);


		// EBO�� Ȱ���� �簢���� �׸���. (�ﰢ�� �ΰ�)
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	}

private:
	GLuint rendering_program;
	GLuint VAO, VBO, EBO;
	GLuint texture1;
};

DECLARE_MAIN(my_application)