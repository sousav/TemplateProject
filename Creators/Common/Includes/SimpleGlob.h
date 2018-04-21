/**
 * @Author: Victor Sousa <vicostudio>
 * @Date:   21/04/2018 03:29:55
 * @Email:  victor.sousa@epitech.eu
 * @Last modified by:   vicostudio
 * @Last modified time: 21/04/2018 03:30:03
 */


#ifndef SIMPLEGLOB_H_
#define SIMPLEGLOB_H_

#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>

class SimpleGlob {

public:
    static bool doesMatch(std::string const &text, std::string wildcardPattern, bool caseSensitive = true) {
        // Escape all regex special chars
        _escapeRegex(wildcardPattern);

        // Convert chars '*?' back to their regex equivalents
        boost::replace_all(wildcardPattern, "\\?", ".");
        boost::replace_all(wildcardPattern, "\\*", ".*");

        boost::regex pattern(wildcardPattern, caseSensitive ? boost::regex::normal : boost::regex::icase);

        return regex_match(text, pattern);
    }

private:
    SimpleGlob();
    virtual ~SimpleGlob ();

    static void _escapeRegex(std::string &regex) {
        boost::replace_all(regex, "\\", "\\\\");
        boost::replace_all(regex, "^", "\\^");
        boost::replace_all(regex, ".", "\\.");
        boost::replace_all(regex, "$", "\\$");
        boost::replace_all(regex, "|", "\\|");
        boost::replace_all(regex, "(", "\\(");
        boost::replace_all(regex, ")", "\\)");
        boost::replace_all(regex, "[", "\\[");
        boost::replace_all(regex, "]", "\\]");
        boost::replace_all(regex, "*", "\\*");
        boost::replace_all(regex, "+", "\\+");
        boost::replace_all(regex, "?", "\\?");
        boost::replace_all(regex, "/", "\\/");
    }

};

#endif /*SIMPLEGLOB_H_*/
