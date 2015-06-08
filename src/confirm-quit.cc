
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "confirm-quit.hh"
#include "application.hh"
#include "video.hh"

ConfirmQuit::ConfirmQuit( Application *a ) : ModeBase( a ) {

}

void ConfirmQuit::activate() {

}

void ConfirmQuit::on_key_down( int k ) {

  switch(k) {
    case GLFW_KEY_N:
    case GLFW_KEY_ESCAPE:
      m_application->set_mode( Application::AM_COLOR_GRID );
      break;

    case GLFW_KEY_Y:
      m_video->stop();
      break;
  }
}

void ConfirmQuit::draw() {

  glColor3f( 1, 1, 1 );

  glEnable( GL_TEXTURE_2D );
  
  m_video->draw_text( 10, 10, "Confirm Quit" );
  m_video->draw_text( 10, 20, "Y yes" );
  m_video->draw_text( 10, 30, "N no / cancel" );

  glDisable( GL_TEXTURE_2D );
}

