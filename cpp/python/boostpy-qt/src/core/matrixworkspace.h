//
// MatrixWorkspace
//
#include "workspace.h"

class MatrixWorkspace : public Workspace {
public:

  const std::string id() const override;
};
