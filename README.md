# 🧟 ZomboidTools

> Tiny utilities that make managing **Project Zomboid** mods less painful.

![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?style=flat&logo=cplusplus&logoColor=white)
![Python](https://img.shields.io/badge/Python-3-3776AB?style=flat&logo=python&logoColor=white)
![Batch](https://img.shields.io/badge/Batch-script-4D4D4D?style=flat)
![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?style=flat)
![License](https://img.shields.io/badge/License-MIT-green?style=flat)

## 🧰 What's inside

| Tool | Language | Purpose |
|------|----------|---------|
| `deleteDisabledMods.cpp` (+ prebuilt `.exe`) | C++ | Deletes every mod folder that is **not enabled** in your mod list |
| `workshopCopier.bat` | Batch | Copies all Steam Workshop mods into one flat folder |
| `workshopModListGenerator.py` | Python | Interactive Workshop mod copier with per-mod logging |

## 🗑️ deleteDisabledMods

Frees disk space by removing disabled mods:

1. Reads the enabled-mod whitelist from `%USERPROFILE%\Zomboid\mods\default.txt` (`mod = ...` entries).
2. Scans every folder in `%USERPROFILE%\Zomboid\mods\`, reading each `mod.info` `id=`.
3. **Permanently deletes** every mod folder whose id is not in the whitelist.

Run the bundled `deleteDisabledMods.exe` (it asks you to type `yes` before doing anything), or build it yourself with any C++17 compiler:

```sh
g++ deleteDisabledMods.cpp -o deleteDisabledMods.exe
```

> ⚠️ Deleted folders are not sent to the Recycle Bin — double-check `default.txt` first.

## 📦 workshopCopier.bat

Collects mods scattered across Steam Workshop download folders (`...\steamapps\workshop\content\108600\<id>\mods\<mod>`) into a single output directory. Just run it and answer two prompts:

```
Workshop path: D:\SteamLibrary\steamapps\workshop\content\108600
Output folder: D:\PZMods
```

A `#` is printed for every copied mod.

## 🐍 workshopModListGenerator.py

Python take on the same job — prompts for the Workshop path and an output folder, creates the output folder if needed, and copies mod subfolders over with `Copied`/`Skipped` messages for each one.

```sh
python workshopModListGenerator.py
```

## 📄 License

MIT — see [LICENSE](LICENSE).
