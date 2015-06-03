
#include "video.hh"
#include "application.hh"

static Video *s_video = NULL;

void on_glfw_key( GLFWwindow* win, int key, int scancode, int action, int mods ) {
  
  if( action == GLFW_PRESS ) 
    s_video->post_key_down_event( key );
  else
    s_video->post_key_up_event(key);
}

Video::Video( int xr, int yr, const char* t ) {
  m_xres        = xr;
  m_yres        = yr;
  m_title       = t;
  m_main_window = NULL;
  s_video       = this;

  m_ts.tv_sec  = 0;
  m_ts.tv_nsec = 50 * 1000;
}

Video::~Video() {

  glfwTerminate();
}

bool Video::open() {

  if(!glfwInit()) return false;

  m_main_window = glfwCreateWindow(m_xres, m_yres, m_title.c_str(), NULL, NULL);

  if(!m_main_window) return false;

  glfwMakeContextCurrent(m_main_window);

  glfwSetKeyCallback( m_main_window, on_glfw_key );

  glViewport(0, 0, m_xres, m_yres);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0.0, m_xres, m_yres, 0.0, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f( 1, 1, 1 );

  glEnable( GL_TEXTURE_2D ); 
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if(!m_font.load( "data/font.png", 8, 8, 32, 128 )) return false;
  glDisable( GL_TEXTURE_2D ); 

  return true;
}

bool Video::is_open() {
  return !glfwWindowShouldClose(m_main_window);
}

void Video::tick() {

  glfwSwapBuffers(m_main_window);
  glfwPollEvents();

  nanosleep( &m_ts, NULL ); 

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); 
}

void Video::post_key_down_event( int k ) {
  m_app->do_key_down(k);
}

void Video::post_key_up_event( int k ) {
  m_app->do_key_up(k); 
}

void Video::set_event_callbacks( Application *a ) {
  m_app = a;
}

void Video::draw_text( int x, int y, const char* s ) { 
  m_font.draw_slow( x, y, s );
}
