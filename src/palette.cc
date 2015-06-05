
#include "palette.hh"

using namespace std;

Palette::Palette() {
  m_colors.resize(256);

  reset();
}

void Palette::reset() {

  
  for( int i = 0; i < 256; i++ ) {
    set_color( i, 0, 0, 0 );
  } 
}

void Palette::load_from_array( const unsigned char *p, int c ) {

  for( int i = 0; i < c; i++ ) {
    set_color(
        i,
        *p, *(p + 1), *(p + 2));
    p += 3;
  }

}

const Palette::T_COLOR & Palette::at( int i ) const {
  return m_colors[i];
}

void Palette::set_color( int i, const Palette::T_COLOR &c ) {
  set_color( i, c.red, c.green, c.blue );
}

void Palette::set_color( int i, int r, int g, int b ) {
  m_colors[i].red   = r;
  m_colors[i].green = g;
  m_colors[i].blue  = b;
}
