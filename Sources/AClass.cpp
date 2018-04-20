/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 23:14:32
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 18/04/2018 23:20:58
 */


#include "AClass.h"

AClass::AClass(std::string const &className): logger(className.c_str()) {
    this->_className = className;
}

AClass::~AClass() {

}


std::string const &AClass::getClassName() const {
    return this->_className;
}
