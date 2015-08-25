// Copyright (c) 2014 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "xwalk/runtime/browser/storage_component.h"

#include "xwalk/runtime/common/xwalk_runtime_features.h"

namespace xwalk {

StorageComponent::StorageComponent()
    : native_file_system_extension_(0),
      dotnet_extension_(0) {
}

StorageComponent::~StorageComponent() {
  if (native_file_system_extension_) {
    delete native_file_system_extension_;
  }
  if (dotnet_extension_)
    delete dotnet_extension_;
}

void StorageComponent::CreateExtensionThreadExtensions(
    content::RenderProcessHost* host,
    extensions::XWalkExtensionVector* extensions) {
  extensions->push_back(new experimental::NativeFileSystemExtension(host));
  extensions->push_back(new experimental::DotNetExtension(host));
}

}  // namespace xwalk
