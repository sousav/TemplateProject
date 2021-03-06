/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 00:55:38
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 02/05/2018 21:49:22
 */


#include "ProjectCreator.h"

{{project_name}}::{{project_name}}(): ACreator("{{project_name}}") {

}

{{project_name}}::~{{project_name}}() {

}

ArgParser::parser {{project_name}}::setupArgParser() const {
    return ArgParser::parser {{
        { "help", {"-h", "--help"}, "Shows this help message.\n", 0},
        { "project_name", {"-n", "--name"}, KRED + "[requiered]" + KNRM + " Specify the project name.\n", 1},
        { "project_type", {"-t", "--type"}, KRED + "[requiered]" + KNRM + " Specify the project type.\n", 1},
        { "project_path", {"-p", "--path"}, "            Specify the path where the project must be created." + KYEL + "\n\tdefault: \"./name\"\n" + KNRM, 1},
        { "list_type", {"-l", "--list"}, "            List all project type possibilities.\n", 0}
    }};
}

bool {{project_name}}::checkArgument(ArgParser::parser_results const &args) const {
    // expect no other argument
    return true;
}

std::unordered_map<std::string, std::string> {{project_name}}::setupProjectKeyword(ArgParser::parser_results const &args) const {
    std::unordered_map<std::string, std::string> keyword;

    keyword.insert(std::make_pair("project_name", args["project_name"].as<std::string>()));

    return keyword;
}

extern "C" {

    ICreator *Create() {
        return new {{project_name}}();
    }

}
