// Copyright (c) 2013 Excellent Media All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_API_ATOM_API_INPUT_INJECTOR_H_
#define ATOM_BROWSER_API_ATOM_API_INPUT_INJECTOR_H_

#include "atom/browser/api/event_emitter.h"
#include "base/compiler_specific.h"
#include "native_mate/handle.h"
#include "base/callback.h"

#include "extensions/input_injector.h"

namespace atom {

namespace api {

class AtomInputInjector : public mate::EventEmitter
					{
 public:
  static mate::Handle<AtomInputInjector> Create(v8::Isolate* isolate);
  void SimulateMouseEvent(int x, int y);

  void SimulateMouseEventWithDelta(int x, int y);

  void SimulateKeyboardEvent(uint32_t button, bool down);

  void SimulateMouseEventWithButton(int x, int y, int button, bool down);

 protected:
  AtomInputInjector();
  virtual ~AtomInputInjector();
  
  scoped_ptr<nwapi::InputInjector> injector_;
  
  // mate::Wrappable implementations:
  virtual mate::ObjectTemplateBuilder GetObjectTemplateBuilder(
      v8::Isolate* isolate);
  
 private:
  DISALLOW_COPY_AND_ASSIGN(AtomInputInjector);
};

}  // namespace api

}  // namespace atom

#endif  // ATOM_BROWSER_API_ATOM_API_INPUT_INJECTOR_H_
