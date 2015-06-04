
#pragma once

#include "mode-base.hh"
#include "palette.hh"

class EditColor;

class ColorGrid : public ModeBase {
private:

  Palette & m_palette;
  EditColor *m_color_edit;

  int m_cur_pos;
  int m_edit_color;
  
public:


  ColorGrid( Application*, Palette & );

  void activate();

  void draw();
  void on_key_down( int );

};
