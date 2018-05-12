
  
# [ProjectCreator](https://sousav.github.io/TemplateProject/Creators/)!

# How to create your own creator

To create a project creator you must first install TemplateProject following this [guide](https://sousav.github.io/TemplateProject/)
<br>

## 1) After installing the TemplateProject executable.
Go to the Creators directory of the TemplateProject source directory 
```shell
cd TemplateProject/Creators
```

## 2) Use TemplateProject to create a basic ProjectCreator and build it.
```shell
TemplateProject -n YourCreatorName -t ProjectCreator
cd YourCreatorName
mkdir build && cd build
cmake .. && make
```

## 3) As an example we will add a custom parameter named "version".
```
ArgParser::parser YourCreatorName::setupArgParser() const {
    return ArgParser::parser { {
        { "help", {"-h", "--help"}, "Shows this help message.\n", 0},
	{ "project_name", {"-n", "--name"}, KRED + "[requiered]" + KNRM + " Specify the project name.\n", 1},
	{ "project_type", {"-t", "--type"}, KRED + "[requiered]" + KNRM + " Specify the project type.\n", 1},
	{ "project_path", {"-p", "--path"}, "            Specify the path where the project must be created." + KYEL + "\n\tdefault: \"./name\"\n" + KNRM, 1},
	{ "list_type", {"-l", "--list"}, "            List all project type possibilities.\n", 0},
	{ "version", {"-v", "--version"}, KRED + "[requiered]" + KNRM + " Specify the project version.\n", 1}
    } };
}
```

## 6) Do your needed argument manipulation
In this example --version is required therefore you need to verify it exist.
```c++
bool YourCreatorName::checkArgument(ArgParser::parser_results const &args) const {
	
	if (!args["version"]) {
        ArgParser::fmt_ostream(std::cerr) << KRED + "\nYou must provide a project version using -v or --version\n" + KNRM << std::endl << this->setupArgParser();
        return false;
    }
	
    return true;
}
```

## 5) Add the version parameter in the keyword map.
```c++
std::unordered_map<std::string, std::string> YourCreatorName::setupProjectKeyword(ArgParser::parser_results const &args) const {
    std::unordered_map<std::string, std::string> keyword;

    keyword.insert(std::make_pair("project_name", args["project_name"].as<std::string>
    keyword.insert(std::make_pair("version", args["version"].as<std::string>()));

    return keyword;
}
```


## 6) Drop your template files in the Templates folder.
During template creation process.
Every  {{version}}  will be replaced by the version specified during the template creation.
<br>

If your Templates README.md contains:
```text
# { {project_name} }, version: { {version} }
```

Executing :
```shell
TemplateProject -n TestProject -t YourCreatorName --version=1.1
```

Will create a README.md containing the following:
```text
# TestProject, version: 1.1
```

## 7) Install your creator!

running:
```shell
make install
```

Will install your  newly created creator next to the TemplateProject Executable and running:
```shell
TemplateProject --list
```
Should now output
```shell
2018-04-22 19:01:32.559  MainClass    INFO Possible project type:
2018-04-22 19:01:32.559  MainClass    INFO CppConsole
2018-04-22 19:01:32.559  MainClass    INFO CppLibrary
2018-04-22 19:01:32.559  MainClass    INFO CppSharedLibrary
2018-04-22 19:01:32.559  MainClass    INFO ProjectCreator
2018-04-22 19:01:32.559  MainClass    INFO YourCreatorName
```
<br>

# Used library
- [argagg](https://github.com/vietjtnguyen/argagg)
	C++ command line argument/option parser.
- [LoggerCpp](https://github.com/SRombauts/LoggerCpp)
	A simple, elegant and efficient C++ logger library.
- [embed-resource](https://github.com/cyrilcode/embed-resource)
	  Embed binary files and resources.

# Contact Information

All feedback greatly appreciated.

- [GitHub](https://github.com/sousav)
- [victor.sousa@epitech.eu](mailto:victor.sousa@epitech.eu)
