
#pragma once

class Video;

#include "palette.hh"
#include "color-grid.hh"
#include "edit-color.hh"
#include "new-grid-mode.hh"
#include "open-file-mode.hh"
#include "save-file-mode.hh"
#include "confirm-quit.hh"

class Application {
private:

  Video *m_video;

  ModeBase *m_current_mode;
  ModeBase *m_last_mode;

  // application modes
  ColorGrid m_color_grid;
  EditColor m_edit_color;

  NewGridMode m_new_grid;
  OpenFileMode m_open_file;
  SaveFileMode m_save_file;
  ConfirmQuit m_confirm_quit;

  Palette m_palette;

public:

  enum { // application mode
    AM_COLOR_GRID,
    AM_EDIT_COLOR,
    AM_NEW_GRID,
    AM_OPEN_FILE,
    AM_SAVE_FILE,
    AM_CONFIRM_QUIT
  };

  Application( Video* );

  void init();
  void cleanup();

  void set_palette( const Palette& );
  const Palette& palette() const;

  void set_mode( int );

  void do_key_down( int );
  void do_key_up( int );
  void do_inkey( unsigned int);
  
  ModeBase *current_mode();
  ModeBase *last_mode();
  ModeBase *get_mode( int );
  Video *video();
};

