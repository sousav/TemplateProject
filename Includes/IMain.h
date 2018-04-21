/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 14:08:57
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 22:36:59
 */


#ifndef IMAIN_H_
#define IMAIN_H_

#define KNRM  std::string("\x1B[0m")
#define KRED  std::string("\x1B[31m")
#define KGRN  std::string("\x1B[32m")
#define KYEL  std::string("\x1B[33m")
#define KBLU  std::string("\x1B[34m")
#define KMAG  std::string("\x1B[35m")
#define KCYN  std::string("\x1B[36m")
#define KWHT  std::string("\x1B[37m")

#include <iostream>
#include <ArgParser/ArgParser.h>

class IMain {

public:
    virtual ~IMain() {

    };

protected:
    virtual ArgParser::parser setupArgParser() const = 0;
    virtual bool Run() = 0;
    virtual bool Run(ArgParser::parser_results const &args) = 0;

};

#endif /*IMAIN_H_*/
