/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 01:14:02
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 17:19:13
 */


#include "ACreator.h"

ACreator::ACreator(std::string const &name): logger(name.c_str()) {
    Log::Manager::setDefaultLevel(Log::Log::eDebug);
    Log::Config::Vector configList;
    Log::Config::addOutput(configList, "OutputConsole");
    Log::Manager::configure(configList);
    this->_name = name;
}

ACreator::~ACreator() {

}

std::string const &ACreator::getName() const {
    return this->_name;
}

bool ACreator::createProject(std::string const &name, std::string const &path, ArgParser::parser_results const &args) {
    if (!createDestination(path)) {
        return false;
    }
    if (!unzipTemplate(path)) {
        return false;
    }
    return true;
}

bool ACreator::createDestination(std::string const &rawPath) {
    boost::filesystem::path path(rawPath);

    if (boost::filesystem::exists(path)) {
        if (boost::filesystem::is_directory(path)) {
            if (!boost::filesystem::is_empty(path)) {
                this->logger.error() << "Directory " << path << " is not an empty directory.";
                return false;
            }
            this->logger.info() << "Directory " << path << " already exist and is empty.";
        } else {
            this->logger.error() << "Path " << path << " already exists.";
            return false;
        }
    } else {
        this->logger.info() << "Creating project directory...";
        if (!boost::filesystem::create_directory(path)) {
            this->logger.info() << "Creating project directory...";
            this->logger.error() << "Could not create folder with the following path: " << path;
            return false;
        }
    }

    return true;
}

bool ACreator::unzipTemplate(std::string const &rawPath) {
    this->logger.info() << "Restoring project archive...";
    Resource text = LOAD_RESOURCE(Template_gz);
    std::ofstream outfile ("Template.gz");
    outfile << std::string(text.data(), text.size()) << std::endl;
    outfile.close();

    this->logger.info() << "Decompressing project archive...";
    const int unzipResult = std::system(std::string("tar -xf Template.gz -C " + rawPath).c_str());
    if (unzipResult) {
        this->logger.error() << "Failed to decompress the project template.";
        return false;
    }

    this->logger.info() << "Removing project archive...";
    boost::filesystem::path path("Template.gz");
    if (!boost::filesystem::remove(path)) {
        this->logger.warning() << "Failed to remove the project archive, you may want to remove it manualy.";
    }

    return true;
}
