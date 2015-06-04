
#pragma once

#include "mode-base.hh"
#include "palette.hh"

class Application;

class Component {
private:

  unsigned char m_value;

public:

  Component();

  void set(unsigned char);

  unsigned char val();

  void inc(int);
  void dec(int);
  float as_float();
};

class EditColor : public ModeBase {
private:

  int m_index;
  
  bool m_update;
  
  Component m_component[3];
  int m_cur_comp;
  
public:

  EditColor( Application* );

  void init();
  void set_color( int, const Palette::T_COLOR& );
  Palette::T_COLOR color();
  bool user_wants_color_updated();

  void draw();
  void on_key_down( int );

};

