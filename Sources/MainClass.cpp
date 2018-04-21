/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 14:17:52
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 04:05:21
 */


#include "MainClass.h"

MainClass::MainClass(int argc, char *argv[]): AMain(argc, argv, "MainClass") {

}

MainClass::~MainClass() {

}


ArgParser::parser MainClass::SetupArgParser() const {
    return ArgParser::parser {{
        { "help", {"-h", "--help"}, "Shows this help message.\n", 0},
        { "project_name", {"-n", "--name"}, KRED + "[requiered]" + KNRM + " Specify the project name.\n", 1},
        { "project_type", {"-t", "--type"}, KRED + "[requiered]" + KNRM + " Specify the project type.\n", 1},
        { "project_path", {"-p", "--path"}, "            Specify the path where the project must be created." + KYEL + "\n\tdefault: \"./name\"\n" + KNRM, 1},
        { "list_type", {"-l", "--list"}, "            List all project type possibilities.\n", 0}
    }};
}

bool MainClass::Run(ArgParser::parser_results const &args) {
    this->registerCreators();

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
        this->logger.notice() << this->_creators[project_type]->getName();
    } else {
        ArgParser::fmt_ostream(std::cerr) << KRED + "\n\"" + project_type + "\" is not a valid project type" + KNRM << std::endl << this->SetupArgParser();
    }

    return true;
}

bool MainClass::checkArgument(ArgParser::parser_results const &args) const {
    if (args["help"]) {
        ArgParser::fmt_ostream(std::cerr) << "Usage:" << std::endl << this->SetupArgParser();
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
        ArgParser::fmt_ostream(std::cerr) << KRED + "\nYou must provide a project name using -n or --name\n" + KNRM << std::endl << this->SetupArgParser();
        return false;
    }
    if (!args["project_type"]) {
        ArgParser::fmt_ostream(std::cerr) << KRED + "\nYou must provide a project type -t or --type\n" + KNRM << std::endl << this->SetupArgParser();
        return false;
    }
    return true;
}

void MainClass::registerCreators() {
    this->_creators = CreatorLoader().withPath("./Creators").withExtension("*.so").run().getCreators();
}
