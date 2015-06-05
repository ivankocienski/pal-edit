
#pragma once

#include <vector>
#include <string>

#include "mode-base.hh"
#include "palette.hh"

class Application;

class NewGridMode : public ModeBase {
private:

  std::vector<std::string> m_names;
  std::vector<Palette> m_palettes;

  int m_menu_pos;
  

public:

  NewGridMode(Application*);

  void activate();
  void on_key_down(int);

  void draw();
};

