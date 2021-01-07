#pragma once

#include <Core.h>
#include <View.h>
#include <List.h>
#include <Table.h>

#include <tlhelp32.h>

struct ProcessView : View
{
  struct ProcessTable : Table<DWORD, DWORD, DWORD, DWORD, std::wstring const>
  {
    ProcessTable(ProcessView* pView) : Table{ pView, L"Ppid Pid Handles Threads Name", L"%d %d %d %d %s" } {}
  } mProcessTable{ this };

  HANDLE mHdlProcessSnap{};

  ProcessView(USHORT x, USHORT y, USHORT width, USHORT height);

  void Update() override;
  void Draw() override;
};

ProcessView::ProcessView(USHORT x, USHORT y, USHORT width, USHORT height)
  : View{ x, y, width, height }
{
  SetFrame();
  Update();
}

void ProcessView::Update()
{
  mProcessTable.Clear();

  PROCESSENTRY32 pe32{};
  pe32.dwSize = sizeof(PROCESSENTRY32);

  mHdlProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

  Process32First(mHdlProcessSnap, &pe32);

  while (Process32Next(mHdlProcessSnap, &pe32))
  {
    mProcessTable.Add(
      pe32.th32ParentProcessID,
      pe32.th32ProcessID,
      pe32.cntUsage,
      pe32.cntThreads,
      pe32.szExeFile
    );
  }

  CloseHandle(mHdlProcessSnap);

  View::Update();
}

void ProcessView::Draw()
{
  mProcessTable.Draw();

  View::Draw();
}