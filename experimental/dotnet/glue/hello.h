#include "windows.h"

#ifndef Hello_Mixed
#define Hello_Mixed

#ifdef NATIVEDLL_EXPORTS
   #define NATIVEDLL_API __declspec(dllexport)
#else
   #define NATIVEDLL_API __declspec(dllimport)
#endif

#define CALLBACK __stdcall

namespace xwalk {
namespace experimental {

typedef void (*PostMessageToJSFunc)(void*, const char*);

class NATIVEDLL_API CHello
{
 public:
   CHello(void*);
   void setJSCallback(PostMessageToJSFunc);
   ~CHello();
   void SayHelloSync(const char* message);
   void SayHelloASync(const char* message);
   void PostMessageToJS(const char* message);
 private:
  void* hello_clr_;
  void* pointer_callback_;
  void* instance_;
  PostMessageToJSFunc callback_js_;
};

}
}

#endif
