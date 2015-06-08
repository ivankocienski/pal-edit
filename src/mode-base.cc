
#include "mode-base.hh"
#include "application.hh"
#include "video.hh"

#include <iostream>
using namespace std;

void ModeBase::set_mode(int m) {
  m_application->set_mode(m);
}

ModeBase::ModeBase( Application* a ) {
  m_application = a; 
  m_video = m_application->video();
}

void ModeBase::activate() { 
  cout << "ModeBase: activate()" << endl;
}

void ModeBase::on_key_down(int) { 
}

void ModeBase::on_inkey(unsigned int) { 
}

void ModeBase::on_key_up(int) { 
}

void ModeBase::move() { 
}

void ModeBase::draw() { 
}
