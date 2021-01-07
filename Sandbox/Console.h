#pragma once

#include <Core.h>

struct Console
{
  HANDLE                     mHdlStdIn  {};
  HANDLE                     mHdlStdOut {};

  CONSOLE_SCREEN_BUFFER_INFO mCsbInfo   {};
  CONSOLE_CURSOR_INFO        mCcInfo    {};

  WORD                       mAttrOld   {};

  DWORD                      mChWritten {};
  DWORD                      mChRead    {};

  std::array<CHAR, 1024>     mChBuffer  {};

  DWORD                      mFdModeDraw{};
  DWORD                      mFdModeRead{};
  DWORD                      mFdModeOld {};

  Console();
  virtual ~Console();

  USHORT Width() const;
  USHORT Height() const;

  std::string const Command() const;

  void SetDrawMode() const;
  void SetReadMode() const;

  void Update();
};

Console::Console()
  : mHdlStdIn{ GetStdHandle(STD_INPUT_HANDLE) }
  , mHdlStdOut{ GetStdHandle(STD_OUTPUT_HANDLE) }
{
  GetConsoleScreenBufferInfo(mHdlStdOut, &mCsbInfo);
  mAttrOld = mCsbInfo.wAttributes;

  GetConsoleCursorInfo(mHdlStdOut, &mCcInfo);
  mCcInfo.bVisible = 0;

  SetConsoleCursorInfo(mHdlStdOut, &mCcInfo);

  GetConsoleMode(mHdlStdIn, &mFdModeOld);
  mFdModeDraw = mFdModeOld & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
  mFdModeRead = mFdModeOld;

  SetDrawMode();
}

Console::~Console()
{
  SetConsoleMode(mHdlStdIn, mFdModeOld);

  SetConsoleTextAttribute(mHdlStdOut, mAttrOld);
}

USHORT Console::Width() const
{
  return (USHORT)mCsbInfo.srWindow.Bottom;
}

USHORT Console::Height() const
{
  return (USHORT)mCsbInfo.srWindow.Right;
}

std::string const Console::Command() const
{
  return { mChBuffer.begin(), mChBuffer.begin() + mChRead };
}

void Console::SetDrawMode() const
{
  SetConsoleMode(mHdlStdIn, mFdModeDraw);
}

void Console::SetReadMode() const
{
  SetConsoleMode(mHdlStdIn, mFdModeRead);
}

void Console::Update()
{
  GetConsoleScreenBufferInfo(mHdlStdOut, &mCsbInfo);

  //WriteFile(mHStdOut, "", 0, &mChWritten, nullptr);
  ReadFile(mHdlStdIn, mChBuffer.data(), 1023, &mChRead, nullptr);
}