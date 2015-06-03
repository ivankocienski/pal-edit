
#include <iostream>

#include "video.hh"
#include "application.hh"

using namespace std;

int main(int argc, char ** argv ) {

  int status = 0;

  try {

    Video vid( 800, 600, "palette editor" );

    Application app( &vid );

    if( !vid.open() ) 
      throw "open video failed";
    
    app.init();

    while( vid.is_open() ) {

      app.current_mode()->draw();

      vid.tick();
    }

  } catch (const char *msg) {

    cerr << "error: " << msg << endl;

    status = -1;
  }

  return status; 
}


