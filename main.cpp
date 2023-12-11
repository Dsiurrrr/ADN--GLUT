#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <cmath>

//CREDITOS A VALOR

void menu_principal(int);
void iniciar(void);
void Cilindro();
void ejes();
void Alambrico();
void Solido();
void girar_objeto_geometrico();
void submenu_rotaciones(int);
void submenu_cilindro(int);

int lados ; // Número de lados del cilindro
GLint modelo = 0;
static GLfloat theta[] = {0.0, 0.0, 0.0};
static int eje = 0;
GLfloat direccion =1.0;
GLfloat px0 = 0, py0 = 0, pz0 = 5;
GLfloat px1 = 0, py1 = 0, pz1 = 4;
GLdouble angulo = 0, incremento_angulo = 0.02;
GLdouble const radio = 0.5;
int grafico = 1;
//GLOBALES
float R = 8, H = 15;
int opcion = 0;

//PARA LOS EJES
int longitud = 15;

//Para los puntos o esferas en el ADN
int numPoints;
int puntos2;
void iniciar(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    longitud = 0;
    lados = 0;
    numPoints=0;
    puntos2=0;
    glShadeModel(GL_FLAT);
}

void Cilindro() {
    glLineWidth(2.0);
    glBegin(GL_LINES);
    for (int i = 0; i <= lados; ++i) {
        float angulo = 2.0f *(M_PI/ lados) * i ;
        float x = R * cos(angulo);
        float z = R * sin(angulo);
         glColor3f(0,8.0,0.2);
        // Vertices verticales
        glVertex3d(x,H , z);
        glVertex3d(x,-H , z);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= lados; ++i) {
        float angulo = 2.0f *(M_PI/ lados) * i ;
        float x = R * cos(angulo);
        float z = R * sin(angulo);
         glColor3f(1.0,0.5,0.0);
        //  SUP
        glVertex3d(x, H , z);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= lados; ++i) {
        float angulo = 2.0f *(M_PI/ lados) * i ;
        float x = R * cos(angulo);
        float z = R * sin(angulo);
         glColor3f(1.0,0.0,0.2);
        //  INF
        glVertex3d(x, -H , z);
    }
    glEnd();
}

void ejes() {
    glLineWidth(2.0);
    glColor3d(0.0,0.5,1.0);
    glBegin(GL_LINES);
    glVertex3d(0, 0, longitud);
    glVertex3d(0, 0, -longitud);
    glEnd();

    glBegin(GL_LINES);
    glVertex3d(0, -longitud, 0);
    glVertex3d(0, longitud, 0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3d(-longitud, 0, 0);
    glVertex3d(longitud, 0, 0);
    glEnd();
}

void Alambrico() {
   //ANGULO EN GENERAL
    float angle = (2.0 * M_PI / numPoints);

    //Hebra1
    for(int i=0;i<numPoints;i++){
       float pz=R*cos(i*angle);
       float px=R*sin(i*angle);
        glLineWidth(2.0);
        glBegin(GL_LINE_STRIP);
        glColor3f(1,0.5,0.5);
        glVertex3f(px,(H-(i*30/numPoints)),pz);
    }
    glEnd();


//Hebra2

    for(int i=0;i<numPoints;i++){
       float pz=R*cos(i*angle);
       float px=R*sin(i*angle);
        glLineWidth(2.0);
        glBegin(GL_LINE_STRIP);
        glColor3f(0,0.5,1.0);
        glVertex3f(-px,(H-(i*30/numPoints)),-pz);
    }
    glEnd();

//PUNTOS HEBRA1

   for(int i=0;i<numPoints;i++){
       float pz=R*cos(i*angle);
       float px=R*sin(i*angle);
        glPointSize(10.0);
        glBegin(GL_POINTS);
        glColor3f(1,0.0,0.0);
        glVertex3f(px,(H-(i*30/numPoints)),pz);
    }
    glEnd();

//PUNTOS_HEBRA2

    for(int i=0;i<numPoints;i++){
       float pz=R*cos(i*angle);
       float px=R*sin(i*angle);
        glPointSize(10.0);
        glBegin(GL_POINTS);
        glColor3f(1,0.0,1.0);
        glVertex3f(-px,(H-(i*30/numPoints)),-pz);
    }
    glEnd();


    //UNIR PUNTOS
   for(int i=0;i<numPoints;i++){
       float pz=R*cos(i*angle);
       float px=R*sin(i*angle);
        glPointSize(5.0);
        glLineWidth(2.0);
        glBegin(GL_LINES);
        glColor3f(1,0.5,0.5);
        glVertex3f(px,(H-(i*30/numPoints)),pz);
        glVertex3f(-px,(H-(i*30/numPoints)),-pz);

    }
    glEnd();
}

void Solido(){
  float angle = (2.0 * M_PI / puntos2);
    //Hebra1
    for(int i=0;i<puntos2;i++){
       float pz=R*cos(i*angle);
       float px=R*sin(i*angle);
        glLineWidth(2.0);
        glBegin(GL_LINE_STRIP);
        glColor3f(1,0.5,0.5);
        glVertex3f(px,(H-(i*30/puntos2)),pz);
    }
    glEnd();

   //Hebra2
    for(int i=0;i<puntos2;i++){
       float pz=R*cos(i*angle);
       float px=R*sin(i*angle);
        glLineWidth(2.0);
        glBegin(GL_LINE_STRIP);
        glColor3f(0,0.0,0.5);
        glVertex3f(-px,(H-(i*30/puntos2)),-pz);
    }
    glEnd();

    //ESFERAS HEBRA1

   for(int i=0;i<puntos2;i++){
       float pz=R*cos(i*angle);
       float px=R*sin(i*angle);
        glLineWidth(4.0);
        glPushMatrix();
        glColor3f(1,0.0,0.0);
        glTranslatef(px,(H-(i*30/puntos2)),pz);
        glutWireSphere(0.3,15,15);
        glPopMatrix();
    }
    glEnd();

     //ESFERAS HEBRA2
    for(int i=0;i<puntos2;i++){
       float pz=R*cos(i*angle);
       float px=R*sin(i*angle);
        glLineWidth(4.0);
        glPushMatrix();
        glColor3f(0.8,0.8,0.2);
        glTranslatef(-px,(H-(i*30/puntos2)),-pz);
        glutWireSphere(0.3,15,15);
        glPopMatrix();
    }
    glEnd();

    //UNIR ESFERAS
       for(int i=0;i<puntos2;i++){
       float pz=R*cos(i*angle);
       float px=R*sin(i*angle);
        glBegin(GL_LINES);
        glColor3f(1.0,0.0,1.0);
        glVertex3f(px,(H-(i*30/puntos2)),pz);
        glVertex3f(-px,(H-(i*30/puntos2)),-pz);
    }
    glEnd();

//  glpopMatrix();
  glutPostRedisplay();


}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glLoadIdentity();
     glClearColor(0,0,0,0);
    glRotatef(theta[1], 0.0, direccion, 0.0);  // Rotación sobre el eje Y----------------------

    // Dibujar ejes
    ejes();
    // Dibujar el ADN alambrico
   Alambrico();
    //Dibujar el ADN solido
    Solido();
    // Dibujar el cilindro
    Cilindro();
    // Dibujar escena
    menu_principal(modelo);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

//POR DEFECTO ESTA DESCATIVADO EL GIRO
void girar_objeto_geometrico() {
    if (eje % 2 != 0 && incremento_angulo > 0) {
        eje=1;
        theta[eje] += incremento_angulo;
        if (theta[eje] > 360.0) {
            theta[eje] -= 360.0;
        }
        glutPostRedisplay();
   }
}

void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case 'Z': incremento_angulo+= 0.01; break;
        case 'X': incremento_angulo-= 0.01; break;
        case 'R': eje+=1; break;
        case 'F': exit(0); break;
    }
    glutPostRedisplay();
}

void myReshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 20.0, -20.0, 20, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void menu_principal(int opcion) {
    switch (opcion) {
        case 3:puntos2=0;numPoints = 30; break;
        case 4:puntos2=15;numPoints = 0; break;
        case 6: exit(0);
    }
    glutPostRedisplay();
}

void submenu_cilindro(int opcion) {
    switch (opcion) {
        case 1:lados=15;break;
        case 2:lados=0; break;
    }
    glutPostRedisplay();
}

void submenu_ejes(int opcion) {
    switch (opcion) {
        case 1:
            longitud = 15;
            break;
        case 2:
            longitud = 0;
            break;
    }
    glutPostRedisplay();
}

void submenu_rotaciones(int opcion) {
    switch (opcion) {
        case 1: direccion = 1  ;break;
        case 2: direccion =-1 ;break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("Modelos 3D con transformaciones");

    int submenu_cilindros = glutCreateMenu(submenu_cilindro);
    glutAddMenuEntry("Activado", 1);
    glutAddMenuEntry("Desactivado", 2);

    int submenu_ejesi = glutCreateMenu(submenu_ejes);
    glutAddMenuEntry("Activado", 1);
    glutAddMenuEntry("Desactivado", 2);

    int submenu_transf = glutCreateMenu(submenu_rotaciones);
    glutAddMenuEntry("Horario", 1);
    glutAddMenuEntry("Antihorario", 2);

    int menu = glutCreateMenu(menu_principal);
    glutAddSubMenu("Cilindro virtual", submenu_cilindros);
    glutAddSubMenu("Ejes", submenu_ejesi);
    glutAddMenuEntry("Modelo Alambrico", 3);
    glutAddMenuEntry("Modelo Solido", 4);
    glutAddSubMenu("Rotaciones", submenu_transf);
    glutAddMenuEntry("Esc", 6);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    iniciar();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(girar_objeto_geometrico);
    glutKeyboardFunc(teclado);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
