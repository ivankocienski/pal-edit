
#include <stdio.h>

#include "application.hh"
#include "video.hh"
#include "mode-base.hh" 

Application::Application(Video* v) : 
  m_video(v), 
  m_color_grid( this, m_palette ),
  m_edit_color( this ),
  m_new_grid( this )
{ 
  m_video->set_event_callbacks( this );
  m_current_mode = NULL;
  m_last_mode = NULL;
}

void Application::init() { 
  set_mode( AM_COLOR_GRID );
}

void Application::cleanup() { }

void Application::set_palette( const Palette &p ) {
  m_palette = p;
}

void Application::set_mode( int m ) {

  m_last_mode = m_current_mode;
  m_current_mode = get_mode(m);

  if( !m_current_mode )
    throw "Application::set_mode(): mode identifier not recognised";

  m_current_mode->activate();
}

ModeBase *Application::current_mode() {
  return m_current_mode;
}

ModeBase *Application::last_mode() {
  return m_last_mode;
}

ModeBase *Application::get_mode( int m ) {
  switch(m) {
    case AM_COLOR_GRID: 
      return (ModeBase *)&m_color_grid;
    case AM_EDIT_COLOR: 
      return (ModeBase *)&m_edit_color;
    case AM_NEW_GRID: 
      return (ModeBase *)&m_new_grid;
    default:
      break;
  }

  return NULL;
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
