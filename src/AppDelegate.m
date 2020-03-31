//
//  RAPAppDelegate.m
//  Boilerplate macOS app
//
//  Created by Fletcher T. Penney on 3/25/20.
//  Copyright © 2020 Fletcher T. Penney. All rights reserved.
//

#import "AppDelegate.h"

#import "MASPreferencesWindowController.h"
#import "DemoPrefsViewController.h"

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void) applicationDidFinishLaunching:(NSNotification *) aNotification {
	// Insert code here to initialize your application
}


- (void) applicationWillTerminate:(NSNotification *)aNotification {
	// Insert code here to tear down your application
}


+ (void) initialize {
	[AppDelegate registerDefaults];
}


+ (void) registerDefaults {
}


#pragma mark - Preferences

- (NSWindowController *) preferencesWindowController {
    static MASPreferencesWindowController * wc;
    static dispatch_once_t onceToken;

    dispatch_once(&onceToken, ^ {
        NSViewController * demo = [[DemoPrefsViewController alloc] init];
        [(DemoPrefsViewController *)demo setViewIdentifier:@"Demo 1"];
        NSViewController * demo2 = [[DemoPrefsViewController alloc] init];
        wc = [[MASPreferencesWindowController alloc] initWithViewControllers:@[demo, demo2] title:@"Preferences"];
    });

    return wc;
}


- (IBAction) openPreferences:(id)sender {
    [[self preferencesWindowController] showWindow:self];
}


@end
