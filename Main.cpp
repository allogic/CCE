#include <windows.h>

#include <cstdio>
#include <cassert>
#include <regex>

#include "View.h"

HANDLE hStdIn{};
HANDLE hStdOut{};

CONSOLE_SCREEN_BUFFER_INFO csbInfo{};

WORD attrOld{};

DWORD cWritten{};
DWORD cRead{};

CHAR cBuffer[1024]{};

DWORD fdModeDraw{};
DWORD fdModeRead{};
DWORD fdModeOld{};

struct ProcessView : View<32, 16>
{
  ProcessView(HANDLE hStdOut) : View(hStdOut, 8, 4) {}
};

void SetDrawMode()
{
  SetConsoleMode(hStdIn, fdModeDraw);
}
void SetReadMode()
{
  SetConsoleMode(hStdIn, fdModeRead);
}

INT main()
{
  hStdIn = GetStdHandle(STD_INPUT_HANDLE);
  hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

  GetConsoleScreenBufferInfo(hStdOut, &csbInfo);

  attrOld = csbInfo.wAttributes;

  GetConsoleMode(hStdIn, &fdModeOld);

  fdModeDraw = fdModeOld & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
  fdModeRead = fdModeOld;

  SetDrawMode();

  ProcessView processView{ hStdOut };
  processView.SetFrame();

  while (1)
  {
    //WriteFile(hStdOut, "", 0, &cWritten, nulptr);

    processView.Blit();

    ReadFile(hStdIn, cBuffer, 1023, &cRead, nullptr);

    if (cBuffer[0] == ':') break;
  }

  SetConsoleMode(hStdIn, fdModeOld);

  SetConsoleTextAttribute(hStdOut, attrOld);

  return 0;
}