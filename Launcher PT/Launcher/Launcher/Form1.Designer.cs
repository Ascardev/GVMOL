namespace Launcher
{
    partial class Form1
    {
        /// <summary>
        /// Variável de designer necessária.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpar os recursos que estão sendo usados.
        /// </summary>
        /// <param name="disposing">verdade se for necessário descartar os recursos gerenciados; caso contrário, falso.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region código gerado pelo Windows Form Designer

        /// <summary>
        /// Método necessário para suporte do Designer - não modifique
        /// o conteúdo deste método com o editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.bgwProcesso = new System.ComponentModel.BackgroundWorker();
            this.lblVerUpdate = new System.Windows.Forms.Label();
            this.lblStatus = new System.Windows.Forms.Label();
            this.lblLoading = new System.Windows.Forms.Label();
            this.tmLoading = new System.Windows.Forms.Timer(this.components);
            this.btnClose = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // bgwProcesso
            // 
            this.bgwProcesso.WorkerReportsProgress = true;
            this.bgwProcesso.DoWork += new System.ComponentModel.DoWorkEventHandler(this.bgwProcesso_DoWork);
            this.bgwProcesso.ProgressChanged += new System.ComponentModel.ProgressChangedEventHandler(this.bgwProcesso_ProgressChanged);
            this.bgwProcesso.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler(this.bgwProcesso_RunWorkerCompleted);
            // 
            // lblVerUpdate
            // 
            this.lblVerUpdate.AutoSize = true;
            this.lblVerUpdate.BackColor = System.Drawing.Color.Transparent;
            this.lblVerUpdate.Font = new System.Drawing.Font("Arial", 8.75F);
            this.lblVerUpdate.ForeColor = System.Drawing.Color.Aqua;
            this.lblVerUpdate.Location = new System.Drawing.Point(12, 326);
            this.lblVerUpdate.Name = "lblVerUpdate";
            this.lblVerUpdate.Size = new System.Drawing.Size(70, 15);
            this.lblVerUpdate.TabIndex = 1;
            this.lblVerUpdate.Text = "Bem Vindo!";
            this.lblVerUpdate.Click += new System.EventHandler(this.lblVerUpdate_Click);
            // 
            // lblStatus
            // 
            this.lblStatus.AutoSize = true;
            this.lblStatus.BackColor = System.Drawing.Color.Transparent;
            this.lblStatus.Font = new System.Drawing.Font("Arial", 10.75F);
            this.lblStatus.ForeColor = System.Drawing.Color.Aqua;
            this.lblStatus.Location = new System.Drawing.Point(-122, 6);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new System.Drawing.Size(332, 17);
            this.lblStatus.TabIndex = 2;
            this.lblStatus.Text = "                                 LOADING                                ";
            this.lblStatus.Click += new System.EventHandler(this.lblStatus_Click);
            // 
            // lblLoading
            // 
            this.lblLoading.AutoSize = true;
            this.lblLoading.BackColor = System.Drawing.Color.Transparent;
            this.lblLoading.Font = new System.Drawing.Font("Arial", 8.75F);
            this.lblLoading.ForeColor = System.Drawing.Color.Cyan;
            this.lblLoading.Location = new System.Drawing.Point(252, 247);
            this.lblLoading.Name = "lblLoading";
            this.lblLoading.RightToLeft = System.Windows.Forms.RightToLeft.Yes;
            this.lblLoading.Size = new System.Drawing.Size(105, 15);
            this.lblLoading.TabIndex = 3;
            this.lblLoading.Text = "...LOADING GAME";
            this.lblLoading.Click += new System.EventHandler(this.lblLoading_Click);
            // 
            // tmLoading
            // 
            this.tmLoading.Interval = 1000;
            this.tmLoading.Tick += new System.EventHandler(this.tmLoading_Tick);
            // 
            // btnClose
            // 
            this.btnClose.AccessibleName = "";
            this.btnClose.BackColor = System.Drawing.Color.Transparent;
            this.btnClose.Cursor = System.Windows.Forms.Cursors.AppStarting;
            this.btnClose.FlatAppearance.BorderSize = 0;
            this.btnClose.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.btnClose.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
            this.btnClose.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnClose.ForeColor = System.Drawing.Color.Red;
            this.btnClose.Location = new System.Drawing.Point(571, 2);
            this.btnClose.Name = "btnClose";
            this.btnClose.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btnClose.Size = new System.Drawing.Size(25, 21);
            this.btnClose.TabIndex = 4;
            this.btnClose.Text = "X";
            this.btnClose.UseVisualStyleBackColor = false;
            this.btnClose.Click += new System.EventHandler(this.btnClose_Click);
            this.btnClose.MouseEnter += new System.EventHandler(this.btnClose_MouseEnter);
            this.btnClose.MouseLeave += new System.EventHandler(this.btnClose_MouseLeave);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("Arial", 10.75F);
            this.label1.ForeColor = System.Drawing.Color.Aqua;
            this.label1.Location = new System.Drawing.Point(487, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(78, 17);
            this.label1.TabIndex = 1;
            this.label1.Text = "Aguarde....";
            this.label1.Click += new System.EventHandler(this.lblVerUpdate_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.BackgroundImage = global::Launcher.Properties.Resources.bg_2;
            this.ClientSize = new System.Drawing.Size(600, 350);
            this.Controls.Add(this.btnClose);
            this.Controls.Add(this.lblLoading);
            this.Controls.Add(this.lblStatus);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.lblVerUpdate);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(600, 350);
            this.MinimizeBox = false;
            this.MinimumSize = new System.Drawing.Size(600, 350);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Launcher";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Form1_MouseDown);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.ComponentModel.BackgroundWorker bgwProcesso;
        private System.Windows.Forms.Label lblVerUpdate;
        private System.Windows.Forms.Label lblStatus;
        private System.Windows.Forms.Label lblLoading;
        private System.Windows.Forms.Timer tmLoading;
        private System.Windows.Forms.Button btnClose;
        private System.Windows.Forms.Label label1;
    }
}

