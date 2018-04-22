/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 14:17:52
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 22/04/2018 03:26:00
 */


#include "MainClass.h"

MainClass::MainClass(int argc, char *argv[]): AMain(argc, argv, "MainClass") {

}

MainClass::~MainClass() {

}


ArgParser::parser MainClass::setupArgParser() const {
    return ArgParser::parser {{
        { "help", {"-h", "--help"}, "Shows this help message.\n", 0}
    }};
}

bool MainClass::Run(ArgParser::parser_results const &args) {

    if (!this->checkArgument(args)) {
        return false;
    }

    return true;
}

bool MainClass::checkArgument(ArgParser::parser_results const &args) const {
    if (args["help"]) {
        ArgParser::fmt_ostream(std::cerr) << "Usage:" << std::endl << this->setupArgParser();
        return false;
    }

    return true;
}
