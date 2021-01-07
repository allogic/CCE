#pragma once

#include <Core.h>

template<typename View, typename Record, typename Type>
struct List : std::vector<Record>
{
  struct Record : Type {};

  View* mpView{};

  List(View* pView);
  virtual ~List();

  template<typename ... Args>
  void Add(Args&& ... args);

  void Remove();
  void Clear();
  void Draw();
};

template<typename View, typename Record, typename Type>
List<View, Record, Type>::List(View* pView)
  : mpView{ pView }
{

}

template<typename View, typename Record, typename Type>
List<View, Record, Type>::~List()
{

}

template<typename View, typename Record, typename Type>
template<typename ... Args>
void List<View, Record, Type>::Add(Args&& ... args)
{
  this->emplace_back(std::forward<Args>(args) ...);
}

template<typename View, typename Record, typename Type>
void List<View, Record, Type>::Remove()
{

}

template<typename View, typename Record, typename Type>
void List<View, Record, Type>::Clear()
{
  this->clear();
}

template<typename View, typename Record, typename Type>
void List<View, Record, Type>::Draw()
{
  SHORT rows{ std::min<SHORT>(mpView->mHeight - 2, (SHORT)this->size()) };

  for (SHORT i{}; i < rows; i++)
  {
    std::wostringstream oss{};

    oss << (*this)[i];

    mpView->SetText(0, i, oss.str());
  }
}