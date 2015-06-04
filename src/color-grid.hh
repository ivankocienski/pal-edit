
#pragma once

#include "mode-base.hh"
#include "palette.hh"

class EditColor;

class ColorGrid : public ModeBase {
private:

  Palette & m_palette;
  EditColor *m_color_edit;
  Palette::T_COLOR m_copy_color;

  int m_cur_pos;
  int m_mark_pos;
  int m_edit_color;

  void normalize_range( int&, int& );
  
public:


  ColorGrid( Application*, Palette & );

  void activate();

  void draw();
  void on_key_down( int );

};
