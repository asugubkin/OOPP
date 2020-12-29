using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO;
using System.Runtime.InteropServices;

namespace SharpForm
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    struct SharpStruct
    {
        [MarshalAs(UnmanagedType.I4)]
        public int i;
        [MarshalAs(UnmanagedType.R8)]
        public double d;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
        public string s;
    };


    public partial class Form : System.Windows.Forms.Form
    {
        [DllImport("MFCLibrary.dll", CharSet = CharSet.Ansi, EntryPoint = "GetSize")]
        static extern int GetFileSize(StringBuilder FileName);

        [DllImport("MFCLibrary.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        static extern void GetFile(StringBuilder FileName, StringBuilder FileData);

        [DllImport("MFCLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern void GetStruct(ref SharpStruct s);

        public Form()
        {
            InitializeComponent();
        }

        private void buttonLoad_Click(object sender, EventArgs e)
        {
            openFileDialog.InitialDirectory = Directory.GetCurrentDirectory();
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                var FileName = new StringBuilder(openFileDialog.FileName);
                int n = GetFileSize(FileName);
                var FileData = new StringBuilder(n);
                GetFile(FileName, FileData);
                textBox.Text = FileData.ToString();

                var s = new SharpStruct();
                s.i = 100;
                s.d = 200;
                s.s = "String from Sharp";
                GetStruct(ref s);
                listBox.Items.Add($"{s.i}");
                listBox.Items.Add($"{s.d}");
                listBox.Items.Add($"{s.s}");
            }
        }
    }
}
