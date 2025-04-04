#pragma once

#include <string>
#include<projectsetting/projectsetting.h>
#include<userinfo/userinfo.h>
#include<rt/rt.h>
#include<vector>
class Aura
{
private:
    ProjectSetting mProjectSetting{};
    UserInfo mUserInfo{};
    RT mRt{"Aura"};
    std::vector<std::string>mArgs{};
public:
    void createNewProject();
    bool compile();
    void run();
    void build();
    void setup();
    void createInstaller();
    void test();
    void fixInstallation();
    void update();
    void debug();
    bool release();
    void vsCode();
    void reBuild();
    void refresh();
    void buildDeps();
    void addDeps();
    void genCMakePreset();
    void createSubProject();
private:
    bool onSetup();
    void setupVcpkg(const std::string&,bool&);
    void installTools(bool&);
    void addToPathUnix();
    void addToPathWin();
    friend void test();
    bool executeCMake(const std::string&);
public:
    Aura(const std::vector<std::string>&args={});
    ~Aura();
};
