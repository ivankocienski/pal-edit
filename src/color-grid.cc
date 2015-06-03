
#include <GL/gl.h>

#include "color-grid.hh"
#include "application.hh"
#include "video.hh"

ColorGrid::ColorGrid( Application *a ) : ModeBase(a) {

}

void ColorGrid::init() {
}

void ColorGrid::draw() {

  glColor3f( 1, 1, 1 );

  glBegin( GL_QUADS );

  glVertex2f( 100, 100 );
  glVertex2f( 200, 100 );
  glVertex2f( 200, 200 );
  glVertex2f( 100, 200 );

  glEnd();

  glEnable( GL_TEXTURE_2D );
  m_video->draw_text( 10, 10, "Hello, World" );

  glDisable( GL_TEXTURE_2D );
}
