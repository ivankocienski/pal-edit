
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "new-grid-mode.hh"
#include "application.hh"
#include "global.hh"
#include "video.hh"

#include "default_palette.hh"

// TODO: figure out a better way of doing this...

using namespace std;

NewGridMode::NewGridMode( Application *a ) : ModeBase(a) {

  m_names.resize(3);
  m_palettes.resize(3);

  m_names[0] = "All black";
  m_names[1] = "DOS VGA"; 
  m_names[2] = "Greyscale";
  //m_names.push_back( "Gamey v1" );

  m_palettes[1].load_from_array( (unsigned char *)default_colors, 256 );

  for( int i = 0; i < 256; i++ ) {
    m_palettes[2].set_color( i, i, i, i );
  }
}

void NewGridMode::activate() {
  m_menu_pos = 0;
}

void NewGridMode::on_key_down( int k ) {

  switch( k ) {
    case GLFW_KEY_UP: 
      m_menu_pos--;
      if( m_menu_pos < 0 ) m_menu_pos = m_names.size() - 1;
      break;

    case GLFW_KEY_DOWN:
      m_menu_pos = (m_menu_pos + 1) % m_names.size();
      break;

    case GLFW_KEY_ENTER:
      m_application->set_palette( m_palettes[m_menu_pos] );

    case GLFW_KEY_ESCAPE:
      m_application->set_mode( Application::AM_COLOR_GRID );
      break;
  }
}

void NewGridMode::draw() {

  int y, x, i;

  glBegin( GL_QUADS );

  x = 300;
  y = 30;
  for( i = 0; i < 256; i++ ) {
    
    m_palettes[ m_menu_pos ].at(i).set_gl();

    glVertex2f( x, y );
    glVertex2f( x + 10, y );
    glVertex2f( x + 10, y + 10);
    glVertex2f( x, y + 10 );

    x += 10;
    if( x >= 460 ) {
      x = 300;
      y += 10;
    }
  }

  glEnd();

  glColor3f( 1, 1, 1 );

  glEnable( GL_TEXTURE_2D );

  m_video->draw_text( 10, 10, "New color grid" );

  y = 30;
  for( int i = 0; i < m_names.size(); i++ ) {

    snprintf( buffer, BUFFER_LEN, "%c %s", i == m_menu_pos ? '>' : ' ', m_names[i].c_str() );
    m_video->draw_text( 15, y, buffer );
    y += 10;
  }

  
  m_video->draw_text( 620, 10, "KEY HELP" );

    m_video->draw_text( 620, 25, " ENTER select" );
    m_video->draw_text( 620, 35, "ESCAPE cancel" );
    m_video->draw_text( 620, 45, "    UP" );
    m_video->draw_text( 620, 55, "  DOWN" );

  glDisable( GL_TEXTURE_2D );

}

