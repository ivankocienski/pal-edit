
#include <iostream>
using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "color-grid.hh"
#include "edit-color.hh"
#include "application.hh"
#include "video.hh"
#include "global.hh"

static const char *hex_chars = "0123456789ABCDEF";

ColorGrid::ColorGrid( Application *a, Palette &p ) : ModeBase(a), m_palette(p) {

  m_mark_pos   = -1;
  m_cur_pos    = 0;
  m_edit_color = -1;
  m_color_edit = (EditColor *)m_application->get_mode( Application::AM_EDIT_COLOR );
}

void ColorGrid::activate() {

  ModeBase::activate();

  if( m_edit_color != -1 ) {
    if( m_color_edit->user_wants_color_updated() ) {
      cout << "updating color" << endl;
      m_palette.set_color( m_cur_pos, m_color_edit->color() );
      m_edit_color = -1;
    }
  }
}

void ColorGrid::normalize_range( int &from, int &to ) {

  if( m_cur_pos < m_mark_pos ) {
    from = m_cur_pos;
    to   = m_mark_pos + 1;
  } else {
    from = m_mark_pos;
    to   = m_cur_pos + 1;
  }
}

void ColorGrid::draw() {

  glColor3f( 1, 1, 1 );

  int x;
  int y;
  int i = 0;

  glBegin( GL_QUADS );

  for( y = 0; y < 16; y++ ) 
    for( x = 0; x < 16; x++ ) {

      float dx = 30 + (x * 20);
      float dy = 20 + (y * 20);

      m_palette.at(i).set_gl();

      glVertex2f( dx +  1, dy +  1);
      glVertex2f( dx + 18, dy +  1);
      glVertex2f( dx + 18, dy + 18);
      glVertex2f( dx +  1, dy + 18);

      i++;
    }

  glEnd();

  glColor3f( 1, 1, 1 );

  if( m_mark_pos == -1 ) {
    if( (anim >> 3) & 1 ) {
      glBegin( GL_LINE_LOOP );

      float dx = 30 + ((m_cur_pos & 15) * 20);
      float dy = 20 + ((m_cur_pos / 16) * 20);

      glVertex2f( dx     , dy );
      glVertex2f( dx + 19, dy );
      glVertex2f( dx + 19, dy + 19 ); 
      glVertex2f( dx,      dy + 19 );


      glEnd();
    }

  } else {
    int from_pos;
    int to_pos;

    normalize_range( from_pos, to_pos );

    for( int i = from_pos; i < to_pos; i++ ) {

      if( (i == m_cur_pos && (anim >> 3) & 1) || i != m_cur_pos ) {

        glBegin( GL_LINE_LOOP );

        float dx = 30 + ((i & 15) * 20);
        float dy = 20 + ((i / 16) * 20);

        glVertex2f( dx     , dy );
        glVertex2f( dx + 19, dy );
        glVertex2f( dx + 19, dy + 19 ); 
        glVertex2f( dx,      dy + 19 );

        glEnd();
      }
    }
  }

  glEnable( GL_TEXTURE_2D );

  buffer[2] = 0;

  for( i = 0; i < 16; i++ ) {

    buffer[0] = '-';
    buffer[1] = hex_chars[i];
    m_video->draw_text( 30 + i * 20, 10, buffer );

    buffer[0] = hex_chars[i];
    buffer[1] = '-';
    m_video->draw_text( 10, 20 + i * 20, buffer ); 
  } 

  m_video->draw_text( 400, 10, "COLOR INFO" );

  snprintf( buffer, BUFFER_LEN, "index %d", m_cur_pos );
  m_video->draw_text( 400, 25, buffer);

  snprintf( buffer, BUFFER_LEN, "  red %03d", m_palette.at(m_cur_pos).red );
  m_video->draw_text( 400, 35, buffer);

  snprintf( buffer, BUFFER_LEN, "green %03d", m_palette.at(m_cur_pos).green );
  m_video->draw_text( 400, 45, buffer);

  snprintf( buffer, BUFFER_LEN, " blue %03d", m_palette.at(m_cur_pos).blue );
  m_video->draw_text( 400, 55, buffer);

  if( m_mark_pos != -1 ) {
    snprintf( buffer, BUFFER_LEN, "mark at %d", m_mark_pos );
    m_video->draw_text( 400, 100, buffer); 
  }

  snprintf( buffer, BUFFER_LEN, "  hex 0x%02x%02x%02x",
      m_palette.at(m_cur_pos).red,
      m_palette.at(m_cur_pos).green,
      m_palette.at(m_cur_pos).blue);
  m_video->draw_text( 400, 65, buffer);


  m_video->draw_text( 620, 10, "KEY HELP" );

  if( m_mark_pos == -1 ) {
    m_video->draw_text( 620, 25, "E edit" );
    m_video->draw_text( 620, 35, "Z black" );
    m_video->draw_text( 620, 45, "X white" );
    m_video->draw_text( 620, 55, "C copy" );
    m_video->draw_text( 620, 65, "V paste" );
    m_video->draw_text( 620, 75, "M mark" );

  } else {
    m_video->draw_text( 620, 25, "M mark release" );
    m_video->draw_text( 620, 35, "Z black" );
    m_video->draw_text( 620, 45, "X white" );
    m_video->draw_text( 620, 55, "V paste" );
    m_video->draw_text( 620, 65, "G gradient" );

  }

  m_video->draw_text( 10, 580, "F1 new grid" );

  glDisable( GL_TEXTURE_2D );
}

void ColorGrid::on_key_down( int k ) {

  int from_pos, to_pos;

  switch( k ) {
    case GLFW_KEY_UP: 
      m_cur_pos -= 16;
      if( m_cur_pos < 0 ) m_cur_pos += 256;
      break;

    case GLFW_KEY_DOWN:
      m_cur_pos += 16;
      if( m_cur_pos > 255 ) m_cur_pos -= 256;
      break;

    case GLFW_KEY_LEFT:
      m_cur_pos--;
      if( m_cur_pos < 0 ) m_cur_pos = 255;
      break;

    case GLFW_KEY_RIGHT:
      m_cur_pos++;
      if( m_cur_pos > 255 ) m_cur_pos = 0;
      break;

    case GLFW_KEY_Z:
      if( m_mark_pos == -1 ) {
        m_palette.set_color( m_cur_pos, 0, 0, 0 );
      } else {
        normalize_range( from_pos, to_pos );
        for( int i = from_pos; i < to_pos; i++ ) 
          m_palette.set_color( i, 0, 0, 0 );
      }
      break;

    case GLFW_KEY_X:
      if( m_mark_pos == -1 ) {
        m_palette.set_color( m_cur_pos, 255, 255, 255 );
      } else {
        normalize_range( from_pos, to_pos );
        for( int i = from_pos; i < to_pos; i++ ) 
          m_palette.set_color( i, 255, 255, 255 );
      }
      break;
    
    case GLFW_KEY_C:
      m_copy_color = m_palette.at(m_cur_pos);
      break;

    case GLFW_KEY_V:
      if( m_mark_pos == -1 ) {
        m_palette.set_color( m_cur_pos, m_copy_color );
      } else {
        normalize_range( from_pos, to_pos );
        for( int i = from_pos; i < to_pos; i++ ) 
          m_palette.set_color( i, m_copy_color );
      }
      break;

    case GLFW_KEY_G:
      if( m_mark_pos != -1 ) {

        normalize_range( from_pos, to_pos );

        if( to_pos - from_pos > 2 ) {
          Palette::T_COLOR from_col = m_palette.at(from_pos);
          Palette::T_COLOR to_col   = m_palette.at(to_pos - 1);

          float step_size = 1.0 / float( to_pos - from_pos - 1);
          float a = 0;

          for( int i = from_pos; i < to_pos; i++ ) {

            int r = from_col.red   * (1.0 - a) + to_col.red   * a;
            int g = from_col.green * (1.0 - a) + to_col.green * a;
            int b = from_col.blue  * (1.0 - a) + to_col.blue  * a;

            m_palette.set_color( i, r, g, b );

            a += step_size;
          }
        }
      }
      break;

    case GLFW_KEY_M:
      if( m_mark_pos == -1 )
        m_mark_pos = m_cur_pos;
      else
        m_mark_pos = -1;
      break;

    case GLFW_KEY_F1:
      m_application->set_mode( Application::AM_NEW_GRID );
      break;


    case GLFW_KEY_E:
      if( m_mark_pos == -1 ) {
        m_edit_color = m_cur_pos;
        m_color_edit->set_color( m_cur_pos, m_palette.at( m_cur_pos ));
        m_application->set_mode( Application::AM_EDIT_COLOR );
      }
      break;
  }
}
