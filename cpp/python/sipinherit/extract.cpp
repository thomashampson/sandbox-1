#include <extract.h>

namespace Detail {
/**
 * @return A pointer to the C++ sip api object
 */
const sipAPIDef *sipAPI() {
  static const sipAPIDef *sip_API = nullptr;
  if (sip_API)
    return sip_API;

  // Try plain sip module
  if (!sip_API) {
    PyErr_Clear();
    sip_API = (const sipAPIDef *)PyCapsule_Import("sip._C_API", 0);
  }

  assert(sip_API);
  return sip_API;
}
} // namespace Detail
