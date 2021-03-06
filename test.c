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

freenect_context *f_ctx;
freenect_device *f_dev;

uint8_t buff1[480*640*3];
uint8_t buff2[480*640*3];
uint8_t * rgb_back = (uint8_t *)&buff1;
uint8_t * rgb_front = (uint8_t *)&buff2;

void draw() {
  freenect_process_events(f_ctx);
  glDrawPixels(640, 480, GL_RGB, GL_UNSIGNED_BYTE, rgb_front);
  glutSwapBuffers();
}

void videoCallBack(freenect_device *dev, void *v, uint32_t timestamp) {
  for (int i=0;i<640*3;i++){
    for(int j=0;j<240;j++){
      uint8_t t;
      int a=i+(640*3*j);
      int b=i+(640*3*(479-j));
      t = (uint8_t) ((uint8_t*)v)[a];
      ((uint8_t*)v)[a]=((uint8_t*)v)[b];
      ((uint8_t*)v)[b] = t;
    }
  }
  rgb_back = rgb_front;
  rgb_front= (uint8_t * )v;
  freenect_set_video_buffer(f_dev, rgb_back);
}

void initDevice() {
  if (freenect_init(&f_ctx, NULL) < 0) {
    exit(1);
  }
  freenect_set_log_level(f_ctx, FREENECT_LOG_DEBUG);
  freenect_select_subdevices(f_ctx, (freenect_device_flags)(FREENECT_DEVICE_MOTOR | FREENECT_DEVICE_CAMERA));

  if (freenect_open_device(f_ctx, &f_dev, 0)) {
    freenect_shutdown(f_ctx);
    exit(1);
  }
  freenect_set_led(f_dev, LED_RED);
  freenect_set_tilt_degs(f_dev,0);
  freenect_set_video_callback(f_dev, videoCallBack);
  freenect_frame_mode fm = freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB);
  freenect_set_video_mode(f_dev, fm);
  freenect_set_video_buffer(f_dev, rgb_back);
  freenect_start_video(f_dev);
  freenect_set_led(f_dev, LED_GREEN);
}

void initDisplay() {
	glDisable(GL_DEPTH_TEST);
	glutCreateWindow("Test");
  glewInit();
	glutReshapeWindow(640,480);
  glutDisplayFunc(draw);
  glutIdleFunc(draw);
}

int main(int argc, char * argv[]) {
  for (int i=0; i < 640*480*3; i+=3) {
    rgb_front[i] = rand();
    rgb_front[i+1] = rand();
    rgb_front[i+2] = rand();
  }
  for (int i=0; i < 640*480*3; i+=3) {
    rgb_back[i] = rand();
    rgb_back[i+1] = rand();
    rgb_back[i+2] = rand();
  }
  printf("initializing\n");
  initDevice();
  glutInit(&argc,argv);
  initDisplay();
  glClearColor(1.0,0.0,0.0,1.0);
  glutMainLoop();
	return 0;
}
