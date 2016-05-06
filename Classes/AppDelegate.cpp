#include "AppDelegate.h"
#include "MainLayer.h"

USING_NS_CC;

static const cocos2d::Size Resolution = cocos2d::Size(853, 480);

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("CocosDemo", Rect(0, 0, Resolution.width, Resolution.height));
#else
        glview = GLViewImpl::create("CocosDemo");
#endif
        director->setOpenGLView(glview);
    }
    glview->setDesignResolutionSize(Resolution.width, Resolution.height, ResolutionPolicy::SHOW_ALL);
    
    auto scene = Scene::create();
    MainLayer *mainLayer = MainLayer::create();
    scene->addChild(mainLayer);
    director->runWithScene(scene);
    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
