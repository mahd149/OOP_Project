// admin.cpp

#include "admin.h"
#include <cstdlib>

#ifdef _WIN32
    #include <windows.h>
#endif

void Admin::openCSV(const string& filename) {
    #ifdef _WIN32
        ShellExecute(0, "open", filename.c_str(), 0, 0, SW_SHOWNORMAL);
    #else
        string command = "xdg-open " + filename + " &";
        system(command.c_str());
    #endif
}
