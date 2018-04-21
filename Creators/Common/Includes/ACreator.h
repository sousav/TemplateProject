/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 01:14:01
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 16:40:47
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
    bool createProject(std::string const &name, std::string const &path, ArgParser::parser_results const &args);

private:
    bool createDestination(std::string const &path);
    bool unzipTemplate(std::string const &path);

private:
    std::string _name;

protected:
    Log::Logger logger;

};

#endif /*ACREATOR_H_*/
