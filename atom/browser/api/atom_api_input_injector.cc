// Copyright (c) 2013 Excellent Media All rights reserved.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "atom/browser/api/atom_api_input_injector.h"

#include "atom/common/node_includes.h"

#undef CHECK_GE
#undef CHECK_EQ
#undef CHECK_LE
#undef CHECK_NE
#undef CHECK_LT
#undef CHECK_GT
#undef CHECK

#include "content/public/browser/browser_thread.h"

#include "base/values.h"
#include "base/command_line.h"
#include "base/environment.h"
#include "base/files/file_path.h"
#include "base/path_service.h"
#include "native_mate/callback.h"
#include "native_mate/dictionary.h"
#include "native_mate/object_template_builder.h"

using content::BrowserThread;

namespace atom {

namespace api {

AtomInputInjector::AtomInputInjector() {
	 injector_ = nwapi::InputInjector::Create();
}

AtomInputInjector::~AtomInputInjector() {
}

void AtomInputInjector::SimulateMouseEvent(int x, int y)
{

  nwapi::protocol::MouseEvent event;
  event.set_x(x);
  event.set_y(y);
  injector_->InjectMouseEvent(event);
}

void AtomInputInjector::SimulateMouseEventWithDelta(int x, int y)
{
  nwapi::protocol::MouseEvent event;
  event.set_wheel_delta_x(x);
  event.set_wheel_delta_y(y);
  injector_->InjectMouseEvent(event);
}

void AtomInputInjector::SimulateKeyboardEvent(uint32_t usb, bool down)
{
  nwapi::protocol::KeyEvent event;
  event.set_pressed(down);
  event.set_usb_keycode(usb);
  injector_->InjectKeyEvent(event);
}

void AtomInputInjector::SimulateMouseEventWithButton(int x, int y, int button, bool down)
{
  nwapi::protocol::MouseEvent event;
  event.set_x(x);
  event.set_y(y);
  //event.set_has_button();
  event.set_button((nwapi::protocol::MouseEvent_MouseButton)button);

/*

  // Leaving this here since converting from JS button types here would be
  // ideal.

  if (button == 1)
  {
	event.set_button(protocol::MouseEvent::BUTTON_LEFT);
  } else if (button == 2) {
	event.set_button(protocol::MouseEvent::BUTTON_RIGHT);
  } else {
	event.set_button(protocol::MouseEvent::BUTTON_LEFT);
  }
  */
  event.set_button_down(down);
  injector_->InjectMouseEvent(event);

  VLOG(1) << "Injected mouse event: " << x << ", " << y << " - " << button << " - " << down;
}

mate::ObjectTemplateBuilder AtomInputInjector::GetObjectTemplateBuilder(
    v8::Isolate* isolate) {
  return mate::ObjectTemplateBuilder(isolate)
      .SetMethod("simulateMouseEvent",
                 base::Bind(&AtomInputInjector::SimulateMouseEvent,
                            base::Unretained(this)))
      .SetMethod("simulateMouseEventWithDelta",
                 base::Bind(&AtomInputInjector::SimulateMouseEventWithDelta,
                            base::Unretained(this)))
      .SetMethod("simulateMouseEventWithButton",
                 base::Bind(&AtomInputInjector::SimulateMouseEventWithButton,
                            base::Unretained(this)))
      .SetMethod("simulateKeyboardEvent",
                 base::Bind(&AtomInputInjector::SimulateKeyboardEvent,
                            base::Unretained(this)));
}


// static
mate::Handle<AtomInputInjector> AtomInputInjector::Create(v8::Isolate* isolate) {
  return CreateHandle(isolate, new AtomInputInjector);
}

}  // namespace api

}  // namespace atom


namespace {

void Initialize(v8::Handle<v8::Object> exports, v8::Handle<v8::Value> unused,
                v8::Handle<v8::Context> context, void* priv) {

  using atom::api::AtomInputInjector;
  v8::Isolate* isolate = context->GetIsolate();
  mate::Handle<AtomInputInjector> input_injector = AtomInputInjector::Create(isolate);
  mate::Dictionary dict(isolate, exports);

  dict.Set("inputInjector", input_injector);
}

}  // namespace

NODE_MODULE_CONTEXT_AWARE_BUILTIN(atom_common_input_injector, Initialize)
