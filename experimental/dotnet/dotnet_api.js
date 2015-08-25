var listener = null;
extension.setMessageListener(function (msg) {
  if (listener instanceof Function) {
    listener(msg);
  };
});

var SayHelloASync = function (message, callback) {
  var _msg = {
    cmd: "SayHello",
    message: message
  }
  listener = callback;
  extension.postMessage(_msg);
}

var SayHelloSync = function (message) {
  var _msg = {
    cmd: "SayHello",
    message: message
  }
  extension.internal.sendSyncMessage(_msg);
}

var DotNet = function () {
};


DotNet.prototype = new Object();
DotNet.prototype.constructor = DotNet;
DotNet.prototype.SayHelloASync = SayHelloASync;
DotNet.prototype.SayHelloSync = SayHelloSync;

exports = new DotNet();
