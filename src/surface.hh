
#pragma once

#include <GL/gl.h>

class Surface {
private:

  GLuint m_id;
  int m_width;
  int m_height;

public:

  Surface();
  ~Surface();

  bool load( const char *);
  int width();
  int height();

  float to_u(int);
  float to_v(int);

  void select();
};

