
#include <string.h>

#include "global.hh"

unsigned char anim = 0;
char buffer[BUFFER_LEN];

void global_init() {
  memset( buffer, 0, sizeof(buffer));
}
