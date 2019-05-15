# Password Calculator (Qt)

QML rewrite of the original version written with wxWidgets: https://github.com/jhasse/pwcalculator

## Dependencies

Fedora:

```
sudo dnf install cmake qt5-qtquickcontrols2-devel gcc-c++ make boost-devel
```

## Building

```
cmake -Bbuild -H.
cmake --build build
```

### Android

```
mkdir build-android
cd build-android
cmake .. -DCMAKE_PREFIX_PATH=<Qt5 for Android> -DCMAKE_TOOLCHAIN_FILE=$ANDROID_HOME/ndk-bundle/build/cmake/android.toolchain.cmake -DCMAKE_INSTALL_PREFIX=dist
make install
<Qt5 for Android>/bin/androiddeployqt --output dist --gradle
adb install -r build-android/dist/build/outputs/apk/*/dist-*.apk
```
