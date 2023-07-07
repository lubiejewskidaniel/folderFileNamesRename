#include <iostream>
#include <windows.h>
#include <string>
#include <algorithm>

int main() {
    const char* folderPath = "C:\\xxx\\"; // Specify the folder path here

    // Find the first file in the folder
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA((std::string(folderPath) + "*").c_str(), &findData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                // Construct the new file name by reversing the letters
                std::string originalName = findData.cFileName;

                // Get the file extension
                std::string fileExtension = originalName.substr(originalName.find_last_of(".") + 1);
                std::string fileNameWithoutExtension = originalName.substr(0, originalName.find_last_of("."));

                // Reverse the file name
                std::reverse(fileNameWithoutExtension.begin(), fileNameWithoutExtension.end());

                std::string newName = fileNameWithoutExtension + "." + fileExtension;

                // Rename the file
                std::string originalPath = std::string(folderPath) + originalName;
                std::string newPath = std::string(folderPath) + newName;
                if (MoveFileA(originalPath.c_str(), newPath.c_str())) {
                    std::cout << "File renamed: " << originalName << " -> " << newName << std::endl;
                }
                else {
                    std::cerr << "Failed to rename file: " << originalName << std::endl;
                }
            }
        } while (FindNextFileA(hFind, &findData));

        FindClose(hFind);
    }
    else {
        std::cerr << "Failed to open folder: " << folderPath << std::endl;
    }

    return 0;
}
