# Solix

> **Use external libraries in Modern C++ as easily as in other modern languages.**
> Solix brings the simplicity of dependency management from languages like Python, Rust, or JavaScript into C++—finally making C++ feel modern to work with.

---

## ✨ Features

* 📦 **Modern C++ Package Management**
  Easily add external libraries using `vcpkg`, without writing CMake by hand.

* ⚡ **Faster Builds**
  Optimized build presets with Clang and Ninja ensure rapid compilation.

* 🧱 **Cross-Platform & Cross-Compiling**
  Build the same project seamlessly across Windows and Linux, and target other platforms too.

* 📁 **Professional Project Structure**
  Automatically generates clean CMake-based layouts.

* 🔄 **Repeatable Builds**
  Get consistent output across machines with unified presets.

* 🎯 **Build From Scratch? Never Again**
  Save hours by never manually writing CMake files again.

* 🧪 **Unit Testing Integration**
  Enable and run tests with ease.

* 🛠️ **Installer Generation**
  Easily package your application for distribution.

* 🧰 **Environment Setup**
  Automatically installs and configures Clang, Ninja, and CMake.

* 🧭 **LLDB Debugger Integration**
  Start debugging sessions with one command.

* 🧹 **.gitignore Generator**
  Prevents unwanted clutter from entering version control.

---

## 🔧 Installation

### Prerequisites

* Git
* CMake
* Clang (on all platforms)
* Ninja (Recommended)
* vcpkg (Handled internally by Solix)

### Building Solix

```bash
cmake --preset=default
cmake --build build/default
```

> Or use Solix itself to bootstrap:

```bash
aura build
```

---

## 🚀 Usage

```bash
solix [command] [project-name]
```

### Core Commands

| Command           | Description                                                         |
| ----------------- | ------------------------------------------------------------------- |
| `create`          | Create a new C/C++ project with all defaults                        |
| `subproject`      | Add a subproject (executable or library)                            |
| `build`           | Configure and compile using Clang + Ninja                           |
| `run`             | Run the compiled binary                                             |
| `compile`         | Compile with custom flags (e.g. Debug or Release)                   |
| `tests`           | Enable and manage unit tests                                        |
| `debug`           | Launch LLDB for debugging                                           |
| `release`         | Compile in release mode                                             |
| `add`             | Add external library using `vcpkg`. Example: `solix add fmt/11.0.2` |
| `initVCPKG`       | Create `vcpkg.json` config in project                               |
| `reload`          | Reload the vcpkg dependency cache                                   |
| `createinstaller` | Generate an installable package                                     |
| `fix`             | Diagnose and fix Solix issues                                       |
| `update`          | Update Solix to the latest version                                  |
| `setup`           | Auto install Clang, Ninja, CMake, and vcpkg                         |

---

## 📂 Example

```bash
solix create myApp
cd myApp
solix add fmt/11.0.2
solix build
solix run
```

---

## 🧠 Why Use Solix?

* Skip repetitive setup and config
* Learn modern C++ without being blocked by tooling
* Fast builds out of the box
* Cross-platform by default
* Just focus on building things

---

## 👨‍💻 Author

Made with 💻 by [Vishal Ahirwar](https://github.com/vishal-ahirwar)

---

## 📄 License

This project is licensed under the BSD 3-Clause License. See `LICENSE` for more info.
