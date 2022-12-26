@echo off

echo Example path to workshop mods: D:\\SteamLibrary\\steamapps\\workshop\\content\\108600
echo.

set /p workshop=Workshop path:
set /p output_path=Output folder:

for /d %%d in ("%workshop%\*") do (
  for /d %%v in ("%%d\mods\*") do (
    xcopy "%%v" "%output_path%\%%~nxv" /e /i > nul
    echo|set /p="#"
  )
)

echo Complete
pause