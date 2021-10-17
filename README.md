# CSCI-4150-HW-P1
ECU CSCI 4150 DIP/CV Fall 2021 Group Programming Assignment <br/>
Contributors: Abelson Abueg and Brandon Miranda

## Instructions for Windows with Microsoft Visual Studio 2019
For our group assignment, we used Microsoft Visual Studio 2019 for working with Windows. To compile our code, you will need to open 'browser.sln' and follow these instruction on how to get OpenCV working on Visual Studio on your Windows machine before building the solution:
* __Install and Configure OpenCV on Windows 10 and Microsoft Visual 2019:__ https://towardsdatascience.com/install-and-configure-opencv-4-2-0-in-windows-10-vc-d132c52063a1
  * Installing OpenCV
  * Setting your environment variable for OpenCV
  * Setting up OpenCV in Microsoft Visual Studio 2019
  * __Important:__  Make sure when your doing this, set the build to x64 _Release_. It is important to set it to _Release_ because the OpenCV windows will not work in _Debug_ mode.

After you have configured OpenCV in your machine and in Microsoft Visual Studio, you'll then need to build the solution.  Again, make sure you are building in x64 Release.

After building the solution, you will find the executable (.exe) file in "\*\browser\x64\release" so you will be able to run the code on your machine.

To run the program, open Powershell and use the 'cd' command to "\*\browser\x64\release", which is where the executable file is located. Below are the basic arguments you can use for the program. Although there are different variations of each command you can use, but in these instructions, we'll use the shortest form of each argument.

* _Open help:_
  * .\browser.exe -h
* _Run program __without__ image preview window size limit (will adjust to display size on Windows):_
  * .\browser.exe _Your-Directory-Path_
  * __Example:__ .\browser.exe "C:\Users\__Some User__\Desktop\directory-to-browse-images
* _Run program __with__ image preview window size limit:_
  * .\browser.exe -r=_Max-INT-Height-Limit-in-Pixels_ -c=_INT-Max-Width-Limit-Pixels_ _STRING-Your-Directory-Path_
  * __Example:__ .\browser.exe -r=720 -c=1280 'C:\Users\__Some User__\Desktop\directory-to-browse-images-from'
  
## Instructions for MacOS
The instructions for running our application on MacOS are very similar to the Windows counterpart. The biggest exception being having to work through Xcode rather than Visual Studio 2019. To begin open 'browser.sln' and follow the instructions on how to install OpenCV on Mac with the following link: https://www.youtube.com/watch?v=HxNZEa7Slyk&t=571s

The steps are mostly the same as above with Windows except for having to switch to a release mode rather than a debug one. Creating the build for the browser defaulty will do. 

After building the solution, you will find the executable (.exe) file in "\*\browser\x64\release" so you will be able to run the code on your machine.

To run the program, open Terminal from the Launchpad menu and use the 'cd' command to "\*\browser\x64\release", which is where the executable file is located. Below are the basic arguments you can use for the program. Although there are different variations of each command you can use, but in these instructions, we'll use the shortest form of each argument.

* _Open help:_
  * .\browser.exe -h
* _Run program __without__ image preview window size limit (will adjust to display size on Windows):_
  * .\browser.exe _Your-Directory-Path_
  * __Example:__ .\browser.exe "C:\Users\__Some User__\Desktop\directory-to-browse-images
* _Run program __with__ image preview window size limit:_
  * .\browser.exe -r=_Max-INT-Height-Limit-in-Pixels_ -c=_INT-Max-Width-Limit-Pixels_ _STRING-Your-Directory-Path_
  * __Example:__ .\browser.exe -r=720 -c=1280 'C:\Users\__Some User__\Desktop\directory-to-browse-images-from'
