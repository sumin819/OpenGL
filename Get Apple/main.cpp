#include <GL/glut.h>
#include <math.h>
#include <vector>
using namespace std;

int MX = 300, MY = 300;
float time = 0;
float timeLL = 0; //다리
float timeLR = 0;
float timeA = 0; //팔 
float x = 0, y = 0; // 사람 좌표 전역변수
float angle = 0;
bool eat = false;

class vec3 {
public:
	float m[3];
	vec3(float x = 0, float y = 0, float z = 0) {
		m[0] = x; m[1] = y; m[2] = z;
	}
};

class Apple {
public:
	vec3 pos;
};
vector<Apple> apples;

void MyMouseMove(GLint X, GLint Y) {
	MX = X;
	MY = Y;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(MX / 300.0, MY / 300.0, 1.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);  //시점변환
}
void MySpecial(int key, int X, int Y) { //x,y는 사람의 현재 위치
	
	if (key == GLUT_KEY_UP) {
		y += 0.5f;
	}
	if (key == GLUT_KEY_DOWN) {
		y -= 0.5f;
	}
	if (key == GLUT_KEY_LEFT) {
			x -= 0.5f;
	}
	if (key == GLUT_KEY_RIGHT) {
		x += 0.5f;
	}
	glutPostRedisplay();
}
void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
	if (KeyPressed == 'a') {
		angle -= 1.5F;
	}
	if (KeyPressed == 's') {
		angle += 1.5F;
	}
	glutPostRedisplay();
}
void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, -100.0, 100.0); // 15가 좋은 view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(MX / 300.0, MY / 300.0, 1.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);  //시점변환
}

void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat mat_shininess[] = { 10.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -5, 5, 5, 0.0 };
	//재질/조명 속성
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glEnable(GL_NORMALIZE); //조명 계산할 때, 법선 벡터를 정확히 다시 계산
}
void MyTimerLL(int n)
{
	timeLL = timeLL + 1;
	glutTimerFunc(1, MyTimerLL, 1);
	glutPostRedisplay();

}
void MyTimerLR(int n)
{
	timeLR = timeLR + 1;
	glutTimerFunc(1, MyTimerLR, 1);
	glutPostRedisplay();

}
void MyTimerA(int n)
{
	timeA = timeA + 1;
	glutTimerFunc(1, MyTimerA, 1);
	glutPostRedisplay();

}

void DrawArm(int n) {
	glPushMatrix(); //팔 시작 
	glTranslatef(1, 0, 1.2); //
	//glRotatef(85, 0, 0, 1);
	if (n == 1)
		glRotatef(150, 45, 45, 1);
	if (n == 2)
		glRotatef(225, 45, 45, 1);

	glPushMatrix();
	glScalef(0.1, 0.7, 0.1);
	glutSolidCube(3);
	glPopMatrix();

	glPopMatrix();
}
void DrawLeg() {
	glPushMatrix();
	glTranslatef(1.4, -1, 0);
	glRotatef(90, 45, 0, 1);
	glTranslatef(0, 0, -1);

	glPushMatrix();
	glScalef(0.13, 0.65, 0.13);
	glutSolidCube(4);
	glPopMatrix();

	glPopMatrix();
}
void DrawCalf() {
	glPushMatrix();
	glTranslatef(1.4, -1, -2);
	glRotatef(90, 45, 0, 1);
	glTranslatef(0, 0, -1);

	glPushMatrix();
	glScalef(0.1, 0.5, 0.1);
	glutSolidCube(4);
	glPopMatrix();

	glPopMatrix();
}
void DrawFoot() {
	glPushMatrix();
	glTranslatef(1.4, -0.6, -1.5);
	glRotatef(0, 90, 90, 1);
	glTranslatef(0, 0, -1);

	glPushMatrix();
	glScalef(0.13, 0.2, 0.13);
	glutSolidCube(4);
	glPopMatrix();

	glPopMatrix();
}
void DrawHuman() {

	glPushMatrix();
	GLfloat mat_diffuse[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat mat_shininess[] = { 10. };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glRotatef(270, 1, 0, 0);
	glutSolidCone(2, 3, 10, 10); //몸통 

	glPushMatrix(); //팔 시작

	glRotatef(sin(timeA * 0.005) * 30, 0, 0, 1); // 30도 ~ -30도

	glPushMatrix(); //팔1
	DrawArm(1);
	glPopMatrix();

	glTranslatef(-2, 0, 0); //팔2
	glPushMatrix();
	DrawArm(2);
	glPopMatrix();
	glPopMatrix(); //팔 끝 

	glTranslatef(-2, 0, 0);

	glPushMatrix(); //하체 시작 

	glPushMatrix(); //왼쪽 다리 시작

	glRotatef(sin(timeLL * 0.005) * 30, 1, 0, 0); // 30도 ~ -30도

	glPushMatrix(); //허벅지-왼
	DrawLeg();
	glPopMatrix();

	glRotatef(sin(timeLL * 0.005) * 5, 1, 0, 0); // 10도 ~ -10도

	glPushMatrix(); //종아리-왼
	DrawCalf();
	glPopMatrix();

	glPushMatrix(); //발-왼
	DrawFoot();
	glPopMatrix();

	glPopMatrix(); //왼쪽 다리 끝

	//////////////////////////////////

	glPushMatrix(); //오른쪽 다리 시작 

	glRotatef(sin(timeLR * 0.005) * 30, 1, 0, 0); // 30도 ~ -30도

	glTranslatef(1.4, 0, 0); //허벅지-오
	glPushMatrix();
	DrawLeg();
	glPopMatrix();

	glRotatef(sin(timeLR * 0.005) * 5, 1, 0, 0); // 10도 ~ -10도

	glPushMatrix(); //종아리-오
	DrawCalf();
	glPopMatrix();

	glPushMatrix(); //발-오
	DrawFoot();
	glPopMatrix();
	glPopMatrix(); //오른쪽 다리 끝

	glPopMatrix(); //하체 끝 

	glTranslatef(2, -0.1, 3); //머리 위치 
	glutSolidSphere(1, 5, 10); //머리

	glPopMatrix();
}
void DrawTableLeg() {
	glPushMatrix();
	glRotatef(0, 0, 90, 1);

	glPushMatrix();
	glScalef(0.03, 1.2, 0.03);
	glutSolidCube(4);
	glPopMatrix();

	glPopMatrix();
}
void DrawApple() {
	Apple apple;
	//glPushMatrix();

	glPushMatrix();
	GLfloat mat_diffuse[] = { 1., 0, 0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat mat_shininess[] = { 20.0 };
	glColor3f(0.9, 0.9, 0.9);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glPushMatrix();
	glTranslatef(0.2, 1, -0.2);
	glutSolidSphere(0.8, 20, 20);
	glPopMatrix();

	glTranslatef(0, 2, 0);
	//glTranslatef(Ax, 0, Ay);

	glRotatef(30, 0, 1, 1);
	glScalef(0.06, 0.2, 0.06);
	glutSolidCube(4);

	glPopMatrix();


	apple.pos.m[0] = 5.5;
	apple.pos.m[1] = 1;
	apple.pos.m[2] = -4.5;
}

void EatCheck() {
	if ((x >= 9.5 && x <= 17 && y <= -1 && y >= -7.5))
		eat = true;
}
void DrawTable() {

	glPushMatrix();
	glColor3f(0.8, 0.8, 0.8);
	GLfloat mat_diffuse[] = { 0.9, 0.6, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat mat_shininess[] = { 20.0 };
	glColor3f(0.9, 0.9, 0.9);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glScalef(5, 0.5, 5);
	glutSolidCube(1.0);

	glPushMatrix();
	glTranslatef(0.4, -2, 0.4);
	DrawTableLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.4, -2, -0.43);
	DrawTableLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, -2, -0.43);
	DrawTableLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.4, -2, 0.43);
	DrawTableLeg();
	glPopMatrix();

	glPopMatrix();

	if (eat == false)
		DrawApple();

}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.5, 1, 0.5);
	//glColor3f(0.2, 0.2, 0.2);

	glPushMatrix();
	GLfloat mat_diffuse[] = { 0.96, 0.86, 0.71, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat mat_shininess[] = { 10. };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glScalef(35, 0.5, 35);
	glutSolidCube(1.0);
	glPopMatrix();

	//사람
	glPushMatrix();
	glTranslatef(-8, 2.4, -8);
	glTranslatef(x, 0, -y);
	glRotatef(angle, 0, 1, 0);
	glScalef(0.8, 0.8, 0.8);
	DrawHuman();
	glPopMatrix();

	//테이블
	glPushMatrix();
	glTranslatef(5, 2, -4);
	glScalef(0.8, 0.8, 0.8);
	DrawTable();
	glPopMatrix();

	glFlush();

	EatCheck();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL Drawing Example");
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutPostRedisplay();
	glutSpecialFunc(MySpecial);
	glutMotionFunc(MyMouseMove);
	glutKeyboardFunc(MyKeyboard);
	glClearColor(1.0, 1.0, 1.0, 1);
	InitLight(); //속성 설정이니 한번만 호출하면됨 
	//glutTimerFunc(0, MyTimer, 1);
	glutTimerFunc(0, MyTimerLL, 1);
	glutTimerFunc(1000, MyTimerLR, 1); //밀리초 
	glutTimerFunc(0, MyTimerA, 1);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}
