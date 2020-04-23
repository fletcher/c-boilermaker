//
//  DemoPrefsViewController.m
//  BoilerRAP
//
//  Created by Fletcher T. Penney on 3/30/20.
//

#import "DemoPrefsViewController.h"

@interface DemoPrefsViewController ()

@end

@implementation DemoPrefsViewController

@synthesize viewIdentifier;

- (instancetype)init {
    self = [super init];
    
    if (self) {
        [self setViewIdentifier:@"DemoPreferences"];
    }
    
    return self;
}


- (void)loadView {
    self.view = [[NSView alloc] init];

    [self.view setFrame:NSMakeRect(0, 0, 200, 200)];
}


- (void)viewDidLoad {
    [super viewDidLoad];

    // Do view setup here.
    unsigned char * uuid = malloc(sizeof(char) * 40);
    char * str = malloc(sizeof(char) * 40);
    uuid_generate_random(uuid);
    uuid_unparse(uuid, str);
    
    [self.view addSubview:[NSTextField labelWithString:[NSString stringWithUTF8String:str]]];
}


- (void)viewDidAppear {
    // No first responder when window first appears or reappears
    [self.view.window makeFirstResponder:nil];
}


#pragma mark - MASPreferences

- (NSImage *) toolbarItemImage {
    return [NSImage imageNamed:NSImageNamePreferencesGeneral];
}


- (NSString *) toolbarItemLabel {
    return @"Demo";
}


@end
