#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

int FlatShaded = 0;    int Wireframed = 0;
//flatshading과 Wireframe을 토글링하기 위한 부울 변수

int ViewX = 0, ViewY = 0;
// 마우스 움직임에 따라 시점을 바꾸기 위한 변수 

void InitLight() {
    GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
    GLfloat mat_shininess[] = { 15.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
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
}

void MyMouseMove(GLint X, GLint Y) {
    // ∏∂øÏΩ∫ øÚ¡˜¿” X,Y∏¶ ¿¸ø™ ∫Øºˆ¿Œ ViewX, ViewYø° «“¥Á
    ViewX = X;
    ViewY = Y;
    glutPostRedisplay();
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q': case 'Q': case '\033':
        exit(0);
        break;
    case 's':
        if (FlatShaded) {
            FlatShaded = 0;
            glShadeModel(GL_SMOOTH);
        }
        else {
            FlatShaded = 1;
            glShadeModel(GL_FLAT);
        }
        glutPostRedisplay();
        break;
        // 여기에 와이어 프레임 토글링을 위한 코드를 삽입할 것 
        // 위의 전역 변수 Wireframed를 사용할 것 
    }
}

void DrawTable() {
    glPushMatrix();

    glRotatef((float)ViewX, 1.0, 1.0, 0.0);
    glRotatef((float)ViewY, 0.0, 0.0, 1.0);

    // Sphere
    glPushMatrix();
    glTranslatef(0.1, 0.075, 0.2);
    glScalef(1.0, 1.0, 1.0);
    glutSolidSphere(0.1, 10, 10);
    glPopMatrix();

    // Cube
    glPushMatrix();
    glTranslatef(-0.1, 0.075, -0.1);
    glRotatef(45.0f, 0.0, 1.0, 0.0);
    glScalef(1.0, 1.0, 1.0);
    glutSolidCube(0.15);
    glPopMatrix();

    // teapot
    glPushMatrix();
    glTranslatef(0.25, 0.075, -0.2);
    glRotatef(45.0f, 0.0, 1.0, 0.0);
    glScalef(1.0, 1.0, 1.0);
    glutSolidTeapot(0.1);
    glPopMatrix();

    // corn
    glPushMatrix();
    glTranslatef(-0.25, 0.0, 0.2);
    glRotatef(45.0f, 0.0, 1.0, 0.0);
    glRotatef(-90.0f, 1.0, 0.0, 0.0);
    glScalef(1.0, 1.0, 1.0);
    glutSolidCone(0.1, 0.5, 10, 10);
    glPopMatrix();

    // Table Top
    glPushMatrix();
    glScalef(1.0, 0.05, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Table leg
    float leg_positions[4][2] = {
        { 0.45,  0.45},
        {-0.45,  0.45},
        { 0.45, -0.45},
        {-0.45, -0.45}
    };

    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(leg_positions[i][0], -0.25, leg_positions[i][1]); // leg pos
        glScalef(0.05, 0.5, 0.05);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    glPopMatrix();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 1.0, 1.0, 0.0);
    // 마우스의 움직임에 따라 시점을 변화시키려면
    // MyMouseMove 함수에서 입력되는 변화량을 참고하여
    // glLookAt 명령어 파라미터를 변경해볼 것 (교재 참조)
    // 아래에 필요한 물체 드로잉 명령을 삽입할 것 
    // glutSolidTeapot(0.2); // 예

    DrawTable();
    glFlush();
}

void MyReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Sample Drawing");

    glClearColor(0.4, 0.4, 0.4, 0.0);
    InitLight();
    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutMotionFunc(MyMouseMove);
    glutReshapeFunc(MyReshape);
    glutMainLoop();
}
