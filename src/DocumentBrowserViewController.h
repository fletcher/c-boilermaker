//
//  DocumentBrowserViewController.h
//  FakeDocApp
//
//  Created by Fletcher T. Penney on 4/13/20.
//  Copyright © 2020 MultiMarkdown Software, LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DocumentBrowserViewController : UIDocumentBrowserViewController

- (void)presentDocumentAtURL:(NSURL *)documentURL;

@end
