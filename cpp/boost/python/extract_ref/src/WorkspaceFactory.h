#ifndef WORKSPACEFACTORY_H_
#define WORKSPACEFACTORY_H_

#include "DataObjects.h"

class WorkspaceFactory {
public:
  static MatrixWorkspaceSharedPtr create();
};

#endif //WORKSPACEFACTORY_H_
