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
  > **NOTE: CMake config currently works only from my [cmake rewrite](https://github.com/godotengine/godot-cpp/pull/1355) of godot-cpp**
  >
  > **If you want to use cmake for Godot before 4.4 dev branch, do 'For custom builds' step below**

- Checkout your version of godot
	- For stable releases: checkout one of [tags](https://github.com/godotengine/godot-cpp/tags)
	```bash
	cd external/godot-cpp/
	git checkout <tag>
	```
	**OR**
	- For custom builds (from [guide](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html#building-the-c-bindings)):
	```bash
	# Generate custom bindings
	./your_godot_executable --dump-extension-api
 	```
	- And then:

  		- Move file to default path
		```bash
 		mv extension_api.json gdextension/extension_api.json
		```
 
 	 	**OR**
  
 		- Specify custom path to file to either scons or cmake
 		```bash
  		scons custom_api_file=path/to/extension_api.json
 		cmake -DGODOT_CUSTOM_API_FILE=path/to/extension_api.json```
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
- Open `project` directory from Godot
- Run scene

  You should see line of text in the center of screen and message in console

# Customizing
- Project name
  - [Regenerate](https://github.com/IvanInventor/godot-cppscript/tree/master#generate-files) cpspcript files with name of your project
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
    HEADER_NAME
    -    cppscript.h
    +    your_name.h
    ```
