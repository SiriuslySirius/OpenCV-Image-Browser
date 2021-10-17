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
#include <conio.h>
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
 * \scales images to fit the target size while maintaining image aspect ratio.
 *
 * Rescales the image specified in the argument to fit the specified target
 * width and height given in the argument while maintaining the original
 * image's aspect ratio.
 *
 * @param [in] Image to be rescaled
 * @param [in] Target width to consider for rescaling
 * @param [in] Target height to consider for rescaling
 * \return Rescaled image.
 *****************************************************************************/

cv::Mat maxRatioResize(const cv::Mat& img, int target_width, int target_height)
{
	double scale_width = float(target_width) / img.size().width;
	double scale_height = float(target_height) / img.size().height;

	cv::Mat newIMG;

	if (scale_width <= scale_height)
	{
		cv::resize(img, newIMG, cv::Size(0, 0), scale_width, scale_width);
	}
	else {
		cv::resize(img, newIMG, cv::Size(0, 0), scale_height, scale_height);
	}

	return newIMG;
}

/******************************************************************************
 * \brief Display the specified image.
 *
 * Display the image specified in the argument.  This function ensures that the
 * image will fit within the window max size restriction provided by the user,
 * while maintaining the aspect ratio of the image.
 *
 * @param [in] Image to be displayed
 * \return Key pressed by the user
 *****************************************************************************/

uchar display(const cv::Mat& img)
{
	// If image is larger than the max window size limit
	if (img.size().width > maxcols || img.size().height > maxrows)
	{
		cv::Mat resized_img = maxRatioResize(img, maxcols, maxrows);
		cv::imshow("Image Preview", resized_img);
	}
	else
	{
		cv::imshow("Image Preview", img);
	}
	uchar response = (uchar) cv::waitKey(0);
	return (response);
}


/*
 * Get File Name from a Path with or without extension
 */
std::string getFileName(std::string filePath, bool withExtension = true, char seperator = '\\')
{
	// Get last dot position
	std::size_t dotPos = filePath.rfind('.');
	std::size_t sepPos = filePath.rfind(seperator);
	if (sepPos != std::string::npos)
	{
		return filePath.substr(sepPos + 1, filePath.size() - (withExtension || dotPos != std::string::npos ? 1 : dotPos));
	}
	return "";
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

		// Loops through the emtire list of files from the given directory and it's subdirectories
		for (int i = 0; i < files.size(); i++)
		{
			// Reads the files
			cv::Mat img = cv::imread(files[i]);

			// if image is not empty, prompt in the console the current image's information and
			// navigation instructions for traversing the images in the list of files
			if (!img.empty())
			{
				// Create an OpenCV window to for previewing the image.
				cv::namedWindow("Image Preview", cv::WINDOW_AUTOSIZE);

				// Prompt current image information.
				std::string filename = getFileName(files[i]);
				std::cout << std::endl << "IMAGE INFORMATION" << std::endl;
				std::cout << std::right << std::setw(19) << "Name: " << std::left << filename.substr(0, filename.find(".")) << std::endl;
				std::cout << std::right << std::setw(19) << "File Type: " << std::left << filename.substr(filename.rfind('.') + 1) << std::endl;
				std::cout << std::right << std::setw(19) << "Filepath: " << std::left << files[i] << std::endl;
				std::cout << std::right << std::setw(19) << "Image Width: " << std::left << img.size().width << "px" << std::endl;
				std::cout << std::right << std::setw(19) << "Image Height: " << std::left << img.size().height << "px" << std::endl;
				std::cout << std::right << std::setw(19) << "Image Dimensions: " << std::left << img.size().width << "px x " << img.size().height << "px" << std::endl;
				std::cout << std::right << std::setw(19) << "Total Pixels: " << std::left << img.size().width * img.size().height << "px" << std::endl;
				std::cout << std::right << std::setw(19) << "File Size (Bytes): " << std::left << img.total() * img.elemSize() << "B" << std::endl;

				// Label to go back to when the user presses the wrong key.
				PROMPT:
				{
					// Prompt controls for navigating the vector of file locations
					std::cout << std::endl << "Awaiting User Response in Image Preview Window..." << std::endl;
					// Condition to prevent this message to display at the last file in the vector.
					if (i != files.size() - 1)
					{
						std::cout << "Press Space or the N key to go to the next image." << std::endl;
					}
					// Condition to prevent this message at the beginning of the vector.
					if (i != 0)
					{
						std::cout << "Press the P key go to the previous image." << std::endl;
					}
					// Condition to prevent this message to display at the last file in the vector.
					if (i != files.size() - 1)
					{
						std::cout << "Press the Q key go to quit the application." << std::endl;
					}
					// Condition to show this message to only display at the last file in the vector.
					if (i == files.size() - 1)
					{
						std::cout << "Press Space, the N key, or the Q key to go to end the application." << std::endl;
					}

					// Get the user response and display image
					 uchar command = display(img);

					// Conditionals for user response to navigate the vector.
					// Refer to comment for navigation instructions regarding index location conditions.
					// Next
					if (command == 'n' || command == 'N' || command == ' ' && i != files.size() - 1)
					{
						// Always destroy the window when you are done.
						cv::destroyAllWindows();
						continue;
					}
					// Previous
					else if (i != 0 && command == 'p' || command == 'P')
					{
						i -= 2;
					}
					// Quit
					else if (command == 'q' || command == 'Q')
					{
						std::cout << std::endl << "Application closed." << std::endl << std::endl;
						// Always destroy the window when you are done.
						cv::destroyAllWindows();
						return(0);
					}
					// Handling invalid key input.
					else
					{
						std::cout << std::endl << "INVALID KEY, TRY AGAIN." << std::endl;
						goto PROMPT;
					}
				}
				// Always destroy the window when you are done.
				cv::destroyAllWindows();
			}
			// If the file is empty, meaning it's not an image, delete the file location out of the
			// vector, then resize the vector, and don't iterate to the next index in the next 
			// iteration. This will take you to the next image by replacing the deleted file location
			// with the file location of the next image.
			else {
				files.erase(files.begin() + i);
				files.resize(files.size());
				i = i-1;
			}

			// Always destroy the window when you are done.
			cv::destroyAllWindows();
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