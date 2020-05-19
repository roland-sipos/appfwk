/**
 * @file Buffer class interface
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef APP_FRAMEWORK_BASE_INCLUDE_APP_FRAMEWORK_BASE_BUFFERS_BUFFERI_HH_
#define APP_FRAMEWORK_BASE_INCLUDE_APP_FRAMEWORK_BASE_BUFFERS_BUFFERI_HH_

#include <memory>
#include <cstddef>

#include "cetlib/BasicPluginFactory.h"
#include "cetlib/compiler_macros.h"


#ifndef EXTERN_C_FUNC_DECLARE_START
#define EXTERN_C_FUNC_DECLARE_START                                            \
  extern "C"                                                                   \
  {
#endif

#define DEFINE_DUNE_BUFFER(klass)                                    \
  EXTERN_C_FUNC_DECLARE_START                                                  \
  std::shared_ptr<appframework::BufferI> make()                        \
  {                                                                            \
    return std::shared_ptr<appframework::BufferI>(new klass());        \
  }                                                                            \
  }

namespace appframework {
/**
 * @brief Attributes of Buffers that can be communicated to framework for
 * DAQProcess configuration and testing.
 *
 */
struct BufferAttributes {
  bool isBounded;    ///< can size increase dynamically?
  bool isSearchable; ///< is the data in the buffer searchable?
};

/**
 * @brief Implementations of the Buffer class are responsible for relaying data
 * between UserModules within a DAQ Application
 *
 * Note that while the Buffer class itself is not templated on a data type (so
 * it can be included in generic containers), all implementations should be.
 */
class BufferI {
public:
  explicit BufferI(BufferAttributes attributes = {false, false})
      : fAttributes(attributes) {}

  virtual void Configure() = 0; ///< called when configured in FSM

  virtual bool empty() const noexcept = 0; ///< is there any available data?
  virtual bool full() const noexcept = 0;  ///< is there any room for more data?
  virtual size_t capacity() const
      noexcept = 0; ///< what is the available capacity?

  BufferI(const BufferI &) = default;
  BufferI &operator=(const BufferI &) = default;
  BufferI(BufferI &&) = default;
  BufferI &operator=(BufferI &&) = default;

protected:
  BufferAttributes fAttributes; /// buffer attributes
};

inline std::shared_ptr<BufferI>
makeBuffer(std::string const& buffer_name)
{
  static cet::BasicPluginFactory bpf("duneBuffer", "make");

  return bpf.makePlugin<std::shared_ptr<BufferI>>(buffer_name);
}

} // namespace appframework

#endif // APP_FRAMEWORK_BASE_INCLUDE_APP_FRAMEWORK_BASE_BUFFERS_BUFFERI_HH_
