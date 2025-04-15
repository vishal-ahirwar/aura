#include <projectgenerator/projectgenerator.h>
#include <log/log.h>
#include <filesystem>
#include <deps/deps.h>
#include <fstream>
#include <chrono>
#include <format>
#include <iostream>
#include <utils/utils.h>
#include "projectgenerator.h"

namespace fs = std::filesystem;
ProjectGenerator::ProjectGenerator() {

};
bool ProjectGenerator::getFromConfig(const std::string &key, std::string &result)
{
	std::vector<std::string> tokens{};
	std::istringstream ss(key);
	std::string token;
	while (std::getline(ss, token, '/'))
	{
		tokens.push_back(token);
	};
	nlohmann::json json;
	for (const auto &token : tokens)
	{
		if (json.is_null())
		{
			if (!mConfig.contains(token))
			{
				return false;
			}
			json = mConfig[token];
		}
		else
		{
			if (!json.contains(token))
			{
				return false;
			}
			json = json[token];
		}
	};
	if (json.is_string())
	{
		result = json.get<std::string>();
	}
	else
	{
		Log::log(token + " is not a string", Type::E_ERROR);
		return false;
	}
	return true;
}

bool ProjectGenerator::generateSubProject(const std::string &projectName, Language lang, bool isRoot)
{
	if (isRoot)
	{
		configCMake();
		generateRootCMake();
		std::ofstream out(mProjectSetting.getProjectName()+"/CMakePresets.json");
		if (!out.is_open())
		{
			Log::log("failed to generate CMakePresets.json", Type::E_ERROR);
			return false;
		};
		out << CMAKE_PRESETS[static_cast<int>(lang)];
		out.close();
		generateVcpkgFiles();
		generateGitIgnoreFile();
		std::ofstream file{mProjectSetting.getProjectName() + "/" + mProjectSetting.getProjectName() + "/CMakeLists.txt"};
		switch (lang)
		{
		case Language::CXX:
			file << std::format("add_executable({} src/main.cpp)# Add your Source Files here\n", projectName);
			break;
		case Language::C:
			file << std::format("add_executable({} src/main.c)# Add your Source Files here\n", projectName);
			break;
		};

		file.close();
	}
	else
	{
		fs::create_directories(projectName + "/src");
		fs::create_directories(projectName + "/include");
		generateSubProjectCMake(projectName);
	};

	generateCppTemplateFile(projectName, isRoot);

	std::vector<std::string> lines{};
	std::string line{};
	std::ifstream in{};
	isRoot ? in.open(mProjectSetting.getProjectName() + "/CMakeLists.txt") : in.open("CMakeLists.txt");
	size_t index = 0, appnedIndex = 0;
	while (std::getline(in, line))
	{
		++index;
		lines.push_back(line);
		if (line.find("@add_subproject") != std::string::npos)
			appnedIndex = index;
	};
	in.close();
	lines.insert(lines.begin() + appnedIndex, std::format("add_subdirectory({})", projectName));
	std::ofstream out;
	isRoot ? out.open(mProjectSetting.getProjectName() + "/CMakeLists.txt") : out.open("CMakeLists.txt");
	for (const auto &line : lines)
		out << line << "\n";
	out.close();
	return true;
}

void ProjectGenerator::generate()
{
	generateProject();
}

void ProjectGenerator::setProjectSetting(const ProjectSetting &projectSetting, const Language &lang)
{
	_lang = lang;
	mProjectSetting = projectSetting;
}

void ProjectGenerator::generateProject()
{
	Log::log("Creating directory..", Type::E_DISPLAY);
	std::string cmdString{};
	createDir();
	if (_lang == Language::C)
	{

		Log::log("Generating Starter Project C language", Type::E_DISPLAY);
	}
	if (_lang == Language::CXX)
	{

		Log::log("Generating Starter Project C++ language", Type::E_DISPLAY);
	}
	generateSubProject(mProjectSetting.getProjectName(), _lang, true);
	Log::log("happy Coding :)", Type::E_DISPLAY);
	writeProjectSettings(&mProjectSetting);
}

void ProjectGenerator::generateVcpkgFiles()
{
	std::ofstream out(mProjectSetting.getProjectName() + "/CMakePresets.json");
	if (!out.is_open())
	{
		Log::log("failed to generate CMakePresets.json", Type::E_ERROR);
		return;
	};
	out << CMAKE_PRESETS[static_cast<int>(_lang)];
	out.close();
}
void ProjectGenerator::generateRootCMake()
{
	std::string config{(mProjectSetting.getProjectName() + "/res/config.h.in")};
	std::ofstream cmake{mProjectSetting.getProjectName() + "/CMakeLists.txt"};
	cmake << "#Auto Generated Root CMake file by aura CLI\n";
	cmake << std::format("#Copyright(c) 2025 {}.All rights reerved.\n", mUserInfo.getUserName());
	cmake << "cmake_minimum_required(VERSION 3.6...3.31)\n";
	if (_lang == Language::CXX)
	{
		std::ofstream file;
		std::string cap("", mProjectSetting.getProjectName().length());
		std::transform(mProjectSetting.getProjectName().begin(), mProjectSetting.getProjectName().end(), cap.begin(), ::toupper);
		file.open(config, std::ios::out);
		if (file.is_open())
		{
			file << "#include<string_view>" << std::endl;
			file << "namespace Project{" << std::endl;
			file << ("\tconstexpr std::string_view VERSION_STRING=\"@" + mProjectSetting.getProjectName() + "_VERSION_MAJOR@.@" + mProjectSetting.getProjectName() + "_VERSION_MINOR@.@" + mProjectSetting.getProjectName() + "_VERSION_PATCH@\";") << std::endl;
			file << ("\tconstexpr std::string_view COMPANY_NAME =\"@COMPANY@\";") << std::endl;
			file << ("\tconstexpr std::string_view COPYRIGHT_STRING= \"@COPYRIGHT@\";") << std::endl;
			file << ("\tconstexpr std::string_view PROJECT_NAME=\"@PROJECT_NAME@\";") << std::endl;
			file << "}";
			file.close();
		};
		cmake << std::format("project({} VERSION 1.0.0 LANGUAGES CXX)\n", mProjectSetting.getProjectName());
	}
	else if (_lang == Language::C)
	{
		std::ofstream file;
		std::string cap("", mProjectSetting.getProjectName().length());
		std::transform(mProjectSetting.getProjectName().begin(), mProjectSetting.getProjectName().end(), cap.begin(), ::toupper);
		file.open(config, std::ios::out);
		if (file.is_open())
		{
			file << ("const char*const VERSION_STRING=\"@" + mProjectSetting.getProjectName() + "_VERSION_MAJOR@.@" + mProjectSetting.getProjectName() + "_VERSION_MINOR@.@" + mProjectSetting.getProjectName() + "_VERSION_PATCH@\";") << std::endl;
			file << ("const char*const COMPANY_NAME =\"@COMPANY@\";") << std::endl;
			file << ("const char*const COPYRIGHT_STRING= \"@COPYRIGHT@\";") << std::endl;
			file << ("const char*const PROJECT_NAME=\"@PROJECT_NAME@\";") << std::endl;
			file.close();
		};
		cmake << std::format("project({} VERSION 1.0.0 LANGUAGES C)\n", mProjectSetting.getProjectName());
	}
	cmake << "include(res/config.cmake)\n";
	cmake << "#@add_find_package Warning: Do not remove this line\n";
	cmake << "#@add_subproject Warning: Do not remove this line\n";
	cmake.close();
}
void ProjectGenerator::generateSubProjectCMake(const std::string &projectName)
{
	if (fs::exists(projectName + "/CMakeLists.txt"))
		return;
	std::ofstream file{projectName + "/CMakeLists.txt"};
	switch (_lang)
	{
	case Language::CXX:
		file << std::format("add_executable({} src/main.cpp)# Add your Source Files here\n", projectName);
		break;
	case Language::C:
		file << std::format("add_executable({} src/main.c)# Add your Source Files here\n", projectName);
		break;
	};

	file.close();
}
void ProjectGenerator::configCMake()
{
	std::ofstream file{mProjectSetting.getProjectName() + "/res/config.cmake"};
	constexpr std::string_view config_in{"@config_in"};
	constexpr std::string_view config_h{"@config_h"};
	constexpr std::string_view comment{"@COPYRIGHT"};
	constexpr std::string_view developer{"@DeveloperName"};
	if (file.is_open())
	{
		constexpr std::string_view _name{"@name"};
		std::string str(CONFIG_CMAKE[static_cast<int>(_lang)]);
		auto index = str.find(_name);
		if (index != std::string::npos)
		{
			str.replace(index, _name.size(), mProjectSetting.getProjectName());
		};
		index = str.find(config_h);
		if (index != std::string::npos)
			str.replace(index, config_h.length(), (mProjectSetting.getProjectName() + "config.h"));
		index = str.find(config_in);
		if (index != std::string::npos)
			str.replace(index, config_in.length(), "res/config.h.in");
		index = str.find(comment);
		if (index != std::string::npos)
			str.replace(index, comment.length(), mUserInfo.getUserName());
		index = str.find(developer);
		if (index != std::string::npos)
			str.replace(index, developer.length(), mUserInfo.getUserName());
		file << str;
		file.close();
	};
};

void ProjectGenerator::readProjectSettings(ProjectSetting *setting)
{
	if (!setting)
		return;
	if (!setting->readConfig())
	{
		Log::log("Failed to read vcpkg.json file", Type::E_ERROR);
		exit(0);
	};
};
void ProjectGenerator::writeProjectSettings(ProjectSetting *setting)
{
	if (!setting)
		return;
	setting->writeConfig(setting->getProjectName() + "/");
};

void ProjectGenerator::generateCMakePreset(const Language &lang)
{
	std::ofstream out("CMakePresets.json");

	if (!out.is_open())
	{
		Log::log("failed to generate CMakePresets.json", Type::E_ERROR);
		return;
	};
	out << CMAKE_PRESETS[static_cast<int>(lang)];
	out.close();
}
// creating folder structure for project
void ProjectGenerator::createDir()
{
	namespace fs = std::filesystem;
	fs::create_directories(mProjectSetting.getProjectName() + "/" + mProjectSetting.getProjectName() + "/src");
	fs::create_directories(mProjectSetting.getProjectName() + "/" + mProjectSetting.getProjectName() + "/include");
	fs::create_directories(mProjectSetting.getProjectName() + "/res");
};
//
void ProjectGenerator::generateCppTemplateFile(const std::string &projectName, bool isRoot)
{
	std::ofstream file;
	if (_lang == Language::CXX)
	{

		isRoot ? file.open("./" + mProjectSetting.getProjectName() + "/" + mProjectSetting.getProjectName() + "/src/main.cpp", std::ios::out) : file.open("./" + projectName + "/src/main.cpp", std::ios::out);
	}
	else if (_lang == Language::C)
	{
		isRoot ? file.open("./" + mProjectSetting.getProjectName() + "/" + mProjectSetting.getProjectName() + "/src/main.c", std::ios::out) : file.open("./" + projectName + "/src/main.c", std::ios::out);
	}
	if (file.is_open())
	{
		std::string_view header{"_HEADER_"};
		std::string_view copyright{"_COPYRIGHT_"};
		std::string_view project{"_PROJECT_"};
		std::string_view comment{"@COPYRIGHT"};

		std::string cap("", mProjectSetting.getProjectName().length());
		std::transform(mProjectSetting.getProjectName().begin(), mProjectSetting.getProjectName().end(), cap.begin(), ::toupper);

		auto index = MAIN_CODE[static_cast<int>(_lang)].find(header);
		if (index != std::string::npos)
			MAIN_CODE[static_cast<int>(_lang)].replace(index, header.length(), ("#include<" + mProjectSetting.getProjectName() + "config.h>"));

		index = MAIN_CODE[static_cast<int>(_lang)].find(copyright);
		if (index != std::string::npos)
			MAIN_CODE[static_cast<int>(_lang)].replace(index, copyright.length(), (cap + "_COPYRIGHT"));

		index = MAIN_CODE[static_cast<int>(_lang)].find(project);
		if (index != std::string::npos)
			MAIN_CODE[static_cast<int>(_lang)].replace(index, project.length(), "\"" + mProjectSetting.getProjectName() + "\"");

		index = MAIN_CODE[static_cast<int>(_lang)].find(comment);
		if (index != std::string::npos)
			MAIN_CODE[static_cast<int>(_lang)].replace(index, comment.length(), mUserInfo.getUserName());

		file << MAIN_CODE[static_cast<int>(_lang)];
		file.close();
	}
}

//
void ProjectGenerator::generateGitIgnoreFile()
{
	std::ofstream file;
	file.open("./" + mProjectSetting.getProjectName() + "/.gitignore", std::ios::out);
	if (file.is_open())
	{
		file << GITIGNORE_CODE;

		file.close();
	};
};
void ProjectGenerator::generateLicenceFile(const UserInfo &user_info)
{
	std::ofstream out;
	out.open("License.txt", std::ios_base::out);
	if (!out.is_open())
	{
		Log::log("Failed to Generate License.txt, You may need to create License.txt by "
				 "yourself :)%s",
				 Type::E_ERROR);
		return;
	};
	std::string _licence{LICENSE_TEXT};
	// TODO
	constexpr std::string_view year{"@_YEAR_"};
	constexpr std::string_view name{"@_OWNER_"};
	auto index = _licence.find(year);
	if (index != std::string::npos)
		_licence.replace(index, year.length(), std::format("{:%Y}", std::chrono::system_clock::now()));
	index = _licence.find(name);
	if (index != std::string::npos)
		_licence.replace(index, name.length(), user_info.getUserName());
	out << _licence;
	out.close();
}