/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 14:15:33
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 22/04/2018 03:30:01
 */


#ifndef MAINCLASS_H_
#define MAINCLASS_H_

#include "AMain.h"

class MainClass : public AMain {

public:
    MainClass(int argc, char *argv[]);
    virtual ~MainClass();

protected:
    virtual ArgParser::parser setupArgParser() const;
    virtual bool Run(ArgParser::parser_results const &args);

private:
    bool checkArgument(ArgParser::parser_results const &args) const;

};


#endif /*MAINCLASS_H_*/
