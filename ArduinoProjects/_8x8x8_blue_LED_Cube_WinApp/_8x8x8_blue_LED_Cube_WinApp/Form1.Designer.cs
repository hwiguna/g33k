namespace _8x8x8_blue_LED_Cube_WinApp
{
    partial class Form1
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
            this.BonkButton = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.OffButton = new System.Windows.Forms.Button();
            this.AnimateBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // BonkButton
            // 
            this.BonkButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.BonkButton.Location = new System.Drawing.Point(13, 13);
            this.BonkButton.Name = "BonkButton";
            this.BonkButton.Size = new System.Drawing.Size(558, 23);
            this.BonkButton.TabIndex = 0;
            this.BonkButton.Text = "Bonk";
            this.BonkButton.UseVisualStyleBackColor = true;
            this.BonkButton.Click += new System.EventHandler(this.BonkButton_Click);
            // 
            // textBox1
            // 
            this.textBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox1.Location = new System.Drawing.Point(13, 101);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(558, 801);
            this.textBox1.TabIndex = 1;
            // 
            // OffButton
            // 
            this.OffButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.OffButton.Location = new System.Drawing.Point(12, 42);
            this.OffButton.Name = "OffButton";
            this.OffButton.Size = new System.Drawing.Size(558, 23);
            this.OffButton.TabIndex = 2;
            this.OffButton.Text = "OFF";
            this.OffButton.UseVisualStyleBackColor = true;
            this.OffButton.Click += new System.EventHandler(this.OffButton_Click);
            // 
            // AnimateBtn
            // 
            this.AnimateBtn.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.AnimateBtn.Location = new System.Drawing.Point(12, 72);
            this.AnimateBtn.Name = "AnimateBtn";
            this.AnimateBtn.Size = new System.Drawing.Size(558, 23);
            this.AnimateBtn.TabIndex = 3;
            this.AnimateBtn.Text = "Animate";
            this.AnimateBtn.UseVisualStyleBackColor = true;
            this.AnimateBtn.Click += new System.EventHandler(this.AnimateBtn_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(583, 914);
            this.Controls.Add(this.AnimateBtn);
            this.Controls.Add(this.OffButton);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.BonkButton);
            this.Name = "Form1";
            this.Text = "Cube WinApp";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_Closing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyDown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button BonkButton;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button OffButton;
        private System.Windows.Forms.Button AnimateBtn;
    }
}

