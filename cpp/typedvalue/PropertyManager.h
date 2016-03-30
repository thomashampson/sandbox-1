#ifndef PROPERTYMANAGER_H_
#define PROPERTYMANAGER_H_

#include <unordered_map>
#include <string>

class Property {
public:
  Property(std::string name) : m_name(name) {}
  virtual ~Property() = default;

  const std::string &name() const { return m_name; }

private:
  std::string m_name;
};

template <typename ValueType> class PropertyWithValue : public Property {
public:
  PropertyWithValue(std::string name, ValueType defaultValue)
      : Property(name), m_value(defaultValue) {}

  inline const ValueType &value() { return m_value; }

private:
  ValueType m_value;
};

class PropertyManager final {
public:
  template <typename ValueType>
  Property &declareProperty(std::string name, ValueType defaultValue) {
    auto prop = new PropertyWithValue<ValueType>(name, defaultValue);
    m_properties.insert(std::make_pair(name, prop));
    return *prop;
  }

  struct TypedValue {
    TypedValue(const PropertyManager &pm_, std::string name_)
        : pm(pm_), name(name_) {}

    template <typename T>
    inline operator T() const { return pm.getValue<T>(name); }

    const PropertyManager &pm;
    std::string name;
  };

  inline TypedValue getProperty(std::string name) const { return TypedValue(*this, name); }

  template <typename ReturnType> ReturnType getValue(std::string name) const {
    typedef PropertyWithValue<ReturnType> ExpectedType;
    auto pitr = m_properties.find(name);
    if (auto prop = dynamic_cast<ExpectedType *>(pitr->second)) {
      return prop->value();
    } else {
      throw std::runtime_error(
          "Cannot return property '" + name +
          "' as requested type. The type must match the declare type.");
    }
  }

private:
  std::unordered_map<std::string, Property *> m_properties;
};

#endif // PROPERTYMANAGER_H_
