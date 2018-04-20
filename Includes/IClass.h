/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   18/04/2018 23:04:44
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 18/04/2018 23:16:09
 */


#ifndef ICLASS_H_
#define ICLASS_H_

class IClass {

public:
    virtual ~IClass() {

    };

    virtual std::string const &getClassName() const = 0;

};

#endif /*ICLASS_H_*/
