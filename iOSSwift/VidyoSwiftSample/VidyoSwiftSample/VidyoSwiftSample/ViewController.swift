//
//  ViewController.swift
//  VidyoSwiftSample
//
//  Created by ApiSamples on 07/07/17.
//  Copyright © 2017 ApiSamples. All rights reserved.
//

import UIKit


class ViewController: UIViewController {

    
    @IBOutlet var Abc: UIView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let xx = VidyoLibrary();
        xx.initializeVidyo(Abc);
        //xx.oi("Abc");
        // Do any additional setup after loading the view, typically from a nib.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

