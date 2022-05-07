#include "../includes/newton.hpp"

void add_to_command(const char *cmd, const char *user, char *CMD)
{
    int j = 0;
    for (auto i = 0; cmd[i] != '\0'; ++i)
    {
        CMD[i] = cmd[i];
        j = i;
    };
    CMD[++j] = ' ';
    for (auto i = 0; user[i] != '\0'; ++i, ++j)
    {
        CMD[j] = user[i];
    };
};

bool c_str_compare(const char *str1, const char *str2)
{
    int i = 0;
    while (str2[i] != '\0')
    {
        if (str1[i] != str2[i])
            return false;
        ++i;
    };
    return true;
};

void initOnCreate(char *argv[])
{
    clock_t start = clock(), end = 0;

    printf("[newton] Creating directory ....\n");

    char cmd[250] = {NULL};
    add_to_command("mkdir ", argv[2], cmd);

    if (!system(cmd))
    {
        char build[100] = {0};
        char temp[250] = {0};
        add_to_command("mkdir ", argv[2], temp);
        add_to_command(temp, "/build", build);
        system(build);
        for (auto i = 0; i < 100; ++i)
            build[i] = 0;
        add_to_command("mkdir ", argv[2], temp);
        add_to_command(temp, "/src", build);
        system(build);
        add_to_command("mkdir ", argv[2], temp);
        add_to_command(temp, "/res", build);
        system(build);
        add_to_command("touch ", argv[2], temp);
        add_to_command(temp, "/CMakeLists.txt", build);
        system(build);
        printf("[newton] Directory Created Successfuly :)\n");
        printf("[newton] writting main.c and CMakeLists.txt ....\n");

        std::ofstream file;
        file.open("./src/main.cc", std::ios::out);

        if (file.is_open())
        {
            const std::string mainCode{R"(

//Auto Genrated C++ file by newton CLI
#include<iostream>
void say_hello()
{
    std::cerr<<"Hello, World\n";
};
int main(int argc,char*argv[])
{
    say_hello();
    return 0;
};

)"};
            file << mainCode;
            file.close();
        };
        file.open("CMakeLists.txt", std::ios::out);
        if (file.is_open())
        {
            const std::string cmakeCode{
                R"(
//Auto Genrated C++ file by newton CLI
cmake_minimum_required(VERSION 3.1)
)"};
            file << cmakeCode << "\n";
            file << "project(" << argv[2] << ")\n";
            file << "add_executable(${PROJECT_NAME} ./src/main.cc)\n";
            file.close();
        };
    };
    end = clock();

    printf("\n[newton]All Done :)\n[newton]Elapsed Time : %8.2f microseconds\n", difftime(end, start));
};
