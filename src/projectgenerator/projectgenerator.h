#ifndef PROJECT_GENERATOR
#define PROJECT_GENERATOR
#include <projectsetting/projectsetting.h>
#include<userinfo/userinfo.h>
#include <constants/constant.hpp>
#include<nlohmann/json.hpp>
class ProjectGenerator
{
private:
    ProjectSetting mProjectSetting;
    inline static UserInfo mUserInfo{};
    nlohmann::json mConfig;
public:
    ProjectGenerator();
    void generate();
    void setProjectSetting(const ProjectSetting &projectSetting, const Language &lang);
    static void readProjectSettings(ProjectSetting *setting);
    static void writeProjectSettings(ProjectSetting *setting);
    static void generateCMakePreset(const Language&);
    bool getFromConfig(const std::string&key,std::string&result);
    bool generateSubProject(const std::string&projectName,Language,bool isRoot=false);
private:
Language _lang{Language::CXX};

private:
    void generateProject();
    void createDir();
    void generateCppTemplateFile(const std::string&projectName,bool isRoot);
    void generateGitIgnoreFile();
    void generateVcpkgFiles();
    void generateRootCMake();
    void generateSubProjectCMake(const std::string&projectName);
    void configCMake();
public:
    static void generateLicenceFile(const UserInfo&userInfo);
};
#endif