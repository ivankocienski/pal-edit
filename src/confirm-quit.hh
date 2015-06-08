
#pragma once

#include "mode-base.hh"

class Application;

class ConfirmQuit : public ModeBase {
private:

public:

  ConfirmQuit( Application* );

  void activate();
  void on_key_down(int);

  void draw();
};

