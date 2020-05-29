/*
 * Copyright (c) 2020, Linus Groh <mail@linusgroh.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Notification.h"
#include "../GlobalObject.h"

namespace Bindings {
namespace LibGUI {

// BEGIN_OBJECT
Notification* Notification::create(JS::GlobalObject& global_object)
{
    return global_object.heap().allocate<Notification>(*static_cast<GlobalObject&>(global_object).gui_notification_prototype());
}

Notification::Notification(JS::Object& prototype)
    : Object(&prototype)
    , m_notification(GUI::Notification::construct())
{
    set_prototype(&prototype);
}
// END_OBJECT

// BEGIN_CONSTRUCTOR
NotificationConstructor::NotificationConstructor()
    : JS::NativeFunction(*interpreter().global_object().function_prototype())
{
    define_property("length", JS::Value(0), JS::Attribute::Configurable);
}

JS::Value NotificationConstructor::call(JS::Interpreter& interpreter)
{
    return construct(interpreter);
}

JS::Value NotificationConstructor::construct(JS::Interpreter& interpreter)
{
    return Notification::create(interpreter.global_object());
}
// END_CONSTRUCTOR

// BEGIN_PROTOTYPE
NotificationPrototype::NotificationPrototype()
    : Object(interpreter().global_object().object_prototype())
{
    u8 attr = JS::Attribute::Writable | JS::Attribute::Configurable;
    define_native_function("show", show, 0, attr);

    define_native_property("text", text_getter, text_setter, 0);
    define_native_property("title", title_getter, title_setter, 0);
}

static GUI::Notification* notification_from(JS::Interpreter& interpreter)
{
    auto* this_object = interpreter.this_value().to_object(interpreter);
    if (!this_object)
        return nullptr;
    if (StringView("Notification") != this_object->class_name()) {
        interpreter.throw_exception<JS::TypeError>("Not a Notification object");
        return nullptr;
    }
    return static_cast<Notification*>(this_object)->notification();
}

JS::Value NotificationPrototype::show(JS::Interpreter& interpreter)
{
    auto* notification = notification_from(interpreter);
    if (!notification)
        return {};
    notification->show();
    return JS::js_undefined();
}

JS::Value NotificationPrototype::text_getter(JS::Interpreter& interpreter)
{
    auto* notification = notification_from(interpreter);
    if (!notification)
        return {};
    return JS::js_string(interpreter, notification->text());
}

void NotificationPrototype::text_setter(JS::Interpreter& interpreter, JS::Value value)
{
    auto* notification = notification_from(interpreter);
    if (!notification)
        return;
    auto text = value.to_string(interpreter);
    if (interpreter.exception())
        return;
    notification->set_text(text);
}

JS::Value NotificationPrototype::title_getter(JS::Interpreter& interpreter)
{
    auto* notification = notification_from(interpreter);
    if (!notification)
        return {};
    return JS::js_string(interpreter, notification->title());
}

void NotificationPrototype::title_setter(JS::Interpreter& interpreter, JS::Value value)
{
    auto* notification = notification_from(interpreter);
    if (!notification)
        return;
    auto title = value.to_string(interpreter);
    if (interpreter.exception())
        return;
    notification->set_title(title);
}
// END_PROTOTYPE

}
}
