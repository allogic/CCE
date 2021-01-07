#pragma once

#include <Core.h>
#include <View.h>

template<typename ... Types>
struct Table : std::vector<std::tuple<Types ...>>
{
  constexpr static DWORD sNumElements{ sizeof ... (Types) };

  View*        mpView {};
  std::wstring mHeader{};
  std::wstring mFormat{};

  Table(View* pView, std::wstring const& header, std::wstring const& format);
  virtual ~Table();

  template<typename ... Args>
  void Add(Args&& ... args);

  void Remove();
  void Clear();
  void Draw();
};

template<typename ... Types>
Table<Types ...>::Table(View* pView, std::wstring const& header, std::wstring const& format)
  : mpView{ pView }
  , mHeader{ header }
  , mFormat{ format }
{

}

template<typename ... Types>
Table<Types ...>::~Table()
{

}

template<typename ... Types>
template<typename ... Args>
void Table<Types ...>::Add(Args&& ... args)
{
  this->emplace_back(std::forward<Args>(args) ...);
}

template<typename ... Types>
void Table<Types ...>::Remove()
{

}

template<typename ... Types>
void Table<Types ...>::Clear()
{

}

template<typename ... Types>
void Table<Types ...>::Draw()
{
  USHORT rows{ std::min<USHORT>(mpView->mHeight - 2, (USHORT)this->size()) };

  mpView->SetText(0, 0, mHeader);

  std::wstring tmpString{};

  for (USHORT i{ 2 }; i < rows; i++)
  {
    std::wstringstream oss{};

    StaticFor<sNumElements>([&](auto elementIdx)
      {
        oss << std::get<elementIdx>((*this)[i]) << L' ';
      });

    std::vector<std::wstring> strings{};

    while (std::getline(oss, tmpString, L' '))
    {
      strings.emplace_back(tmpString);
    }

    for (auto const& string : strings)
    {
      tmpString.clear();
      tmpString.resize(mpView->mWidth);

      std::swprintf(tmpString.data(), mpView->mWidth, L"test %6s", string);
    }


    mpView->SetText(0, i, oss.str());
  }

  delete[] pBuffer;
}