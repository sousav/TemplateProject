/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 01:14:02
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 03:38:09
 */


#include "ACreator.h"

ACreator::ACreator(std::string const &name) {
    this->_name = name;
}

ACreator::~ACreator() {

}

std::string const &ACreator::getName() const {
    return this->_name;
}
