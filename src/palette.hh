
#pragma once

#include <vector>
#include <GL/gl.h>

class Palette {
public:

  typedef struct _S_COLOR {
    unsigned char red;
    unsigned char green;
    unsigned char blue; 

    void set_gl() const {
      glColor3f(
          float(red)   / 255.0,
          float(green) / 255.0,
          float(blue)  / 255.0);
    }

  } T_COLOR, *PT_COLOR;

  Palette();

  void reset();

  void set_color( int, const T_COLOR& );
  void set_color( int, int, int, int );
  void load_from_array( const unsigned char*, int );
  bool load_from_file( const char* );
  bool save_to_file( const char* ) const;

  const T_COLOR & at( int ) const;

private:
  std::vector<T_COLOR> m_colors;
};

