
#include <stdio.h>

#include "application.hh"
#include "video.hh"
#include "mode-base.hh" 

Application::Application(Video* v) : 
  m_video(v), 
  m_color_grid( this, m_palette ),
  m_edit_color( this ),
  m_new_grid( this ),
  m_open_file( this ),
  m_save_file( this ),
  m_confirm_quit( this )
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
const Palette& Application::palette() const {
  return m_palette;
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
    case AM_OPEN_FILE:
      return (ModeBase *)&m_open_file;
    case AM_SAVE_FILE:
      return (ModeBase *)&m_save_file;
    case AM_CONFIRM_QUIT:
      return (ModeBase *)&m_confirm_quit;
      
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

void Application::do_inkey( unsigned int k ) {
  m_current_mode->on_inkey(k);
}
