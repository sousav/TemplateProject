/*
https://stackoverflow.com/a/34109000
*/

#include "ExecutablePath.h"
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/predef.h>
#include <boost/version.hpp>
#include <boost/tokenizer.hpp>

#if (BOOST_VERSION > BOOST_VERSION_NUMBER(1,64,0))
#  include <boost/process.hpp>
#endif

#if (BOOST_OS_CYGWIN || BOOST_OS_WINDOWS)
#  include <Windows.h>
#endif


namespace boost {
namespace detail {

std::string GetEnv(const std::string& varName)
{
  if (varName.empty()) return "";
#if (BOOST_OS_BSD || BOOST_OS_CYGWIN || BOOST_OS_LINUX || BOOST_OS_MACOS || BOOST_OS_SOLARIS)
  char* value = std::getenv(varName.c_str());
  if (!value) return "";
  return value;
#elif (BOOST_OS_WINDOWS)
  typedef std::vector<char> char_vector;
  typedef std::vector<char>::size_type size_type;
  char_vector value(8192, 0);
  size_type size = value.size();
  bool haveValue = false;
  bool shouldContinue = true;
  do
  {
    DWORD result = GetEnvironmentVariableA(varName.c_str(), &value[0], size);
    if (result == 0)
    {
      shouldContinue = false;
    }
    else if (result < size)
    {
      haveValue = true;
      shouldContinue = false;
    }
    else
    {
      size *= 2;
      value.resize(size);
    }
  } while (shouldContinue);
  std::string ret;
  if (haveValue)
  {
    ret = &value[0];
  }
  return ret;
#else
  return "";
#endif
}

bool GetDirectoryListFromDelimitedString(
  const std::string& str,
  std::vector<std::string>& dirs)
{
  typedef boost::char_separator<char> char_separator_type;
  typedef boost::tokenizer<
    boost::char_separator<char>, std::string::const_iterator,
    std::string> tokenizer_type;
  dirs.clear();
  if (str.empty())
  {
    return false;
  }
#if (BOOST_OS_WINDOWS)
  const std::string os_pathsep(";");
#else
  const std::string os_pathsep(":");
#endif
  char_separator_type pathSep(os_pathsep.c_str());
  tokenizer_type strTok(str, pathSep);
  typename tokenizer_type::iterator strIt;
  typename tokenizer_type::iterator strEndIt = strTok.end();
  for (strIt = strTok.begin(); strIt != strEndIt; ++strIt)
  {
    dirs.push_back(*strIt);
  }
  if (dirs.empty())
  {
    return false;
  }
  return true;
}

std::string search_path(const std::string& file)
{
  if (file.empty()) return "";
  std::string ret;
#if (BOOST_VERSION > BOOST_VERSION_NUMBER(1,64,0))
  {
    namespace bp = boost::process;
    boost::filesystem::path p = bp::search_path(file);
    ret = p.make_preferred().string();
  }
#endif
  if (!ret.empty()) return ret;
  // Drat! I have to do it the hard way.
  std::string pathEnvVar = GetEnv("PATH");
  if (pathEnvVar.empty()) return "";
  std::vector<std::string> pathDirs;
  bool getDirList = GetDirectoryListFromDelimitedString(pathEnvVar, pathDirs);
  if (!getDirList) return "";
  std::vector<std::string>::const_iterator it = pathDirs.cbegin();
  std::vector<std::string>::const_iterator itEnd = pathDirs.cend();
  for ( ; it != itEnd; ++it)
  {
    boost::filesystem::path p(*it);
    p /= file;
    if (boost::filesystem::exists(p) && boost::filesystem::is_regular_file(p))
    {
      return p.make_preferred().string();
    }
  }
  return "";
}

std::string executable_path_fallback(const char *argv0)
{
  if (argv0 == nullptr) return "";
  if (argv0[0] == 0) return "";
#if (BOOST_OS_WINDOWS)
  const std::string os_sep("\\");
#else
  const std::string os_sep("/");
#endif
  if (strstr(argv0, os_sep.c_str()) != nullptr)
  {
    boost::system::error_code ec;
    boost::filesystem::path p(
      boost::filesystem::canonical(
        argv0, boost::filesystem::current_path(), ec));
    if (ec.value() == boost::system::errc::success)
    {
      return p.make_preferred().string();
    }
  }
  std::string ret = search_path(argv0);
  if (!ret.empty())
  {
    return ret;
  }
  boost::system::error_code ec;
  boost::filesystem::path p(
    boost::filesystem::canonical(
      argv0, boost::filesystem::current_path(), ec));
  if (ec.value() == boost::system::errc::success)
  {
    ret = p.make_preferred().string();
  }
  return ret;
}

}
}

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/predef.h>
#include <boost/version.hpp>
#include <boost/tokenizer.hpp>

#if (BOOST_VERSION > BOOST_VERSION_NUMBER(1,64,0))
#  include <boost/process.hpp>
#endif

#if (BOOST_OS_CYGWIN || BOOST_OS_WINDOWS)
#  include <Windows.h>
#endif

namespace boost {

#if (BOOST_OS_CYGWIN || BOOST_OS_WINDOWS)

std::string executable_path(const char* argv0)
{
  typedef std::vector<char> char_vector;
  typedef std::vector<char>::size_type size_type;
  char_vector buf(1024, 0);
  size_type size = buf.size();
  bool havePath = false;
  bool shouldContinue = true;
  do
  {
    DWORD result = GetModuleFileNameA(nullptr, &buf[0], size);
    DWORD lastError = GetLastError();
    if (result == 0)
    {
      shouldContinue = false;
    }
    else if (result < size)
    {
      havePath = true;
      shouldContinue = false;
    }
    else if (
      result == size
      && (lastError == ERROR_INSUFFICIENT_BUFFER || lastError == ERROR_SUCCESS)
      )
    {
      size *= 2;
      buf.resize(size);
    }
    else
    {
      shouldContinue = false;
    }
  } while (shouldContinue);
  if (!havePath)
  {
    return detail::executable_path_fallback(argv0);
  }
  // On Microsoft Windows, there is no need to call boost::filesystem::canonical or
  // boost::filesystem::path::make_preferred. The path returned by GetModuleFileNameA
  // is the one we want.
  std::string ret = &buf[0];
  return ret;
}

#elif (BOOST_OS_MACOS)

#  include <mach-o/dyld.h>

std::string executable_path(const char* argv0)
{
  typedef std::vector<char> char_vector;
  char_vector buf(1024, 0);
  uint32_t size = static_cast<uint32_t>(buf.size());
  bool havePath = false;
  bool shouldContinue = true;
  do
  {
    int result = _NSGetExecutablePath(&buf[0], &size);
    if (result == -1)
    {
      buf.resize(size + 1);
      std::fill(std::begin(buf), std::end(buf), 0);
    }
    else
    {
      shouldContinue = false;
      if (buf.at(0) != 0)
      {
        havePath = true;
      }
    }
  } while (shouldContinue);
  if (!havePath)
  {
    return detail::executable_path_fallback(argv0);
  }
  std::string path(&buf[0], size);
  boost::system::error_code ec;
  boost::filesystem::path p(
    boost::filesystem::canonical(path, boost::filesystem::current_path(), ec));
  if (ec.value() == boost::system::errc::success)
  {
    return p.make_preferred().string();
  }
  return detail::executable_path_fallback(argv0);
}

#elif (BOOST_OS_SOLARIS)

#  include <stdlib.h>

std::string executable_path(const char* argv0)
{
  std::string ret = getexecname();
  if (ret.empty())
  {
    return detail::executable_path_fallback(argv0);
  }
  boost::filesystem::path p(ret);
  if (!p.has_root_directory())
  {
    boost::system::error_code ec;
    p = boost::filesystem::canonical(
      p, boost::filesystem::current_path(), ec);
    if (ec.value() != boost::system::errc::success)
    {
      return detail::executable_path_fallback(argv0);
    }
    ret = p.make_preferred().string();
  }
  return ret;
}

#elif (BOOST_OS_BSD)

#  include <sys/sysctl.h>

std::string executable_path(const char* argv0)
{
  typedef std::vector<char> char_vector;
  int mib[4]{0};
  size_t size;
  mib[0] = CTL_KERN;
  mib[1] = KERN_PROC;
  mib[2] = KERN_PROC_PATHNAME;
  mib[3] = -1;
  int result = sysctl(mib, 4, nullptr, &size, nullptr, 0);
  if (-1 == result)
  {
    return detail::executable_path_fallback(argv0);
  }
  char_vector buf(size + 1, 0);
  result = sysctl(mib, 4, &buf[0], &size, nullptr, 0);
  if (-1 == result)
  {
    return detail::executable_path_fallback(argv0);
  }
  std::string path(&buf[0], size);
  boost::system::error_code ec;
  boost::filesystem::path p(
    boost::filesystem::canonical(
      path, boost::filesystem::current_path(), ec));
  if (ec.value() == boost::system::errc::success)
  {
    return p.make_preferred().string();
  }
  return detail::executable_path_fallback(argv0);
}

#elif (BOOST_OS_LINUX)

#  include <unistd.h>

std::string executable_path(const char *argv0)
{
  typedef std::vector<char> char_vector;
  typedef std::vector<char>::size_type size_type;
  char_vector buf(1024, 0);
  size_type size = buf.size();
  bool havePath = false;
  bool shouldContinue = true;
  do
  {
    ssize_t result = readlink("/proc/self/exe", &buf[0], size);
    if (result < 0)
    {
      shouldContinue = false;
    }
    else if (static_cast<size_type>(result) < size)
    {
      havePath = true;
      shouldContinue = false;
      size = result;
    }
    else
    {
      size *= 2;
      buf.resize(size);
      std::fill(std::begin(buf), std::end(buf), 0);
    }
  } while (shouldContinue);
  if (!havePath)
  {
    return detail::executable_path_fallback(argv0);
  }
  std::string path(&buf[0], size);
  boost::system::error_code ec;
  boost::filesystem::path p(
    boost::filesystem::canonical(
      path, boost::filesystem::current_path(), ec));
  if (ec.value() == boost::system::errc::success)
  {
    return p.make_preferred().string();
  }
  return detail::executable_path_fallback(argv0);
}

#else

std::string executable_path(const char *argv0)
{
  return detail::executable_path_fallback(argv0);
}

#endif

}
