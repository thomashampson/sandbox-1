#include "PropertyManager.h"

//#define BOOST_NO_CXX11_NULLPTR
#include <boost/shared_ptr.hpp>
#include <memory>

#include <iostream>
#include <vector>



class DataItem final {
public:
  typedef std::vector<double> StorageType;

  DataItem() : m_data(10, 1.0) {}
  inline StorageType::size_type size() const { return m_data.size(); }
private:
   StorageType m_data;
};

typedef boost::shared_ptr<DataItem> DataItem_boost_sptr;
typedef std::shared_ptr<DataItem> DataItem_std_sptr;

int main() {
  PropertyManager pm;
  pm.declareProperty("InputStd", DataItem_std_sptr(new DataItem));
  pm.declareProperty("InputBoost", DataItem_boost_sptr(new DataItem));

  DataItem_std_sptr input_std;
  input_std = pm.getProperty("InputStd"); // this compiles

  DataItem_boost_sptr input_boost = nullptr;
//input_boost = pm.getProperty("InputBoost"); // this DOES NOT compile

}
