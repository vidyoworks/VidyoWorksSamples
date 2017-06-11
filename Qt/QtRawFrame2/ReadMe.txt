QtRawFrame2 Qt sample

Platform support
Can be run on Windows, Mac and Linux. It is expected to run on Android and iOS also, but we have done no QA on these platforms. Use android or iOS specif samples on these platforms.

What does this sample does
User custom renderer using raw frame. Has options for Static and dynamic view. Has also options for self view.

How to build this sample
1) Make sure to install Qt. We tested with Qt 4.8
2) Make sure that you have the header files at VidyoClient/include. If not, refer to section on "How to upgrade headers and lib".
3) Make sure you have the libs at VidyoClient/lib. If not, refer to section on "How to upgrade headers and lib".
4) Open Qt creator and build.
You should expect to see the executable file as a result of successful build

How to upgrade headers and lib
1) Download updated headers and libs from our website. Let us say you downloaded to ~/tmp
2) ./pullvc.sh ~/tmp

How to bundle VC lib in the bundle on Mac
Mac may have issues running the shared lib from a given path unless you do this.
./deploy.sh $YOUR_APP_BUNDLE_NAME
where $YOUR_APP_BUNDLE_NAME is you app bundle name

