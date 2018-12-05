
//은면제거, 컬링, 카메라 적용 됨


#include"pch.h"




#define WWIDTH 800
#define WHEIGHT 600
#define DEPTH 400
#define LENGTH 200



GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void TimerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
void MenuFunc(int button);

void drawline();




Camera<float3> m_Camera((float)WHEIGHT / (float)WWIDTH);

c_background background;
c_ship ship;
c_texture TXTR;
CSound sound;

void main(int argc, char *argv[]) {

	srand((unsigned)time(NULL));


	//초기화 함수들
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); 	// 디스플레이 모드 설정
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 			// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);							// 윈도우의 위치지정 
	glutInitWindowSize(WWIDTH, WHEIGHT); 						// 윈도우의 크기 지정 
	glutCreateWindow("Example"); 								// 윈도우 생성 (윈도우 이름)

	//SetupRC();//초기화 함수

	glutDisplayFunc(drawScene); 								// 출력 함수의 지정 
	glutReshapeFunc(Reshape);									// 다시 그리기 함수의 지정 

	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);

	glutTimerFunc(100, TimerFunction, 1);


	//카메라
	m_Camera.Initialize(float3{ 0,0,0 }, 300, 1, 1000, 90);

	sound.Play(0);

	background.init();
	ship.backGround = &background;
	//ship.p_Texture = &TXTR;
	ship.init();

	glutMainLoop();

}
float degreeX = 0;
float degreeY = 0;
float degreeZ = 0;


GLvoid drawScene(GLvoid)
{
	//은면제거

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glEnable(GL_DEPTH_TEST | GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);      // 바탕색을 'blue' 로 지정 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      // 설정된 색으로 전체를 칠하기 


	m_Camera.LookAtOrtho();

	glPushMatrix();//=========================
	{
		glRotated(180, 0, 1, 0);//축이 돌아가서 돌렸음

		background.drawSea();
		ship.drawShip();




		drawline();


		//fill


	}
	glPopMatrix();//=========================


	glutSwapBuffers();                              // 화면에 출력하기

	//은면제거
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	//은면제거
}



GLvoid Reshape(int w, int h)
{

	glutPostRedisplay();
}


void TimerFunction(int value)
{

	background.seaUpdate();
	ship.update();

	//m_Camera.Rotate(0,0.1);
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(50, TimerFunction, 1);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{


	case 'x':
		m_Camera.Rotate(0.f, 0.1f);
		break;
	case 'X':
		m_Camera.Rotate(0.f, -0.1f);
		break;
	case 'y':
		m_Camera.Rotate(0.1f, 0.f);
		break;
	case 'Y':
		m_Camera.Rotate(-0.1f, 0.f);
		break;
	case 'z':
		m_Camera.zoom(0.9f);
		break;
	case 'Z':
		m_Camera.zoom(1.1f);
		break;
	case '+':
		break;
	case '-':
		sound.Play(1);
		break;
	}

	ship.keybard(key);
}


void Mouse(int button, int state, int x, int y)
{
	float mouseX = WWIDTH / 2 - x;
	float mouseY = -(y - WHEIGHT / 2);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}


}

void Motion(int x, int y)
{
	float mouseX = WWIDTH / 2 - x;
	float mouseY = -(y - WHEIGHT / 2);

}

void drawline()
{

	glPushMatrix();//=========================
	glColor3f(1.0, 0.0f, 0.0f);
	//x
	glBegin(GL_LINES);
	glVertex3f(0, WHEIGHT / 2, 0);
	glVertex3f(0, 0, 0);
	//glVertex3f(0, -WHEIGHT / 2, 0);
	glEnd();
	glPopMatrix();//=========================

	glPushMatrix();//=========================
	glColor3f(0.0f, 1.0f, 0.0f);
	//y
	glBegin(GL_LINES);
	glVertex3f(WWIDTH / 2, 0, 0);
	glVertex3f(0, 0, 0);
	//glVertex3f(-WWIDTH / 2, 0, 0);
	glEnd();
	glPopMatrix();//=========================

	glPushMatrix();//=========================
	glColor3f(0.0f, 0.0f, 1.0f);
	//z
	glBegin(GL_LINES);
	glVertex3f(0, 0, DEPTH / 2);
	glVertex3f(0, 0, 0);
	//glVertex3f(0, 0, -DEPTH / 2);
	glEnd();
	glPopMatrix();//=========================

}

