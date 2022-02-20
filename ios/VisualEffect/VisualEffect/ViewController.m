//
//  ViewController.m
//  VisualEffect
//
//  Created by Jason on 2022/2/20.
//

#import "ViewController.h"
#import "CGDrawController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Do any additional setup after loading the view.
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event {
    CGDrawController *vc = [[CGDrawController alloc] init];
    [self.navigationController pushViewController:vc animated:YES];

}

@end
