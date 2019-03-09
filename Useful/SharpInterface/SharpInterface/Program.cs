using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading;
using System.Windows.Forms;

namespace SharpInterface
{
    static class Program
    {
        [STAThreadAttribute]
        static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            string filename = "";
            for (int index = 0; index != args.Length; ++index)
            {
                if (args[index].Length < 2) continue;

                if (args[index].Length > 4 && args[index].Substring(0, 5) == "/name")
                    filename = args[index].Substring(5).Replace('*', ' ');

                else if (args[index].Substring(0, 2) == "/n")
                    filename = args[index].Substring(2).Replace('*', ' ');
            }
            Okno okno = new Okno(ref filename);
            for (int index = 0; index != args.Length; ++index)
            {
                if (args[index].Length < 2) continue;

                if (args[index] == "/o" || (args[index].Length > 4 && args[index] == "/once"))
                    okno.once = true;

                else if (args[index].Length > 4 && args[index].Substring(0, 5) == "/save")
                {
                    okno.savefile = args[index].Substring(5).Replace('*', ' ');
                    okno.save = new FileStream(okno.savefile, FileMode.Create, FileAccess.Write, FileShare.None);
                }

                else if (args[index].Substring(0, 2) == "/s")
                {
                    okno.savefile = args[index].Substring(2).Replace('*', ' ');
                    okno.save = new FileStream(okno.savefile, FileMode.Create, FileAccess.Write, FileShare.None);
                }
                else if (args[index] == "-n" || (args[index].Length > 4 && args[index] == "-nolog"))
                    okno.nolog = true;
            }
            if (!okno.IsDisposed) Application.Run(okno);
        }
    }
}
