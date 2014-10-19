// Interface for a device that receives input events.
// This interface handles input event messages defined in event.proto.

#ifndef NWAPI_PROTOCOL_INPUT_STUB_H_
#define NWAPI_PROTOCOL_INPUT_STUB_H_

#include "base/basictypes.h"
#include "gen/event.pb.h"

namespace nwapi {
namespace protocol {

/*class KeyEvent;
class MouseEvent; */

struct MousePosition
{
  int x;
  int y;
};

class InputStub {
 public:
  InputStub() {}
  virtual ~InputStub() {}

  // Implementations must never assume the presence of any |event| fields,
  // nor assume that their contents are valid.
  virtual void InjectKeyEvent(const KeyEvent& event) = 0;
  virtual void InjectMouseEvent(const MouseEvent& event) = 0;

  virtual MousePosition GetMousePosition() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(InputStub);
};

}  // namespace nwapi
}  // namespace remoting

#endif  // NWAPI_PROTOCOL_INPUT_STUB_H_
