#include <iostream>
#include <Eigen/Core>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <cmath>

template <typename T>
std::string ToString(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

using namespace std;
using namespace cv;

std::vector<std::vector<float> > digits;

int K = 10; 
float error_des = 0.001;
float error = 1000;

int main(int argc, char **argv) 
{
   // Load the data
   std::vector<float> img_array;
   
   std::ifstream source("/home/jxu/coding/KMeans/data/digits.txt",  std::ifstream::in);
   if(! source)
     std::cout << "Can't open data!" << std::endl;
   
   for (std::string line; std::getline(source, line);)
   {
     std::istringstream in(line);
     
     float number;
     while(in.rdbuf()->in_avail() != 0)
     {
        in >> number;
        std::cout << number << " ";  
	img_array.push_back(number);
     }
     std::cout << std::endl;
     digits.push_back(img_array);
     //std::cout << img_array.size() << std::endl;
     img_array.clear();
     //std::cout << img_array.size() << std::endl;
     std::vector<std::vector<float> > centroids;
     // start the algorithm
     //**************************************************************************************
     // initialize the centroids
     srand(time(NULL));
     for (int i = 0; i < K; i++)
     {
        std::vector<float> centroid;
        for(int j = 0; j < 64; j++)
	{
	  float randnum= rand() % 4 - 1;    // random number from -1 to 3, tricky here after reserving the distribution of data
	  centroid.push_back(randnum);
	}
	centroids.push_back(centroid);
	centroid.clear();
     }
     
     // start the iteration
     while (error > error_des)
     {
       // initialize
       std::vector<std::vector<float> > centroids;
       std::vector<int> assignments(1797, 0);
       std::vector<int> class_stat(10, 0);
       // assign each sample to the nearest centroid, here can be in parallel?????
       for(int i = 0; i < 1797; i++)
       {
	 std::vector<float> distances(10, 0);     // distance to each centroid
	 for (int j = 0; j < K; j++)
	 {
	   for (int m = 0; m < 64; m++)
	   {
	     distances[j] += abs(digits[i][m] - centroids[j][m]);
	   }
	 }
	std::vector<float>::iterator min_pos;
	min_pos = std::min_element(distances.begin(), distances.end());
	assignments[i] = std::distance(distances.begin(), min_pos);
	int assignment = std::distance(distances.begin(), min_pos);
	class_stat[assignment] += 1;
      }
      
      // create new centroid
      std::vector<std::vector<float> > sums;
      for(int p = 0; p < 10; p++)
      {
         std::vector<float> sum_array(0, 64);
	 sums.push_back(sum_array);
      }
      for (int n = 0; n < 1797; n++)
      {
	int index = assignments[n];
	for(int q = 0; q < 64; q++)
	{
	  sums[index][q] += abs(digits[n][q] - centroids[index][q]);
	}
      }
      
      for(int x = 0; x < K; x++)
      {
	for (int y = 0; y < 64; y++)
	{
	  centroids[x][y] = sums[x][y] / class_stat[x];
	}
      }
      
      // compute error
    }
  }
   
   return 0;
}
