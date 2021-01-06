#pragma once

#include <windows.h>

template<SHORT Width, SHORT Height>
struct View
{
  HANDLE     hBuffer{};
  CHAR_INFO  ciBuffer[Width * Height]{};
  SMALL_RECT writeRect{};

  View(HANDLE hStdOut, SHORT x, SHORT y);
  virtual ~View();

  void SetFrame();

  void Blit();
};

template<SHORT Width, SHORT Height>
View<Width, Height>::View(HANDLE hStdOut, SHORT x, SHORT y)
{
  hBuffer = CreateConsoleScreenBuffer(
    GENERIC_READ,
    FILE_SHARE_READ,
    nullptr,
    CONSOLE_TEXTMODE_BUFFER,
    nullptr
  );
  writeRect = { x, y, x + Width, y + Height };
}
template<SHORT Width, SHORT Height>
View<Width, Height>::~View()
{
  
}

template<SHORT Width, SHORT Height>
void View<Width, Height>::SetFrame()
{
  for (SHORT i{}; i < Width; i++)
    for (SHORT j{}; j < Height; j++)
    {
      ciBuffer[i + j * Width].Char = { .AsciiChar{ '.' } };
    }
}

template<SHORT Width, SHORT Height>
void View<Width, Height>::Blit()
{
  WriteConsoleOutput(
    hBuffer,
    ciBuffer,
    COORD{ Width, Height },
    COORD{ 0, 0 },
    &writeRect
  );
}