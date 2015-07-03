#ifndef CODE_H
#define CODE_H

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <QString>

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------

/**
 * Defines an abstraction for code text
 */
class Code {
public:
  /// Build directly or indirectly from just text
  Code(const QString &text);

  inline const QString &str() const { return m_content; }

private:
  QString m_content;
};

#endif // CODE_H
