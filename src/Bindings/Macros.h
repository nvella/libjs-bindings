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

#define OBJECT(Name) class Name final : public JS::Object

#define __OBJECT(Name)                      \
public:                                     \
    static Name* create(JS::GlobalObject&); \
                                            \
    Name(JS::Object&);                      \
    virtual ~Name() override {};            \
                                            \
private:                                    \
    virtual const char* class_name() const override { return #Name; }

#define __OBJECT_WITH_ARGS(Name, args...)         \
public:                                           \
    static Name* create(JS::GlobalObject&, args); \
                                                  \
    Name(JS::Object&, args);                      \
    virtual ~Name() override {};                  \
                                                  \
private:                                          \
    virtual const char* class_name() const override { return #Name; }

#define MEMBER(T, name)                 \
public:                                 \
    T name() const { return m_##name; } \
                                        \
private:                                \
    T m_##name;

#define CONSTRUCTOR(Name) class Name##Constructor final : public JS::NativeFunction

#define __CONSTRUCTOR(Name)                                        \
public:                                                            \
    Name##Constructor();                                           \
    virtual ~Name##Constructor() override {};                      \
                                                                   \
    virtual JS::Value call(JS::Interpreter&) override;             \
    virtual JS::Value construct(JS::Interpreter&) override;        \
                                                                   \
private:                                                           \
    virtual bool has_constructor() const override { return true; } \
    virtual const char* class_name() const override { return #Name "Constructor"; }

#define PROTOTYPE(Name) class Name##Prototype final : public JS::Object

#define __PROTOTYPE(Name)                   \
public:                                     \
    Name##Prototype();                      \
    virtual ~Name##Prototype() override {}; \
                                            \
private:                                    \
    virtual const char* class_name() const override { return #Name "Prototype"; }

#define FUNCTION(name) static JS::Value name(JS::Interpreter&)
#define PROPERTY_GETTER(name) static JS::Value name##_getter(JS::Interpreter&)
#define PROPERTY_SETTER(name) static void name##_setter(JS::Interpreter&, JS::Value)