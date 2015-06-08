
#pragma once

#include <string>
#include <list>

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <time.h>

#include "font.hh"

class Application;

class Video {
private:

  std::string m_title;
  int m_xres;
  int m_yres;
  bool m_inkey_capture;

  Font m_font;

  GLFWwindow* m_main_window;

  void post_key_down_event( int );
  void post_key_up_event( int );
  void post_inkey_event( int );

  Application *m_app;
  struct timespec m_ts;

  void push_inkey( unsigned int );

public:

  Video( int, int, const char* );
  ~Video();

  bool open();
  void tick();
  bool is_open();

  void set_inkey_capture(bool);

  void set_event_callbacks( Application* );
  void draw_text( int, int, const char* );

  friend void on_glfw_key( GLFWwindow*, int, int, int, int );
  friend void on_glfw_char( GLFWwindow*, unsigned int );
};

