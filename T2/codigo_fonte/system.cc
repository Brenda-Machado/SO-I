#include "system.h"
#include <iostream>
#include "debug.h"

__BEGIN_API

void System::init(){
	db<System>(TRC) << "System::init() chamado\n";
	setvbuf (stdout, 0, _IONBF, 0);
}

__END_API
