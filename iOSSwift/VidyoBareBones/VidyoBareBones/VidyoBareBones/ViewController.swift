//
//  ViewController.swift
//  VidyoBareBones
//
//  Created by Dinesh Sinha on 3/15/17.
//  Copyright © 2017 Dinesh Sinha. All rights reserved.
//

import UIKit
//#import "/Users/dinesh/try/swift/VidyoBareBones/VidyoBareBones-Bridging-Header.h"

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }

    @IBAction func onClicked(_ sender: Any) {
        let alert = UIAlertController(title: "Alert", message: "Message", preferredStyle: UIAlertControllerStyle.alert)
        alert.addAction(UIAlertAction(title: "Click", style: UIAlertActionStyle.default, handler: nil))
        self.present(alert, animated: true, completion: nil)
        
        var instanceOfVcObject: VcTalker = VcTalker()
        instanceOfVcObject.initializeVc()
        
    }
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

