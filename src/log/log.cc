#include <log/log.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include "log.h"
#include <auraConfig.h>
void Log::log(const std::string_view &msg, Type e_type)
{
    fmt::print(fmt::emphasis::faint | fmt::fg(fmt::color::blue_violet), "{}", msg);
}
void Log::about()
{
    // Title and Description
    fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::light_sky_blue),
               "About:\n");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Learning C/C++ and tired of creating files and folders and running .cpp,\n"
               "compiling manually again and again?\n"
               "Try this—it does a lot for you!\n"
               "It creates a fully structured project\n"
               "with a CMake file, a clean folder structure, a .gitignore file, and commands to\n"
               "save you time while learning C++ without needing to create\n"
               "a new project every time you want to explore a new concept in C/C++ ;)\n\n");

    // Version Info
    fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::green),
               "Aura {}.{}.{}\n",AURA_VERSION_MAJOR,AURA_VERSION_MINOR,AURA_VERSION_PATCH);
    fmt::print(fmt::fg(fmt::color::gray),
               "{}\n\n",AURA_COPYRIGHT);

    // Usage Section
    fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::light_sky_blue),
               "Usage:\n");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "aura <command> projectname\n\n");

    // Available Commands
    fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::light_sky_blue),
               "Available Commands\n\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  create         - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Create a new C/C++ project. Example: aura create projectName\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  compile        - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Compile the project. Usage: cd into project directory and run 'aura compile <additional cmake args>'\n"
               "                  Example: aura compile -DCMAKE_BUILD_TYPE=Debug\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  run            - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Run the compiled binary. Ensure you compile the project before running this command.\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  help           - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Show the help wizard.\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  build          - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Compile and run the project with a single command.\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  setup          - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Install a g++ compiler and CMake if not already installed.\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  utest          - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Enable unit testing. Example: aura create test --test\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  createinstaller- ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Create a packaged build of your application.\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  update         - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Update Aura to the latest version.\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  add            - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Add an external library using Conan package manager. Example: aura add fmt/11.0.2\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  reload         - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Reload the package list. Example: aura reload\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  rebuild        - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Remove the build directory and recompile the project.\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  initconan      - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Add a Conan file.\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  debug          - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Start the GDB debugger.\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  release        - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Compile in release mode. You can also use: aura compile -DCMAKE_BUILD_TYPE=Release\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  vscode         - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Generate VSCode C/C++ configuration files.\n");

    fmt::print(fmt::fg(fmt::color::yellow),
               "  fix            - ");
    fmt::print(fmt::fg(fmt::color::white_smoke),
               "Fix the Aura installation.\n");
}