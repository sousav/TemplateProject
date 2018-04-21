/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 01:14:01
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 03:37:56
 */


#ifndef ICREATOR
#define ICREATOR

#include <string>

class ICreator {

public:
    virtual ~ICreator() {};

    virtual std::string const &getName() const = 0;

};

#endif /*ICREATOR*/
