

#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

#include "application.hh"
#include "open-file-mode.hh"
#include "global.hh"
#include "video.hh"
#include "palette.hh"

OpenFileMode::OpenFileMode( Application *a ) : ModeBase(a) {
}

void OpenFileMode::activate() {
  ModeBase::activate();

  m_directory.scan();

  m_dir_pos = 0;
  m_dir_top = 0;
}

void OpenFileMode::load_palette_file( const char *p ) { 
  Palette new_pal;

  if( new_pal.load_from_file( p ))
    m_application->set_palette( new_pal );
}

void OpenFileMode::on_key_down( int k ) {

  switch( k ) {
    case GLFW_KEY_UP: 
      m_dir_pos--;
      if( m_dir_pos < 0 ) m_dir_pos = m_directory.count() - 1;
      break;

    case GLFW_KEY_DOWN:
      m_dir_pos = (m_dir_pos + 1) % m_directory.count();
      break;

    case GLFW_KEY_R:
      {
        int c = m_directory.count();
        m_directory.scan();

        if( m_directory.count() != c ) {
          m_dir_pos = 0;
          m_dir_top = 0;
        }
      }
      break;

    case GLFW_KEY_ENTER:
      {
        const Directory::T_DIR_ENTRY &e = m_directory.entry( m_dir_pos );
        if( e.is_dir ) {
          m_directory.cd( e.name );
          m_directory.scan();
          m_dir_pos = 0;
          m_dir_top = 0;
          break;
        }

        load_palette_file( (m_directory.path() + "/" + e.name).c_str() );
      }

      //m_application->set_palette( m_palettes[m_menu_pos] );

    case GLFW_KEY_ESCAPE:
      m_application->set_mode( Application::AM_COLOR_GRID );
      break;
  }
}

void OpenFileMode::draw() {
  
  int y;

  glColor3f( 1, 1, 1 );

  glEnable( GL_TEXTURE_2D );

  m_video->draw_text( 10, 10, "Open palette file" );
  m_video->draw_text( 10, 30, m_directory.path().c_str() );

  y = 40;
  for( int i = 0; i < m_directory.count(); i++ ) {

    const Directory::T_DIR_ENTRY &e = m_directory.entry(i);
    
    snprintf( 
        buffer,
        BUFFER_LEN, 
        "%c %c %s", 
        i == m_dir_pos ? '>' : ' ', 
        e.is_dir ? 'd' : ' ',
        e.name.c_str() );

    m_video->draw_text( 20, y, buffer );
    y += 10;
  }

  
  m_video->draw_text( 620, 10, "KEY HELP" );

    m_video->draw_text( 620, 25, " ENTER select" );
    m_video->draw_text( 620, 35, "ESCAPE cancel" );
    m_video->draw_text( 620, 45, "    UP" );
    m_video->draw_text( 620, 55, "  DOWN" );

  glDisable( GL_TEXTURE_2D );


}

