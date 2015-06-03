
#pragma once

#include <string>

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <time.h>

#include "font.hh"

class Video {
private:

  std::string m_title;
  int m_xres;
  int m_yres;

  Font m_font;

  GLFWwindow* m_main_window;

  void post_key_down_event( int );
  void post_key_up_event( int );

  struct timespec m_ts;

public:

  Video( int, int, const char* );
  ~Video();

  bool open();

  void tick();

  bool is_open();

  void draw_text( int, int, const char* );

  friend void on_glfw_key( GLFWwindow*, int, int, int, int );
};

