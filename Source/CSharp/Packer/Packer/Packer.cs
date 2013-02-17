using System;
using System.IO;
using System.Data;
using System.Text;
using System.Collections;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;

namespace Packer
{
    public partial class Packer : Form
    {
        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        internal static extern IntPtr LoadLibraryExW([In, MarshalAs(UnmanagedType.LPWStr)] String lpFileName, IntPtr hFile, UInt32 dwFlags);
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        internal static extern IntPtr FreeLibrary([In] IntPtr hModule);
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        internal static extern IntPtr GetProcAddress([In] IntPtr hModule, [In, MarshalAs(UnmanagedType.LPStr)] string lpProcName);
        [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        internal static extern Int32 GetPrivateProfileStringW(String section, String key, String lpDefault, String retVal, int size, String filePath);

        Boolean EscDownHandled, NeedStop;
        String  FullInputPath, DefaultExtension;
        PackWorker Worker;
        Thread PackThread;

        [StructLayout(LayoutKind.Sequential, Pack=1)]
        public struct SPackFileInfo
        {
            public Int32  Encrypt;
            public Int32  Compress;
            [MarshalAs(UnmanagedType.LPWStr)] public String FileName;
        }

        ArrayList FileInfo = new ArrayList();

        delegate Boolean FShowStatus([In, MarshalAs(UnmanagedType.LPWStr)] String Status, Int32 Percent);
        delegate void FPackCallback(SPackFileInfo[] FileInfo,
                                    UInt32 Count,
                                    [In, MarshalAs(UnmanagedType.LPWStr)] String OutputFile,
                                    [In, MarshalAs(UnmanagedType.LPWStr)] String PathOfFiles,
                                    [In, MarshalAs(UnmanagedType.LPWStr)] String Parameter,
                                    [In, MarshalAs(UnmanagedType.FunctionPtr)] FShowStatus ShowStatusCallBack);

        public class PackWorker
        {
            Packer Caller;
            IntPtr hModule;
            SPackFileInfo[] info;
            FPackCallback PackFiles;
            String FullOutput;
            String FullInputPath;
            String Parameter;

            public void SetParam(Packer Caller, 
                              IntPtr hModule, 
                              SPackFileInfo[] PackInfo, 
                              Delegate PackFiles, 
                              String FullOutput, 
                              String FullInputPath, 
                              String Parameter)
            {
                this.Caller = Caller;
                this.hModule = hModule;
                this.info = PackInfo;
                this.PackFiles = (FPackCallback)PackFiles;
                this.FullOutput = FullOutput;
                this.FullInputPath = FullInputPath;
                this.Parameter = Parameter;
            }

            public void Pack()
            {
                String text, title;

                Caller.btnAll.Enabled    = false;
                Caller.btnBrowse.Enabled = false;
                Caller.btnClear.Enabled  = false;
                Caller.btnDelete.Enabled = false;
                Caller.btnInvert.Enabled = false;
                Caller.btnNone.Enabled   = false;
                Caller.btnPlugin.Enabled = false;

                text = Caller.btnPack.Text;
                title = Caller.Text;

                Caller.btnPack.Text = "&Stop";

                try
                {
                    PackFiles(info, (UInt32)info.Length, FullOutput, FullInputPath, Parameter, Caller.ShowStatus);
                }
                catch (Exception e)
                {
                    Caller.MyMsgBox(e.Message);
                }
                FreeLibrary(hModule);
                Caller.Text = title;

                Caller.btnAll.Enabled    = true;
                Caller.btnBrowse.Enabled = true;
                Caller.btnClear.Enabled  = true;
                Caller.btnDelete.Enabled = true;
                Caller.btnInvert.Enabled = true;
                Caller.btnNone.Enabled   = true;
                Caller.btnPlugin.Enabled = true;

                Caller.btnPack.Text = text;
            }
        }

        public Packer()
        {
            InitializeComponent();

            this.KeyPreview = true;
            this.AllowDrop  = true;
            this.StartPosition = FormStartPosition.CenterScreen;
            this.FormBorderStyle = FormBorderStyle.FixedSingle;

            EscDownHandled = false;
            NeedStop = false;

            textBoxOutput.AllowDrop = true;
            textBoxPlugin.AllowDrop = true;

            Worker = new PackWorker();
            PackThread = new Thread(Worker.Pack);

            btnUpdate_Click(null, null);

            listBoxFiles.SelectionMode = SelectionMode.MultiExtended;
            textBoxOutput.Font = new System.Drawing.Font("Tahoma", 10);
            textBoxPlugin.Font = textBoxOutput.Font;
            textBoxOutput.Update();
            textBoxPlugin.Update();

//            textBoxPlugin.Text = System.AppDomain.CurrentDomain.BaseDirectory + "yu-ris.dll";
//            textBoxPlugin.Text = System.AppDomain.CurrentDomain.BaseDirectory + "SQLI.dll";
//            textBoxPlugin.Text = Directory.GetCurrentDirectory() + "\\krkr2_xp3.dll";
//            textBoxParam.Text = "fatesn";
//            textBoxParam.Text = "fateha";
//            textBoxParam.Text = "realsister";
//            textBoxParam.Text = "natsuzora";
//            textBoxParam.Text = "gb2312";
//            textBoxParam.Text = "tenshin";

            System.Drawing.Point Location = new System.Drawing.Point();

            Location = btnBrowse.Location;
            Location.Y = textBoxOutput.Location.Y + textBoxOutput.Height / 2 - btnBrowse.Height / 2;
            btnBrowse.Location = Location;

            Location = btnPlugin.Location;
            Location.Y = textBoxPlugin.Location.Y + textBoxPlugin.Height / 2 - btnPlugin.Height / 2;
            btnPlugin.Location = Location;
        }

        private void Packer_FormClosing(object sender, FormClosingEventArgs e)
        {
            btnClear.PerformClick();
        }

        private DialogResult MyMsgBox(String text)
        {
            return MessageBox.Show(this, text, null, MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
        }

        private UInt32 AddFilesToList(String file, String FullDirectoryName)
        {
            UInt32 Count;
            FileAttributes Attribute;

            Count = 0;

            try
            {
                Attribute = File.GetAttributes(file);
                if ((Attribute & FileAttributes.Directory) != 0)
                {
                    String[] Files = Directory.GetDirectories(file);

                    for (UInt32 i = 0; i != Files.Length; ++i)
                    {
                        Count += AddFilesToList(Files[i], FullDirectoryName);
                    }

                    Files = Directory.GetFiles(file);
                    for (UInt32 i = 0; i != Files.Length; ++i)
                    {
                        Count += AddFilesToList(Files[i], FullDirectoryName);
                    }
                }
                else
                {
                    String RelativePath;
                    RelativePath = Path.GetFullPath(file);

                    if (RelativePath.IndexOf(FullDirectoryName) != -1)
                        RelativePath = file.Substring(FullDirectoryName.Length);

//                    if (listBoxFiles.FindString(RelativePath) == CheckedListBox.NoMatches)
                    {
                        SPackFileInfo info;

                        info = new SPackFileInfo();
                        info.Compress = 0;
                        info.Encrypt = 0;
                        info.FileName = RelativePath;
                        FileInfo.Add(info);
//                        listBoxFiles.Items.Add(RelativePath);
                        ++Count;
                    }
                }
            }
            catch (Exception e)
            {
                MyMsgBox(e.ToString());
            }

            return Count;
        }

        private void Packer_DragDrop(Object sender, DragEventArgs e)
        {
            String FullDirectoryName;
            String[] fileNames = (String[])e.Data.GetData(DataFormats.FileDrop);

            if (textBoxOutput.Text == "")
            {
                FullDirectoryName = fileNames[0];
                if ((File.GetAttributes(FullDirectoryName) & FileAttributes.Directory) != 0)
                {
                    if (FullDirectoryName[FullDirectoryName.Length - 1] == '\\')
                        FullDirectoryName = FullDirectoryName.Substring(0, FullDirectoryName.Length - 1);
                    FullInputPath = FullDirectoryName;
                }
                else
                {
                    String Extension;
                    Int32 Index;

                    Extension = Path.GetExtension(FullDirectoryName);
                    if (Extension != null)
                    {
                        Index = FullDirectoryName.IndexOf(Extension);
                        FullDirectoryName = FullDirectoryName.Substring(0, Index);
                    }
                    FullInputPath = Path.GetDirectoryName(FullDirectoryName);
                }

                textBoxOutput.Text = FullDirectoryName + "." + DefaultExtension;
            }

            for (UInt32 i = 0; i != fileNames.Length; ++i)
            {
                if ((File.GetAttributes(fileNames[i]) & FileAttributes.Directory) != 0)
                {
                    FullDirectoryName = fileNames[i];
                }
                else
                {
                    FullDirectoryName = Path.GetDirectoryName(fileNames[i]);
                }

                if (FullDirectoryName[FullDirectoryName.Length - 1] != '\\')
                    FullDirectoryName += '\\';

                AddFilesToList(fileNames[i], FullDirectoryName);
            }
        }

        private void Packer_DragEnter(Object sender, DragEventArgs e)
        {
            e.Effect = e.Data.GetDataPresent(DataFormats.FileDrop) ? DragDropEffects.Copy : DragDropEffects.None;
        }

        private void Packer_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == (Keys)Keys.Escape)
                EscDownHandled = true;
        }

        private void Packer_KeyUp(Object sender, KeyEventArgs e)
        {
            if (EscDownHandled == true && e.KeyCode == (Keys)Keys.Escape)
            {
                EscDownHandled = false;
                Close();
            }
        }

        private void listBoxFiles_SelectedIndexChanged(object sender, EventArgs e)
        {
            Int32 Index;
            SPackFileInfo info;

            if (listBoxFiles.SelectedItems.Count != 1)
            {
                cbCompress.Checked = false;
                cbEncrypt.Checked = false;
                return;
            }

            Index = listBoxFiles.Items.IndexOf(listBoxFiles.SelectedItems[0]);
            if (Index == -1 || Index >= FileInfo.Count)
            {
                cbCompress.Checked = false;
                cbEncrypt.Checked = false;
                return;
            }

            info = (SPackFileInfo)FileInfo[Index];
            cbCompress.Checked = info.Compress == 1;
            cbEncrypt.Checked = info.Encrypt == 1;
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            listBoxFiles.Items.Clear();
            FileInfo.Clear();
            textBoxOutput.Text = null;
            progressBar1.Value = 0;
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            int index, Index, Count;

            Count = listBoxFiles.SelectedIndices.Count;
            Index = listBoxFiles.SelectedIndex;
            for (int i = 0; i != Count; ++i)
            {
                index = listBoxFiles.Items.IndexOf(listBoxFiles.SelectedIndices[0]);
                listBoxFiles.Items.RemoveAt(index);
                FileInfo.RemoveAt(index);
            }

            try
            {
                listBoxFiles.SelectedIndex = Index;
            }
            catch
            {
                listBoxFiles.SelectedIndex = Index - 1;
            }
        }

        private void textBoxOutput_DragDrop(object sender, DragEventArgs e)
        {
            String FileName = ((String[])e.Data.GetData(DataFormats.FileDrop))[0];

            if (File.GetAttributes(FileName) != FileAttributes.Directory)
            {
                ((TextBox)sender).Text = FileName;
            }
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            Int32 Index = ((Button)sender).TabIndex;
            SaveFileDialog sfd = new SaveFileDialog();

            sfd.OverwritePrompt = false;
            sfd.FileName = Index == 1 ? textBoxOutput.Text : textBoxPlugin.Text;
            sfd.InitialDirectory = sfd.FileName;
            if (Index == 2)
                sfd.Title = "Select a plugin";
            try
            {
                if ((File.GetAttributes(sfd.InitialDirectory) & FileAttributes.Directory) == 0)
                    sfd.InitialDirectory = Path.GetDirectoryName(sfd.InitialDirectory);
            }
            catch {}

            if (sfd.ShowDialog(this) == DialogResult.OK)
            {
                if (Index == 1)
                    textBoxOutput.Text = sfd.FileName;
                else if (Index == 2)
                    textBoxPlugin.Text = sfd.FileName;
            }
        }

        private Delegate GetFuncionAddress(IntPtr hModule, String ProcName, Type t)
        {
            IntPtr FunctionPointer;

            FunctionPointer = GetProcAddress(hModule, ProcName);
            if (FunctionPointer == IntPtr.Zero)
                return null;

            return Marshal.GetDelegateForFunctionPointer(FunctionPointer, t);
        }

        private Boolean ShowStatus(String Status, Int32 Percent)
        {
            progressBar1.Value = Percent > 100 ? 100 : Percent;
            if (Status != null)
                this.Text = Status;

            return !NeedStop;
        }

        private void btnPack_Click(object sender, EventArgs e)
        {
            if (PackThread.IsAlive)
            {
                NeedStop = true;
                return;
            }

            if (textBoxOutput.Text == null || textBoxOutput.Text == "")
                return;
            else if (FileInfo.Count == 0)
                return;

            IntPtr hModule;
            FPackCallback PackFiles;
            SPackFileInfo[] info;

            hModule = LoadLibraryExW(textBoxPlugin.Text, IntPtr.Zero, 0);
            if (hModule == IntPtr.Zero)
            {
                MyMsgBox("Can't load \"" + textBoxPlugin.Text + "\"");
                return;
            }

            PackFiles = (FPackCallback)GetFuncionAddress(hModule, "PackFiles", typeof(FPackCallback));
            if (PackFiles == null)
            {
                MyMsgBox("Invalid plugin: \"" + textBoxPlugin.Text + "\"");
                return;
            }

            info = new SPackFileInfo[FileInfo.Count];
            info = (SPackFileInfo[])FileInfo.ToArray(typeof(SPackFileInfo));

            NeedStop = false;
            Worker.SetParam(this, hModule, info, PackFiles, 
                Path.GetFullPath(textBoxOutput.Text), FullInputPath, textBoxParam.Text);
            PackThread = new Thread(Worker.Pack);
            PackThread.Start();
        }

        private void btnAll_Click(object sender, EventArgs e)
        {
            for (Int32 i = 0; i != listBoxFiles.Items.Count; ++i)
                listBoxFiles.SelectedItems.Add(listBoxFiles.Items[i]);
        }

        private void btnNone_Click(object sender, EventArgs e)
        {
            listBoxFiles.SelectedItems.Clear();
        }

        private void btnInvert_Click(object sender, EventArgs e)
        {
            Object Items;
            for (Int32 i = 0; i != listBoxFiles.Items.Count; ++i)
            {
                Items = listBoxFiles.Items[i];
                if (listBoxFiles.SelectedItems.IndexOf(Items) == -1)
                    listBoxFiles.SelectedItems.Add(Items);
                else
                    listBoxFiles.SelectedItems.Remove(Items);
            }
        }

        private void cbEncrypt_CheckedChanged(object sender, EventArgs e)
        {
            Int32 Index;
            SPackFileInfo info;
            for (Int32 i = 0; i != listBoxFiles.SelectedItems.Count; ++i)
            {
                Index = listBoxFiles.Items.IndexOf(listBoxFiles.SelectedItems[i]);
                if (Index == -1)
                    continue;

                info = (SPackFileInfo)FileInfo[Index];
                info.Encrypt = cbEncrypt.Checked ? 1 : 0;
                FileInfo[Index] = info;
            }
        }

        private void cbCompress_CheckedChanged(object sender, EventArgs e)
        {
            Int32 Index;
            SPackFileInfo info;
            for (Int32 i = 0; i != listBoxFiles.SelectedItems.Count; ++i)
            {
                Index = listBoxFiles.Items.IndexOf(listBoxFiles.SelectedItems[i]);
                if (Index == -1)
                    continue;

                info = (SPackFileInfo)FileInfo[Index];
                info.Compress = cbCompress.Checked ? 1 : 0;
                FileInfo[Index] = info;
            }
        }

        private void btnUpdate_Click(object sender, EventArgs e)
        {
            String ConfigPath = System.AppDomain.CurrentDomain.BaseDirectory + "Packer.ini";

            if (File.Exists(ConfigPath) == false)
                return;

            String Section = "Amano";
            String RetBuffer = new String('\0', 512);

            GetPrivateProfileStringW(Section, "Plugin", "", RetBuffer, RetBuffer.Length, ConfigPath);
            if (File.Exists(RetBuffer) == false)
            {
                RetBuffer = System.AppDomain.CurrentDomain.BaseDirectory + RetBuffer;
            }
            textBoxPlugin.Text = RetBuffer;

            RetBuffer = new String('\0', 1024);
            GetPrivateProfileStringW(Section, "Param", "", RetBuffer, RetBuffer.Length, ConfigPath);
            textBoxParam.Text = RetBuffer;

            RetBuffer = new String('\0', 512);
            GetPrivateProfileStringW(Section, "Extension", "", RetBuffer, RetBuffer.Length, ConfigPath);
            DefaultExtension = RetBuffer;
        }
    }
}