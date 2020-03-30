//
//  Document.m
//  Boilerplate macOS app
//
//  Created by Fletcher T. Penney on 3/30/20.
//  Copyright © 2020 Fletcher T. Penney. All rights reserved.
//

#import "Document.h"

@interface Document ()

@end

@implementation Document

- (instancetype)init {
	self = [super init];

	if (self) {
		// Add your subclass-specific initialization here.
	}

	return self;
}


+ (BOOL)autosavesInPlace {
	return YES;
}


- (void)makeWindowControllers {
	// Override to return the Storyboard file name of the document.
	NSWindowController * wc = [[NSStoryboard storyboardWithName:@"Main" bundle:nil] instantiateControllerWithIdentifier:@"Document Window Controller"];
	[self addWindowController:wc];

	// Remember window positioning
	if (self.fileURL && ![self.fileURL.path isEqualToString:@""]) {
		[[wc window] setFrameAutosaveName:self.fileURL.path];
		[[wc window] saveFrameUsingName:self.fileURL.path];
	} else {
		[[wc window] setFrameAutosaveName:@"Unsaved Document"];
		[[wc window] saveFrameUsingName:@"Unsaved Document"];
	}

	// Enable window tabbing
	if (@available(macOS 10.12, *)) {
		if ([wc.window respondsToSelector:@selector(setTabbingIdentifier:)]) {
			[wc.window setTabbingIdentifier:@"RAPDocumentTab"];
		} else {
			// Fallback on earlier versions
		}
	}

	// Notify view controller of our path on disk
	[[[wc window] contentViewController] setRepresentedObject:self.fileURL];
}


- (NSData *)dataOfType:(NSString *)typeName error:(NSError **)outError {
	// Insert code here to write your document to data of the specified type. If outError != NULL, ensure that you create and set an appropriate error if you return nil.
	// Alternatively, you could remove this method and override -fileWrapperOfType:error:, -writeToURL:ofType:error:, or -writeToURL:ofType:forSaveOperation:originalContentsURL:error: instead.
	// [NSException raise:@"UnimplementedMethod" format:@"%@ is unimplemented", NSStringFromSelector(_cmd)];
	return nil;
}


- (BOOL)readFromData:(NSData *)data ofType:(NSString *)typeName error:(NSError **)outError {
	// Insert code here to read your document from the given data of the specified type. If outError != NULL, ensure that you create and set an appropriate error if you return NO.
	// Alternatively, you could remove this method and override -readFromFileWrapper:ofType:error: or -readFromURL:ofType:error: instead.
	// If you do, you should also override -isEntireFileLoaded to return NO if the contents are lazily loaded.
	// [NSException raise:@"UnimplementedMethod" format:@"%@ is unimplemented", NSStringFromSelector(_cmd)];
	return YES;
}


- (BOOL)readFromFileWrapper:(NSFileWrapper *)fileWrapper ofType:(NSString *)typeName error:(NSError * __autoreleasing  _Nullable *)outError {
	return YES;
}


- (void)saveDocument:(id)sender {
	[super saveDocument:sender];

	// Update window positioning if we have been saved
	NSWindowController * wc = [[self windowControllers] firstObject];

	if (self.fileURL && ![self.fileURL.path isEqualToString:@""]) {
		[[wc window] setFrameAutosaveName:self.fileURL.path];
		[[wc window] saveFrameUsingName:self.fileURL.path];
	} else {
		[[wc window] setFrameAutosaveName:@"Unsaved Document"];
		[[wc window] saveFrameUsingName:@"Unsaved Document"];
	}
}


@end
