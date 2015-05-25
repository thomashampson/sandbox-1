#ifndef DATAOBJECTS_H_
#define DATAOBJECTS_H_

#include <boost/make_shared.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <iostream>
#include <map>
#include <string>
#include <vector>

//------------------------------------------------------------------------------
// DataItem
//------------------------------------------------------------------------------
class DataItem : private boost::noncopyable{
public:
  virtual ~DataItem() {};
  virtual const std::string id() const = 0;
};

//------------------------------------------------------------------------------
// Workspace
//------------------------------------------------------------------------------
class Workspace : public DataItem {
public:
  Workspace();
  ~Workspace();
  const std::string name() const;

private:
  std::string m_name;
};

typedef boost::shared_ptr<Workspace> WorkspaceSharedPtr;
typedef boost::weak_ptr<Workspace> WorkspaceWeakPtr;

//------------------------------------------------------------------------------
// MatrixWorkspace
//------------------------------------------------------------------------------
class MatrixWorkspace : public Workspace {

public:
  MatrixWorkspace();
  const std::vector<double> & readX() const;

private:
  std::vector<double> m_x;
};

typedef boost::shared_ptr<MatrixWorkspace> MatrixWorkspaceSharedPtr;

//------------------------------------------------------------------------------
// Workspace2D
//------------------------------------------------------------------------------
class Workspace2D : public MatrixWorkspace {
public:
  const std::string id() const;
};

typedef boost::shared_ptr<Workspace2D> Workspace2DSharedPtr;

#endif //DATAOBJECTS_H_
