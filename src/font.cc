
#include <GL/gl.h>
#include <string.h>
#include <stdio.h>

#include "font.hh"
#include "png++/png.hpp"

Font::Font() {
	m_charListID   = 0;
  m_font_surface = 0;
	
	m_baseChar   = 0;
	m_charWidth  = 0;
	m_charHeight = 0;
	m_numChars   = 0;
}

#include <vector>
using namespace std;

bool Font::load_texture( const char *fn, float &o_w, float &o_h ) {

  png::image< png::rgba_pixel >image;
  image.read(fn);

  vector<unsigned char> pixel_buffer;
  pixel_buffer.resize( image.get_width() * image.get_height() * 4 );
  unsigned char *pb = pixel_buffer.data();

  for( unsigned int y = 0; y < image.get_height(); y++ ) {

    png::image< png::rgba_pixel >::row_type const & row = image.get_row(y);

    for( unsigned int x = 0; x < image.get_width(); x++ ) {

      *pb = row.at(x).red;   pb++;
      *pb = row.at(x).green; pb++;
      *pb = row.at(x).blue;  pb++;
      *pb = row.at(x).alpha; pb++;
    }
  }

  glGenTextures( 1, &m_font_surface);
  glBindTexture( GL_TEXTURE_2D, m_font_surface);

  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
  
  glTexImage2D(
    GL_TEXTURE_2D, 
    0, 
    GL_RGBA, 
    image.get_width(),
    image.get_height(),
    0,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    pixel_buffer.data()
  );

  o_w = (float)image.get_width();
  o_h = (float)image.get_height();

  return true;
}

bool Font::load( const char* ifn, int cw, int ch, int start, int end) {

  float image_w;
  float image_h;

  if( !load_texture( ifn, image_w, image_h )) return false;

  /* do magic */
	float x1;
	float x2;
	float y1;
	float y2;
	
	int ix;
	int iy;
	int n;
	
	m_numChars   = end - start;
	m_baseChar   = start;
	m_charWidth  = cw;
	m_charHeight = ch;
	
	m_charListID = glGenLists(m_numChars);
	
	ix = 0;
	iy = 0;

	for(n = 0; n < m_numChars; n++) {
		
		x1 = (float)ix / image_w;
		y1 = (float)iy / image_h;
		x2 = (float)(ix + m_charWidth) / image_w;
		y2 = (float)(iy + m_charHeight) / image_h;
		
		glNewList(m_charListID + n, GL_COMPILE);
		
		  glBegin(GL_QUADS);
			
			glTexCoord2f(x1, y1); glVertex2i(0, 0);
      glTexCoord2f(x2, y1); glVertex2i(m_charWidth, 0);
			glTexCoord2f(x2, y2); glVertex2i(m_charWidth, m_charHeight);
			glTexCoord2f(x1, y2); glVertex2i(0, m_charHeight);
			
		  glEnd();
		  
		  glTranslated(m_charWidth + 1, 0, 0);
		  
		glEndList();
		
		ix += m_charWidth;
		if(ix >= image_w) {
			ix = 0;
			iy += m_charHeight;
			
			if(iy >= image_h) break;
		}
	}

  return true;
}

Font::~Font() {

  if(m_font_surface) glDeleteTextures(1, &m_font_surface);
	if(m_charListID) glDeleteLists(m_charListID, m_numChars);
}

void Font::draw_fast(const char* s, int l) {
	glListBase(m_charListID - m_baseChar);
	glCallLists(l, GL_BYTE, s);
}

void Font::draw(const char* s, int len) {
  glBindTexture( GL_TEXTURE_2D, m_font_surface);
  glPushMatrix();

	glListBase(m_charListID - m_baseChar);
	glCallLists(len, GL_BYTE, s);

  glPopMatrix();
}

void Font::draw_slow(int x, int y, const char* s) {
  glBindTexture( GL_TEXTURE_2D, m_font_surface);

  glPushMatrix();
	glLoadIdentity();
	glTranslated(x, y, 0);
	glListBase(m_charListID - m_baseChar);
	
	glCallLists(strlen(s), GL_BYTE, s);
  glPopMatrix();
}

int Font::width() {

	return m_charWidth;
}

int Font::strWidth(char* s) {
	
	return m_charWidth * strlen(s);
}

int Font::height() {

	return m_charHeight;
}

int Font::centerOffset(char* s) {
	
	return (640 - (m_charWidth * strlen(s))) / 2.0;
}

