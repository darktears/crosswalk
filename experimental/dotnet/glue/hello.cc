// This is the main DLL file.
#include "hello.h"

// Utilities for Native<>CLI conversions
#include <vcclr.h>

#include <cstdio>

using namespace System;
using namespace System::Reflection;
using namespace Runtime::InteropServices;

namespace xwalk {
namespace experimental {

public ref class Bridge: public Object {
public:
  Bridge() {}
  void setParent(CHello* parent) { parent_ = parent;  }
  void PostMessageToJS(String^ message) {
    IntPtr p = Marshal::StringToHGlobalAnsi(message);
    const char* pAnsi = static_cast<const char*>(p.ToPointer());
    parent_->PostMessageToJS(pAnsi);
    Marshal::FreeHGlobal(p);
  }
private:
  CHello* parent_;
};

CHello::CHello(void* instance)
{
  try {
    Assembly^ helloAssembly = Assembly::LoadFrom("C:\\Users\\Alexis\\Development\\crosswalk\\src\\out\\Debug_x64\\xwalk_csharp.dll");
    Type^ helloType = helloAssembly->GetType("xwalk.experimental.Hello", true);
    ConstructorInfo^ helloConstructor = helloType->GetConstructor(gcnew array<Type^>(0));
    Object^ helloObject = helloConstructor->Invoke(gcnew array<Object^>(0){});
    gcroot<Object^> *pointer_clr = new gcroot<Object^>(helloObject);
    hello_clr_ = static_cast<void*>(pointer_clr);
    instance_ = instance;


    MethodInfo^ helloMethod = helloType->GetMethod("setCallback");
    Bridge^ callback = gcnew Bridge;
    gcroot<Object^> *pointer_callback = new gcroot<Object^>(callback);
    pointer_callback_ = static_cast<void*>(pointer_callback);
    callback->setParent(this);
    Object^ returnValue = helloMethod->Invoke(((Object^)*pointer_clr), gcnew array<Object^>(1){ callback });
  }
  catch (Exception^ e) {
    Console::WriteLine("Problem loading the dll");
    Console::WriteLine(e->ToString());
  }
}

void CHello::setJSCallback(PostMessageToJSFunc callback_js)
{
  callback_js_ = callback_js;
}

void CHello::SayHelloASync(const char* message)
{
  try {
    String^ message_str = gcnew String(message);
    gcroot<Object^> *pointer_clr = static_cast<gcroot<Object^>*>(hello_clr_);
    Type^ helloType = ((Object^)*pointer_clr)->GetType();
    MethodInfo^ helloMethod = helloType->GetMethod("SayHelloASync");
    Object^ returnValue = helloMethod->Invoke(((Object^)*pointer_clr), gcnew array<Object^>(1){ message_str });
  }
  catch (Exception^ e) {
    Console::WriteLine("Problem invoking the dll");
    Console::WriteLine(e->ToString());
  }
}

void CHello::PostMessageToJS(const char* message)
{
  callback_js_(instance_, message);
}

CHello::~CHello()
{
  if (hello_clr_)
  {
    gcroot<Object^> *pointer_clr = static_cast<gcroot<Object^>*>(hello_clr_);
    delete pointer_clr;
    hello_clr_ = 0;
  }
}

}
}
