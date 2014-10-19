#ifndef WEBKIT_HOST_INPUT_INJECTOR_H
#define WEBKIT_HOST_INPUT_INJECTOR_H

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"

#include "input_stub.h"

namespace base {
class SingleThreadTaskRunner;
}  // namespace base

namespace nwapi {

class InputInjector : public protocol::InputStub {
 public:
  // Creates a default input injector for the current platform. This
  // object should do as much work as possible on |main_task_runner|,
  // using |ui_task_runner| only for tasks actually requiring a UI
  // thread.
  static scoped_ptr<InputInjector> Create();
};

}  // namespace nwapi

#endif  // WEBKIT_HOST_INPUT_INJECTOR_H
