#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <libfreenect/libfreenect.h>
#include <libfreenect/libfreenect_sync.h>

#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glext.h>
#include <GL/freeglut.h>
#include <math.h>

int window;
GLuint gl_rgb_tex;

GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

GLuint VBO;

freenect_context *f_ctx;
freenect_device *f_dev;

uint8_t rgb_back[480][640][3];
uint8_t rgb_mid[480][640][3];
uint8_t rgb_front[480][640][3];

uint8_t r=128, g=128, b=128, a=128;

void displayloop() {
//glClear(GL_COLOR_BUFFER_BIT);

  glClear(GL_COLOR_BUFFER_BIT);
  glDrawPixels(640, 480, GL_RGB, GL_UNSIGNED_BYTE, &rgb_front);
  glutSwapBuffers();
}

void initFreeNect() {
  freenect_init(&f_ctx,NULL);

}

int main(int argc, char * argv[]) {

  printf("initializing\n");
  initFreeNect();

  for (int i=0; i < 480; i++) {
    for (int j=0; j < 640; j++) {
      rgb_front[i][j][0] = i;
      rgb_front[i][j][1] = g;
      rgb_front[i][j][2] = b;
    }
  }

	glutInit(&argc,argv);
	//glutInitContextVersion (4, 5);
	glDisable(GL_DEPTH_TEST);
	glutCreateWindow("Test");
  glewInit();
	glutReshapeWindow(800,600);
  glutDisplayFunc(displayloop);

  glClearColor(1.0,0.0,0.0,1.0);

  glutMainLoop();

	return 0;
}
