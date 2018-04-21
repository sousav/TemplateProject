/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 00:55:40
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 22:36:25
 */


#ifndef CPPCONSOLE_H_
#define CPPCONSOLE_H_

#include <boost/filesystem.hpp>
#include "ACreator.h"

class CppConsole : public ACreator {

public:
    CppConsole();
    virtual ~CppConsole();

    ArgParser::parser setupArgParser() const;
    bool checkArgument(ArgParser::parser_results const &args) const;

};


#endif /*CPPCONSOLE_H_*/
