#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>
#include <set>
#include "image.h"
#include "priority_queue.h"

// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);

// ===================================================================================================

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
    exit(1);
  }

  // open the input image
  Image<Color> input;
  if (!input.Load(argv[1])) {
    std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
    exit(1);
  }

  // a place to write the distance values
  Image<DistancePixel> distance_image;
  distance_image.Allocate(input.Width(),input.Height());

  // calculate the distance field (each function returns the maximum distance value)
  double max_distance = 0;
  if (std::string(argv[3]) == std::string("naive_method")) {
    max_distance = NaiveDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("improved_method")) {
    max_distance = ImprovedDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_map")) {
    max_distance = FastMarchingMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
    // EXTRA CREDIT: implement FastMarchingMethod with a hash table
  } else {
    std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
    exit(1);
  }

  // convert distance values to a visualization
  Image<Color> output;
  output.Allocate(input.Width(),input.Height());
  for (int i = 0; i < input.Width(); i++) {
    for (int j = 0; j < input.Height(); j++) {
      double v = distance_image.GetPixel(i,j).getValue();
      if (std::string(argv[4]) == std::string("greyscale")) {
	output.SetPixel(i,j,GreyBands(v,max_distance*1.01,1));
      } else if (std::string(argv[4]) == std::string("grey_bands")) {
	output.SetPixel(i,j,GreyBands(v,max_distance,4));
      } else if (std::string(argv[4]) == std::string("rainbow")) {
	output.SetPixel(i,j,Rainbow(v,max_distance));
      } else {
	// EXTRA CREDIT: create other visualizations 
	std::cerr << "ERROR: Unknown visualization style" << std::endl;
	exit(0);
      }
    }
  }
  // save output
  if (!output.Save(argv[2])) {
    std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
    exit(1);
  }

  return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  // return the maximum distance value
  double answer = 0;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      double closest = -1;      
      // loop over all other pixels in the input image
      for (int i2 = 0; i2 < w; i2++)  {
	for (int j2 = 0; j2 < h; j2++) {
	  const Color& c = input.GetPixel(i2,j2);      
	  // skip all pixels that are not black
	  if (!c.isBlack()) continue;
	  // calculate the distance between the two pixels
	  double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
	  // store the closest distance to a black pixel
	  if (closest < 0 || distance < closest) {
	    closest = distance;
	  }
	}
      }
      assert (closest >= 0);
      answer = std::max(answer,closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i,j);
      p.setValue(closest);
    }
  }
  return answer;
}


double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {

  int w = input.Width();
  int h = input.Height();
  double answer = 0;
  
  // Find the coordinates of all black pixels
  std::vector<std::pair<int, int>> black_pixels;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      if (input.GetPixel(i, j).isBlack()) {
        black_pixels.push_back({i, j});
      }
    }
  }
  
  // Loop over all pixels in the image and calculate the closest distance to a black pixel
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      double closest = -1;
      for (const std::pair<int, int>& coord : black_pixels) {
        double distance = sqrt((i - coord.first) * (i - coord.first) + (j - coord.second) * (j - coord.second));
        if (closest < 0 || distance < closest) {
          closest = distance;
        }
      }
      assert(closest >= 0);
      answer = std::max(answer, closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i,j);
      p.setValue(closest);
    }
  }
  
  return answer;

}

void find_neighbours(int h, int w, DistancePixel current_pixel,Image<DistancePixel> &distance_image,std:: set<DistancePixel*>& near) {
    // Loop through all neighbouring positions
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
          int numx = current_pixel.getX()+ dx;
          int numy = current_pixel.getY() + dy;
          // Check to see that positions are within bounds
           if (numx >= 0 && numy < h && numy >= 0 && numx < w && !(dx == 0 && dy == 0)) {
              DistancePixel* cur= &distance_image.GetPixel(numx,numy);
              int posx = distance_image.GetPixel(numx,numy).getX();
              int posy = distance_image.GetPixel(numx,numy).getY();
              double distance = sqrt((current_pixel.getX() - posx)*(current_pixel.getX()- posx) + (current_pixel.getY() - posy)*(current_pixel.getY() - posy));
              double distance2 = distance + distance_image.GetPixel(current_pixel.getX(),current_pixel.getY()).getValue();
              // See if distance value should be updated
              if(distance_image.GetPixel(numx,numy).getValue() > distance2) {
                distance_image.GetPixel(numx,numy).setValue(distance2);
              }
              // Store neighbour values in current_neighbours set
              cur->setX(posx);
              cur->setY(posy);
              cur->setValue(distance2);
              near.insert(cur);
           }
        }
    }
  // Remove value if it is equal to zero
  std::set<DistancePixel*>::iterator it;
  for (it = near.begin(); it != near.end(); ++it) {
  if ((*it)->getValue() == 0) {
    near.erase(*it);
    }
  }
}


double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  //Initialize variables
  std::set <DistancePixel*> all_neighs;
  int w = input.Width();
  int h = input.Height();
  std::vector <DistancePixel*> black_pixels;
  // Loop through pixels in the image and identify and store black_pixels
  for(int i = w-1; i >= 0; i--) {
    for(int z = 0; z < h; z++) {
      distance_image.GetPixel(i,z).setX(i);
      distance_image.GetPixel(i,z).setY(z);
      if (input.GetPixel(i,z).isBlack()) {
        distance_image.GetPixel(i,z).setValue(0);
        black_pixels.push_back(&distance_image.GetPixel(i,z));
        all_neighs.insert(&distance_image.GetPixel(i,z));
      }
      // If pixel is not a black pixel set value to "infinity"
      else {
        distance_image.GetPixel(i,z).setValue(9999999);
      }
    }
  }
  //Create the priority_queue
  DistancePixel_PriorityQueue priority_queue(black_pixels);
  // Loop while priority_queue is not empty
  while(priority_queue.empty()!= true) {
    //Find and copy top element in priority_queue
    const DistancePixel& pixel = *priority_queue.top();
    DistancePixel& pixelcopy = distance_image.GetPixel(pixel.getX(),pixel.getY());
    pixelcopy.setX(pixel.getX());
    pixelcopy.setY(pixel.getY());
    pixelcopy.setValue(pixel.getValue());

    std:: set <DistancePixel*> current_neighbours;
 
    find_neighbours(h,w,pixelcopy,distance_image,current_neighbours);
    //Pop top element in priority queue once neighbours have been found
    priority_queue.pop();
    std::set<DistancePixel*>::iterator it;
    // Add elements to priority queue
    for (it = current_neighbours.begin(); it != current_neighbours.end(); ++it) {
        if(!priority_queue.in_heap(*it) && all_neighs.find(*it) == all_neighs.end() ) {
          priority_queue.push((*it));
          
        }

        all_neighs.insert((*it));
    }

  }
  // Calculate maximium value
  double maxval = 0;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      if(distance_image.GetPixel(j,i).getValue() > maxval) {
        maxval = distance_image.GetPixel(j,i).getValue();
      }
    }
  }

  // for(int i = 0; i < h; ++i){
  //   for(int j = 0; j < w; ++i){
  //     DistancePixel temp = distance_image.GetPixel(i,j);
  //     std::cout << temp.getValue() << " | ";
  //   }
  //   std::cout << std::endl;
  // }

  return maxval;
  


}

// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
  Color answer;
  if (distance < 0.001) {
    // black
    answer.r = 0; answer.g = 0; answer.b = 0;
  } else if (distance < 0.2*max_distance) {
    // blue -> cyan
    double tmp = distance * 5.0 / max_distance;
    answer.r = 0;
    answer.g = tmp*255;
    answer.b = 255;
  } else if (distance < 0.4*max_distance) {
    // cyan -> green
    double tmp = (distance-0.2*max_distance) * 5.0 / max_distance;
    answer.r = 0;
    answer.g = 255;
    answer.b = (1-tmp*tmp)*255;
  } else if (distance < 0.6*max_distance) {
    // green -> yellow
    double tmp = (distance-0.4*max_distance) * 5.0 / max_distance;
    answer.r = sqrt(tmp)*255;
    answer.g = 255;
    answer.b = 0;
  } else if (distance < 0.8*max_distance) {
    // yellow -> red
    double tmp = (distance-0.6*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = (1-tmp*tmp)*255;
    answer.b = 0;
  } else if (distance < max_distance) {
    // red -> white
    double tmp = (distance-0.8*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = tmp*255;
    answer.b = tmp*255;
  } else {
    // white
    answer.r = answer.g = answer.b = 255;
  }  
  return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
  Color answer;
  if (distance < 0.001) {
    // red
    answer.r = 255; answer.g = 0; answer.b = 0;
  } else {
    // shades of grey
    answer.r = answer.g = answer.b = int(num_bands*256*distance/double(max_value)) % 256;
  }  
  return answer;
}

// ===================================================================================================



 