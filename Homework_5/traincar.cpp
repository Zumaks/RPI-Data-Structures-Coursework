// =======================================================================
//
// IMPORTANT NOTE: You should edit this file
//
// =======================================================================

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "traincar.h"

// =======================================================================
// =======================================================================
//
//  HERE'S WHERE YOU SHOULD IMPLEMENT THE FUNCTIONS YOU PROTOTYPED IN
//  THE "traincar_prototypes.h" FILE.
//


void PushFront(TrainCar*& head, TrainCar* new_car) { 
    // Check if the new car is null
    if (new_car == nullptr) {
        return;
    }

    // Set the new car's next pointer to the current head of the linked list
    new_car->next = head;

    // Set the new car's prev pointer to null, since it will be the new head of the linked list
    new_car->prev = nullptr;

    // If the linked list is not empty, set the previous pointer of the old head to the new car
    if (head != nullptr) {
        head->prev = new_car;
    }

    // Set the head of the linked list to the new car
    head = new_car;
}



TrainCar* pop_front(TrainCar* &train) {
    // If the train is empty, return NULL
    if (train == NULL) { 
        return NULL;
    }
    // If there is only one car in the train, remove it and set train to NULL
    else if(train->next == NULL) { 
        TrainCar* removed_elem = train;
        train = NULL;
        return removed_elem;
    }
    // If there is more than one car in the train, remove the first car and update train
    else {
        TrainCar* removed_elem = train;
        train->next->prev = NULL;
        train  = train->next;
        removed_elem->next = NULL;
        return removed_elem;
    }
}



void PushBack(TrainCar*& head, TrainCar* new_car) {
    // if the list is empty, set the new car to be the head
    if (head == NULL) {
        head = new_car;
        return;
    }

    // find the last car in the list
    TrainCar* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    // add the new car to the end of the list
    current->next = new_car;
    new_car->prev = current;
}


// This function deletes all the TrainCars in a linked list pointed to by train
void DeleteAllCars(TrainCar* &train) {
  // Set current to the beginning of the linked list
  TrainCar* current = train;

  // Traverse the linked list
  while (current != NULL) {
    // Save the next TrainCar pointer before deleting the current one
    TrainCar* next = current->next;

    // Delete the current TrainCar
    delete current;

    // Move to the next TrainCar in the linked list
    current = next;
  }

  // Set the linked list to be empty by pointing train to NULL
  train = NULL;
}



void TotalWeightAndCountCars(TrainCar* train, int &total_weight, int &num_engines, int &num_freight_cars, int &num_passenger_cars, int &num_dining_cars, int &num_sleeping_cars){
     // Initialize all counters to zero
     total_weight = 0;
     num_engines = 0;
     num_freight_cars = 0;
     num_passenger_cars = 0;
     num_dining_cars = 0;
     num_sleeping_cars = 0;
    
    // Traverse through the linked list of train cars
    TrainCar* current = train;
    while (current != NULL) {
        // Store the next train car so we can move to it after processing the current one
        TrainCar* next = current->next;
        
        // Add the weight of the current train car to the total weight of the train
        total_weight = total_weight + current->getWeight();
        
        // Increment the appropriate counter based on the type of the current train car
        if (current->isEngine() == true) {
            num_engines = num_engines + 1;
        }
        else if (current->isDiningCar() == true) {
            num_dining_cars = num_dining_cars + 1;
        }
        else if (current->isFreightCar() == true) {
            num_freight_cars = num_freight_cars + 1;
        }
        else if (current->isPassengerCar() == true) { 
            num_passenger_cars = num_passenger_cars + 1;
        }
        else if (current->isSleepingCar() == true) { 
            num_sleeping_cars = num_sleeping_cars + 1;
        }
        
        // Move to the next train car
        current = next;
  }
}

float CalculateSpeed(TrainCar* train) {
    TrainCar* current = train;
    int total_weight = 0;
    int num_engines = 0;
    
    // Traverse the train to get the total weight and number of engines.
    while (current != NULL) {
        total_weight = total_weight + current->getWeight();
        if (current->isEngine() == true) {
            num_engines = num_engines + 1;
        }
        current = current->next;
    }
    
    // Calculate the horsepower of the train.
    double horsepower = num_engines * 3000;
    
    // Calculate the maximum speed of the train
    float max_speed = (horsepower*550*3600)/(2000 * 0.02 * 5280 * total_weight);
    return max_speed;
}

// This function calculates the average distance between a passenger car and the nearest dining car
// on a given train.
float AverageDistanceToDiningCar(TrainCar* train) {
    TrainCar* current = train;
    int total_distance = 0;
    int total_pas_carts = 0;

    // Iterate over each train car
    while (current != NULL) {
        // If the current car is a passenger car, calculate the distance to the nearest dining car
        if (current->isPassengerCar() == true) {
            total_pas_carts = total_pas_carts + 1;
            int count = 0;
            int temp_count = 0 ;
            TrainCar* new_current = current;
            // Iterate over the train cars after the current car until a dining car is found
            while (new_current != NULL) {
                if (new_current->isDiningCar() == true) { 
                    count += temp_count;
                    break;
                }
                temp_count = temp_count + 1;
                new_current = new_current->next;
            }
            int temp_count2 = 0;
            TrainCar* new_current2 = current->prev;
            // Iterate over the train cars before the current car until a dining car is found
            while (new_current2 != NULL) {
                temp_count2 = temp_count2 + 1;
                if (new_current2->isDiningCar() == true) { 
                    count += temp_count2;
                    break;
                }
                new_current2 = new_current2->prev;
            }
            total_distance = total_distance + count;
            current = current->next;
        }
        // If the current car is not a passenger car, simply move on to the next car
        else { 
            current = current->next;
        }
    }
    // If there are no passenger cars, return 0
    if (total_pas_carts == 0 ){
        return 0;
    }
    // Otherwise, calculate and return the average distance between a passenger car and the nearest dining car
    else {
        float avg_distance = (float)total_distance/total_pas_carts;
        return avg_distance;
    }
}
int ClosestEngineToSleeperCar(TrainCar* train){
    // Initialize variables
    int worst_case_scenario = 0;  // the worst-case scenario distance between an engine and sleeping car
    TrainCar* current = train;  // pointer to current train car
    int engine_loc = 0;  // the index of the current engine

    // Iterate through each train car
    while (current != NULL) {
        engine_loc = engine_loc + 1;  // increment engine location counter
        if (current->isEngine() == true) { 
            // Search for the closest sleeping car ahead of the engine
            TrainCar* new_current = train;  // pointer to a new current train car
            int current_index = 0;  // the location of the engine
            while (current_index < engine_loc && new_current != NULL) {
                new_current = new_current->next;
                current_index++;
            }
            TrainCar* new_current2 = new_current;  
            int count = 0;  // the distance between the engine and the closest sleeping car ahead of it
            while (new_current2 != NULL) {
                count = count + 1;
                if (new_current2->isSleepingCar() == true) {
                    // Update the worst-case scenario distance if necessary
                    if(count < worst_case_scenario && worst_case_scenario != 0) { 
                        worst_case_scenario = count;
                        break;
                    }
                    else if (worst_case_scenario == 0) { 
                        worst_case_scenario = count;
                        break;
                    }
                }
                new_current2 = new_current2->next;
            }

            // Search for the closest sleeping car behind the engine
            int count2 = 0;  // the distance between the engine and the closest sleeping car behind it
            new_current2 = new_current->prev;
            while (new_current2 != NULL) {
                count2 = count2 + 1;
                if (new_current2->isSleepingCar() == true) {
                    // Update the worst-case scenario distance if necessary
                    if(count2 < worst_case_scenario && worst_case_scenario != 0) { 
                        worst_case_scenario = count2;
                        break;
                    }
                    else if (worst_case_scenario == 0) { 
                        worst_case_scenario = count2;
                        break;
                    }
                }
                new_current2 = new_current2->prev;
            }
        }
        current = current->next;
    }

    return worst_case_scenario;
}


std::vector<TrainCar*> ShipFreight(TrainCar* &engines, TrainCar* &freight, int min_speed, int max_cars_per_train) {
    // Initialize an empty vector to hold the resulting trains.
    std::vector<TrainCar*> trains;

    // Initialize two pointers to the start of the freight list.
    TrainCar* current_car = freight;
    TrainCar* current_car2 = freight;

    // Count the number of freight cars in the list.
    float freight_count = 0;
    while (current_car != NULL) {
        freight_count++;
        current_car = current_car->next;
    }

    // Calculate the number of trains needed to ship all the freight.
    float train_num = freight_count/max_cars_per_train;
    int floor_train_num = floor(train_num);

    // Initialize counters
    int counter1 = 0;
    int counter3 = 0;

    // Initialize a pointer to the current train being assembled.
    TrainCar* cur_train = NULL;

    // Loop through the freight cars and assemble trains.
    while (counter3 <= freight_count) {
        counter1++;

        // If the current train is full, add it to the list of trains and start a new train.
        if (counter1 == max_cars_per_train) { 
             trains.push_back(cur_train);
             cur_train = NULL;
             counter1 = 0;
        }
        // If all the freight has been added to trains, add the last train to the list of trains.
        else if (counter3 == freight_count) {
            trains.push_back(cur_train);
            cur_train = NULL;
            break;
        }
        // If this is the first car in the train, add an engine.
        else if (counter1 == 1) { 
            PushBack(cur_train,pop_front(engines));
        }
        // If the current train's speed is too slow, add an engine to the front of the train.
        else if (CalculateSpeed(cur_train) < min_speed) { 
            PushFront(cur_train,pop_front(engines));
        }
        //If no engines left skip
        else if (engines == NULL && counter3!= freight_count) { 
            DeleteAllCars(cur_train);
            cur_train = NULL;
            break;
        }
        // Otherwise, add a freight car to the current train and increment the freight car counter.
        else {
            PushBack(cur_train,pop_front(freight));
            counter3++;
        }
    }

    return trains;
}



void Separate(TrainCar* train1, TrainCar* &train2, TrainCar* &train3) {

    TrainCar* current_car_test = train1;
    int engine_count = 0;
    int total_count = 0;
    while (current_car_test != NULL) {
        if (current_car_test->isEngine()) {
            engine_count++;
        }
        total_count++;
        current_car_test = current_car_test->next;
    }
    int post_engine_removal_size = total_count - engine_count;



    // Start at the first car of train1.
    TrainCar* current_car = train1;
    int engine_counter = 0;
    // Loop over all the cars in train1.
    while (current_car != NULL) {
        // If the current car is an engine, remove it from train1 and add it to train2 and train3.
        if (current_car->isEngine() && engine_counter % 2 == 0) {
            // Save a pointer to the engine that we're removing from train1.
            TrainCar* removed_engine = current_car;
            // Unlink the engine from train1.
            // If the engine is the first car of train1, set train1's first car pointer to the next car.
            if (current_car == train1) {
                train1 = current_car->next;
            }
            // If the engine has a previous car, update its next pointer to skip over the engine.
            if (current_car->prev != NULL) {
                current_car->prev->next = current_car->next;
            }
            // If the engine has a next car, update its previous pointer to skip over the engine.
            if (current_car->next != NULL) {
                current_car->next->prev = current_car->prev;
            }
            // Add the removed engine to the end of train2.
            if (train2 == NULL) {
                // If train2 is currently empty, make the removed engine the first car of train2.
                PushFront(train2,removed_engine);
            } else {
                // Otherwise, find the last car of train2 and add the removed engine after it.
                PushBack(train2,removed_engine);
            }
        } 

        else if (current_car->isEngine() && engine_counter % 2 != 0) {
            // Save a pointer to the engine that we're removing from train1.
            TrainCar* removed_engine = current_car;
            // Unlink the engine from train1.
            // If the engine is the first car of train1, set train1's first car pointer to the next car.
            if (current_car == train1) {
                train1 = current_car->next;
            }
            // If the engine has a previous car, update its next pointer to skip over the engine.
            if (current_car->prev != NULL) {
                current_car->prev->next = current_car->next;
            }
            // If the engine has a next car, update its previous pointer to skip over the engine.
            if (current_car->next != NULL) {
                current_car->next->prev = current_car->prev;
            }
            // Add the removed engine to the end of train3.
            if (train3 == NULL) {
                // If train3 is currently empty, make the removed engine the first car of train3.
                PushFront(train3,removed_engine);
            } else {
                // Otherwise, find the last car of train3 and add the removed engine after it.
                PushBack(train3,removed_engine);
            }
        }
        
        else {
            // If the current car is not an engine, just move on to the next car in train1.
            current_car = current_car->next;
        }
        engine_counter++;
    }
    // Seperating the stripped of engines train into two trains train 2 and 3 
    TrainCar* current_modified_car = train1;
    float halfway_point = post_engine_removal_size/2;
        int counter = 0;
        while(current_modified_car != NULL) {
            // Checking to see if there is an even amount of 
            if (counter < floor(halfway_point)) { 
                PushBack(train2,current_modified_car);
            }
            else {
                PushBack(train3,current_modified_car);
            }
            counter++;
    }

}
    













































    // TrainCar* current_car = train1;
    // while (current_car != NULL) {
    //     if(current_car->isEngine()) { 
    //         TrainCar* removed_engine = current_car;

    //     }
    //     current_car = current_car->next;
    // }