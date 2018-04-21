/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 14:15:33
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 22:36:51
 */


#ifndef MAINCLASS_H_
#define MAINCLASS_H_

#include <boost/filesystem.hpp>
#include "AMain.h"
#include "ICreator.h"
#include "CreatorLoader.h"

class MainClass : public AMain {

public:
    MainClass(int argc, char *argv[]);
    virtual ~MainClass();

protected:
    virtual ArgParser::parser setupArgParser() const;
    virtual bool Run(ArgParser::parser_results const &args);

private:
    bool checkArgument(ArgParser::parser_results const &args) const;
    void registerCreators();

private:
    std::map<std::string, std::shared_ptr<ICreator>> _creators;

};


#endif /*MAINCLASS_H_*/
