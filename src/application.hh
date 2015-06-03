
#pragma once

class Video;

#include "palette.hh"
#include "color-grid.hh"

class Application {
private:

  Video *m_video;

  ModeBase *m_current_mode;

  // application modes
  ColorGrid m_color_grid;

  Palette m_palette;

public:

  enum { // application mode
    AM_COLOR_GRID
  };

  Application( Video* );

  void init();
  void cleanup();

  void set_mode( int );

  void do_key_down( int );
  void do_key_up( int );
  
  ModeBase *current_mode();
  Video *video();
};

