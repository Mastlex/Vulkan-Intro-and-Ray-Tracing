@echo off

setlocal
set GLSL_COMPILER="C:\VulkanSDK\1.2.148.1\Bin\glslangValidator.exe"
set SOURCE_FOLDER="./"
set BINARIES_FOLDER="./"

:: raygen shaders
%GLSL_COMPILER% -V -S rgen %SOURCE_FOLDER%ray_gen.glsl -o %BINARIES_FOLDER%ray_gen.bin

:: closest-hit shaders
%GLSL_COMPILER% -V -S rchit %SOURCE_FOLDER%ray_chit.glsl -o %BINARIES_FOLDER%ray_chit.bin
%GLSL_COMPILER% -V -S rchit %SOURCE_FOLDER%shadow_ray_chit.glsl -o %BINARIES_FOLDER%shadow_ray_chit.bin

:: miss shaders
%GLSL_COMPILER% -V -S rmiss %SOURCE_FOLDER%ray_miss.glsl -o %BINARIES_FOLDER%ray_miss.bin
%GLSL_COMPILER% -V -S rmiss %SOURCE_FOLDER%shadow_ray_miss.glsl -o %BINARIES_FOLDER%shadow_ray_miss.bin

pause
