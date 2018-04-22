/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 01:14:01
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 22/04/2018 02:58:25
 */


#ifndef ICREATOR_H_
#define ICREATOR_H_

#define KNRM  std::string("\x1B[0m")
#define KRED  std::string("\x1B[31m")
#define KGRN  std::string("\x1B[32m")
#define KYEL  std::string("\x1B[33m")
#define KBLU  std::string("\x1B[34m")
#define KMAG  std::string("\x1B[35m")
#define KCYN  std::string("\x1B[36m")
#define KWHT  std::string("\x1B[37m")

#include <iostream>
#include <unordered_map>
#include <string>
#include <boost/filesystem.hpp>
#include "ArgParser/ArgParser.h"
#include "Logger/Logger.h"
#include "Logger/Manager.h"
#include "Resource.h"

class ICreator {

public:
    virtual ~ICreator() {};

    virtual std::string const &getName() const = 0;
    virtual bool createProject(std::string const &name, std::string const &path, int argc, char **argv) = 0;

private:
    virtual ArgParser::parser setupArgParser() const = 0;
    virtual bool checkArgument(ArgParser::parser_results const &args) const = 0;
    virtual bool createDestination(std::string const &path) const = 0;
    virtual bool unzipTemplate(std::string const &path) const = 0;
    virtual std::unordered_map<std::string, std::string> setupProjectKeyword(ArgParser::parser_results const &args) const = 0;
    virtual bool replaceKeyword(std::unordered_map<std::string, std::string> const &keyword) const = 0;

};

#endif /*ICREATOR_H_*/
