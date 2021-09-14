#pragma once
#include <any>
#include <array>
#include <string>
#include <vector>
#include <variant>
#include <iterator>
#include <stack>
#include <memory>
#include <unordered_map>
#include <mutex>
#include <map>
#include <cmath>
#include <limits>
#include <tuple>
#include <utility>
#include <functional>
#include <thread>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <chrono>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <boost/format.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/core/ignore_unused.hpp>
#include "boost/algorithm/string.hpp"

using namespace std::chrono_literals;

#include "wobjectdefs.h"

template <typename T> inline T* getPtrHelper(T* ptr) { return ptr; }
template <typename Ptr> inline auto getPtrHelper(Ptr& ptr) -> decltype(ptr.operator->()) { return ptr.operator->(); }


#define DECLARE_PRIVATE(Class) \
inline Class##Private * d_func() \
    { Q_CAST_IGNORE_ALIGN(return reinterpret_cast<Class##Private *>(getPtrHelper(d_ptr));) } \
    inline const Class##Private* d_func() const \
    { Q_CAST_IGNORE_ALIGN(return reinterpret_cast<const Class##Private *>(getPtrHelper(d_ptr));) } \
friend class Class##Private; \

#define DECLARE_PRIVATE_D(Dptr, Class) \
inline Class##Private* d_func() \
    { return dynamic_cast<Class##Private*>(getPtrHelper(Dptr)); } \
inline const Class##Private* d_func() const \
    { return dynamic_cast<const Class##Private*>(getPtrHelper(Dptr)); } \
friend class Class##Private;


#define T_DECLARE_PRIVATE(Class) \
inline Class##Private<T> * d_func() \
    { Q_CAST_IGNORE_ALIGN(return reinterpret_cast<Class##Private<T> *>(getPtrHelper(d_ptr));) } \
    inline const Class##Private<T>* d_func() const \
    { Q_CAST_IGNORE_ALIGN(return reinterpret_cast<const Class##Private<T> *>(getPtrHelper(d_ptr));) } \
friend class Class##Private<T>; \

#define T_DECLARE_PRIVATE_D(Dptr, Class) \
inline Class##Private<T>* d_func() \
    { return dynamic_cast<Class##Private<T>*>(getPtrHelper(Dptr)); } \
inline const Class##Private<T>* d_func() const \
    { return dynamic_cast<const Class##Private<T>*>(getPtrHelper(Dptr)); } \
friend class Class##Private<T>;

#define DECLARE_IMPLEMENT_Q(Class) \
inline Class##<T>* q_func() \
    { return static_cast<Class##<T>*>(getPtrHelper(q_ptr));} \
inline const Class##<T>* q_func() const \
    { return static_cast<const Class##<T>*>(getPtrHelper(q_ptr)); } \
friend class Class##<T>;




#define T_Q_D(Class) Class##Private<T> * const d = d_func()
#define T_Q_Q(Class) Class<T> * const q = q_func()