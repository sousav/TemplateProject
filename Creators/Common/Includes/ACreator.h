/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 01:14:01
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 22/04/2018 01:09:16
 */


#ifndef ACREATOR_H_
#define ACREATOR_H_

#include "ICreator.h"

class ACreator : public ICreator {

public:
    ACreator(std::string const &name);
    ACreator(ACreator const &obj) = delete;
    ACreator &operator=(ACreator const &obj) = delete;
    virtual ~ACreator();

    std::string const &getName() const;
    bool createProject(std::string const &name, std::string const &path, int argc, char **argv);

private:
    virtual ArgParser::parser setupArgParser() const = 0;
    virtual bool checkArgument(ArgParser::parser_results const &args) const = 0;
    bool createDestination(std::string const &path) const;
    bool unzipTemplate(std::string const &path) const;

private:
    std::string _name;

protected:
    Log::Logger logger;

};

#endif /*ACREATOR_H_*/
