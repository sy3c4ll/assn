#ifndef OPTION_HPP
#define OPTION_HPP

#include <memory>

template <typename T>
class option {
  bool type;
  T data;

  option(bool _type): type(_type) {}
  option(bool _type, T const& _data): type(_type), data(_data) {}

public:
  constexpr static option<T> some(T const& value) noexcept { return option{true, value}; }
  constexpr static option<T> none() noexcept { return option{false}; }
  bool is_some() const noexcept { return type; }
  bool is_none() const noexcept { return !type; }
  option<T const*> as_ref() const noexcept { return type ? option<T const*>::some(&data) : option<T const*>::none(); }
  option<T*> as_mut() noexcept { return type ? option<T*>::some(&data) : option<T*>::none(); }
  T expect(char const* msg) const { if (type) return data; else throw msg; }
  T unwrap() const { if (type) return data; else throw; }
  T unwrap_or(T const& dfl) const noexcept { return type ? data : dfl; }
  T unwrap_or_else(T (*f)(void)) const noexcept { return type ? data : f(); }
  T unwrap_unchecked() const noexcept { return data; }
  template <typename U>
  option<U> map(U (*f)(T)) const noexcept { return type ? option<U>::some(f(data)) : option<U>::none(); }
  template <typename U>
  U map_or(U const& dfl, U (*f)(T)) const noexcept { return type ? f(data) : dfl; }
  template <typename U>
  U map_or_else(U (*dfl)(void), U (*f)(T)) const noexcept { return type ? f(data) : dfl(); }
  template <typename U>
  option<U> opt_and(option<U> const& optb) const noexcept { return type ? optb : option<U>::none(); }
  template <typename U>
  option<U> opt_and_then(option<U> (*f)(T)) const noexcept { return type ? f(data) : option<U>::none(); }
  option<T> filter(bool (*predicate)(T)) const noexcept { return type && predicate(data) ? *this : none(); }
  option<T> opt_or(option<T> const& optb) const noexcept { return type ? *this : optb; }
  option<T> opt_or_else(option<T> (*f)(void)) const noexcept { return type ? *this : f(); }
  option<T> opt_xor(option<T> const& optb) const noexcept { return type ? optb.type ? none() : *this : optb; }
  T& insert(T const& value) noexcept { type = true, data = value; return data; }
  T& get_or_insert(T const& value) noexcept { if (!type) type = true, data = value; return data; }
  T& get_or_insert_with(T (*f)(void)) noexcept { if (!type) type = true, data = f(); return data; }
  option<T> take() noexcept { type = false; return some(std::move(data)); }
  option<T> replace(T const& value) noexcept { T old = std::move(data); data = value; return some(std::move(old)); }
  bool operator==(option<T> const& optb) const noexcept { return type == optb.type && (type == false || data == optb.data); }
  bool operator<(option<T> const& optb) const noexcept { return type < optb.type || (type == true && data < optb.data); }
};

template <typename T>
class option<T*> {
  T* data;

  option(T* _data): data(_data) {}

public:
  constexpr static option<T*> some(T* value) noexcept { return option{value}; }
  constexpr static option<T*> none() noexcept { return option{nullptr}; }
  bool is_some() const noexcept { return data; }
  bool is_none() const noexcept { return !data; }
  option<T* const*> as_ref() const noexcept { return data ? option<T* const*>::some(&data) : option<T* const*>::none(); }
  option<T**> as_mut() noexcept { return data ? option<T**>::some(&data) : option<T**>::none(); }
  T* expect(char const* msg) const { if (data) return data; else throw msg; }
  T* unwrap() const { if (data) return data; else throw; }
  T* unwrap_or(T* dfl) const noexcept { return data ? data : dfl; }
  T* unwrap_or_else(T* (*f)(void)) const noexcept { return data ? data : f(); }
  T* unwrap_unchecked() const noexcept { return data; }
  template <typename U>
  option<U> map(U (*f)(T*)) const noexcept { return data ? option<U>::some(f(data)) : option<U>::none(); }
  template <typename U>
  U map_or(U const& dfl, U (*f)(T*)) const noexcept { return data ? f(data) : dfl; }
  template <typename U>
  U map_or_else(U (*dfl)(void), U (*f)(T*)) const noexcept { return data ? f(data) : dfl(); }
  template <typename U>
  option<U> opt_and(option<U> const& optb) const noexcept { return data ? optb : option<U>::none(); }
  template <typename U>
  option<U> opt_and_then(option<U> (*f)(T*)) const noexcept { return data ? f(data) : option<U>::none(); }
  option<T*> filter(bool (*predicate)(T*)) const noexcept { return data && predicate(data) ? *this : none(); }
  option<T*> opt_or(option<T*> const& optb) const noexcept { return data ? *this : optb; }
  option<T*> opt_or_else(option<T*> (*f)(void)) const noexcept { return data ? *this : f(); }
  option<T*> opt_xor(option<T*> const& optb) const noexcept { return data ? optb.data ? none() : *this : optb; }
  T*& insert(T* value) noexcept { data = value; return data; }
  T*& get_or_insert(T* value) noexcept { if (!data) data = value; return data; }
  T*& get_or_insert_with(T* (*f)(void)) noexcept { if (!data) data = f(); return data; }
  option<T*> take() noexcept { T* old = data; data = nullptr; return some(old); }
  option<T*> replace(T* value) noexcept { T* old = data; data = value; return some(old); }
  bool operator==(option<T*> const& optb) const noexcept { return data == optb.data; }
  bool operator<(option<T*> const& optb) const noexcept { return (!data && optb.data) || (data && optb.data && *data < *optb.data); }
};

template <typename T>
class option<std::unique_ptr<T>> {
  std::unique_ptr<T> data;

  option(std::unique_ptr<T> _data): data(std::move(_data)) {}

public:
  constexpr static option<std::unique_ptr<T>> some(std::unique_ptr<T> value) noexcept { return option{std::move(value)}; }
  constexpr static option<std::unique_ptr<T>> none() noexcept { return option{nullptr}; }
  bool is_some() const noexcept { return data; }
  bool is_none() const noexcept { return !data; }
  option<std::unique_ptr<T> const*> as_ref() const noexcept { return data ? option<std::unique_ptr<T> const*>::some(&data) : option<std::unique_ptr<T> const*>::none(); }
  option<std::unique_ptr<T>*> as_mut() noexcept { return data ? option<std::unique_ptr<T>*>::some(&data) : option<std::unique_ptr<T>*>::none(); }
  std::unique_ptr<T> expect(char const* msg) { if (data) return std::move(data); else throw msg; }
  std::unique_ptr<T> unwrap() { if (data) return std::move(data); else throw; }
  std::unique_ptr<T> unwrap_or(std::unique_ptr<T> dfl) noexcept { return data ? std::move(data) : std::move(dfl); }
  std::unique_ptr<T> unwrap_or_else(std::unique_ptr<T> (*f)(void)) noexcept { return data ? std::move(data) : std::move(f()); }
  std::unique_ptr<T> unwrap_unchecked() noexcept { return std::move(data); }
  template <typename U>
  option<U> map(U (*f)(std::unique_ptr<T>&)) const noexcept { return data ? option<U>::some(f(data)) : option<U>::none(); }
  template <typename U>
  U map_or(U const& dfl, U (*f)(std::unique_ptr<T>&)) const noexcept { return data ? f(data) : dfl; }
  template <typename U>
  U map_or_else(U (*dfl)(void), U (*f)(std::unique_ptr<T>&)) const noexcept { return data ? f(data) : dfl(); }
  template <typename U>
  option<U> opt_and(option<U> optb) const noexcept { return data ? std::move(optb) : option<U>::none(); }
  template <typename U>
  option<U> opt_and_then(option<U> (*f)(std::unique_ptr<T>&)) const noexcept { return data ? f(data) : option<U>::none(); }
  option<std::unique_ptr<T>> filter(bool (*predicate)(std::unique_ptr<T>&)) noexcept { return data && predicate(data) ? std::move(*this) : none(); }
  option<std::unique_ptr<T>> opt_or(option<std::unique_ptr<T>> optb) noexcept { return data ? std::move(*this) : std::move(optb); }
  option<std::unique_ptr<T>> opt_or_else(option<std::unique_ptr<T>> (*f)(void)) noexcept { return data ? std::move(*this) : std::move(f()); }
  option<std::unique_ptr<T>> opt_xor(option<std::unique_ptr<T>> optb) noexcept { return data ? optb.data ? none() : std::move(*this) : std::move(optb); }
  std::unique_ptr<T>& insert(std::unique_ptr<T> value) noexcept { data = std::move(value); return data; }
  std::unique_ptr<T>& get_or_insert(std::unique_ptr<T> value) noexcept { if (!data) data = std::move(value); return data; }
  std::unique_ptr<T>& get_or_insert_with(std::unique_ptr<T> (*f)(void)) noexcept { if (!data) data = std::move(f()); return data; }
  option<std::unique_ptr<T>> take() noexcept { std::unique_ptr<T> old = std::move(data); data = nullptr; return some(std::move(old)); }
  option<std::unique_ptr<T>> replace(std::unique_ptr<T> value) noexcept { std::unique_ptr<T> old = std::move(data); data = std::move(value); return some(std::move(old)); }
  bool operator==(option<std::unique_ptr<T>> const& optb) const noexcept { return data == optb.data; }
  bool operator<(option<T> const& optb) const noexcept { return (!data && optb.data) || (data && optb.data && *data < *optb.data); }
};

template <typename T>
constexpr auto some = option<T>::some;
template <typename T>
constexpr auto none = option<T>::none;

#endif // OPTION_HPP
