import glob
import os
import shutil

if __name__ == '__main__':
    print('Use OS based file path separator')
    print('Example path to workshop mods: D:\\SteamLibrary\\steamapps\\workshop\\content\\108600')
    print()
    workshop_path = input('Workshop path > ')
    output_path = input('Output folder > ')
    if not os.path.isdir(output_path):
        os.mkdir(output_path)
        print('Output folder created')
    else:
        print('Output folder exists')
    mods = glob.glob(workshop_path + '/*')
    print('Total:', len(mods), 'ids')
    for mod in mods:
        mod_id = mod.split('\\')[-1]  # 1299328280
        mod_path = mod + '\\mods'  # D:\SteamLibrary\steamapps\workshop\content\108600\1299328280\mods
        mod_addons = glob.glob(mod_path + '\\*')
        for mod_addon in mod_addons:
            addon_name = mod_addon.split('\\')[-1]
            new_addon_folder = output_path + '\\' + addon_name
            print(addon_name, new_addon_folder)
            if not os.path.isdir(new_addon_folder):
                shutil.copytree(mod_addon, new_addon_folder)
                print('Copied from', mod_id, 'to', addon_name)
            else:
                print('Skipped from', mod_id, 'to', addon_name)
        break
    input('Complete')
