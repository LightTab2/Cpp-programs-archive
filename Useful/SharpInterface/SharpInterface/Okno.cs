using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SharpInterface
{
    public partial class Okno : Form
    {
        public bool once, nolog = false;
        public string filename = "", savefile = "";
        const int timeout = 20000;
        Process p;
        ProcessStartInfo prc;
        //Thread th;
        StreamReader opt;
        StreamWriter inpt;
        public FileStream save;
        public Okno(ref string fn)
        {
            filename = fn;
            InitializeComponent();
            OtworzPlik.FileName = filename;
            while (!File.Exists(filename))
            {
                MessageBox.Show(this, "Nie znaleziono pliku w lokalizacji \"" + filename + '\"', "Błąd", MessageBoxButtons.OK, MessageBoxIcon.Error);
                if (OtworzPlik.ShowDialog() == DialogResult.Cancel)
                { this.Dispose(); return; }

                filename = OtworzPlik.FileName;
            }

            prc = new ProcessStartInfo
            {
                WindowStyle = ProcessWindowStyle.Hidden,
                CreateNoWindow = true,
                UseShellExecute = false,
                RedirectStandardInput = true,
                RedirectStandardOutput = true,
                FileName = filename
            };


            p = Process.Start(prc);
            opt = p.StandardOutput;
            inpt = p.StandardInput;
        }
        ~Okno()
        {
            p.CloseMainWindow();
            p.Close();
            p.WaitForExit(200);
            p.Kill();
            p.Dispose();
            opt.Dispose();
            inpt.Dispose();
            save.Dispose();
        }

        private void OtworzPlik_FileOk(object sender, CancelEventArgs e)
        {

        }

        private void Przeslij(object sender, EventArgs e)
        {
            StringReader reader = new StringReader(Input.Text);
            string instr = reader.ReadLine(), str = "";
            Output.Text = "";
            if (instr == null) return;
            do
            {
                inpt.WriteLine(instr);
                do
                {
                    Thread th = new Thread(() =>
                    {
                        str = opt.ReadLine();
                    });
                    th.Start();
                    th.Join(timeout);
                    th.Abort();
                    if (!nolog) Console.WriteLine(str);
                    Output.AppendText(str + "\r\n");
                    if (savefile != "")
                    {
                        byte[] info = new UTF8Encoding(true).GetBytes(str + '\n');
                        save.Write(info, 0, info.Length);
                        save.Flush();
                    }
                } while (opt.Peek() > -1);
                if (once)
                {
                    this.Close();
                    this.Dispose();
                    return;
                }
                if (p.HasExited == true)
                {
                    p.Dispose();
                    opt.Dispose();
                    inpt.Dispose();
                    p = Process.Start(prc);
                    opt = p.StandardOutput;
                    inpt = p.StandardInput;
                    reader.Dispose();
                    return;
                }
            } while ((str = reader.ReadLine()) != null);
            reader.Dispose();
        }
    }
}