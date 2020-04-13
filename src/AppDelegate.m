//
//  RAPAppDelegate.m
//  Boilerplate iOS app
//
//  Created by Fletcher T. Penney on 4/13/20.
//  Copyright © 2020 Fletcher T. Penney. All rights reserved.
//

#import "AppDelegate.h"
#import "DocumentBrowserViewController.h"
#import "DocumentViewController.h"
#import "Document.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary<UIApplicationLaunchOptionsKey,id> *)launchOptions {
    // Override point for customization after application launch.
    return YES;
}


/*
+ (void) initialize {
	[AppDelegate registerDefaults];
}


+ (void) registerDefaults {
}
*/


#pragma mark - URL Handling

- (BOOL)application:(UIApplication *)app openURL:(NSURL *)inputURL options:(NSDictionary<UIApplicationOpenURLOptionsKey, id> *)options {
    // Ensure the URL is a file URL
    if (!inputURL.isFileURL) {
        return NO;
    }

    // Reveal / import the document at the URL
    DocumentBrowserViewController *documentBrowserViewController = (DocumentBrowserViewController *)self.window.rootViewController;
    [documentBrowserViewController revealDocumentAtURL:inputURL importIfNeeded:YES completion:^(NSURL * _Nullable revealedDocumentURL, NSError * _Nullable error) {
        if (error) {
            // Handle the error appropriately
            NSLog(@"Failed to reveal the document at URL %@ with error: '%@'", inputURL, error);
            return;
        }
        
        // Present the Document View Controller for the revealed URL
        [documentBrowserViewController presentDocumentAtURL:revealedDocumentURL];
    }];
    return YES;
}


@end
