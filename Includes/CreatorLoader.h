/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 03:27:16
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 03:57:02
 */


#ifndef CREATORLOADER_HPP_
#define CREATORLOADER_HPP_

#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/algorithm/string.hpp>
#include "SimpleGlob.h"
#include "ICreator.h"
#include "AClass.h"

typedef ICreator *(*creator_lib)();

class CreatorLoader: public AClass {

public:
    CreatorLoader(std::string const &path = "undefined", std::string const &extension = ".so");
    CreatorLoader(CreatorLoader const &obj);
    CreatorLoader &operator=(CreatorLoader const &obj);
    virtual ~CreatorLoader();

    CreatorLoader &withPath(std::string const &path);
    CreatorLoader &withExtension(std::string const &extension);
    CreatorLoader &run();
    std::map<std::string, std::shared_ptr<ICreator>> const &getCreators() const;

private:
    std::string _path;
    std::string _extension;
    std::map<std::string, std::shared_ptr<ICreator>> _creators;

};

#endif /*CREATORLOADER_HPP_*/
