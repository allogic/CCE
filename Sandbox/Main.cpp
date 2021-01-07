#include <Console.h>
#include <ViewManager.h>

#include <Views/ProcessView.h>
#include <Views/CommandView.h>

INT main()
{
  Console console{};

  ViewManager viewManager{};

  viewManager.Add<ProcessView>("p", (USHORT)4, (USHORT)2, (USHORT)32, (USHORT)8);
  viewManager.Add<CommandView>("c", (USHORT)0, (USHORT)(console.Height() - 2), (USHORT)(console.Width() + 1), (USHORT)3);

  while (1)
  {
    console.Update();

    auto const cmd{ console.Command() };

    viewManager.Update();
    viewManager.Draw();

    if (cmd[0] == ':')
    {
      break;
    }
  }

  return 0;
}