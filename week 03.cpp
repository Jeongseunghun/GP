//배경색 칠하기//////////////////////////////////////////
// sb6.h 헤더 파일을 포함시킨다.
#include <sb6.h>
#include <vmath.h>

// sb6::application을 상속받는다.
class my_application2 : public sb6::application
{
private:
	GLuint rendering_program;
	GLuint vertex_array_object;

public:

	GLuint compile_shaders(void){
		GLuint vertex_shader;
		GLuint tcs, tes, gs;
		GLuint fragment_shader;
		GLuint program;

		static const GLchar * vertex_shader_source[] = {
			"#version 430 core                                                 \n"
			"                                                                  \n"
			"layout (location = 0) in vec4 offset;                             \n"
			"layout (location = 1) in vec4 color;                              \n"
			"out VS_OUT {                                                      \n"
			"    vec4 color;                                                   \n"
			"} vs_out;                                                         \n"
			"void main(void)                                                   \n"
			"{                                                                 \n"
			"   const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),  \n"
			"                            vec4(-0.25, 0.25, 0.5, 1.0),          \n"
			"                            vec4(0.25, 0.25, 0.5, 1.0));          \n"
			"   gl_Position = vertices[gl_VertexID] + offset;                  \n"
			"   vs_out.color = color;                                          \n"
			"}                                                                 \n"
		};


		static const GLchar * tcs_source[] = {
			"#version 430 core                                                           \n"
			"                                                                            \n"
			"layout (vertices = 3) out;                                                  \n"
			"                                                                            \n"
			"void main(void)                                                             \n"
			"{                                                                           \n"
			"   if(gl_InvocationID==0){                                                  \n"
			"      gl_TessLevelInner[0] = 5.0;                                           \n"
			"      gl_TessLevelOuter[0] = 5.0;                                           \n"
			"      gl_TessLevelOuter[1] = 5.0;                                           \n"
			"      gl_TessLevelOuter[2] = 5.0;                                           \n"
			"   }                                                                        \n"
			"   gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position; \n"
			"}                                                                           \n"
		};

		static const GLchar * tes_source[] = {
			"#version 430 core                                             \n"
			"                                                              \n"
			"layout (triangles , equal_spacing , cw) in;                   \n"
			"                                                              \n"
			"                                                              \n"
			"void main(void)                                               \n"
			"{                                                             \n"
			"   gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +     \n"
			"                  gl_TessCoord.y * gl_in[1].gl_Position +     \n"
			"                  gl_TessCoord.z * gl_in[2].gl_Position);     \n"
			"}                                                             \n"
		};

		static const GLchar * gs_source[] = {
			"#version 430 core                                             \n"
			"                                                              \n"
			"layout (triangles) in;                                        \n"
			"layout (points, max_vertices = 3) out;                        \n"
			"                                                              \n"
			"void main(void)                                               \n"
			"{                                                             \n"
			"   int i;                                                     \n"
			"   for(int i=0; i < gl_in.length(); i++){                     \n"
			"       gl_Position = gl_in[i].gl_Position;                    \n"
			"       EmitVertex();                                          \n"
			"       gl_Position[0] *= -1;                                  \n"
			"       gl_Position[1] *= -1;                                  \n"
			"       EmitVertex();                                          \n"
			"   }                                                          \n"

			"}                                                             \n"
		};


		static const GLchar * fragment_shader_source[] =
		{
			"#version 430 core                         \n"
			"                                          \n"
			//"in VS_OUT{                                \n"
			//"   vec4 color;                            \n"
			//"} fs_in;                                  \n"
			"out vec4 color;                           \n"
			"void main(void)                           \n"
			"{                                         \n"
			//"   color = vec4(0.5,0.5,0.6,1.0); //fs_in.color; \n"
			"     color=vec4(sin(gl_FragCoord.x*0.25)*0.5 + 0.5,  \n"
			"               cos(gl_FragCoord.y*0.25)*0.5 + 0.5, \n"
			"               sin(gl_FragCoord.x*0.25)*cos(gl_FragCoord.y*0.25),1.0); \n"
			"}                                         \n"
		};

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		tcs = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(tcs, 1, tcs_source, NULL);
		glCompileShader(tcs);

		tes = glCreateShader(GL_TESS_EVALUATION_SHADER);
		glShaderSource(tes, 1, tes_source, NULL);
		glCompileShader(tes);

		gs = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gs, 1, gs_source, NULL);
		glCompileShader(gs);

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		//4. 프로그램 객체를 생성한다.
		program = glCreateProgram();

		//5. 쉐이더 객체를 프로그램 객체에 어태치시킨다.
		glAttachShader(program, vertex_shader);
		glAttachShader(program, tcs);
		glAttachShader(program, tes);
		glAttachShader(program, gs);
		glAttachShader(program, fragment_shader);


		//6. 프로그램 객체에 어태치된 모든 쉐이더 객체를 링크한다.
		glLinkProgram(program);

		//7.쉐이더 객체를 삭제한다.
		glDeleteShader(vertex_shader);
		glDeleteShader(tcs);
		glDeleteShader(tes);
		glDeleteShader(gs);
		glDeleteShader(fragment_shader);
		return program;
	}

	virtual void startup(){
		rendering_program = compile_shaders();
		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);
	}

	virtual void shutdown(){
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program);
	}

	// 렌더링 virtual 함수를 작성해서 오버라이딩한다.
	virtual void render(double currentTime)
	{
		const GLfloat red[] = { (float)sin(currentTime)*0.5f + 0.5f, (float)cos(currentTime)*0.5f + 0.5f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, red);

		glUseProgram(rendering_program);

		GLfloat attrib[] = { (float)sin(currentTime)*0.5f, (float)cos(currentTime)*0.5f, 0.0f, 0.0f };
		//입력 속성 0의 값을 갱신한다.
		glVertexAttrib4fv(0, attrib);

		GLfloat color[] = { 1.0f, 0.0f, 0.0f, 0.0f };

		glVertexAttrib4fv(1, color);

		glLineWidth(5.0f);
		glPointSize(5.0f);
		glPatchParameteri(GL_PATCH_VERTICES, 3);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawArrays(GL_PATCHES, 0, 3);
	}
};

// DECLARE_MAIN의 하나뿐인 인스턴스
DECLARE_MAIN(my_application2)