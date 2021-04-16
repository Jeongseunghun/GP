//배경색 칠하기//////////////////////////////////////////
// sb6.h 헤더 파일을 포함시킨다.
#include <sb6.h>
// 수학적인 것을 쓰기 위해 헤더 파일 포함.
#include <vmath.h>

// sb6::application을 상속받는다.
class my_application : public sb6::application
{
public:
	// 렌더링 virtual 함수를 작성해서 오버라이딩한다.
	virtual void render(double currentTime)
	{
		const GLfloat red[] = { (float)sin(currentTime)* 0.5f + 0.5f,
			(float)cos(currentTime)* 0.5f + 0.5f,
			(float)sin(currentTime)*0.5 + 0.5f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, red);
	}
};

// DECLARE_MAIN의 하나뿐인 인스턴스
DECLARE_MAIN(my_application)