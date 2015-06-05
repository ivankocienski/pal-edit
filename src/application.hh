
#pragma once

class Video;

#include "palette.hh"
#include "color-grid.hh"
#include "edit-color.hh"
#include "new-grid-mode.hh"

class Application {
private:

  Video *m_video;

  ModeBase *m_current_mode;
  ModeBase *m_last_mode;

  // application modes
  ColorGrid m_color_grid;
  EditColor m_edit_color;

  NewGridMode m_new_grid;

  Palette m_palette;

public:

  enum { // application mode
    AM_COLOR_GRID,
    AM_EDIT_COLOR,
    AM_NEW_GRID
  };

  Application( Video* );

  void init();
  void cleanup();

  void set_palette( const Palette& );

  void set_mode( int );

  void do_key_down( int );
  void do_key_up( int );
  
  ModeBase *current_mode();
  ModeBase *last_mode();
  ModeBase *get_mode( int );
  Video *video();
};

