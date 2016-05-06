cocos compile -p android --android-studio
if [ $? -eq 0 ]; then
    adb install -rf ../bin/debug/android/CocosDemo-debug.apk
    adb shell am start rong.cocos.demo/org.cocos2dx.cpp.AppActivity
fi
