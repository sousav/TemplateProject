/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 23:05:12
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 18/04/2018 23:20:21
 */


#ifndef ACLASS_H_
#define ACLASS_H_

#include <string>
#include "IClass.h"
#include "Logger/Logger.h"

class AClass : public IClass {

public:
    AClass(std::string const &className);
    virtual ~AClass();

    std::string const &getClassName() const;

protected:
    Log::Logger logger;

private:
    std::string _className;

};

#endif /*ACLASS_H_*/
