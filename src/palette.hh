
#pragma once

#include <vector>

class Palette {
public:

  typedef struct _S_COLOR {
    unsigned char red;
    unsigned char green;
    unsigned char blue; 
  } T_COLOR, *PT_COLOR;

  Palette();

  void reset();

  const T_COLOR & at( int ) const;

private:
  std::vector<T_COLOR> m_colors;
};

