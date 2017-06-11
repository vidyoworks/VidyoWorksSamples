using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace UnifiedDotNetSample
{
    public partial class RoomLink : Form
    {
        public string m_strPortal;
        public string m_strRoomKey;
        public string m_strDisplayName;
        public string m_strPin;
        public Boolean m_bMakeCall;

        const string c_strPortal = "http://test.sandboxga.vidyo.com";
        const string c_strRoomKey = "iUC7CrJ822";
        const string c_strDisplayName = "TestUser";
        const string c_strPin = "";

        
        public RoomLink()
        {
            InitializeComponent();
            textBoxPortal.Text = c_strPortal;
            textBoxRoomKey.Text = c_strRoomKey;
            textBoxDisplayName.Text = c_strDisplayName;
            textBoxPin.Text = c_strPin;
            m_bMakeCall = false;
        }

        private void buttonJoin_Click(object sender, EventArgs e)
        {
            m_bMakeCall = true;
            m_strPortal = textBoxPortal.Text;
            m_strRoomKey = textBoxRoomKey.Text;
            m_strDisplayName = textBoxDisplayName.Text;
            m_strPin = textBoxPin.Text;
            this.Close();
        }
    }
}
