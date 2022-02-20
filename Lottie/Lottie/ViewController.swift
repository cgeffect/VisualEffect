//
//  ViewController.swift
//  Lottie
//
//  Created by Jason on 2022/2/20.
//

import UIKit
import Lottie

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()

        let path = Bundle.main.path(forResource: "Watermelon", ofType: "json")!
        let animation = Animation.filepath(path, animationCache: nil)
        let animationView = AnimationView(animation: animation)
        view.addSubview(animationView)
        preferredContentSize = animationView.bounds.size
        animationView.center = self.view.center;
        animationView.loopMode = .loop
        animationView.play()

    }


}

