
#include "palette.hh"
#include "default_palette.hh"

using namespace std;

Palette::Palette() {
  m_colors.resize(256);

  reset();
}

void Palette::reset() {

  for( int i = 0; i < 256; i++ ) {
    m_colors[i].red   = default_colors[i][0];
    m_colors[i].green = default_colors[i][1];
    m_colors[i].blue  = default_colors[i][2];
  }

}

const Palette::T_COLOR & Palette::at( int i ) const {
  return m_colors[i];
}

void Palette::set_color( int i, const Palette::T_COLOR &c ) {
  m_colors[i].red   = c.red;
  m_colors[i].green = c.green;
  m_colors[i].blue  = c.blue;
}

void Palette::set_color( int i, int r, int g, int b ) {
  m_colors[i].red   = r;
  m_colors[i].green = g;
  m_colors[i].blue  = b;
}
