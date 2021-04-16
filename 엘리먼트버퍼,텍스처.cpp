#include <sb6.h>
#include <vmath.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class my_application : public sb6::application
{
public:
	// 쉐이더 컴파일한다.
	GLuint compile_shaders(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		// 버텍스 쉐이더 소스 코드
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
		rendering_program = compile_shaders();
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		// 삼각형 세점 위치를 정의한다.
		GLfloat vertices[] = {
			//3차원 위치         //컬러            //텍스처 좌표
			0.25f, 0.25f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,         //우측 상단
			-0.25f, 0.25f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,        //좌측 상단
			-0.25f, -0.25f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,       //좌측 하단
			0.25f, -0.25f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f         //우측 하단
		
		};

		// 삼각형으로 그릴 인덱스를 정의한다.
		GLuint indices[] = {
			0, 1, 2,  //첫번째 삼각형
			0, 2, 3   //두번째 삼각형
		};
	

		// VBO를 생성하여 vertices 값들을 복사
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// VBO를 나누어서 각 버텍스 속성으로 연결
		// 위치 속성(location =0)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// 컬러 속성(location =1)
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// 텍스처 좌표 속성 (location =2)
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// EBO를 생성하고 indices 값들을 복사
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// VBO 및 버텍스 속성을 다 했으니 VBO와 VAO를 unbind한다.
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//텍스처 객체 만들고 바인딩
		glGenTextures(1, &texture1);
		glBindTexture(GL_TEXTURE_2D, texture1);


		// 텍스처 이미지 로드하기
		int width, height, nrChannels;
		unsigned char *data = stbi_load("../../src/_myApp_/wall.jpg", &width, &height, &nrChannels, 0);

		if (data){
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		stbi_image_free(data);


			// 텍스처 샘플링/필터링 설정
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
	}

	// 애플리케이션 끝날 때 호출된다.
	virtual void shutdown()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteProgram(rendering_program);
	}

	// 렌더링 virtual 함수를 작성해서 오버라이딩한다.
	virtual void render(double currentTime)
	{
		const GLfloat color[] = { (float)sin(currentTime) * 0.5 + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 0.0f, 1.0f };
		const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, black);

		// 렌더링위해 생성한 프로그램 객체를 사용하도록 한다.
		glUseProgram(rendering_program);

		// z축에 대한 회전 행렬을 만든다.
		float angle = currentTime * 50;
		vmath::mat4 rm = vmath::mat4::identity();
		// "rotMat" uniform에 대한 위치를 가져온다.
		GLint rotMatLocation = glGetUniformLocation(rendering_program, "rotMat");
		// "rotMat" uniform으로 전달한다.
		glUniformMatrix4fv(rotMatLocation, 1, GL_FALSE, rm);

		// 텍스처를 bind한다.
		glUniform1i(glGetUniformLocation(rendering_program, "texture1"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// 미리 설정한 VAO를 그리기 위해 bind 한다.
		glBindVertexArray(VAO);


		// EBO를 활용해 사각형을 그린다. (삼각형 두개)
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	}

private:
	GLuint rendering_program;
	GLuint VAO, VBO, EBO;
	GLuint texture1;
};

DECLARE_MAIN(my_application)