#pragma once

#include <Core.h>

#include <View.h>

struct ViewManager : std::map<std::string const, View*>
{
  ViewManager();
  virtual ~ViewManager();

  template<typename View, typename ... Args>
  void Add(std::string const& name, Args&& ... args);

  void Update();
  void Draw();
};

ViewManager::ViewManager()
{

}

ViewManager::~ViewManager()
{

}

template<typename View, typename ... Args>
void ViewManager::Add(std::string const& name, Args&& ... args)
{
  this->emplace(name, new View{ std::forward<Args>(args) ... });
}

void ViewManager::Update()
{
  for (const auto& [name, pView] : *this)
    pView->Update();
}

void ViewManager::Draw()
{
  for (const auto& [name, pView] : *this)
    pView->Draw();
}