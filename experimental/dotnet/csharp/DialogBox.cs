using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace xwalk.experimental
{
  public partial class DialogBox : Form
  {
    public DialogBox(Hello main)
    {
      parent = main;
      InitializeComponent();
    }

    public void setLabel(string message) {
      this.message.Text = message;
    }

    public void showDialogASync(string message)
    {
      this.label1.Visible = true;
      this.textBox1.Visible = true;
      this.sendButton.Visible = true;
      setLabel(message);
      ShowDialog();
    }
    public void showDialogSync(string message)
    {
      this.label1.Visible = false;
      this.textBox1.Visible = false;
      this.sendButton.Visible = false;
      setLabel(message);
      ShowDialog();
    }

    private void sendButton_Click(object sender, EventArgs e)
    {
      if (this.textBox1.Text.Length == 0)
        return;
      parent.PostMessageToJS(this.textBox1.Text);
      Close();
    }

    private Hello parent;
  }
}
