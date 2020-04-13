//
//  main.m
//  Boilerplate iOS app main()
//
//  Created by Fletcher T. Penney on 4/13/2020.
//  Copyright © 2020 Fletcher T. Penney. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppDelegate.h"

int main(int argc, char * argv[]) {
    NSString * appDelegateClassName;
    @autoreleasepool {
        // Setup code that might create autoreleased objects goes here.
        appDelegateClassName = NSStringFromClass([AppDelegate class]);
    }
	return UIApplicationMain(argc, argv, nil, appDelegateClassName);
}
