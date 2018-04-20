/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 14:15:33
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 19/04/2018 00:08:24
 */


#ifndef MAINCLASS_H_
#define MAINCLASS_H_

#include <boost/filesystem.hpp>
#include "AMain.h"

class MainClass : public AMain {

public:
    MainClass(int argc, char *argv[]);
    virtual ~MainClass();

protected:
    virtual ArgParser::parser SetupArgParser() const;
    virtual bool Run(ArgParser::parser_results const &args);

private:
    bool checkArgument(ArgParser::parser_results const &args) const;
    void registerCreators();

private:
    std::map<std::string, std::function<bool(std::string const &, std::string const&)>> _creators;

};


#endif /*MAINCLASS_H_*/
