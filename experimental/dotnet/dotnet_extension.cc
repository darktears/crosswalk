// Copyright (c) 2014 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/experimental/dotnet/dotnet_extension.h"

#include "grit/xwalk_resources.h"
#include "ui/base/resource/resource_bundle.h"
#include "xwalk/experimental/dotnet/glue/hello.h"

#include <fcntl.h>
#include <io.h>
#include <ios>
#include <cstdio>

static void OpenConsole()
{
  int outHandle, errHandle, inHandle;
  FILE *outFile, *errFile, *inFile;
  AllocConsole();
  CONSOLE_SCREEN_BUFFER_INFO coninfo;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
  coninfo.dwSize.Y = 9999;
  SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

  outHandle = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
  errHandle = _open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE), _O_TEXT);
  inHandle = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE), _O_TEXT);

  outFile = _fdopen(outHandle, "w");
  errFile = _fdopen(errHandle, "w");
  inFile = _fdopen(inHandle, "r");

  *stdout = *outFile;
  *stderr = *errFile;
  *stdin = *inFile;

  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);

  std::ios::sync_with_stdio();

}

namespace {
static void PostMessageToJSCallback(void* instance, const char* message) {
  if (instance) {
    xwalk::experimental::DotNetInstance* inst = reinterpret_cast<xwalk::experimental::DotNetInstance*>(instance);
    inst->PostMessageToJS(
      scoped_ptr<base::Value>(
      new base::StringValue(message)));
  }
}
}

namespace xwalk {
namespace experimental {

DotNetExtension::DotNetExtension(
  content::RenderProcessHost* host) {
  host_ = host;
  set_name("xwalk.experimental.dotnet");
  set_javascript_api(
    ResourceBundle::GetSharedInstance().GetRawDataResource(
    IDR_XWALK_DOTNET_API).as_string());
}

DotNetExtension::~DotNetExtension() {}

XWalkExtensionInstance* DotNetExtension::CreateInstance() {
  return new DotNetInstance(host_);
}

DotNetInstance::DotNetInstance(content::RenderProcessHost* host)
  : handler_(this),
  host_(host),
  hello_clr_(0) {

  //OpenConsole();
  hello_clr_ = new CHello(this);
  hello_clr_->setJSCallback(&PostMessageToJSCallback);
}

DotNetInstance::~DotNetInstance() {
  if (hello_clr_)
    delete hello_clr_;
}

void DotNetInstance::HandleMessage(scoped_ptr<base::Value> msg) {
  base::DictionaryValue* dict;
  std::string command;
  if (!msg->GetAsDictionary(&dict) || !dict->GetString("cmd", &command)) {
    LOG(ERROR) << "Fail to handle command sync message.";
    SendSyncReplyToJS(scoped_ptr<base::Value>(new base::StringValue("")));
    return;
  }

  if (command == "SayHello") {
    std::string message;
    dict->GetString("message", &message);
    hello_clr_->SayHelloASync(message.c_str());
  }
}

void DotNetInstance::HandleSyncMessage(
    scoped_ptr<base::Value> msg) {
}

}  // namespace experimental
}  // namespace xwalk
