#include "DataObjects.h"

#include <sstream>

//------------------------------------------------------------------------------
// Workspace
//------------------------------------------------------------------------------
Workspace::Workspace() : m_name("Tester") {
    std::cerr << "Created workspace " << this << "\n";
    std::ostringstream os;
    os << m_name << "-" << this << "\n";
  }

Workspace::~Workspace() {
  std::cerr << "Deleted workspace " << this << "\n";
};

const std::string Workspace::name() const {
  return m_name;
}

//------------------------------------------------------------------------------
// MatrixWorkspace
//------------------------------------------------------------------------------
MatrixWorkspace::MatrixWorkspace() : Workspace(), m_x(10) {
}

const std::vector<double> & MatrixWorkspace::readX() const {
  return m_x;
}

//------------------------------------------------------------------------------
// Workspace2D
//------------------------------------------------------------------------------
const std::string Workspace2D::id() const {
  return "Workspace2D";
}
