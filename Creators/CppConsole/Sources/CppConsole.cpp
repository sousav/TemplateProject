/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 00:55:38
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 16:04:25
 */


#include "CppConsole.h"

CppConsole::CppConsole(): ACreator("CppConsole") {

}

CppConsole::~CppConsole() {

}


extern "C" {

    ICreator *Create() {
        return new CppConsole();
    }

}
