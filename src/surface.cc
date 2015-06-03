
#include <string.h>
#include <stdlib.h>
#include "png++/png.hpp"

#include "surface.hh"

Surface::Surface() {
  m_id = 0;
}

Surface::~Surface() {
  if(m_id) glDeleteTextures( 1, &m_id );
}

bool Surface::load( const char *from ) {

  png::image< png::rgba_pixel >image;
  image.read(from);

  m_width  = image.get_width();
  m_height = image.get_height();

  unsigned char *data = NULL;
  data = (unsigned char*)calloc( m_width * m_height * 4, sizeof(unsigned char));
  if(!data) return 0;

  unsigned char *d = data;

  for( int y = 0; y < m_height; y++ ) {

    png::image< png::rgba_pixel >::row_type const & row = image.get_row(y);

    for(int x = 0; x < m_width; x++ ) {

      *d = row.at(x).red;   d++;
      *d = row.at(x).green; d++;
      *d = row.at(x).blue;  d++;
      *d = row.at(x).alpha; d++;
    }
  }


  glGenTextures( 1, &m_id );
  glBindTexture( GL_TEXTURE_2D, m_id );

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGBA,
    m_width,
    m_height,
    0, // border
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    data 
  );

  free(data);

  return true;
}

int Surface::width() {
  return m_width;
}

int Surface::height() {
  return m_height;
}

float Surface::to_u(int x) {
  return (float)m_width / (float)x;
}

float Surface::to_v(int y) {
  return (float)m_height / (float)y;
}

void Surface::select() {
  glBindTexture( GL_TEXTURE_2D, m_id );
}

