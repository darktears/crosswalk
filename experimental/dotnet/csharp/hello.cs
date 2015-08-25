using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace XWalk.ClrAssembly
{
  public class Hello
  {
    [DllImport("xwalk_mixeddll.dll")]
    static public extern void CallPostMessageToJS(IntPtr pointer, string message);

    public Hello(IntPtr parent)
    {
      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);
      System.Console.WriteLine("Created .NET Instance!");
      nativeObject = parent;
    }

    public void SayHelloSync(string message)
    {
      DialogBox dialog = new DialogBox(this);
      dialog.showDialogSync(message);
    }
    public void SayHelloASync(string message)
    {
      DialogBox dialog = new DialogBox(this);
      dialog.showDialogASync(message);
      //MessageBox.Show(message, "I'm a dialog created with .NET");
    }

    public void PostMessageToJS(string message)
    {
      System.Console.WriteLine("Posting message to JS!");
      CallPostMessageToJS(nativeObject, message);
    }

    private IntPtr nativeObject;
  }
}
