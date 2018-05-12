/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 00:55:40
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 12/05/2018 17:45:39
 */


#ifndef PROJECTCREATOR_H_
#define PROJECTCREATOR_H_

#include <boost/filesystem.hpp>
#include "ACreator.h"

class CppSharedLibrary : public ACreator {

public:
    CppSharedLibrary();
    virtual ~CppSharedLibrary();

    ArgParser::parser setupArgParser() const;
    bool checkArgument(ArgParser::parser_results const &args) const;
    std::unordered_map<std::string, std::string> setupProjectKeyword(ArgParser::parser_results const &args) const;

};


#endif /*PROJECTCREATOR_H_*/
