namespace LearnSerialPort
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.output = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.UploadButton = new System.Windows.Forms.Button();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.FilePathTextbox = new System.Windows.Forms.TextBox();
            this.CommandTextbox = new System.Windows.Forms.TextBox();
            this.ExecuteButton = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.PortTextbox = new System.Windows.Forms.TextBox();
            this.BrowseButton = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.BaudRateBox = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.LineDelayTextbox = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.LuaCodeTextbox = new System.Windows.Forms.TextBox();
            this.SaveOnESPButton = new System.Windows.Forms.Button();
            this.LuaFilenameTextbox = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.RestartButton = new System.Windows.Forms.Button();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.RunAfterSaving = new System.Windows.Forms.CheckBox();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.label4 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.LoadFromESPButton = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // output
            // 
            this.output.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.output.Location = new System.Drawing.Point(6, 19);
            this.output.Multiline = true;
            this.output.Name = "output";
            this.output.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.output.Size = new System.Drawing.Size(388, 620);
            this.output.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(2, 11);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Lua File:";
            // 
            // UploadButton
            // 
            this.UploadButton.Location = new System.Drawing.Point(55, 34);
            this.UploadButton.Name = "UploadButton";
            this.UploadButton.Size = new System.Drawing.Size(100, 23);
            this.UploadButton.TabIndex = 9;
            this.UploadButton.Text = "Upload";
            this.UploadButton.UseVisualStyleBackColor = true;
            this.UploadButton.Click += new System.EventHandler(this.UploadButton_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // FilePathTextbox
            // 
            this.FilePathTextbox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.FilePathTextbox.Location = new System.Drawing.Point(55, 8);
            this.FilePathTextbox.Name = "FilePathTextbox";
            this.FilePathTextbox.Size = new System.Drawing.Size(538, 20);
            this.FilePathTextbox.TabIndex = 10;
            // 
            // CommandTextbox
            // 
            this.CommandTextbox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.CommandTextbox.Location = new System.Drawing.Point(6, 35);
            this.CommandTextbox.Multiline = true;
            this.CommandTextbox.Name = "CommandTextbox";
            this.CommandTextbox.Size = new System.Drawing.Size(680, 578);
            this.CommandTextbox.TabIndex = 13;
            this.CommandTextbox.Text = "dofile(\"door.lua\")";
            // 
            // ExecuteButton
            // 
            this.ExecuteButton.Location = new System.Drawing.Point(6, 6);
            this.ExecuteButton.Name = "ExecuteButton";
            this.ExecuteButton.Size = new System.Drawing.Size(100, 23);
            this.ExecuteButton.TabIndex = 12;
            this.ExecuteButton.Text = "Execute";
            this.ExecuteButton.UseVisualStyleBackColor = true;
            this.ExecuteButton.Click += new System.EventHandler(this.ExecuteButton_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 20);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(26, 13);
            this.label3.TabIndex = 14;
            this.label3.Text = "Port";
            // 
            // PortTextbox
            // 
            this.PortTextbox.Location = new System.Drawing.Point(38, 18);
            this.PortTextbox.Name = "PortTextbox";
            this.PortTextbox.Size = new System.Drawing.Size(56, 20);
            this.PortTextbox.TabIndex = 15;
            this.PortTextbox.Text = "COM1";
            // 
            // BrowseButton
            // 
            this.BrowseButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.BrowseButton.Location = new System.Drawing.Point(599, 6);
            this.BrowseButton.Name = "BrowseButton";
            this.BrowseButton.Size = new System.Drawing.Size(90, 23);
            this.BrowseButton.TabIndex = 16;
            this.BrowseButton.Text = "Browse";
            this.BrowseButton.UseVisualStyleBackColor = true;
            this.BrowseButton.Click += new System.EventHandler(this.Browse_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(121, 21);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(31, 13);
            this.label5.TabIndex = 19;
            this.label5.Text = "baud";
            // 
            // BaudRateBox
            // 
            this.BaudRateBox.FormattingEnabled = true;
            this.BaudRateBox.Items.AddRange(new object[] {
            "9600",
            "14400",
            "19200",
            "28800",
            "38400",
            "57600",
            "115200"});
            this.BaudRateBox.Location = new System.Drawing.Point(158, 17);
            this.BaudRateBox.Name = "BaudRateBox";
            this.BaudRateBox.Size = new System.Drawing.Size(70, 21);
            this.BaudRateBox.TabIndex = 20;
            this.BaudRateBox.Text = "9600";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(256, 21);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(57, 13);
            this.label6.TabIndex = 21;
            this.label6.Text = "Line Delay";
            // 
            // LineDelayTextbox
            // 
            this.LineDelayTextbox.Location = new System.Drawing.Point(319, 18);
            this.LineDelayTextbox.Name = "LineDelayTextbox";
            this.LineDelayTextbox.Size = new System.Drawing.Size(56, 20);
            this.LineDelayTextbox.TabIndex = 22;
            this.LineDelayTextbox.Text = "200";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(381, 21);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(20, 13);
            this.label7.TabIndex = 23;
            this.label7.Text = "ms";
            // 
            // LuaCodeTextbox
            // 
            this.LuaCodeTextbox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.LuaCodeTextbox.Location = new System.Drawing.Point(9, 58);
            this.LuaCodeTextbox.Multiline = true;
            this.LuaCodeTextbox.Name = "LuaCodeTextbox";
            this.LuaCodeTextbox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.LuaCodeTextbox.Size = new System.Drawing.Size(677, 555);
            this.LuaCodeTextbox.TabIndex = 24;
            this.LuaCodeTextbox.Text = resources.GetString("LuaCodeTextbox.Text");
            this.LuaCodeTextbox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.LuaCodeTextbox_keyDown);
            // 
            // SaveOnESPButton
            // 
            this.SaveOnESPButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.SaveOnESPButton.Location = new System.Drawing.Point(230, 6);
            this.SaveOnESPButton.Name = "SaveOnESPButton";
            this.SaveOnESPButton.Size = new System.Drawing.Size(100, 23);
            this.SaveOnESPButton.TabIndex = 25;
            this.SaveOnESPButton.Text = "Save on ESP";
            this.SaveOnESPButton.UseVisualStyleBackColor = true;
            this.SaveOnESPButton.Click += new System.EventHandler(this.SaveOnESPButton_Click);
            // 
            // LuaFilenameTextbox
            // 
            this.LuaFilenameTextbox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.LuaFilenameTextbox.Location = new System.Drawing.Point(64, 8);
            this.LuaFilenameTextbox.Name = "LuaFilenameTextbox";
            this.LuaFilenameTextbox.Size = new System.Drawing.Size(160, 20);
            this.LuaFilenameTextbox.TabIndex = 26;
            this.LuaFilenameTextbox.Text = "door.lua";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 11);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(52, 13);
            this.label8.TabIndex = 27;
            this.label8.Text = "Filename:";
            // 
            // groupBox1
            // 
            this.groupBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox1.Controls.Add(this.RestartButton);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.PortTextbox);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.BaudRateBox);
            this.groupBox1.Controls.Add(this.LineDelayTextbox);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Location = new System.Drawing.Point(13, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(1114, 49);
            this.groupBox1.TabIndex = 28;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Communication";
            // 
            // RestartButton
            // 
            this.RestartButton.Location = new System.Drawing.Point(432, 15);
            this.RestartButton.Name = "RestartButton";
            this.RestartButton.Size = new System.Drawing.Size(100, 23);
            this.RestartButton.TabIndex = 14;
            this.RestartButton.Text = "Restart";
            this.RestartButton.UseVisualStyleBackColor = true;
            this.RestartButton.Click += new System.EventHandler(this.RestartButton_Click);
            // 
            // tabControl1
            // 
            this.tabControl1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(13, 69);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(700, 645);
            this.tabControl1.TabIndex = 29;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.LoadFromESPButton);
            this.tabPage1.Controls.Add(this.RunAfterSaving);
            this.tabPage1.Controls.Add(this.label8);
            this.tabPage1.Controls.Add(this.SaveOnESPButton);
            this.tabPage1.Controls.Add(this.LuaCodeTextbox);
            this.tabPage1.Controls.Add(this.LuaFilenameTextbox);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(692, 619);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Editor";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // RunAfterSaving
            // 
            this.RunAfterSaving.AutoSize = true;
            this.RunAfterSaving.Checked = true;
            this.RunAfterSaving.CheckState = System.Windows.Forms.CheckState.Checked;
            this.RunAfterSaving.Location = new System.Drawing.Point(64, 35);
            this.RunAfterSaving.Name = "RunAfterSaving";
            this.RunAfterSaving.Size = new System.Drawing.Size(104, 17);
            this.RunAfterSaving.TabIndex = 28;
            this.RunAfterSaving.Text = "Run after saving";
            this.RunAfterSaving.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.label4);
            this.tabPage2.Controls.Add(this.label2);
            this.tabPage2.Controls.Add(this.CommandTextbox);
            this.tabPage2.Controls.Add(this.ExecuteButton);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(692, 619);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Immediate";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(151, 11);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(45, 13);
            this.label4.TabIndex = 23;
            this.label4.Text = "Macros:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(202, 11);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(42, 13);
            this.label2.TabIndex = 22;
            this.label2.Text = "File List";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.label1);
            this.tabPage3.Controls.Add(this.FilePathTextbox);
            this.tabPage3.Controls.Add(this.UploadButton);
            this.tabPage3.Controls.Add(this.BrowseButton);
            this.tabPage3.Location = new System.Drawing.Point(4, 22);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(692, 619);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "Upload";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.output);
            this.groupBox2.Location = new System.Drawing.Point(727, 69);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(400, 645);
            this.groupBox2.TabIndex = 30;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Output";
            // 
            // LoadFromESPButton
            // 
            this.LoadFromESPButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.LoadFromESPButton.Location = new System.Drawing.Point(336, 6);
            this.LoadFromESPButton.Name = "LoadFromESPButton";
            this.LoadFromESPButton.Size = new System.Drawing.Size(100, 23);
            this.LoadFromESPButton.TabIndex = 29;
            this.LoadFromESPButton.Text = "Load from ESP";
            this.LoadFromESPButton.UseVisualStyleBackColor = true;
            this.LoadFromESPButton.Click += new System.EventHandler(this.LoadFromESPButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1139, 726);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Lua Uploader - Hari Wiguna 2014";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TextBox output;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button UploadButton;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.TextBox FilePathTextbox;
        private System.Windows.Forms.TextBox CommandTextbox;
        private System.Windows.Forms.Button ExecuteButton;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox PortTextbox;
        private System.Windows.Forms.Button BrowseButton;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox BaudRateBox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox LineDelayTextbox;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox LuaCodeTextbox;
        private System.Windows.Forms.Button SaveOnESPButton;
        private System.Windows.Forms.TextBox LuaFilenameTextbox;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button RestartButton;
        private System.Windows.Forms.CheckBox RunAfterSaving;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button LoadFromESPButton;
    }
}

