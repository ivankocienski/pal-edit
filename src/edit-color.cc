
#include <stdio.h>

#include "edit-color.hh"
#include "application.hh"
#include "video.hh"

static char buffer[256];
static unsigned char anim = 0;

/*
 * Component
 */

Component::Component() {
  m_value = 0;
}

void Component::set(unsigned char v) {
  m_value = v;
}

unsigned char Component::val() {
  return m_value;
}

void Component::inc(int d) {
  int v = m_value + d;
  if( v < 0 ) v = 0;
  if( v > 255 ) v = 255;

  m_value = v;
}

void Component::dec(int d) {
  int v = m_value - d;
  if( v < 0 ) v = 0;
  if( v > 255 ) v = 255;

  m_value = v;
}

float Component::as_float() {
  return float(m_value) / 255.0;
}


/*
 * EditColor
 */


EditColor::EditColor( Application *a ) : ModeBase(a) {
  m_update = false;
  m_cur_comp = 0;
}

void EditColor::set_color( int i, const Palette::T_COLOR &c ) {
  m_index = i;
  m_component[0].set( c.red );
  m_component[1].set( c.green );
  m_component[2].set( c.blue );
}

Palette::T_COLOR EditColor::color() {
  Palette::T_COLOR c;

  c.red   = m_component[0].val();
  c.green = m_component[1].val();
  c.blue  = m_component[2].val();

  return c;
}

void EditColor::init() {
  m_update = false;
}

bool EditColor::user_wants_color_updated() {
  return m_update;
}

void EditColor::draw() {

  anim++;
  
  glBegin( GL_QUADS );

  glColor3f(
      m_component[0].as_float(),
      m_component[1].as_float(),
      m_component[2].as_float());

  glVertex2f(  10,  10 );
  glVertex2f( 110,  10 );
  glVertex2f( 110, 110 );
  glVertex2f(  10, 110 );

  glColor3f( 1, 1, 1 );

  int  y = 202;
  for( int i = 0; i < 3; i++ ) {
    glVertex2f( 11, y );
    glVertex2f( 11 + m_component[i].val(), y );
    glVertex2f( 11 + m_component[i].val(), y + 36 );
    glVertex2f( 11, y + 36 );
    
    y += 100;
  }

  glEnd();

  if( (m_cur_comp == 0 && (anim >> 3) & 1) || m_cur_comp != 0 ) {
    glBegin( GL_LINE_LOOP );
    glColor3f( 1, 0.2, 0.2 );
    glVertex2f( 10, 200 );
    glVertex2f( 265, 200 );
    glVertex2f( 265, 240 );
    glVertex2f( 10, 240 );
    glEnd();
  }

  if( (m_cur_comp == 1 && (anim >> 3) & 1) || m_cur_comp != 1 ) {
    glBegin( GL_LINE_LOOP );
    glColor3f( 0.2, 1, 0.2 );
    glVertex2f( 10, 300 );
    glVertex2f( 265, 300 );
    glVertex2f( 265, 340 );
    glVertex2f( 10, 340 );
    glEnd();
  }

  if( (m_cur_comp == 2 && (anim >> 3) & 1) || m_cur_comp != 2 ) {
    glBegin( GL_LINE_LOOP );
    glColor3f( 0.2, 0.2, 1 );
    glVertex2f( 10, 400 );
    glVertex2f( 265, 400 );
    glVertex2f( 265, 440 );
    glVertex2f( 10, 440 );
    glEnd();
  }

  glColor3f( 1, 1, 1 );

  glEnable( GL_TEXTURE_2D );

  m_video->draw_text( 400, 10, "COLOR EDIT" );

  snprintf( buffer, 256, "index %d", m_index );
  m_video->draw_text( 400, 25, buffer);

  snprintf( buffer, 256, "%03d", m_component[0].val() );
  m_video->draw_text( 10, 190, buffer);

  snprintf( buffer, 256, "%03d", m_component[1].val() );
  m_video->draw_text( 10, 290, buffer);

  snprintf( buffer, 256, "%03d", m_component[2].val() );
  m_video->draw_text( 10, 390, buffer);

  snprintf( buffer, 256, "  hex 0x%02x%02x%02x",
      m_component[0].val(),
      m_component[1].val(),
      m_component[2].val());
  m_video->draw_text( 400, 65, buffer);


  m_video->draw_text( 650, 10, "KEY HELP" );
  m_video->draw_text( 650, 25, "I   0% component" );
  m_video->draw_text( 650, 35, "O  50% component" );
  m_video->draw_text( 650, 45, "P 100% component" );
  m_video->draw_text( 650, 55, "E save, return" );

  m_video->draw_text( 650, 70, "  PGUP + 25" );
  m_video->draw_text( 650, 80, "PGDOWN -25" );

  m_video->draw_text( 650,  95, "  E save, return" );
  m_video->draw_text( 650, 105, "ESC cancel" );

  glDisable( GL_TEXTURE_2D );
}

void EditColor::on_key_down( int k ) {

  switch( k ) {
    case GLFW_KEY_UP:
      m_cur_comp--;
      if(m_cur_comp < 0) m_cur_comp = 2;
      break;

    case GLFW_KEY_DOWN:
      m_cur_comp = (m_cur_comp + 1) % 3;
      break;

    case GLFW_KEY_LEFT:
      m_component[m_cur_comp].dec(1);
      break;

    case GLFW_KEY_RIGHT:
      m_component[m_cur_comp].inc(1);
      break;

    case GLFW_KEY_PAGE_UP:
      m_component[m_cur_comp].inc(25);
      break;

    case GLFW_KEY_PAGE_DOWN:
      m_component[m_cur_comp].dec(25);
      break;

    case GLFW_KEY_I:
      m_component[m_cur_comp].set(0);
      break;

    case GLFW_KEY_O:
      m_component[m_cur_comp].set(127);
      break;

    case GLFW_KEY_P:
      m_component[m_cur_comp].set(255);
      break;

    case GLFW_KEY_E:
      m_update = true;


    case GLFW_KEY_ESCAPE:
      m_application->set_mode( Application::AM_COLOR_GRID );
      break;

  }

}

