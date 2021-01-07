#pragma once

#include <Core.h>
#include <View.h>

struct CommandView : View
{
  CommandView(USHORT x, USHORT y, USHORT width, USHORT height);
};

CommandView::CommandView(USHORT x, USHORT y, USHORT width, USHORT height)
  : View{ x, y, width, height }
{
  SetFrame();
}