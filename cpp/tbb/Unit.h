#ifndef UNIT_H_
#define UNIT_H_

#include <string>
#include <tbb/concurrent_unordered_map.h>
#include <utility>

class Unit {
public:
  virtual ~Unit() = default;
  virtual std::string unitID() const = 0;

protected:
    // Add a 'quick conversion' for a unit pair
  void addConversion(std::string to, const double &factor,
                     const double &power)  const;

private:
  /// A 'quick conversion' requires the constant by which to multiply the input
  /// and the power to which to raise it
  using ConstantAndPower = std::pair<double, double>;
  /// Lists, for a given starting unit, the units to which a 'quick conversion'
  /// can be made
  using UnitConversions = tbb::concurrent_unordered_map<std::string, ConstantAndPower>
      ;
  /// The possible 'quick conversions' are held in a map with the starting unit
  /// as the key
  using ConversionsMap = tbb::concurrent_unordered_map<std::string, UnitConversions>
      ;
  /// The table of possible 'quick conversions'
  static ConversionsMap s_conversionFactors;
};

class Wavelength : public Unit {
public:
  Wavelength();
  std::string unitID() const;
};


#endif
