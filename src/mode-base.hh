
#pragma once

class Application;
class Video;

class ModeBase {
protected:

  Application *m_application;
  Video *m_video;

  void set_mode(int);

public:
  
  ModeBase( Application* );

  virtual void activate();
 
  virtual void on_key_down(int);
  virtual void on_key_up(int);

  virtual void move();
  virtual void draw();
};

