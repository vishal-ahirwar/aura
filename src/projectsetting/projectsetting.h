#ifndef _PROJECT_SETTING_H
#define _PROJECT_SETTING_H
#include<string>
class ProjectSetting
{
    std::string _project_name{};
    std::string _developer_name{};
    std::string _build_date{};
    std::string _cmake_args{};
    std::string _lang{"CXX"};
public:
    const std::string& getProjectName()const;
    const std::string& getDeveloperName()const;
    const std::string& getBuildDate()const;
    const std::string& getCMakeArgs()const;
    void set(const std::string&project_name,const std::string&developer_name,const std::string&build_date,const std::string&cmake_args);
    bool readConfig();
    bool writeConfig(const std::string&path="");
};
#endif