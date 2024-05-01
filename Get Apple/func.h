#include <GL/glut.h>
#include <math.h>
#include <vector>
using namespace std;

void MyMouseMove(GLint X, GLint Y);
void MyKeyboard(unsigned char KeyPressed, int X, int Y);
void MySpecial(int key, int X, int Y);
void MyReshape(int w, int h);
void DrawArm(int n);
void DrawLeg();
void DrawCalf();
void DrawFoot();
void DrawHuman();
void DrawTableLeg();
void DrawTable();
void DrawApple();
void MyDisplay();
void InitLight();
void MyTimerLL(int n);
void MyTimerLR(int n);
void MyTimerA(int n);
void EatCheck();


