#pragma once

#include <windows.h>

#undef min
#undef max

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cmath>
#include <utility>
#include <cassert>
#include <vector>
#include <array>
#include <tuple>
#include <map>
#include <algorithm>

/*
* Type deduction utilities.
*/

template<typename T>
struct Identity
{
  using Type = T;
  using Ptr  = T*;
  using CPtr = T const*;
  using Ref  = T&;
  using CRef = T const&;
};

/*
* Compile time string literal.
*/

template<DWORD N>
struct StringLiteral
{
  constexpr StringLiteral(CHAR const (&str)[N])
  {
    std::copy_n(str, N, mValue);
  }

  CHAR mValue[N]{};
};

template<DWORD N>
struct WStringLiteral
{
  constexpr WStringLiteral(WCHAR const (&str)[N])
  {
    std::copy_n(str, N, mValue);
  }

  WCHAR mValue[N]{};
};

/*
* Compile time for loop
*/

template<typename Predicate, DWORD ... Sizes>
constexpr void StaticFor(Predicate&& predicate, std::index_sequence<Sizes ...>)
{
  (
    predicate(std::integral_constant<DWORD, Sizes>{}),
    ...
  );
}

template<DWORD Iterations, typename Predicate>
constexpr void StaticFor(Predicate&& predicate)
{
  StaticFor(std::forward<Predicate>(predicate), std::make_index_sequence<Iterations>());
}