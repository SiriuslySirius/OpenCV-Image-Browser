/******************************************************************************
 * \brief Image Browser using OpenCV
 *
 * This is a program to read and display images using OpenCV.  It displays all
 * images in the directory specified as the parameter, as well as images in
 * any subdirectories and their subdirectories, to an arbitrary depth (as
 * limited by the operating system).
 *
 * @param directory The directory that contains all the images to be displayed.
 *****************************************************************************/

#include <iostream>
#include <iomanip>
#include <vector>
#include <assert.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/utility.hpp>
#include "dir.hpp"
#include "browser.hpp"
#ifdef _WIN32
#include <Windows.h>
#endif

int maxcols;	//!< Default max number of columns to show
int maxrows;	//!< Default max number of rows to show


/******************************************************************************
 * \brief Display the specified image.
 *
 * Display the image specified in the argument.  This function ensures that the
 * image will fit in the windows, while maintaining the aspect ratio.
 *
 * @param [in] Image to be displayed
 * \return Key pressed by the user
 *****************************************************************************/

uchar display(const cv::Mat& img)
{
	// To Do
	uchar response = 'c';
	return (response);
}


int main( int argc, const char ** argv )
{
	try
	{
		// parse the command line arguments

		cv::CommandLineParser parser(argc, argv, keys);
		std::string dir = parser.get<std::string>(0);

		parser.about("Image Browser v1.0");
		if (parser.has("help") || dir.empty() )
		{
			parser.printMessage();
			return (1);
		}

		// find the maximum number of rows and columns 
		// on screen.  
		// if those are specified in command line, 
		// use those.  
		// otherwise, use the default values for Linux or Apple
		// compute to the maximum dimensions of primary screen for the Windows case.

		maxrows = parser.get<uint>("rows");		//!< maximum number of rows in display window
		maxcols = parser.get<uint>("cols");		//!< maximum number of columns in display window

#ifdef _WIN32
		if (maxrows == 0 || maxcols == 0)
		{
			maxcols = static_cast<int>(GetSystemMetrics(SM_CXSCREEN));
			maxrows = static_cast<int>(GetSystemMetrics(SM_CYSCREEN));
		}
#endif

		// scan all files in the specified directory.  
		// if there are subdirectories,
		// the files in there are scanned as well 
		// in depth-first order.

		std::vector<std::string> files;		//!< List of all files
		files = file_list(dir, files);

		assert(files.size() != 0);	// ensure that the list of files is not empty


		// display file names in the list

		for (int i = 0; i < files.size(); i++)
		{
			std::cout << std::endl;
			std::cout << std::setw(3) << i << ". " << std::setw(60) << files[i];
			std::cout << std::endl;
		}
	}
	catch (std::string& str)	// handle string exception
	{
		std::cerr << "Error: " << argv[0] << ": " << str << std::endl;
		return (1);
	}
	catch (cv::Exception& e)	// handle OpenCV exception
	{
		std::cerr << "Error: " << argv[0] << ": " << e.msg << std::endl;
		return (1);
	}

	return (0);
}