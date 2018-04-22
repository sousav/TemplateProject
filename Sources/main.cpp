/**
 * @Author: Victor Sousa <vicostudio>
 * @Email:  victor.sousa@epitech.eu
 * @Date:   14/04/2018 18:09:05
 *
 * @Last modified by:   vicostudio
 * @Last modified time: 22/04/2018 03:11:36
 */

#include <Logger/Manager.h>
#include <Logger/Logger.h>
#include <MainClass.h>

#define PROJECT_NAME std::string("TemplateProject")

int main(int argc, char *argv[]) {
    Log::Manager::setDefaultLevel(Log::Log::eDebug);
    Log::Config::Vector configList;
    Log::Config::addOutput(configList, "OutputConsole");
    Log::Manager::configure(configList);
    Log::Logger logger("Main.cpp");
    logger.notice() << "Running " << PROJECT_NAME;
    logger.notice() << "The project creator wizard.";

    MainClass main(argc, argv);
    if (main.AMain::Run()) {
        logger.notice() << "Project creation succeded";
        return 0;
    }
    return -1;
}
