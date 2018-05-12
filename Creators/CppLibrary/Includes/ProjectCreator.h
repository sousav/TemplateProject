/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 00:55:40
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 02/05/2018 21:41:17
 */


#ifndef PROJECTCREATOR_H_
#define PROJECTCREATOR_H_

#include <boost/filesystem.hpp>
#include "ACreator.h"

class CppLibrary : public ACreator {

public:
    CppLibrary();
    virtual ~CppLibrary();

    ArgParser::parser setupArgParser() const;
    bool checkArgument(ArgParser::parser_results const &args) const;
    std::unordered_map<std::string, std::string> setupProjectKeyword(ArgParser::parser_results const &args) const;

};


#endif /*PROJECTCREATOR_H_*/
