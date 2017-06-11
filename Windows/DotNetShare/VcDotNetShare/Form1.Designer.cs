namespace VidyoClientCS
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
            this.pnlVideoArea = new System.Windows.Forms.Panel();
            this.tmrSubscribe = new System.Windows.Forms.Timer(this.components);
            this.buttonStart = new System.Windows.Forms.Button();
            this.buttonStop = new System.Windows.Forms.Button();
            this.buttonJoin = new System.Windows.Forms.Button();
            this.buttonEnd = new System.Windows.Forms.Button();
            this.buttonMuteCamera = new System.Windows.Forms.Button();
            this.buttonMuteMic = new System.Windows.Forms.Button();
            this.buttonShare = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // pnlVideoArea
            // 
            this.pnlVideoArea.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pnlVideoArea.Location = new System.Drawing.Point(26, 349);
            this.pnlVideoArea.Name = "pnlVideoArea";
            this.pnlVideoArea.Size = new System.Drawing.Size(803, 244);
            this.pnlVideoArea.TabIndex = 4;
            this.pnlVideoArea.SizeChanged += new System.EventHandler(this.pnlVideoArea_SizeChanged);
            // 
            // buttonStart
            // 
            this.buttonStart.Location = new System.Drawing.Point(73, 51);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(75, 23);
            this.buttonStart.TabIndex = 5;
            this.buttonStart.Text = "Start";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // buttonStop
            // 
            this.buttonStop.Location = new System.Drawing.Point(199, 51);
            this.buttonStop.Name = "buttonStop";
            this.buttonStop.Size = new System.Drawing.Size(75, 23);
            this.buttonStop.TabIndex = 6;
            this.buttonStop.Text = "Stop";
            this.buttonStop.UseVisualStyleBackColor = true;
            this.buttonStop.Click += new System.EventHandler(this.buttonStop_Click);
            // 
            // buttonJoin
            // 
            this.buttonJoin.Location = new System.Drawing.Point(73, 94);
            this.buttonJoin.Name = "buttonJoin";
            this.buttonJoin.Size = new System.Drawing.Size(75, 23);
            this.buttonJoin.TabIndex = 7;
            this.buttonJoin.Text = "Join";
            this.buttonJoin.UseVisualStyleBackColor = true;
            this.buttonJoin.Click += new System.EventHandler(this.buttonJoin_Click);
            // 
            // buttonEnd
            // 
            this.buttonEnd.Location = new System.Drawing.Point(199, 94);
            this.buttonEnd.Name = "buttonEnd";
            this.buttonEnd.Size = new System.Drawing.Size(75, 23);
            this.buttonEnd.TabIndex = 8;
            this.buttonEnd.Text = "End";
            this.buttonEnd.UseVisualStyleBackColor = true;
            this.buttonEnd.Click += new System.EventHandler(this.buttonEnd_Click);
            // 
            // buttonMuteCamera
            // 
            this.buttonMuteCamera.Location = new System.Drawing.Point(26, 613);
            this.buttonMuteCamera.Name = "buttonMuteCamera";
            this.buttonMuteCamera.Size = new System.Drawing.Size(75, 23);
            this.buttonMuteCamera.TabIndex = 9;
            this.buttonMuteCamera.Text = "MuteCamera";
            this.buttonMuteCamera.UseVisualStyleBackColor = true;
            this.buttonMuteCamera.Click += new System.EventHandler(this.buttonMuteCamera_Click);
            // 
            // buttonMuteMic
            // 
            this.buttonMuteMic.Location = new System.Drawing.Point(182, 613);
            this.buttonMuteMic.Name = "buttonMuteMic";
            this.buttonMuteMic.Size = new System.Drawing.Size(75, 23);
            this.buttonMuteMic.TabIndex = 10;
            this.buttonMuteMic.Text = "MuteMic";
            this.buttonMuteMic.UseVisualStyleBackColor = true;
            this.buttonMuteMic.Click += new System.EventHandler(this.buttonMuteMic_Click);
            // 
            // buttonShare
            // 
            this.buttonShare.Location = new System.Drawing.Point(347, 613);
            this.buttonShare.Name = "buttonShare";
            this.buttonShare.Size = new System.Drawing.Size(99, 23);
            this.buttonShare.TabIndex = 11;
            this.buttonShare.Text = "ShareScreen";
            this.buttonShare.UseVisualStyleBackColor = true;
            this.buttonShare.Click += new System.EventHandler(this.buttonShare_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1235, 661);
            this.Controls.Add(this.buttonShare);
            this.Controls.Add(this.buttonMuteMic);
            this.Controls.Add(this.buttonMuteCamera);
            this.Controls.Add(this.buttonEnd);
            this.Controls.Add(this.buttonJoin);
            this.Controls.Add(this.buttonStop);
            this.Controls.Add(this.buttonStart);
            this.Controls.Add(this.pnlVideoArea);
            this.Name = "Form1";
            this.Text = "VidyoSample";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pnlVideoArea;
        private System.Windows.Forms.Timer tmrSubscribe;
        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.Button buttonStop;
        private System.Windows.Forms.Button buttonJoin;
        private System.Windows.Forms.Button buttonEnd;
        private System.Windows.Forms.Button buttonMuteCamera;
        private System.Windows.Forms.Button buttonMuteMic;
        private System.Windows.Forms.Button buttonShare;
    }
}

