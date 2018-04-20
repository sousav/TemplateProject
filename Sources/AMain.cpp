/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 19:23:16
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 18/04/2018 23:34:31
 */

#include "AMain.h"

AMain::AMain(int argc, char *argv[], std::string const &className): AClass(className) {
    this->_argc = argc;
    this->_argv = argv;
}

AMain::~AMain() {

}


bool AMain::Run() {
    ArgParser::parser parser = this->SetupArgParser();

    ArgParser::parser_results args;
    try {
        args = parser.parse(this->_argc, this->_argv);
    } catch (const std::exception& e) {
        this->logger.error() << e.what();
        return false;
    }

    return this->Run(args);
}
