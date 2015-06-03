
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "color-grid.hh"
#include "application.hh"
#include "video.hh"

unsigned char anim = 0;
static const char *hex_chars = "0123456789ABCDEF";

ColorGrid::ColorGrid( Application *a, Palette &p ) : ModeBase(a), m_palette(p) {

  m_cur_pos = 0;
}

void ColorGrid::init() {
}

static char buffer[256];

void ColorGrid::draw() {

  anim++;

  glColor3f( 1, 1, 1 );

  int x;
  int y;
  int i = 0;

  glBegin( GL_QUADS );

  for( y = 0; y < 16; y++ ) 
    for( x = 0; x < 16; x++ ) {

      float dx = 30 + (x * 20);
      float dy = 20 + (y * 20);

      glColor3f( 
          float(m_palette.at(i).red)   / 255.0,
          float(m_palette.at(i).green) / 255.0,
          float(m_palette.at(i).blue)  / 255.0);

      glVertex2f( dx +  1, dy +  1);
      glVertex2f( dx + 18, dy +  1);
      glVertex2f( dx + 18, dy + 18);
      glVertex2f( dx +  1, dy + 18);

      i++;
    }

  glEnd();

  glColor3f( 1, 1, 1 );

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

  snprintf( buffer, 256, "index %d", m_cur_pos );
  m_video->draw_text( 400, 25, buffer);

  snprintf( buffer, 256, "  red %03d", m_palette.at(m_cur_pos).red );
  m_video->draw_text( 400, 35, buffer);

  snprintf( buffer, 256, "green %03d", m_palette.at(m_cur_pos).green );
  m_video->draw_text( 400, 45, buffer);

  snprintf( buffer, 256, " blue %03d", m_palette.at(m_cur_pos).blue );
  m_video->draw_text( 400, 55, buffer);

  snprintf( buffer, 256, "  hex 0x%02x%02x%02x",
      m_palette.at(m_cur_pos).red,
      m_palette.at(m_cur_pos).green,
      m_palette.at(m_cur_pos).blue);
  m_video->draw_text( 400, 65, buffer);


  m_video->draw_text( 650, 10, "KEY HELP" );
  m_video->draw_text( 650, 25, "E; edit" );
  m_video->draw_text( 650, 35, "S; select" );

  glDisable( GL_TEXTURE_2D );
}

void ColorGrid::on_key_down( int k ) {

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
  }
}
