/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 03:23:05
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 03:58:57
 */


#include "CreatorLoader.h"

CreatorLoader::CreatorLoader(std::string const &path, std::string const &extension): AClass("CreatorLoader") {
    this->_path = path;
    this->_extension = extension;
}

CreatorLoader::CreatorLoader(CreatorLoader const &obj): AClass("CreatorLoader") {
    this->_path = obj._path;
    this->_extension = obj._extension;
    this->_creators = obj._creators;
}

CreatorLoader &CreatorLoader::operator=(CreatorLoader const &obj) {
    this->_path = obj._path;
    this->_extension = obj._extension;
    this->_creators = obj._creators;
    return *this;
}


CreatorLoader::~CreatorLoader() {

}

CreatorLoader &CreatorLoader::withPath(std::string const &path) {
    this->_path = path;
    return *this;
}

CreatorLoader &CreatorLoader::withExtension(std::string const &extension) {
    this->_extension = extension;
    return *this;
}

CreatorLoader &CreatorLoader::run() {
    boost::filesystem::path p(this->_path);
    if(!boost::filesystem::is_directory(p)) {
        throw std::logic_error("Could not open Folder \"" + this->_path + "\"");
        return *this;
    }
    for(auto const &entry : boost::make_iterator_range(boost::filesystem::directory_iterator(p), {})) {
        if (SimpleGlob::doesMatch(entry.path().generic_string(), this->_extension)) {
            try {
                void *fileHandle = dlopen(entry.path().generic_string().c_str(), RTLD_NOW);
                if (fileHandle == NULL) {
                    throw std::logic_error("DlOpen error on file " + entry.path().generic_string() + ":\n" + std::string(dlerror()));
                }

                creator_lib creator = (creator_lib)dlsym(fileHandle, "Create");
                if (creator == NULL) {
                    throw std::logic_error("Failed to resolve ExternC symbol \"Create\" on file " + entry.path().generic_string());
                }

                ICreator *iCreator = creator();
                if (iCreator == NULL) {
                    throw std::logic_error("Failed to create creator on file " + entry.path().generic_string());
                }

                this->_creators[iCreator->getName()] = std::shared_ptr<ICreator>(iCreator);
                this->logger.info() << "Loaded Creator: " << entry.path().filename().generic_string();
            } catch (std::exception const & e) {
                this->logger.error() << e.what();
            };
        }
    }
    return *this;
}

std::map<std::string, std::shared_ptr<ICreator>> const &CreatorLoader::getCreators() const {
    return this->_creators;
}
