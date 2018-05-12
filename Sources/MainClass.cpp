/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 14:17:52
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 07/05/2018 11:05:24
 */


#include "MainClass.h"

MainClass::MainClass(int argc, char *argv[]): AMain(argc, argv, "MainClass") {

}

MainClass::~MainClass() {

}


ArgParser::parser MainClass::setupArgParser() const {
    return ArgParser::parser {{
        { "help", {"-h", "--help"}, "Shows this help message.\n", 0},
        { "project_name", {"-n", "--name"}, KRED + "[required]" + KNRM + " Specify the project name.\n", 1},
        { "project_type", {"-t", "--type"}, KRED + "[required]" + KNRM + " Specify the project type.\n", 1},
        { "project_path", {"-p", "--path"}, "            Specify the path where the project must be created." + KYEL + "\n\tdefault: \"./name\"\n" + KNRM, 1},
        { "list_type", {"-l", "--list"}, "            List all project type possibilities.\n", 0}
    }};
}


bool MainClass::Run(ArgParser::parser_results const &args) {
    if (!this->registerCreators()) {
        return false;
    }

    if (!this->checkArgument(args)) {
        return false;
    }

    std::string project_name = args["project_name"].as<std::string>();
    std::string project_type = args["project_type"].as<std::string>();
    std::string project_path = boost::filesystem::current_path().string() + "/" + args["project_name"].as<std::string>();
    if (args["project_path"]) {
        project_path = args["project_path"].as<std::string>();
    }


    std::map<std::string, std::shared_ptr<ICreator>>::iterator it = this->_creators.find(project_type);
    if (it != this->_creators.end()) {
        return this->_creators[project_type]->createProject(project_name, project_path, this->_argc, this->_argv);
    } else {
        ArgParser::fmt_ostream(std::cerr) << KRED + "\n\"" + project_type + "\" is not a valid project type" + KNRM << std::endl << this->setupArgParser();
    }

    return false;
}

bool MainClass::checkArgument(ArgParser::parser_results const &args) const {
    if (args["help"]) {
        ArgParser::fmt_ostream(std::cerr) << "Usage:" << std::endl << this->setupArgParser();
        return false;
    }

    if (args["list_type"]) {
        this->logger.info() << "Possible project type:";
        for (auto const &e: this->_creators) {
            this->logger.info() << e.first;
        }
        return false;
    }

    if (!args["project_name"]) {
        ArgParser::fmt_ostream(std::cerr) << KRED + "\nYou must provide a project name using -n or --name\n" + KNRM << std::endl << this->setupArgParser();
        return false;
    }
    if (!args["project_type"]) {
        ArgParser::fmt_ostream(std::cerr) << KRED + "\nYou must provide a project type -t or --type\n" + KNRM << std::endl << this->setupArgParser();
        return false;
    }
    return true;
}

bool MainClass::registerCreators() {
    boost::filesystem::path path(boost::executable_path(this->_argv[0]));
    try {
        this->_creators = CreatorLoader().withPath(path.parent_path().string() + "/Creators").withExtension("*.so").run().getCreators();
    } catch (std::exception &e) {
        this->logger.error() << "Could not load any creator library:\n" << e.what();
        return false;
    }
    return true;
}
