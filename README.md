# godot-cppscript-template
Minimalistic template project to start with GDExtension development with godot-cppscript preinstalled.

## Installation
- Install [dependencies](https://github.com/IvanInventor/godot-cppscript#dependencies)
- (Optional) use this template via GitHub
- Clone project
```bash
git clone https://github.com/IvanInventor/godot-cppscript-template --recurse-submodules godot-project
cd godot-project
```
### Prepare godot-cpp repo
  > **NOTE: CMake config currently works only from my cmake rewrite of godot-cpp**
  > You can still use it with any Godot >= 4.1 version, if you
  > - switch godot-cpp submodule to rewrite branch
  >   ```bash
  >   git submodule set-url external/godot-cpp https://github.com/IvanInventor/godot-cpp
  >   git submodule set-branch --branch cmake-rewrite external/godot-cpp
  >   git submodule update external/godot-cpp
  >   ```
  > - generate custom bindings from you binary (from [guide](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html#building-the-c-bindings)):
  >   ```bash
  >   # Generate custom bindings
  >   ./your_godot_executable --dump-extension-api
  >   mv extension_api.json external/godot-cpp/gdextension/extension_api.json
  >   ```
- Checkout your version of godot
	- For stable releases: checkout one of [tags](https://github.com/godotengine/godot-cpp/tags)
	```bash
	cd external/godot-cpp/
	git checkout <tag>
	```
	OR
	- For custom builds (from [guide](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html#building-the-c-bindings)):
	```bash
	# switch to branch corresponding to godot version
	# Godot 4.1.3 -> 4.1
	cd external/godot-cpp/
	git pull origin 4.1
	git switch 4.1
	# Generate custom bindings
	./your_godot_executable --dump-extension-api
	mv extension_api.json gdextension/extension_api.json
	```
- Build project
  - Scons
  ```bash
  scons
  ```
  - CMake
  ```bash
  cmake -Bbuild
  cmake --build build
  ```
- Open godot-project/project directory from Godot
- Run scene

  You should see line of text in the center of screen and message in console

# Customizing
- Project name
  - [Regenerate](https://github.com/IvanInventor/godot-cppscript/blob/master/README.md#generate-files) cpspcript files with name of your project
  - Remove old `project/scripts.gdextension` file
  - Modify builder scripts
    - Scons
      ```diff
      # Customize this values depending on your project
      -library_name = 'scripts'
      +library_name = '<your_name>'
      ```
    - Cmake
      ```diff
      -project(scripts LANGUAGES CXX)
      +project(your_name LANGUAGES CXX)
      ```
- Header name ([why?](https://github.com/IvanInventor/godot-cppscript/wiki/General-info#why-unique-header-name-over-cppscripth-is-preferred))
  - SCons
    ```diff
    # Name of header to be included to enable cppscript
    # (Prefer name unique to your project)
    -'header_name' : 'cppscript.h',
    +'header_name' : 'your_name.h',
    ```
  - Cmake
    ```diff
    # Name of header to be included to enable cppscript
    # (Prefer name unique to your project)
    -cppscript.h
    +your_name.h
    ```
