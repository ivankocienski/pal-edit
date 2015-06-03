
#include "application.hh"
#include "video.hh"
#include "mode-base.hh" 

Application::Application(Video* v) : m_video(v), m_color_grid( this, m_palette ) { 
  m_video->set_event_callbacks( this );
}

void Application::init() { 
  set_mode( AM_COLOR_GRID );
}

void Application::cleanup() { }

void Application::set_mode( int m ) {

  switch(m) {
    case AM_COLOR_GRID:
      m_current_mode = (ModeBase *)&m_color_grid;
      break;

    default:
      throw "Application::set_mode(): mode identifier not recognised";
      break;
  } 

  m_current_mode->activate();
}

ModeBase *Application::current_mode() {
  return m_current_mode;
}

Video* Application::video() {
  return m_video;
}

void Application::do_key_down( int k ) {
  m_current_mode->on_key_down(k);
}

void Application::do_key_up( int k ) {
  m_current_mode->on_key_up(k);
}
