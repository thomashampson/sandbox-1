//
// Main interface to the Workspace hierarchy
//
#include <string>

class Workspace {
public:
  virtual ~Workspace() = default;

  virtual const std::string id() const = 0;
};
