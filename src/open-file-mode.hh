
#pragma once

#include "mode-base.hh"
#include "directory.hh"

class Application;

class OpenFileMode : public ModeBase {
private:

  Directory m_directory;

  int m_dir_pos;
  int m_dir_top;
  
  void load_palette_file( const char* );

public:

  OpenFileMode( Application* );

  void activate();
  void on_key_down(int);

  void draw();
};

