
#include <iostream>
using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "save-file-mode.hh"
#include "application.hh"
#include "video.hh"
#include "global.hh"

SaveFileMode::SaveFileMode( Application *a ) : ModeBase(a) {
  m_filename = "untitled";
  m_dir_path = Directory::getcwd();

  m_dir_scanner.set_directory_mode();
}
  
void SaveFileMode::activate() {
  ModeBase::activate();

  m_cur_pos  = 0;
  m_sub_mode = SM_TOP; 
}

void SaveFileMode::on_key_down(int k) {

  switch( m_sub_mode ) {
    case SM_TOP:        on_key_top_menu(k); break;
//    case SM_TYPE_NAME: on_key_type_menu(k); break;
    case SM_SELECT_DIR: on_key_select_dir(k); break;
  }
}

void SaveFileMode::draw() {

  switch( m_sub_mode ) {
    case SM_TOP:        draw_top_menu(); break;
    case SM_TYPE_NAME:  draw_type_name(); break;
    case SM_SELECT_DIR: draw_select_dir(); break;
  }
}

void SaveFileMode::draw_top_menu() {

  glColor3f( 1, 1, 1 );

  glEnable( GL_TEXTURE_2D );

  m_video->draw_text( 10, 10, "Save palette file" );

  m_video->draw_text( 30, 30, "location" );
  m_video->draw_text( 150, 30, m_dir_path.c_str());

  m_video->draw_text( 30, 40, "file name" );
  m_video->draw_text( 150, 40, m_filename.c_str() );

  m_video->draw_text( 30, 50, "save" );

  m_video->draw_text( 10, 30 + 10 * m_cur_pos, ">" );

  m_video->draw_text( 620, 10, "KEY HELP" );

  m_video->draw_text( 620, 25, " ENTER select" );
  m_video->draw_text( 620, 35, "ESCAPE cancel" );
  m_video->draw_text( 620, 45, "    UP" );
  m_video->draw_text( 620, 55, "  DOWN" );

  glDisable( GL_TEXTURE_2D );

}

void SaveFileMode::on_key_top_menu(int k) {

  switch( k ) {
    case GLFW_KEY_UP: 
      m_cur_pos--;
      if( m_cur_pos < 0 ) m_cur_pos = 2;
      break;

    case GLFW_KEY_DOWN:
      m_cur_pos = (m_cur_pos + 1) % 3;
      break;

    case GLFW_KEY_ENTER:

      {
        switch( m_cur_pos ) {
          case 0: // select dir
            m_dir_scanner.scan( m_dir_path );
            m_dir_pos  = 0;
            m_sub_mode = SM_SELECT_DIR; 
            return;

          case 1: // type file name
            m_video->set_inkey_capture(true);
            m_newfilename = m_filename;
            m_sub_mode    = SM_TYPE_NAME;
            return;

          case 2:
            // save file now...
            m_application->palette().save_to_file( (m_dir_path + "/" + m_filename + ".pal" ).c_str() );
            break;
        }
      }

    case GLFW_KEY_ESCAPE:
      m_application->set_mode( Application::AM_COLOR_GRID );
      break;
  }


}

void SaveFileMode::draw_type_name() {

  glColor3f( 1, 1, 1 );

  glEnable( GL_TEXTURE_2D );

  m_video->draw_text( 10, 10, "Save palette file" );
  m_video->draw_text( 10, 20, "Enter file name" );

  m_video->draw_text( 30, 40, "file name" );
  m_video->draw_text( 150, 40, m_newfilename.c_str() );


  m_video->draw_text( 620, 10, "KEY HELP" );

  m_video->draw_text( 620, 25, " ENTER select" );
  m_video->draw_text( 620, 35, "ESCAPE cancel" );
  m_video->draw_text( 620, 45, "    UP" );
  m_video->draw_text( 620, 55, "  DOWN" );

  glDisable( GL_TEXTURE_2D );
}

void SaveFileMode::on_inkey( unsigned int k ) {

  if( k == GLFW_KEY_BACKSPACE ) { // backspace 
    if( m_newfilename.length() > 0 ) {
      m_newfilename.erase( m_newfilename.length() - 1, 1 );
    }
  }

  if( k == GLFW_KEY_ENTER ) {
    if( m_newfilename.length() > 0 ) {
      m_video->set_inkey_capture( false );
      m_filename = m_newfilename;
      m_sub_mode = SM_TOP;
      return;
    }
  }

  if( k == GLFW_KEY_ESCAPE ) {
    m_video->set_inkey_capture( false );
    m_sub_mode = SM_TOP;
    return;
  }

  if( isalnum(k) ) {
    m_newfilename.push_back(k); 
  }

}

void SaveFileMode::draw_select_dir() {

  glColor3f( 1, 1, 1 );

  glEnable( GL_TEXTURE_2D );

  m_video->draw_text( 10, 10, "Save palette file" );
  m_video->draw_text( 10, 20, "Select Directory" );

  m_video->draw_text( 30, 40, "directory" );
  m_video->draw_text( 30, 50, m_dir_scanner.path().c_str() );

  int max = 40;
  if( max > m_dir_scanner.count() ) max = m_dir_scanner.count();
  for( int i = 0; i < max; i++ ) {
    snprintf( buffer, BUFFER_LEN, "%c %s", m_dir_pos == i ? '>' : ' ', m_dir_scanner.entry(i).name.c_str() );
    m_video->draw_text( 30, 70 + i * 10, buffer );
  }

  m_video->draw_text( 620, 10, "KEY HELP" );

  m_video->draw_text( 620, 25, " ENTER go into directory" );
  m_video->draw_text( 620, 35, "ESCAPE cancel" );
  m_video->draw_text( 620, 45, "    UP" );
  m_video->draw_text( 620, 55, "  DOWN" );
  m_video->draw_text( 620, 65, "     R refresh" );
  m_video->draw_text( 620, 75, "     E use this directory" );

  glDisable( GL_TEXTURE_2D );

}

void SaveFileMode::on_key_select_dir(int k) {

  switch( k ) {
    case GLFW_KEY_UP: 
      m_dir_pos--;
      if( m_dir_pos < 0 ) m_dir_pos = m_dir_scanner.count() - 1;
      break;

    case GLFW_KEY_DOWN:
      m_dir_pos = (m_dir_pos + 1) % m_dir_scanner.count();
      break;

    case GLFW_KEY_R:
      {
        int c = m_dir_scanner.count();
        m_dir_scanner.scan();

        if( c != m_dir_scanner.count() ) 
          m_dir_pos = 0;

      }
      break;

    case GLFW_KEY_ENTER:
      m_dir_scanner.cd( m_dir_scanner.entry(m_dir_pos).name );
      m_dir_scanner.scan();
      m_dir_pos = 0;
      break;

    case GLFW_KEY_E:
      m_dir_path = m_dir_scanner.path();

    case GLFW_KEY_ESCAPE:
      m_sub_mode = SM_TOP;
      break;
  } 
}

