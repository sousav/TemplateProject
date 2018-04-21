/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 00:55:38
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 22:36:28
 */


#include "CppConsole.h"

CppConsole::CppConsole(): ACreator("CppConsole") {

}

CppConsole::~CppConsole() {

}

ArgParser::parser CppConsole::setupArgParser() const {
    return ArgParser::parser {{
        // expect no other argument
    }};
}

bool CppConsole::checkArgument(ArgParser::parser_results const &args) const {
    // expect no other argument
    return true;
}

extern "C" {

    ICreator *Create() {
        return new CppConsole();
    }

}
