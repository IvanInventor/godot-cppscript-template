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
  scons api_version=4.7
  ```
  - CMake
  ```bash
  cmake -Bbuild -DGODOTCPP_API_VERSION=4.7
  cmake --build build
  ```
- Open `project` directory from Godot
- Run scene

  You should see line of text in the center of screen and message in console

# Customizing
- Project name
  - Rename with oneliner script (cppscript_example_name -> your_name)
    - Bash (non-Windows)
```bash
NEWNAME="your_name"; mv "project/cppscript_example_name.gdextension" "project/$NEWNAME.gdextension" && find project -type f -exec sed -i "s/cppscript_example_name/$NEWNAME/g" {} + && sed -i "s/cppscript_example_name/$NEWNAME/g" CMakeLists.txt SConstruct
```
    - PowerShell (Windows)
```powershell
$NEWNAME="your_name"; Move-Item "project/cppscript_example_name.gdextension" "project/$NEWNAME.gdextension"; Get-ChildItem project -File -Recurse | ForEach-Object { (Get-Content $_.FullName -Raw) -replace 'cppscript_example_name',[regex]::Escape($NEWNAME) | Set-Content $_.FullName }; Get-ChildItem CMakeLists.txt,SConstruct | ForEach-Object { (Get-Content $_.FullName -Raw) -replace 'cppscript_example_name',[regex]::Escape($NEWNAME) | Set-Content $_.FullName }
```
  OR
  - Manually:
    - Rename project/cppscript_example_name.gdextension -> project/your_name.gdextension
    - Replace all occurences of `cppscript_example_name` in `src/`,`CMakeLists.txt`,`SConstruct`
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
