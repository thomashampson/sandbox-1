#ifndef SINGLETONHOLDER_H_
#define SINGLETONHOLDER_H_

template<typename T>
class SingletonHolder {
public:

  static T& instance();
};

template<typename T>
inline T&  SingletonHolder<T>::instance() {
  static T* instance = []() {
    return new T;
  }();
  return *instance;
}

#endif // SINGLETONHOLDER_H_
