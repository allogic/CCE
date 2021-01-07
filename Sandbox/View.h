#pragma once

#include <Core.h>

struct View : std::vector<CHAR_INFO>
{
  HANDLE mHdlStdOut{};
  HANDLE mHdlBuffer{};
  USHORT mX        {};
  USHORT mY        {};
  USHORT mWidth    {};
  USHORT mHeight   {};
  UINT   mSize     {};

  View(USHORT x, USHORT y, USHORT width, USHORT height);
  virtual ~View();

  virtual void SetFrame();
  virtual void SetText(USHORT x, USHORT y, std::wstring const& str);
  virtual void Update();
  virtual void Draw();
};

View::View(USHORT x, USHORT y, USHORT width, USHORT height)
  : mHdlStdOut{ GetStdHandle(STD_OUTPUT_HANDLE) }
  , mX{ x }
  , mY{ y }
  , mWidth{ width }
  , mHeight{ height }
  , mSize{ (UINT)width * height }
{
  this->resize(mSize);
  for (UINT i{}; i < (UINT)mSize; i++)
    (*this)[i].Char.UnicodeChar = L' ';
}

View::~View()
{
  
}

void View::SetFrame()
{
  for (USHORT i{}; i < mWidth; i++)
    for (USHORT j{}; j < mHeight; j++)
    {
      UINT idx{ (UINT)i + j * mWidth };

      (*this)[idx].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

      if (i == 0 || i == mWidth - 1)           (*this)[idx].Char.UnicodeChar = L'│';
      if (j == 0 || j == mHeight - 1)          (*this)[idx].Char.UnicodeChar = L'─';
      if (i == 0 && j == 0)                    (*this)[idx].Char.UnicodeChar = L'┌';
      if (i == 0 && j == mHeight - 1)          (*this)[idx].Char.UnicodeChar = L'└';
      if (i == mWidth - 1 && j == 0)           (*this)[idx].Char.UnicodeChar = L'┐';
      if (i == mWidth - 1 && j == mHeight - 1) (*this)[idx].Char.UnicodeChar = L'┘';
    }
}

void View::SetText(USHORT x, USHORT y, std::wstring const& str)
{
  USHORT size = std::min<USHORT>(mWidth, (USHORT)str.size());

  for (USHORT i{}; i < size; i++)
  {
    UINT idx{ (UINT)(x + i) + y * mWidth };

    (*this)[idx].Attributes       = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    (*this)[idx].Char.UnicodeChar = str[i];
  }
}

void View::Update()
{

}

void View::Draw()
{
  SMALL_RECT rect{ (SHORT)mX, (SHORT)mY, (SHORT)(mX + mWidth), (SHORT)(mY + mHeight) };

  WriteConsoleOutput(
    mHdlStdOut,
    this->data(),
    COORD{ (SHORT)mWidth, (SHORT)mHeight },
    COORD{ 0, 0 },
    &rect
  );
}