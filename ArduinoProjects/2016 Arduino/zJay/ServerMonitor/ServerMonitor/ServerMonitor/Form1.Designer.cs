namespace PCNanny
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
            this.components = new System.ComponentModel.Container();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.label1 = new System.Windows.Forms.Label();
            this.ip1 = new System.Windows.Forms.Label();
            this.powerButton1 = new System.Windows.Forms.Button();
            this.resetButton1 = new System.Windows.Forms.Button();
            this.Temperature1 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.label5 = new System.Windows.Forms.Label();
            this.ip2 = new System.Windows.Forms.Label();
            this.powerButton2 = new System.Windows.Forms.Button();
            this.resetButton2 = new System.Windows.Forms.Button();
            this.Temperature2 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.label9 = new System.Windows.Forms.Label();
            this.ip3 = new System.Windows.Forms.Label();
            this.powerButton3 = new System.Windows.Forms.Button();
            this.resetButton3 = new System.Windows.Forms.Button();
            this.Temperature3 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.label13 = new System.Windows.Forms.Label();
            this.ip4 = new System.Windows.Forms.Label();
            this.powerButton4 = new System.Windows.Forms.Button();
            this.resetButton4 = new System.Windows.Forms.Button();
            this.Temperature4 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Font = new System.Drawing.Font("Minecrafter", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tabControl1.Location = new System.Drawing.Point(12, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(543, 167);
            this.tabControl1.TabIndex = 9;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Controls.Add(this.ip1);
            this.tabPage1.Controls.Add(this.powerButton1);
            this.tabPage1.Controls.Add(this.resetButton1);
            this.tabPage1.Controls.Add(this.Temperature1);
            this.tabPage1.Controls.Add(this.label4);
            this.tabPage1.Location = new System.Drawing.Point(4, 24);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(535, 139);
            this.tabPage1.TabIndex = 1;
            this.tabPage1.Text = "Server 01 ";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(71, 11);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(162, 21);
            this.label1.TabIndex = 22;
            this.label1.Text = "IP Address";
            // 
            // ip1
            // 
            this.ip1.AutoSize = true;
            this.ip1.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ip1.Location = new System.Drawing.Point(239, 11);
            this.ip1.Name = "ip1";
            this.ip1.Size = new System.Drawing.Size(205, 21);
            this.ip1.TabIndex = 21;
            this.ip1.Text = "192.168.255.251";
            // 
            // powerButton1
            // 
            this.powerButton1.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.powerButton1.Location = new System.Drawing.Point(243, 83);
            this.powerButton1.Name = "powerButton1";
            this.powerButton1.Size = new System.Drawing.Size(122, 45);
            this.powerButton1.TabIndex = 20;
            this.powerButton1.Text = "Power";
            this.powerButton1.UseVisualStyleBackColor = true;
            this.powerButton1.Click += new System.EventHandler(this.powerButton1_Click);
            // 
            // resetButton1
            // 
            this.resetButton1.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.resetButton1.Location = new System.Drawing.Point(371, 83);
            this.resetButton1.Name = "resetButton1";
            this.resetButton1.Size = new System.Drawing.Size(122, 45);
            this.resetButton1.TabIndex = 19;
            this.resetButton1.Text = "Reset";
            this.resetButton1.UseVisualStyleBackColor = true;
            this.resetButton1.Click += new System.EventHandler(this.resetButton1_Click);
            // 
            // Temperature1
            // 
            this.Temperature1.AutoSize = true;
            this.Temperature1.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Temperature1.Location = new System.Drawing.Point(239, 47);
            this.Temperature1.Name = "Temperature1";
            this.Temperature1.Size = new System.Drawing.Size(40, 21);
            this.Temperature1.TabIndex = 18;
            this.Temperature1.Text = "???";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(41, 47);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(192, 21);
            this.label4.TabIndex = 17;
            this.label4.Text = "Temperature";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.label5);
            this.tabPage2.Controls.Add(this.ip2);
            this.tabPage2.Controls.Add(this.powerButton2);
            this.tabPage2.Controls.Add(this.resetButton2);
            this.tabPage2.Controls.Add(this.Temperature2);
            this.tabPage2.Controls.Add(this.label8);
            this.tabPage2.Location = new System.Drawing.Point(4, 24);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Size = new System.Drawing.Size(535, 139);
            this.tabPage2.TabIndex = 2;
            this.tabPage2.Text = "Server 02 ";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(71, 11);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(162, 21);
            this.label5.TabIndex = 16;
            this.label5.Text = "IP Address";
            // 
            // ip2
            // 
            this.ip2.AutoSize = true;
            this.ip2.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ip2.Location = new System.Drawing.Point(239, 11);
            this.ip2.Name = "ip2";
            this.ip2.Size = new System.Drawing.Size(212, 21);
            this.ip2.TabIndex = 15;
            this.ip2.Text = "192.168.255.252";
            // 
            // powerButton2
            // 
            this.powerButton2.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.powerButton2.Location = new System.Drawing.Point(243, 83);
            this.powerButton2.Name = "powerButton2";
            this.powerButton2.Size = new System.Drawing.Size(122, 45);
            this.powerButton2.TabIndex = 14;
            this.powerButton2.Text = "Power";
            this.powerButton2.UseVisualStyleBackColor = true;
            this.powerButton2.Click += new System.EventHandler(this.powerButton2_Click);
            // 
            // resetButton2
            // 
            this.resetButton2.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.resetButton2.Location = new System.Drawing.Point(371, 83);
            this.resetButton2.Name = "resetButton2";
            this.resetButton2.Size = new System.Drawing.Size(122, 45);
            this.resetButton2.TabIndex = 13;
            this.resetButton2.Text = "Reset";
            this.resetButton2.UseVisualStyleBackColor = true;
            this.resetButton2.Click += new System.EventHandler(this.resetButton2_Click);
            // 
            // Temperature2
            // 
            this.Temperature2.AutoSize = true;
            this.Temperature2.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Temperature2.Location = new System.Drawing.Point(239, 47);
            this.Temperature2.Name = "Temperature2";
            this.Temperature2.Size = new System.Drawing.Size(40, 21);
            this.Temperature2.TabIndex = 12;
            this.Temperature2.Text = "???";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(41, 47);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(192, 21);
            this.label8.TabIndex = 11;
            this.label8.Text = "Temperature";
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.label9);
            this.tabPage3.Controls.Add(this.ip3);
            this.tabPage3.Controls.Add(this.powerButton3);
            this.tabPage3.Controls.Add(this.resetButton3);
            this.tabPage3.Controls.Add(this.Temperature3);
            this.tabPage3.Controls.Add(this.label12);
            this.tabPage3.Location = new System.Drawing.Point(4, 24);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(535, 139);
            this.tabPage3.TabIndex = 3;
            this.tabPage3.Text = "Server 03 ";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(71, 11);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(162, 21);
            this.label9.TabIndex = 16;
            this.label9.Text = "IP Address";
            // 
            // ip3
            // 
            this.ip3.AutoSize = true;
            this.ip3.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ip3.Location = new System.Drawing.Point(239, 11);
            this.ip3.Name = "ip3";
            this.ip3.Size = new System.Drawing.Size(211, 21);
            this.ip3.TabIndex = 15;
            this.ip3.Text = "192.168.255.253";
            // 
            // powerButton3
            // 
            this.powerButton3.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.powerButton3.Location = new System.Drawing.Point(243, 83);
            this.powerButton3.Name = "powerButton3";
            this.powerButton3.Size = new System.Drawing.Size(122, 45);
            this.powerButton3.TabIndex = 14;
            this.powerButton3.Text = "Power";
            this.powerButton3.UseVisualStyleBackColor = true;
            this.powerButton3.Click += new System.EventHandler(this.powerButton3_Click);
            // 
            // resetButton3
            // 
            this.resetButton3.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.resetButton3.Location = new System.Drawing.Point(371, 83);
            this.resetButton3.Name = "resetButton3";
            this.resetButton3.Size = new System.Drawing.Size(122, 45);
            this.resetButton3.TabIndex = 13;
            this.resetButton3.Text = "Reset";
            this.resetButton3.UseVisualStyleBackColor = true;
            this.resetButton3.Click += new System.EventHandler(this.resetButton3_Click);
            // 
            // Temperature3
            // 
            this.Temperature3.AutoSize = true;
            this.Temperature3.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Temperature3.Location = new System.Drawing.Point(239, 47);
            this.Temperature3.Name = "Temperature3";
            this.Temperature3.Size = new System.Drawing.Size(40, 21);
            this.Temperature3.TabIndex = 12;
            this.Temperature3.Text = "???";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label12.Location = new System.Drawing.Point(41, 47);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(192, 21);
            this.label12.TabIndex = 11;
            this.label12.Text = "Temperature";
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.label13);
            this.tabPage4.Controls.Add(this.ip4);
            this.tabPage4.Controls.Add(this.powerButton4);
            this.tabPage4.Controls.Add(this.resetButton4);
            this.tabPage4.Controls.Add(this.Temperature4);
            this.tabPage4.Controls.Add(this.label16);
            this.tabPage4.Location = new System.Drawing.Point(4, 24);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(535, 139);
            this.tabPage4.TabIndex = 4;
            this.tabPage4.Text = "Server 04 ";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label13.Location = new System.Drawing.Point(71, 11);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(162, 21);
            this.label13.TabIndex = 16;
            this.label13.Text = "IP Address";
            // 
            // ip4
            // 
            this.ip4.AutoSize = true;
            this.ip4.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ip4.Location = new System.Drawing.Point(239, 11);
            this.ip4.Name = "ip4";
            this.ip4.Size = new System.Drawing.Size(211, 21);
            this.ip4.TabIndex = 15;
            this.ip4.Text = "192.168.255.254";
            // 
            // powerButton4
            // 
            this.powerButton4.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.powerButton4.Location = new System.Drawing.Point(243, 83);
            this.powerButton4.Name = "powerButton4";
            this.powerButton4.Size = new System.Drawing.Size(122, 45);
            this.powerButton4.TabIndex = 14;
            this.powerButton4.Text = "Power";
            this.powerButton4.UseVisualStyleBackColor = true;
            this.powerButton4.Click += new System.EventHandler(this.powerButton4_Click);
            // 
            // resetButton4
            // 
            this.resetButton4.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.resetButton4.Location = new System.Drawing.Point(371, 83);
            this.resetButton4.Name = "resetButton4";
            this.resetButton4.Size = new System.Drawing.Size(122, 45);
            this.resetButton4.TabIndex = 13;
            this.resetButton4.Text = "Reset";
            this.resetButton4.UseVisualStyleBackColor = true;
            this.resetButton4.Click += new System.EventHandler(this.resetButton4_Click);
            // 
            // Temperature4
            // 
            this.Temperature4.AutoSize = true;
            this.Temperature4.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Temperature4.Location = new System.Drawing.Point(239, 47);
            this.Temperature4.Name = "Temperature4";
            this.Temperature4.Size = new System.Drawing.Size(40, 21);
            this.Temperature4.TabIndex = 12;
            this.Temperature4.Text = "???";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Font = new System.Drawing.Font("Minecrafter", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label16.Location = new System.Drawing.Point(41, 47);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(192, 21);
            this.label16.TabIndex = 11;
            this.label16.Text = "Temperature";
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ControlDark;
            this.ClientSize = new System.Drawing.Size(571, 191);
            this.Controls.Add(this.tabControl1);
            this.Name = "Form1";
            this.Text = "Server Monitor";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.tabPage4.ResumeLayout(false);
            this.tabPage4.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label ip2;
        private System.Windows.Forms.Button powerButton2;
        private System.Windows.Forms.Button resetButton2;
        private System.Windows.Forms.Label Temperature2;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label ip3;
        private System.Windows.Forms.Button powerButton3;
        private System.Windows.Forms.Button resetButton3;
        private System.Windows.Forms.Label Temperature3;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label ip4;
        private System.Windows.Forms.Button powerButton4;
        private System.Windows.Forms.Button resetButton4;
        private System.Windows.Forms.Label Temperature4;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label ip1;
        private System.Windows.Forms.Button powerButton1;
        private System.Windows.Forms.Button resetButton1;
        private System.Windows.Forms.Label Temperature1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Timer timer1;
    }
}

