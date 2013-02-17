namespace Packer
{
    partial class Packer
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
            this.btnClear = new System.Windows.Forms.Button();
            this.btnPack = new System.Windows.Forms.Button();
            this.btnDelete = new System.Windows.Forms.Button();
            this.listBoxFiles = new System.Windows.Forms.ListBox();
            this.textBoxOutput = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btnBrowse = new System.Windows.Forms.Button();
            this.btnNone = new System.Windows.Forms.Button();
            this.btnAll = new System.Windows.Forms.Button();
            this.btnInvert = new System.Windows.Forms.Button();
            this.cbEncrypt = new System.Windows.Forms.CheckBox();
            this.cbCompress = new System.Windows.Forms.CheckBox();
            this.textBoxPlugin = new System.Windows.Forms.TextBox();
            this.btnPlugin = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.textBoxParam = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.btnUpdate = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnClear
            // 
            this.btnClear.Location = new System.Drawing.Point(457, 469);
            this.btnClear.Name = "btnClear";
            this.btnClear.Size = new System.Drawing.Size(98, 28);
            this.btnClear.TabIndex = 1;
            this.btnClear.Text = "&Clear";
            this.btnClear.UseVisualStyleBackColor = true;
            this.btnClear.Click += new System.EventHandler(this.btnClear_Click);
            // 
            // btnPack
            // 
            this.btnPack.Location = new System.Drawing.Point(561, 469);
            this.btnPack.Name = "btnPack";
            this.btnPack.Size = new System.Drawing.Size(98, 28);
            this.btnPack.TabIndex = 1;
            this.btnPack.Text = "&Pack";
            this.btnPack.UseVisualStyleBackColor = true;
            this.btnPack.Click += new System.EventHandler(this.btnPack_Click);
            // 
            // btnDelete
            // 
            this.btnDelete.Location = new System.Drawing.Point(353, 469);
            this.btnDelete.Name = "btnDelete";
            this.btnDelete.Size = new System.Drawing.Size(98, 28);
            this.btnDelete.TabIndex = 1;
            this.btnDelete.Text = "&Remove";
            this.btnDelete.UseVisualStyleBackColor = true;
            this.btnDelete.Click += new System.EventHandler(this.btnDelete_Click);
            // 
            // listBoxFiles
            // 
            this.listBoxFiles.FormattingEnabled = true;
            this.listBoxFiles.Location = new System.Drawing.Point(12, 179);
            this.listBoxFiles.Name = "listBoxFiles";
            this.listBoxFiles.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.listBoxFiles.Size = new System.Drawing.Size(647, 277);
            this.listBoxFiles.TabIndex = 2;
            this.listBoxFiles.SelectedIndexChanged += new System.EventHandler(this.listBoxFiles_SelectedIndexChanged);
            // 
            // textBoxOutput
            // 
            this.textBoxOutput.AcceptsTab = true;
            this.textBoxOutput.AllowDrop = true;
            this.textBoxOutput.Location = new System.Drawing.Point(12, 25);
            this.textBoxOutput.MaxLength = 260;
            this.textBoxOutput.Name = "textBoxOutput";
            this.textBoxOutput.Size = new System.Drawing.Size(543, 20);
            this.textBoxOutput.TabIndex = 3;
            this.textBoxOutput.DragDrop += new System.Windows.Forms.DragEventHandler(this.textBoxOutput_DragDrop);
            this.textBoxOutput.DragEnter += new System.Windows.Forms.DragEventHandler(this.Packer_DragEnter);
            // 
            // label1
            // 
            this.label1.AllowDrop = true;
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(39, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Output";
            // 
            // btnBrowse
            // 
            this.btnBrowse.Location = new System.Drawing.Point(561, 20);
            this.btnBrowse.Name = "btnBrowse";
            this.btnBrowse.Size = new System.Drawing.Size(98, 28);
            this.btnBrowse.TabIndex = 1;
            this.btnBrowse.Text = "&Browse";
            this.btnBrowse.UseVisualStyleBackColor = true;
            this.btnBrowse.Click += new System.EventHandler(this.btnBrowse_Click);
            // 
            // btnNone
            // 
            this.btnNone.Location = new System.Drawing.Point(116, 469);
            this.btnNone.Name = "btnNone";
            this.btnNone.Size = new System.Drawing.Size(98, 28);
            this.btnNone.TabIndex = 1;
            this.btnNone.Text = "&None";
            this.btnNone.UseVisualStyleBackColor = true;
            this.btnNone.Click += new System.EventHandler(this.btnNone_Click);
            // 
            // btnAll
            // 
            this.btnAll.Location = new System.Drawing.Point(12, 469);
            this.btnAll.Name = "btnAll";
            this.btnAll.Size = new System.Drawing.Size(98, 28);
            this.btnAll.TabIndex = 1;
            this.btnAll.Text = "&All";
            this.btnAll.UseVisualStyleBackColor = true;
            this.btnAll.Click += new System.EventHandler(this.btnAll_Click);
            // 
            // btnInvert
            // 
            this.btnInvert.Location = new System.Drawing.Point(220, 469);
            this.btnInvert.Name = "btnInvert";
            this.btnInvert.Size = new System.Drawing.Size(98, 28);
            this.btnInvert.TabIndex = 1;
            this.btnInvert.Text = "&Invert";
            this.btnInvert.UseVisualStyleBackColor = true;
            this.btnInvert.Click += new System.EventHandler(this.btnInvert_Click);
            // 
            // cbEncrypt
            // 
            this.cbEncrypt.Appearance = System.Windows.Forms.Appearance.Button;
            this.cbEncrypt.AutoSize = true;
            this.cbEncrypt.Location = new System.Drawing.Point(12, 150);
            this.cbEncrypt.Name = "cbEncrypt";
            this.cbEncrypt.Size = new System.Drawing.Size(53, 23);
            this.cbEncrypt.TabIndex = 6;
            this.cbEncrypt.Text = "&Encrypt";
            this.cbEncrypt.UseVisualStyleBackColor = true;
            this.cbEncrypt.CheckedChanged += new System.EventHandler(this.cbEncrypt_CheckedChanged);
            // 
            // cbCompress
            // 
            this.cbCompress.Appearance = System.Windows.Forms.Appearance.Button;
            this.cbCompress.AutoSize = true;
            this.cbCompress.Location = new System.Drawing.Point(71, 150);
            this.cbCompress.Name = "cbCompress";
            this.cbCompress.Size = new System.Drawing.Size(63, 23);
            this.cbCompress.TabIndex = 6;
            this.cbCompress.Text = "Co&mpress";
            this.cbCompress.UseVisualStyleBackColor = true;
            this.cbCompress.CheckedChanged += new System.EventHandler(this.cbCompress_CheckedChanged);
            // 
            // textBoxPlugin
            // 
            this.textBoxPlugin.AcceptsTab = true;
            this.textBoxPlugin.AllowDrop = true;
            this.textBoxPlugin.Location = new System.Drawing.Point(12, 68);
            this.textBoxPlugin.MaxLength = 260;
            this.textBoxPlugin.Name = "textBoxPlugin";
            this.textBoxPlugin.Size = new System.Drawing.Size(543, 20);
            this.textBoxPlugin.TabIndex = 3;
            this.textBoxPlugin.DragDrop += new System.Windows.Forms.DragEventHandler(this.textBoxOutput_DragDrop);
            this.textBoxPlugin.DragEnter += new System.Windows.Forms.DragEventHandler(this.Packer_DragEnter);
            // 
            // btnPlugin
            // 
            this.btnPlugin.Location = new System.Drawing.Point(561, 63);
            this.btnPlugin.Name = "btnPlugin";
            this.btnPlugin.Size = new System.Drawing.Size(98, 28);
            this.btnPlugin.TabIndex = 2;
            this.btnPlugin.Text = "&Browse";
            this.btnPlugin.UseVisualStyleBackColor = true;
            this.btnPlugin.Click += new System.EventHandler(this.btnBrowse_Click);
            // 
            // label2
            // 
            this.label2.AllowDrop = true;
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 52);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(36, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Plugin";
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(151, 152);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(507, 20);
            this.progressBar1.TabIndex = 7;
            // 
            // textBoxParam
            // 
            this.textBoxParam.AcceptsTab = true;
            this.textBoxParam.AllowDrop = true;
            this.textBoxParam.Location = new System.Drawing.Point(12, 113);
            this.textBoxParam.MaxLength = 260;
            this.textBoxParam.Name = "textBoxParam";
            this.textBoxParam.Size = new System.Drawing.Size(543, 20);
            this.textBoxParam.TabIndex = 3;
            this.textBoxParam.DragDrop += new System.Windows.Forms.DragEventHandler(this.textBoxOutput_DragDrop);
            this.textBoxParam.DragEnter += new System.Windows.Forms.DragEventHandler(this.Packer_DragEnter);
            // 
            // label3
            // 
            this.label3.AllowDrop = true;
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 97);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(55, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Parameter";
            // 
            // btnUpdate
            // 
            this.btnUpdate.Location = new System.Drawing.Point(561, 108);
            this.btnUpdate.Name = "btnUpdate";
            this.btnUpdate.Size = new System.Drawing.Size(98, 28);
            this.btnUpdate.TabIndex = 2;
            this.btnUpdate.Text = "&Update";
            this.btnUpdate.UseVisualStyleBackColor = true;
            this.btnUpdate.Click += new System.EventHandler(this.btnUpdate_Click);
            // 
            // Packer
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(671, 511);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.cbCompress);
            this.Controls.Add(this.cbEncrypt);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxParam);
            this.Controls.Add(this.textBoxPlugin);
            this.Controls.Add(this.textBoxOutput);
            this.Controls.Add(this.listBoxFiles);
            this.Controls.Add(this.btnUpdate);
            this.Controls.Add(this.btnPlugin);
            this.Controls.Add(this.btnBrowse);
            this.Controls.Add(this.btnPack);
            this.Controls.Add(this.btnAll);
            this.Controls.Add(this.btnInvert);
            this.Controls.Add(this.btnNone);
            this.Controls.Add(this.btnDelete);
            this.Controls.Add(this.btnClear);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "Packer";
            this.Text = "Packer";
            this.DragDrop += new System.Windows.Forms.DragEventHandler(this.Packer_DragDrop);
            this.DragEnter += new System.Windows.Forms.DragEventHandler(this.Packer_DragEnter);
            this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Packer_KeyUp);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Packer_FormClosing);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Packer_KeyDown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnClear;
        private System.Windows.Forms.Button btnPack;
        private System.Windows.Forms.Button btnDelete;
        private System.Windows.Forms.ListBox listBoxFiles;
        private System.Windows.Forms.TextBox textBoxOutput;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnBrowse;
        private System.Windows.Forms.Button btnNone;
        private System.Windows.Forms.Button btnAll;
        private System.Windows.Forms.Button btnInvert;
        private System.Windows.Forms.CheckBox cbEncrypt;
        private System.Windows.Forms.CheckBox cbCompress;
        private System.Windows.Forms.TextBox textBoxPlugin;
        private System.Windows.Forms.Button btnPlugin;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.TextBox textBoxParam;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btnUpdate;
    }
}

