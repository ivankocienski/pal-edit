
#include "video.hh"
#include "application.hh"

/* friend functions */
void on_glfw_key( GLFWwindow* win, int key, int scancode, int action, int mods ) {
  
  Video *v = (Video *)glfwGetWindowUserPointer(win);

  if( action == GLFW_PRESS ) {
    v->post_key_down_event( key );
  } else
    v->post_key_up_event(key);
}

void on_glfw_char( GLFWwindow *w, unsigned int code ) {
  Video *v = (Video *)glfwGetWindowUserPointer(w);
  v->post_inkey_event( code );
}

Video::Video( int xr, int yr, const char* t ) {
  m_xres        = xr;
  m_yres        = yr;
  m_title       = t;
  m_main_window = NULL;
  m_inkey_capture = false;

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
  glfwSetWindowUserPointer( m_main_window, this );

  glfwSetKeyCallback( m_main_window, on_glfw_key );
  glfwSetCharCallback( m_main_window, on_glfw_char );

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
//  cout << "post_key_down_event k=" << k << endl;

  if( m_inkey_capture ) {
    if( k == GLFW_KEY_ENTER || k == GLFW_KEY_BACKSPACE || k == GLFW_KEY_ESCAPE ) 
      m_app->do_inkey(k);

  } else
    m_app->do_key_down(k);


}

void Video::post_key_up_event( int k ) {
  m_app->do_key_up(k); 
}

void Video::post_inkey_event( int k ) {
  m_app->do_inkey(k);
}

void Video::set_event_callbacks( Application *a ) {
  m_app = a;
}

void Video::set_inkey_capture( bool ic ) {
  m_inkey_capture = ic;
}

void Video::draw_text( int x, int y, const char* s ) { 
  m_font.draw_slow( x, y, s );
}

