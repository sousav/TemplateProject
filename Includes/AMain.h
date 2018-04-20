/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 19:22:41
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 18/04/2018 23:33:32
 */


#ifndef AMAIN_H_
#define AMAIN_H_

#include "IMain.h"
#include "AClass.h"

class AMain: public IMain, public AClass {

public:
    AMain(int argc, char *argv[], std::string const &className);
    virtual ~AMain();

    bool Run();
    virtual bool Run(ArgParser::parser_results const &args) = 0;

protected:
    virtual ArgParser::parser SetupArgParser() const = 0;

private:
    int _argc;
    char **_argv;

};

#endif /*AMAIN_H_*/
