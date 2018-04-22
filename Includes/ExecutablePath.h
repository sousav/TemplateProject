/*
https://stackoverflow.com/a/34109000
*/
#ifndef EXECUTABLEPATH_HPP_
#define EXECUTABLEPATH_HPP_


#ifndef BOOST_EXECUTABLE_PATH_HPP_
#define BOOST_EXECUTABLE_PATH_HPP_

#pragma once

#include <string>

namespace boost {
    std::string executable_path(const char * argv0);
}

#endif // BOOST_EXECUTABLE_PATH_HPP_


#ifndef BOOST_DETAIL_EXECUTABLE_PATH_INTERNALS_HPP_
#define BOOST_DETAIL_EXECUTABLE_PATH_INTERNALS_HPP_

#pragma once

#include <string>
#include <vector>

namespace boost {
    namespace detail {
        std::string GetEnv(const std::string& varName);
        bool GetDirectoryListFromDelimitedString(const std::string& str, std::vector<std::string>& dirs);
        std::string search_path(const std::string& file);
        std::string executable_path_fallback(const char * argv0);
    }
}

#endif // BOOST_DETAIL_EXECUTABLE_PATH_INTERNALS_HPP_


#endif /*EXECUTABLEPATH_HPP_*/
