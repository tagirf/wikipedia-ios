@import WMF;
@class MWKDataStore;
@class WMFShareFunnel;
@class WMFLegacyArticleViewController;
#import "WMFViewController.h"
#import "WMFTableOfContentsDisplay.h"
#import "LegacyWebViewController.h"
#import "WMFImageGalleryViewController.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString *const WMFEditPublishedNotification;

@protocol WMFArticlePreviewingActionsDelegate <NSObject>

- (void)readMoreArticlePreviewActionSelectedWithArticleController:(WMFLegacyArticleViewController *)articleController;

- (void)saveArticlePreviewActionSelectedWithArticleController:(WMFLegacyArticleViewController *)articleController didSave:(BOOL)didSave articleURL:(NSURL *)articleURL;

- (void)shareArticlePreviewActionSelectedWithArticleController:(WMFLegacyArticleViewController *)articleController
                                       shareActivityController:(UIActivityViewController *)shareActivityController;

- (void)viewOnMapArticlePreviewActionSelectedWithArticleController:(WMFLegacyArticleViewController *)articleController;

@end

/**
 *  View controller responsible for displaying article content.
 */
@interface WMFLegacyArticleViewController : WMFViewController <WMFWebViewControllerDelegate, WMFImagePreviewingActionsDelegate>

- (instancetype)initWithArticleURL:(NSURL *)url
                         dataStore:(MWKDataStore *)dataStore
                             theme:(WMFTheme *)theme;

@property (nonatomic, strong, readonly) NSURL *articleURL;
@property (nonatomic, strong, readonly, nullable) NSString *visibleSectionAnchor;

@property (nonatomic, strong, readonly) MWKDataStore *dataStore;

@property (nonatomic, strong, nullable) dispatch_block_t articleLoadCompletion;
@property (nonatomic, strong, nullable) dispatch_block_t viewDidLoadCompletion;

@property (nonatomic, strong, readonly, nullable) MWKArticle *article;

@property (nonatomic) WMFTableOfContentsDisplayMode tableOfContentsDisplayMode;
@property (nonatomic) WMFTableOfContentsDisplaySide tableOfContentsDisplaySide;
@property (nonatomic) WMFTableOfContentsDisplayState tableOfContentsDisplayState;
@property (nonatomic, getter=isUpdateTableOfContentsSectionOnScrollEnabled) BOOL updateTableOfContentsSectionOnScrollEnabled;

@property (nonatomic, strong, nullable) MWKSection *currentSection;               //doesn't actually update the view, only here for access from Swift category
@property (nonatomic, strong, nullable) NSString *anchorToRestoreScrollOffset; //doesn't actually update the view, only here for access from Swift category

@property (nonatomic, getter=isSavingOpenArticleTitleEnabled) BOOL savingOpenArticleTitleEnabled;
@property (nonatomic, getter=isAddingArticleToHistoryListEnabled) BOOL addingArticleToHistoryListEnabled;
@property (nonatomic, getter=isPeekingAllowed) BOOL peekingAllowed;
@property (nonatomic, getter=shouldRequestLatestRevisionOnInitialLoad) BOOL requestLatestRevisionOnInitialLoad;

@property (weak, nonatomic, nullable) id<WMFArticlePreviewingActionsDelegate> articlePreviewingActionsDelegate;

///**
// *  We need to do this to prevent auto loading from occuring,
// *  if we do something to the article like edit it and force a reload
// */
@property (nonatomic, assign) BOOL skipFetchOnViewDidAppear;

- (UIButton *)titleButton;

- (void)articleDidLoad;
- (void)kickoffProgressView;

- (void)scrollToAnchor:(nullable NSString *)anchor animated:(BOOL)animated completion:(nullable dispatch_block_t)completion;

@end

@interface WMFLegacyArticleViewController (WMFBrowserViewControllerInterface)

@property (strong, nonatomic, nullable, readonly) WMFShareFunnel *shareFunnel;

- (BOOL)canRefresh;
- (BOOL)canShare;
- (BOOL)hasLanguages;
- (BOOL)hasTableOfContents;
- (BOOL)hasReadMore;
- (BOOL)hasAboutThisArticle;

- (void)fetchArticleIfNeeded;

- (void)shareArticleWhenReady;

@end

@interface WMFLegacyArticleViewController (WMFSubclasses)

@property (nonatomic, strong, readonly) UIBarButtonItem *saveToolbarItem;
@property (nonatomic, strong, readonly) UIBarButtonItem *languagesToolbarItem;
@property (nonatomic, strong, readonly) UIBarButtonItem *shareToolbarItem;
@property (nonatomic, strong, readonly) UIBarButtonItem *readingThemesControlsToolbarItem;
@property (nonatomic, strong, readonly) UIBarButtonItem *showTableOfContentsToolbarItem;
@property (nonatomic, strong, readonly) UIBarButtonItem *hideTableOfContentsToolbarItem;

- (NSArray<UIBarButtonItem *> *)articleToolBarItems;

- (void)updateToolbarItemEnabledState;
- (void)calculateTableOfContentsDisplayState;

@end

NS_ASSUME_NONNULL_END