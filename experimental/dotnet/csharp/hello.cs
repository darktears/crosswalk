using System;
using System.Reflection;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace xwalk.experimental
{
  public class Hello
  {
    public Hello()
    {
      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);
      System.Console.WriteLine("Created .NET Instance!");
    }

    public void setCallback(object obj) {
      nativeCallback = obj;
    }

    public void SayHelloASync(string message)
    {
      DialogBox dialog = new DialogBox(this);
      dialog.showDialogASync(message);
    }

    public void PostMessageToJS(string message)
    {
      System.Console.WriteLine("Posting message to JS!");
      Type callbackType = nativeCallback.GetType();
      MethodInfo callbackMethod = callbackType.GetMethod("PostMessageToJS");
      callbackMethod.Invoke(nativeCallback, new object[1] { message });
    }
    private object nativeCallback;
  }
}
