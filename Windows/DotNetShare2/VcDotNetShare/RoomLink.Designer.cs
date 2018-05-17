namespace UnifiedDotNetSample
{
    partial class RoomLink
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
            this.textBoxPortal = new System.Windows.Forms.TextBox();
            this.textBoxRoomKey = new System.Windows.Forms.TextBox();
            this.textBoxDisplayName = new System.Windows.Forms.TextBox();
            this.textBoxPin = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.buttonJoin = new System.Windows.Forms.Button();
            this.checkBoxCameraMute = new System.Windows.Forms.CheckBox();
            this.checkBoxMicMute = new System.Windows.Forms.CheckBox();
            this.checkBoxSpeakerMute = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // textBoxPortal
            // 
            this.textBoxPortal.Location = new System.Drawing.Point(50, 37);
            this.textBoxPortal.Name = "textBoxPortal";
            this.textBoxPortal.Size = new System.Drawing.Size(332, 20);
            this.textBoxPortal.TabIndex = 0;
            // 
            // textBoxRoomKey
            // 
            this.textBoxRoomKey.Location = new System.Drawing.Point(50, 88);
            this.textBoxRoomKey.Name = "textBoxRoomKey";
            this.textBoxRoomKey.Size = new System.Drawing.Size(332, 20);
            this.textBoxRoomKey.TabIndex = 1;
            // 
            // textBoxDisplayName
            // 
            this.textBoxDisplayName.Location = new System.Drawing.Point(50, 138);
            this.textBoxDisplayName.Name = "textBoxDisplayName";
            this.textBoxDisplayName.Size = new System.Drawing.Size(332, 20);
            this.textBoxDisplayName.TabIndex = 2;
            // 
            // textBoxPin
            // 
            this.textBoxPin.Location = new System.Drawing.Point(50, 189);
            this.textBoxPin.Name = "textBoxPin";
            this.textBoxPin.Size = new System.Drawing.Size(332, 20);
            this.textBoxPin.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(50, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(34, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Portal";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(50, 72);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "RoomKey";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(50, 122);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(69, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "DisplayName";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(50, 173);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(22, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Pin";
            // 
            // buttonJoin
            // 
            this.buttonJoin.Location = new System.Drawing.Point(53, 269);
            this.buttonJoin.Name = "buttonJoin";
            this.buttonJoin.Size = new System.Drawing.Size(94, 23);
            this.buttonJoin.TabIndex = 8;
            this.buttonJoin.Text = "Join";
            this.buttonJoin.UseVisualStyleBackColor = true;
            this.buttonJoin.Click += new System.EventHandler(this.buttonJoin_Click);
            // 
            // checkBoxCameraMute
            // 
            this.checkBoxCameraMute.AutoSize = true;
            this.checkBoxCameraMute.Location = new System.Drawing.Point(53, 230);
            this.checkBoxCameraMute.Name = "checkBoxCameraMute";
            this.checkBoxCameraMute.Size = new System.Drawing.Size(86, 17);
            this.checkBoxCameraMute.TabIndex = 9;
            this.checkBoxCameraMute.Text = "CameraMute";
            this.checkBoxCameraMute.UseVisualStyleBackColor = true;
            // 
            // checkBoxMicMute
            // 
            this.checkBoxMicMute.AutoSize = true;
            this.checkBoxMicMute.Location = new System.Drawing.Point(205, 230);
            this.checkBoxMicMute.Name = "checkBoxMicMute";
            this.checkBoxMicMute.Size = new System.Drawing.Size(67, 17);
            this.checkBoxMicMute.TabIndex = 10;
            this.checkBoxMicMute.Text = "MicMute";
            this.checkBoxMicMute.UseVisualStyleBackColor = true;
            // 
            // checkBoxSpeakerMute
            // 
            this.checkBoxSpeakerMute.AutoSize = true;
            this.checkBoxSpeakerMute.Location = new System.Drawing.Point(317, 230);
            this.checkBoxSpeakerMute.Name = "checkBoxSpeakerMute";
            this.checkBoxSpeakerMute.Size = new System.Drawing.Size(90, 17);
            this.checkBoxSpeakerMute.TabIndex = 11;
            this.checkBoxSpeakerMute.Text = "SpeakerMute";
            this.checkBoxSpeakerMute.UseVisualStyleBackColor = true;
            // 
            // RoomLink
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(455, 320);
            this.Controls.Add(this.checkBoxSpeakerMute);
            this.Controls.Add(this.checkBoxMicMute);
            this.Controls.Add(this.checkBoxCameraMute);
            this.Controls.Add(this.buttonJoin);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBoxPin);
            this.Controls.Add(this.textBoxDisplayName);
            this.Controls.Add(this.textBoxRoomKey);
            this.Controls.Add(this.textBoxPortal);
            this.Name = "RoomLink";
            this.Text = "RoomKey";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBoxPortal;
        private System.Windows.Forms.TextBox textBoxRoomKey;
        private System.Windows.Forms.TextBox textBoxDisplayName;
        private System.Windows.Forms.TextBox textBoxPin;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button buttonJoin;
        private System.Windows.Forms.CheckBox checkBoxCameraMute;
        private System.Windows.Forms.CheckBox checkBoxMicMute;
        private System.Windows.Forms.CheckBox checkBoxSpeakerMute;
    }
}