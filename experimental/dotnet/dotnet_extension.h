// Copyright (c) 2014 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef XWALK_EXPERIMENTAL_DOT_NET_EXTENSION_H_
#define XWALK_EXPERIMENTAL_DOT_NET_EXTENSION_H_

#include "base/values.h"
#include "content/public/browser/render_process_host.h"
#include "xwalk/extensions/browser/xwalk_extension_function_handler.h"
#include "xwalk/extensions/common/xwalk_extension.h"

namespace xwalk {
  namespace experimental {
    using extensions::XWalkExtension;
    using extensions::XWalkExtensionFunctionHandler;
    using extensions::XWalkExtensionFunctionInfo;
    using extensions::XWalkExtensionInstance;

    class CHello;

    class DotNetExtension : public XWalkExtension {
    public:
      explicit DotNetExtension(content::RenderProcessHost* host);
      ~DotNetExtension() override;

      // XWalkExtension implementation.
      XWalkExtensionInstance* CreateInstance() override;

    private:
      content::RenderProcessHost* host_;
    };

    class DotNetInstance : public XWalkExtensionInstance {
    public:
      explicit DotNetInstance(content::RenderProcessHost* host);
      ~DotNetInstance() override;

      // XWalkExtensionInstance implementation.
      void HandleMessage(scoped_ptr<base::Value> msg) override;
      void HandleSyncMessage(scoped_ptr<base::Value> msg) override;

    private:
      XWalkExtensionFunctionHandler handler_;
      content::RenderProcessHost* host_;
      CHello* hello_clr_;
    };
  }  // namespace experimental
}  // namespace xwalk

#endif  // XWALK_EXPERIMENTAL_DOT_NET_EXTENSION_H_
