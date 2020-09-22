//
//  ViewController.swift
//  VidyoSwiftSample
//
//  Created by ApiSamples on 07/07/17.
//  Copyright © 2017 ApiSamples. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    //Properties
    @IBOutlet var Abc: UIView!
    
    @IBOutlet weak var TextPortal: UITextField!
    @IBOutlet weak var TextRoomKey: UITextField!
    @IBOutlet weak var TextDisplayName: UITextField!
    @IBOutlet weak var TextPin: UITextField!
    
    var m_lib = VidyoLibrary()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        m_lib.initializeVidyo(Abc);
        
        TextPortal.text = "http://test.sandboxga.vidyo.com"
        TextRoomKey.text = "iUC7CrJ822"
        TextDisplayName.text = "ddd"
        
       
        //xx.oi("Abc");
        // Do any additional setup after loading the view, typically from a nib.
    }

    @IBAction func JoinClicked(_ sender: UIButton) {
        let portal = TextPortal.text;
        let roomKey = TextRoomKey.text;
        let displayName = TextDisplayName.text;
        m_lib.connect(toRoom: portal, roomKey, displayName);
    }
    
    @IBAction func LeaveClicked(_ sender: UIButton) {
        m_lib.leaveRoom();
    }
}


