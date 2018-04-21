/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 01:14:01
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 16:47:09
 */


#ifndef ICREATOR_H_
#define ICREATOR_H_

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
    virtual bool createProject(std::string const &name, std::string const &path, ArgParser::parser_results const &args) = 0;

private:
    virtual bool createDestination(std::string const &path) = 0;
    virtual bool unzipTemplate(std::string const &path) = 0;

};

#endif /*ICREATOR_H_*/
