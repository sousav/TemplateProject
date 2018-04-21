/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 01:14:01
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 03:38:15
 */


#ifndef ACREATOR
#define ACREATOR

#include "ICreator.h"

class ACreator : public ICreator {

public:
    ACreator(std::string const &name);
    ACreator(ACreator const &obj) = delete;
    ACreator &operator=(ACreator const &obj) = delete;
    virtual ~ACreator();

    std::string const &getName() const;

private:
    std::string _name;

};

#endif /*ACREATOR*/
