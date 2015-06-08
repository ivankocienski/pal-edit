
#include <fstream>
#include <iostream>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

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

bool Palette::load_from_file( const char *path ) {

  /* for now, text files */
  string line;
  ifstream file;
  file.open( path, fstream::in );
  vector<string> words;
  int i = 0;

  if( !file.is_open() ) {
    cerr << "error: could not open file " << path << endl;
    return false;
  }

  while( !file.eof() ) {

    getline( file, line );

    boost::split( words, line, boost::is_any_of("\t \n\r"));

    if( words.empty() ) continue;

    if( words[0] == "c" ) {

      int c = boost::lexical_cast<int>( words[1] );
      cout << "loading " << c << " colors";

      continue;
    }

    if( words[0] == "e" ) {

      int r = boost::lexical_cast<int>( words[1] );
      int g = boost::lexical_cast<int>( words[2] );
      int b = boost::lexical_cast<int>( words[3] );

      set_color( i++, r, g, b );

      continue;
    }

    //cerr << "error: uncrecognised line type in palette file: " << words[0] << endl;
    //return false;
  }

  return true;
}

bool Palette::save_to_file( const char *path ) const {

  ofstream file;
  file.open(path, fstream::out | fstream::trunc );

  if( !file.is_open() ) return false;

  file << "c " << m_colors.size() << endl;

  for( int i = 0; i < m_colors.size(); i++ ) {
    file 
      << "e " 
      << int(m_colors[i].red)   << " " 
      << int(m_colors[i].green) << " " 
      << int(m_colors[i].blue)  << endl;
  }

  return true; 
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
