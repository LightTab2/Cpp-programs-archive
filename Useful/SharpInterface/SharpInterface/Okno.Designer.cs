namespace SharpInterface
{
    partial class Okno
    {
        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Kod generowany przez Projektanta formularzy systemu Windows
        private void InitializeComponent()
        {
            this.OtworzPlik = new System.Windows.Forms.OpenFileDialog();
            this.Przycisk = new System.Windows.Forms.Button();
            this.Input = new System.Windows.Forms.TextBox();
            this.Output = new System.Windows.Forms.TextBox();
            this.Info = new System.Windows.Forms.TextBox();
            this.Info2 = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // OtworzPlik
            // 
            this.OtworzPlik.DefaultExt = "*.exe";
            this.OtworzPlik.FileName = "OtworzPlik";
            this.OtworzPlik.Filter = "Programy|*.exe|Wszystkie pliki|*.*";
            this.OtworzPlik.FileOk += new System.ComponentModel.CancelEventHandler(this.OtworzPlik_FileOk);
            // 
            // Przycisk
            // 
            this.Przycisk.Location = new System.Drawing.Point(241, 171);
            this.Przycisk.Name = "Przycisk";
            this.Przycisk.Size = new System.Drawing.Size(75, 23);
            this.Przycisk.TabIndex = 0;
            this.Przycisk.Text = "Prześlij input";
            this.Przycisk.UseVisualStyleBackColor = true;
            this.Przycisk.Click += new System.EventHandler(this.Przeslij);
            // 
            // Input
            // 
            this.Input.Location = new System.Drawing.Point(11, 31);
            this.Input.Multiline = true;
            this.Input.Name = "Input";
            this.Input.Size = new System.Drawing.Size(560, 132);
            this.Input.TabIndex = 1;
            // 
            // Output
            // 
            this.Output.Location = new System.Drawing.Point(12, 218);
            this.Output.Multiline = true;
            this.Output.Name = "Output";
            this.Output.ReadOnly = true;
            this.Output.Size = new System.Drawing.Size(560, 132);
            this.Output.TabIndex = 2;
            // 
            // Info
            // 
            this.Info.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.Info.Location = new System.Drawing.Point(270, 12);
            this.Info.Name = "Info";
            this.Info.ReadOnly = true;
            this.Info.Size = new System.Drawing.Size(30, 13);
            this.Info.TabIndex = 3;
            this.Info.Text = "Input";
            // 
            // Info2
            // 
            this.Info2.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.Info2.Location = new System.Drawing.Point(263, 200);
            this.Info2.Name = "Info2";
            this.Info2.ReadOnly = true;
            this.Info2.Size = new System.Drawing.Size(37, 13);
            this.Info2.TabIndex = 4;
            this.Info2.Text = "Output";
            // 
            // Okno
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(584, 362);
            this.Controls.Add(this.Info2);
            this.Controls.Add(this.Info);
            this.Controls.Add(this.Output);
            this.Controls.Add(this.Input);
            this.Controls.Add(this.Przycisk);
            this.MaximumSize = new System.Drawing.Size(600, 400);
            this.MinimumSize = new System.Drawing.Size(600, 400);
            this.Name = "Okno";
            this.Text = "Sharp Interface";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.OpenFileDialog OtworzPlik;
        private System.Windows.Forms.Button Przycisk;
        private System.Windows.Forms.TextBox Input;
        private System.Windows.Forms.TextBox Output;
        private System.Windows.Forms.TextBox Info;
        private System.Windows.Forms.TextBox Info2;
    }
}

