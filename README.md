
# Welcome to [TemplateProject](https://sousav.github.io/TemplateProject/)!
## The simple multi-language project creator wizard

TemplateProject is a C++ executable designed to load any project creator as a dynamic library.

# How to build

Follow these step in order to build the TemplateProject executable and a first project creator library.
```shell
git clone https://github.com/sousav/TemplateProject.git
cd TemplateProject
mkdir build && cd build
cmake .. && make TemplateProject CppConsole
./TemplateProject -h
```
It should output:
```shell
Usage:
    -h, --help
        Shows this help message.

    -n, --name
        [requiered] Specify the project name.

    -t, --type
        [requiered] Specify the project type.

    -p, --path
                    Specify the path where the project must be created.
	default: "./name"

    -l, --list
                    List all project type possibilities.
```

# How to install

After running
```shell
make install
```
you should be able to run
```shell
TemplateProject -h
```

<br>All installed files can be checked with
```
ls -LR /usr/local/bin/TemplateProject*
````
which should ouput the following
```shell
/usr/local/bin/TemplateProject

/usr/local/bin/TemplateProjectCreator:
Creators        TemplateProject

/usr/local/bin/TemplateProjectCreator/Creators:
libCppConsole.so
```


# How to use
## required
You can see that there is two required parameters:
```shell
--name=YourProjectName --type=TheCreatorNeeded
```

<br>You can get the list of all loaded project creator with
```shell
TemplateProject --list
```
It should output
```shell
2018-04-22 19:01:32.559  MainClass    INFO Possible project type:
2018-04-22 19:01:32.559  MainClass    INFO CppConsole
```
This means the TemplateProject executable found the library CppConsole.
Therefore you can use
```shell
--type=CppConole
```
in order to create a C++ console project.

## option
There is also a third parameter
```shell
--path=Your/Project/Path
```
<br>If not specified, your project will be create using the following path
```shell
/your/pwd/YourProjectName
```

<br>**WARNING:
If using an existing directory, it must be empty.
Otherwise, it will be created.**
<br>

## Project creation
In order to create a C++ console project, named TestProject
```shell
TemplateProject --name TestProject --type CppConsole
```

<br>In order to create a C++ console project, named TestProject in your working directory
```shell
TemplateProject --name TestProject --type CppConsole --path=.
```
<br>


# Create your ProjectCreator

[ProjectCreator readme](Creators)
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
