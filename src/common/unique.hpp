#pragma once

// copyable unique ptr

/*
template <class... Args>
Node(BlockPtr&& self, Args&&... args) : gui::logic::Drawable(std::move(self)) {
	descendants.reserve(sizeof...(args));
	generate(std::move(args)...);
}
*/

#include <forward_list>

template <class T>
class Unique {
private:
	Unique(T* ptr) : ptr_(ptr) {}
public:
	Unique() = default;
	Unique(Unique& src) : ptr_(src.ptr_) { src.ptr_ = nullptr; }
	Unique(Unique&& src) : ptr_(src.ptr_) { src.ptr_ = nullptr; }
	Unique& operator=(Unique& src) { delete ptr_; ptr_ = src.ptr_; return *this; }
	Unique& operator=(Unique&& src) { delete ptr_; ptr_ = src.ptr_; return *this; }

	template <class... Args>
	static Unique make(Args&&... args) {
		return Unique(new T(std::forward<Args>(args)...));
	}
	~Unique() { delete ptr_; }

public:
	T* operator->() { return ptr_; }
	const T* operator->() const { return ptr_; }
	T& operator*() { return *ptr_; }
	const T& operator*() const { return *ptr_; }

private:
	T* ptr_ = nullptr;
};