#include "WorkspaceFactory.h"

MatrixWorkspaceSharedPtr WorkspaceFactory::create() {
  return boost::make_shared<Workspace2D>();
}
