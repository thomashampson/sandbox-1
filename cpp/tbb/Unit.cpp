#include "Unit.h"

#include <algorithm>

namespace PhysicalConstants {
  static double h = 6e-34;
  static double meV = 1.6e-16;
  static double NeutronMass = 1e-27;
  static double meVtoWavenumber = 2;
}

Unit::ConversionsMap Unit::s_conversionFactors;

void Unit::addConversion(std::string to, const double &factor,
                         const double &power) const {
  std::transform(to.cbegin(), to.cend(), to.begin(), toupper);
  // Add the conversion to the map (does nothing if it's already there)
  s_conversionFactors[unitID()][to] = std::make_pair(factor, power);
}

Wavelength::Wavelength() : Unit() {
  const double AngstromsSquared = 1e20;
  const double factor =
      (AngstromsSquared * PhysicalConstants::h * PhysicalConstants::h) /
      (2.0 * PhysicalConstants::NeutronMass * PhysicalConstants::meV);
  addConversion("Energy", factor, -2.0);
  addConversion("Energy_inWavenumber",
                factor * PhysicalConstants::meVtoWavenumber, -2.0);
  addConversion("Momentum", 2 * M_PI, -1.0);
}

std::string Wavelength::unitID() const {
  return "Wavelength";
}
