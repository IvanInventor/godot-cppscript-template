**[Main project](https://github.com/IvanInventor/godot-cppscript) | [Documentation](https://github.com/IvanInventor/godot-cppscript/wiki) | [Usage example](#usage-example)**

# godot-cppscript-template
Minimalistic template project to start with GDExtension development with godot-cppscript preinstalled.

## Installation
- Install [dependencies](https://github.com/IvanInventor/godot-cppscript#dependencies)
- (Optional) use this template via GitHub
- Clone project
```bash
git clone https://github.com/IvanInventor/godot-cppscript-template --recurse-submodules godot-project
cd godot-project
git submodule update --remote external/cppscript
```
### Prepare godot-cpp repo
- Latest godot-cpp beta
```bash
git submodule update --remote external/godot-cpp
```
OR
- For stable releases: checkout one of [tags](https://github.com/godotengine/godot-cpp/tags)
```bash
cd external/godot-cpp/
git checkout <tag>
```
OR
- For custom builds (from [guide](https://docs.godotengine.org/en/stable/tutorials/scripting/gdextension/gdextension_cpp_example.html#building-the-c-bindings)):
   Switch to branch corresponding to godot version

  Godot > 4.5.x -> 4.5 tag or master branch
  ```bash
  cd external/godot-cpp/
  git fetch origin 4.5
  git switch 4.5
  ```
  - Generate custom bindings
  ```bash
  ./your_godot_executable --dump-extension-api
  ```

  - Install bindings
    - Replace included one
    ```bash
    mv extension_api.json external/godot-cpp/gdextension/extension_api.json
    ```
    OR
    - Add it to git and point to it with builder parameter
      - Scons
      ```bash
      scons custom_api_file=extension_api.json ...
      ```
      - Cmake
      ```bash
      cmake -DGODOTCPP_CUSTOM_API_FILE=extension_api.json ...
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
    NEWNAME="your_name"; mv "project/cppscript_example_name.gdextension" "project/$NEWNAME.gdextension" && find src project -type f -exec sed -i "s/cppscript_example_name/$NEWNAME/g" {} + && sed -i "s/cppscript_example_name/$NEWNAME/g" CMakeLists.txt SConstruct
    ```
    - PowerShell (Windows)
    ```powershell
    $NEWNAME="your_name"; Move-Item "project/cppscript_example_name.gdextension" "project/$NEWNAME.gdextension"; Get-ChildItem project,src -File -Recurse | ForEach-Object { (Get-Content $_.FullName -Raw) -replace 'cppscript_example_name',[regex]::Escape($NEWNAME) | Set-Content $_.FullName }; Get-ChildItem CMakeLists.txt,SConstruct | ForEach-Object { (Get-Content $_.FullName -Raw) -replace 'cppscript_example_name',[regex]::Escape($NEWNAME) | Set-Content $_.FullName }
    ```
  OR
  - Manually:
    - Rename project/cppscript_example_name.gdextension -> project/your_name.gdextension
    - Replace all occurences of `cppscript_example_name` in `project/`, `src/`, `CMakeLists.txt`, `SConstruct`
- Header name ([why?](https://github.com/IvanInventor/godot-cppscript/wiki/General-info#why-unique-header-name-over-cppscripth-is-preferred))
  - SCons
```diff
--- a/SConstruct
+++ b/SConstruct
@@ -74,7 +74,7 @@ generated = create_cppscript_target(
 		{
 		# Name of header to be included to enable cppscript
 		# (Prefer name unique to your project)
-		'header_name' : 'cppscript.h',
+		'header_name' : 'your_name.h',

 		# Path to C++ header files
 		'header_dir' : SRC_DIR,
```
  - Cmake
```diff
--- a/CMakeLists.txt
+++ b/CMakeLists.txt
@@ -85,7 +85,7 @@ create_cppscript_target(
 	# Name of header to be included to enable cppscript
 	# (Prefer name unique to your project)
 	HEADER_NAME
-		cppscript.h
+		your_name.h
```
