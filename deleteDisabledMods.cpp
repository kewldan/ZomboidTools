#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <Windows.h>
#include <fileapi.h>
#include <vector>
#include <filesystem>

using namespace std;

int main()
{
    char *userProfile = getenv("USERPROFILE");
    char *base_path = new char[256];
    strcpy(base_path, userProfile);
    strcat(base_path, "\\Zomboid\\mods\\default.txt");

    ifstream file(base_path);
    string line;
    vector<char *> whitelist;

    while (getline(file, line))
    {
        size_t d = line.find("mod = ");
        if (d != -1)
        {
            char *mod_name = new char[128];
            strcpy(mod_name, line.c_str() + strlen("mod = ") + d);
            mod_name[strlen(mod_name) - 1] = 0;
            whitelist.push_back(mod_name);
        }
    }

    base_path[strlen(base_path) - strlen("default.txt")] = 0;
    strcat(base_path, "*");

    WIN32_FIND_DATA findData;
    HANDLE hFind;
    hFind = FindFirstFile(base_path, &findData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        cerr << "Error searching directory" << endl;
        return 1;
    }

    base_path[strlen(base_path) - 1] = 0;

    cout << "Enabled mods: " << endl;
    for (char *white_id : whitelist)
    {
        cout << white_id << ", ";
    }

    cout << "\n" << endl;

    do
    {
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if (strcmp(findData.cFileName, ".") != 0 && strcmp(findData.cFileName, ".."))
            {
                static char *buffer = new char[256];
                strcpy(buffer, base_path);
                strcat(buffer, findData.cFileName);
                strcat(buffer, "\\mod.info");

                file = ifstream(buffer);

                while (getline(file, line))
                {
                    if (line.find("id=") == 0)
                    {
                        const char *id = line.c_str() + strlen("id=");
                        bool found = false;
                        for (char *white_id : whitelist)
                        {
                            if (strcmp(white_id, id) == 0)
                            {
                                found = true;
                                break;
                            }
                        }

                        if (!found)
                        {
                            file.close();
                            buffer[strlen(buffer) - strlen("mod.info")] = 0;
                            cout << buffer << endl;
                            filesystem::remove_all(buffer);
                        }
                    }
                }

                if(file.is_open()){
                    file.close();
                }
            }
        }
    } while (FindNextFile(hFind, &findData));

    FindClose(hFind);

    return 0;
}