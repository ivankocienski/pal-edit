
#pragma once

#include "mode-base.hh"
#include "palette.hh"

class ColorGrid : public ModeBase {
private:

  Palette & m_palette;

  int m_cur_pos;
  
public:


  ColorGrid( Application*, Palette & );

  void init();

  void draw();
  void on_key_down( int );

};
