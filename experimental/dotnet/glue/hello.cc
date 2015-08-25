// This is the main DLL file.
#include "hello.h"

// Utilities for Native<>CLI conversions
#include <vcclr.h>

#include <cstdio>

using namespace System;
using namespace Runtime::InteropServices;
using namespace XWalk::ClrAssembly;

namespace xwalk {
namespace experimental {

CHello::CHello(void* instance)
{
  IntPtr native(this);
  Hello^ hello = gcnew Hello(native);
  gcroot<Hello^> *pointer_clr = new gcroot<Hello^>(hello);

  hello_clr_ = static_cast<void*>(pointer_clr);
  instance_ = instance;
}

void CHello::setJSCallback(PostMessageToJSFunc callback_js)
{
  callback_js_ = callback_js;
}

void CHello::SayHelloASync(const char* message)
{
  String^ message_str = gcnew String(message);
  gcroot<Hello^> *pointer_clr = static_cast<gcroot<Hello^>*>(hello_clr_);
  ((Hello^)*pointer_clr)->SayHelloASync(message_str);
}

void CHello::SayHelloSync(const char* message)
{
  String^ message_str = gcnew String(message);
  gcroot<Hello^> *pointer_clr = static_cast<gcroot<Hello^>*>(hello_clr_);
  ((Hello^)*pointer_clr)->SayHelloSync(message_str);
}

void CHello::PostMessageToJS(const char* message)
{
  callback_js_(instance_, message);
}

CHello::~CHello()
{
  if (hello_clr_)
  {
    gcroot<Hello^> *pointer_clr = static_cast<gcroot<Hello^>*>(hello_clr_);
    delete pointer_clr;
    hello_clr_ = 0;
  }
}

void CallPostMessageToJS(CHello* instance, const char* message)
{
  if (instance) {
    instance->PostMessageToJS(message);
  }
}
}
}
