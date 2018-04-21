/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 00:55:38
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 03:47:01
 */


#include "CppConsole.h"

CppConsole::CppConsole(): ACreator("CppConsole") {
    
/*
Resource text = LOAD_RESOURCE(Template_gz);
std::ofstream outfile ("Template.gz");
outfile << std::string(text.data(), text.size()) << std::endl;
outfile.close();
std::system("mkdir Template");
std::system("tar -xvf Template.gz -C ./Template && rm Template.gz");
*/

}

CppConsole::~CppConsole() {

}


extern "C" {

    ICreator *Create() {
        return new CppConsole();
    }

}
