#include "matrixworkspace.h"

using std::string;

const string MatrixWorkspace::id() const {
  static string id_str("MatrixWorkspace");
  return id_str;
}
