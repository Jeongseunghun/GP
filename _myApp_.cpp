//���� ĥ�ϱ�//////////////////////////////////////////
// sb6.h ��� ������ ���Խ�Ų��.
#include <sb6.h>
// �������� ���� ���� ���� ��� ���� ����.
#include <vmath.h>

// sb6::application�� ��ӹ޴´�.
class my_application : public sb6::application
{
public:
	// ������ virtual �Լ��� �ۼ��ؼ� �������̵��Ѵ�.
	virtual void render(double currentTime)
	{
		const GLfloat red[] = { (float)sin(currentTime)* 0.5f + 0.5f,
			(float)cos(currentTime)* 0.5f + 0.5f,
			(float)sin(currentTime)*0.5 + 0.5f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, red);
	}
};

// DECLARE_MAIN�� �ϳ����� �ν��Ͻ�
DECLARE_MAIN(my_application)