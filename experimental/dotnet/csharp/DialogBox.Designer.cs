namespace xwalk.experimental
{
  partial class DialogBox
  {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
      if (disposing && (components != null))
      {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.Label = new System.Windows.Forms.Label();
      this.textBox1 = new System.Windows.Forms.TextBox();
      this.message = new System.Windows.Forms.Label();
      this.title = new System.Windows.Forms.Label();
      this.label1 = new System.Windows.Forms.Label();
      this.sendButton = new System.Windows.Forms.Button();
      this.SuspendLayout();
      //
      // Label
      //
      this.Label.AutoSize = true;
      this.Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.Label.Location = new System.Drawing.Point(12, 85);
      this.Label.Name = "Label";
      this.Label.Size = new System.Drawing.Size(288, 17);
      this.Label.TabIndex = 0;
      this.Label.Text = "We received this message from JavaScript : ";
      //
      // textBox1
      //
      this.textBox1.Location = new System.Drawing.Point(311, 140);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new System.Drawing.Size(100, 20);
      this.textBox1.TabIndex = 1;
      //
      // message
      //
      this.message.AutoSize = true;
      this.message.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.message.ForeColor = System.Drawing.Color.Red;
      this.message.Location = new System.Drawing.Point(307, 82);
      this.message.Name = "message";
      this.message.Size = new System.Drawing.Size(60, 24);
      this.message.TabIndex = 2;
      this.message.Text = "label1";
      //
      // title
      //
      this.title.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.title.Location = new System.Drawing.Point(12, 13);
      this.title.Name = "title";
      this.title.Size = new System.Drawing.Size(423, 72);
      this.title.TabIndex = 3;
      this.title.Text = "I\'m an ugly .Net Dialog, no kidding";
      //
      // label1
      //
      this.label1.AutoSize = true;
      this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label1.Location = new System.Drawing.Point(12, 140);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(292, 17);
      this.label1.TabIndex = 4;
      this.label1.Text = "What would you like to answer to JavaScript?";
      //
      // sendButton
      //
      this.sendButton.Location = new System.Drawing.Point(417, 138);
      this.sendButton.Name = "sendButton";
      this.sendButton.Size = new System.Drawing.Size(75, 23);
      this.sendButton.TabIndex = 5;
      this.sendButton.Text = "Send";
      this.sendButton.UseVisualStyleBackColor = true;
      this.sendButton.Click += new System.EventHandler(this.sendButton_Click);
      //
      // DialogBox
      //
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(504, 198);
      this.Controls.Add(this.sendButton);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.title);
      this.Controls.Add(this.message);
      this.Controls.Add(this.textBox1);
      this.Controls.Add(this.Label);
      this.Name = "DialogBox";
      this.Text = ".NET Dialog";
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Label Label;
    private System.Windows.Forms.TextBox textBox1;
    private System.Windows.Forms.Label message;
    private System.Windows.Forms.Label title;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Button sendButton;
  }
}
