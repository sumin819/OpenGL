#include <GL/glut.h>
#include <math.h>
#include <vector>
using namespace std;
int MX = 300, MY = 300;
float time = 0;
float x = 0, y = 0; 

class vec3 {
public:
	float m[3];
	vec3(float x=0, float y=0, float z=0) {
		m[0] = x; m[1] = y; m[2] = z;
	}
	vec3 operator+(vec3 x) {
		return vec3(m[0] + x.m[0],
			m[1] + x.m[1], m[2] + x.m[2]);
	}
	vec3 operator-(vec3 x) {
		return vec3(m[0] - x.m[0],
			m[1] - x.m[1], m[2] - x.m[2]);
	}
	vec3 operator*(float x) {
		return vec3(m[0] * x, m[1] * x, m[2] * x);
	}
	float Length() {
		return sqrtf(m[0] * m[0] + m[1] * m[1] + m[2] * m[2]);
	}
};
class SnowBall {
public:
	vec3 v; 
	vec3 pos;
};
vector<SnowBall> snowballs;

void MyMouseMove(GLint X, GLint Y) {
	MX = X;
	MY = Y;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(MX / 300.0, MY / 300.0, 1.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0); 
}
void MySpecial(int key, int X, int Y) {
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
	if (KeyPressed == ' ') { //spacebar 
		SnowBall sb;
		sb.pos.m[0] = x + 1.2; 
		sb.pos.m[1] = 0.5;
		sb.pos.m[2] = y + 8;
		sb.v.m[0] = 0;
		sb.v.m[1] = 0;
		sb.v.m[2] = -1.5;
		snowballs.push_back(sb);
		glutPostRedisplay();
	}
}


void MyIdle() {
	time += 1.0;
	glutPostRedisplay();
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(MX / 300.0, MY / 300.0, 1.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0); 
}
void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 15.0 };
	GLfloat light_specular[] = { 1.0, 0.8, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -3, 6, 3.0, 0.0 };

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
	glEnable(GL_NORMALIZE); 
}

bool HitCheck() {
	vec3 big_snow(sin(time * 0.0001) * 10, 1.0, -7);
	int size = snowballs.size();
	for (int i = 0; i < size; i++) {
		vec3 diff = big_snow - snowballs[i].pos;
		if (diff.Length() < 1.5)
			return true;
	}
	return false;
}


void UpdateSnowballs() {
	vec3 acc(0, -0.8, 0);
	float snowTime = 0.001;
	int size = snowballs.size();
	for (int i = 0; i < size; i++) {
		snowballs[i].v = snowballs[i].v + acc * snowTime;
		snowballs[i].pos = snowballs[i].pos + snowballs[i].v * snowTime;

		if (snowballs[i].pos.m[1] < 0.5 + 0.25) {
			snowballs[i].pos.m[1] = 0.75;
			snowballs[i].v.m[1] = fabs(snowballs[i].v.m[1]); 
			
		}
	}

	for (int i = 0; i < snowballs.size(); ) { 
		if (snowballs[i].pos.m[2] > 10 || snowballs[i].pos.m[2] < -10)
			snowballs.erase(snowballs.begin() + i);
		//else if (snowballs[i].v.Length() < 0.0001) 
			//snowballs.erase(snowballs.begin() + i);
		else 
			i++;
	}
}

void DrawSnowballs() {
	//UpdateSnowballs(); // update
	int size = snowballs.size();
	for (int i = 0; i < size; i++) {
		glPushMatrix();
		glTranslatef(snowballs[i].pos.m[0], snowballs[i].pos.m[1], snowballs[i].pos.m[2]);
		glutSolidSphere(0.5, 20, 20);
		glPopMatrix();
	}
}

void DrawSnowman() {
	glPushMatrix();

	glTranslatef(0, 3, 0); // 
	glutSolidSphere(3, 20, 20); //body
	
	glPushMatrix(); //

		glTranslatef(2.5, 0, 0);
		glRotatef(sin(time * 0.0005) * 30 - 30, 0, 0, 1); // 

		glTranslatef(0, 2.5, 0);
		glPushMatrix();
			glScalef(0.1, 1, 0.1);
			glutSolidCube(5);
		glPopMatrix();


		glTranslatef(0, 2.5, 0);
		glPushMatrix();
			glRotatef(sin(time * 0.0005) * 30 - 30, 0, 0, 1);
			glTranslatef(0, 1.5, 0);
			glScalef(0.1, 1, 0.1);
			glutSolidCube(3);
		glPopMatrix();

	glPopMatrix();

	glRotatef(sin(time * 0.0005) * 15, 1, 0, 0);
	glTranslatef(0, 6, 0);
	glutSolidSphere(3, 20, 20); //head
	glPopMatrix();
}
void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1, 1, 0);
	glPushMatrix();
		glScalef(20, 0.5, 20);
		glutSolidCube(1.0);
	glPopMatrix();


	glPushMatrix();
		glTranslatef(0, 0, 8); 
		glTranslatef(x, 0, y); 
		glScalef(0.2, 0.2, 0.2);
		//glTranslatef(0, 3, 0); 
		DrawSnowman();
	glPopMatrix();
	


	glPushMatrix();
		glTranslatef(0, 0, -7); 
		glTranslatef(sin(time * 0.0001) * 10, 0, 0); 
		glScalef(0.3, 0.3, 0.3);
		DrawSnowman();
	glPopMatrix();


	DrawSnowballs();
	glFlush();

	bool hit = HitCheck();
	if (hit) exit(0); 
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL Drawing Example");
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutIdleFunc(MyIdle);
	glutPostRedisplay();
	glutSpecialFunc(MySpecial);
	glutMotionFunc(MyMouseMove);
	glutKeyboardFunc(MyKeyboard);
	glClearColor(0.4, 0.4, 0.4, 1);
	InitLight(); 

	glutMainLoop();
	return 0;
}