
#pragma once

class Video;

#include "color-grid.hh"

class Application {
private:

  Video *m_video;

  ModeBase *m_current_mode;

  // application modes
  ColorGrid m_color_grid;


public:

  enum { // application mode
    AM_COLOR_GRID
  };

  Application( Video* );

  void init();
  void cleanup();

  void set_mode( int );

  ModeBase *current_mode();
  Video *video();
};

