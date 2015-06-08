
#pragma once

#include <string>

#include "mode-base.hh"
#include "directory.hh"

class SaveFileMode : public ModeBase {
private:

  enum { // sub mode
    SM_TOP,
    SM_TYPE_NAME,
    SM_SELECT_DIR
  };
  
  int m_sub_mode;
  int m_cur_pos;

  std::string m_dir_path;
  std::string m_filename;
  std::string m_newfilename;

  int m_dir_pos;
  Directory m_dir_scanner;

  void draw_top_menu();
  void on_key_top_menu(int);

  void draw_type_name();
//  void on_key_type_menu(int);

  void draw_select_dir();
  void on_key_select_dir(int);

public:

  SaveFileMode( Application* );

  void activate();
  void on_key_down(int);
  void on_inkey(unsigned int);

  void draw();
};

