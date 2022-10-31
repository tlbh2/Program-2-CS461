// Online C++ compiler to run C++ program online
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdlib>
#include <string>

#define generations 100
#define population 500
#define num_courses 11
#define num_faculty 10
#define num_times 6
#define num_rooms 9

using namespace std;

// int getLenghtOfArray(string arr[100]) {
//     for (int i : arr) {
//     num ++;
//   }
//   cout << num << "\n";
//   return num;
// }



int sizeOfIntArray(int arr[10]) {
    int arr3[10];
    int size = 0;
    for (int i = 0; i < 10; i++) {
        arr3[i] = arr[i];
        // cout<< arr3[i] <<endl;    
    }

    for (int i : arr3)
        size++;
    return size;
    // cout << "size: " << size;
}


// int sizeOfStrArray(string arr[11]){
//     int arr3[11];
//     int size = 0;
//     for(int i=0; i<11; i++){
//         strcpy(arr3[i], arr[i]);
//         // cout<< arr3[i] <<endl;    
//     }

//     for(int i : arr3)
//         size++;
//   return size;     
//     // cout << "size: " << size;
// } NOT WORKING AT THE MOMENT


bool IsNotEmpty(const string& str)
{
    return !str.empty();
}

void GeneticAlgorithm(string time_table[population][num_courses][3], string courses_names[num_courses], string room_names[num_rooms], int room_capacity[num_rooms], int courses_expected_enrollment[num_courses], string courses_prefered_faculty[num_courses][10], string courses_other_faculty[num_courses][10], string faculty[num_faculty]) {


    // string time_table2[population][num_courses][3];

    float fitness = 0.0;
    float scores[population];

    string class_time_pairs[num_courses * 2];
    int class_time_index = 0;

    string ins_time_pairs[num_faculty * 2];
    int ins_time_index = 0;

    int classes_per_instructor[num_faculty];
    for (int i = 0; i < num_faculty; i++)
        classes_per_instructor[i] = 0;

    string room_per_course[num_courses];
    int time_slot_per_course[num_courses];

    for (int gen = 0; gen < generations; gen++) {
        fitness = 0.0;
        class_time_index = 0;
        ins_time_index = 0;
        for (int i = 0; i < num_faculty; i++)
            classes_per_instructor[i] = 0;


        cout << "////////////////////////////////" << endl;
        cout << "Generation = " << gen + 1 << endl;


        for (int pop = 0; pop < population; pop++) {
            fitness = 0;
            // cout << "\n\n\nPopulation = " << pop <<endl;
            class_time_index = 0;
            ins_time_index = 0;

            for (int ele = 0; ele < num_courses; ele++) {
                // cout << "\nCourse = " << courses_names[ele] <<endl;

                // getting class data
                string room = time_table[pop][ele][0];
                string time_slot = time_table[pop][ele][1];
                string instructor = time_table[pop][ele][2];

                // Checking 2 classes in 1 room at 1 time
                class_time_pairs[class_time_index] = room;
                class_time_index++;
                class_time_pairs[class_time_index] = time_slot;
                class_time_index++;

                // Checking 2 classes 1 teacher at 1 time
                ins_time_pairs[ins_time_index] = instructor;
                ins_time_index++;
                ins_time_pairs[ins_time_index] = time_slot;
                ins_time_index++;

                // Room capacity and enrollment size
                int room_index = 0;
                for (int i = 0; i < num_rooms; i++) {
                    if (room_names[i].compare(room) == 0)
                        break;
                    room_index++;
                }
                int expected_enrollment = courses_expected_enrollment[ele];
                int capacity = room_capacity[room_index];
                if (capacity < expected_enrollment) {
                    fitness = fitness - 0.5;
                    // cout << "capacity < expexted_enrollment" << endl;
                }
                else if (capacity > 6 * expected_enrollment) {
                    fitness = fitness - 0.4;
                    // cout << "capacity > 6*expexted_enrollment" << endl;
                }
                else if (capacity > 3 * expected_enrollment) {
                    fitness = fitness - 0.2;
                    // cout << "capacity > 3*expexted_enrollment" << endl;
                }
                else {
                    fitness = fitness + 0.3;
                    // cout << "Capacity Good" << endl;
                }


                // Check if course is taught by prefered
                bool prefered = false;
                int num_prefered = 0;

                for (int i = 0; i < 6; i++)
                {
                    if (courses_prefered_faculty[ele][i].empty())
                        break;
                    num_prefered++;
                }


                for (int i = 0; i < num_prefered; i++) {
                    if (courses_prefered_faculty[ele][i].compare(instructor) == 0) {
                        fitness += 0.5;
                        prefered = true;
                        // cout << "Taught by Prefered Teacher" << endl;
                        break;
                    }
                }

                // Check if course is taught by other
                int num_other = 0;
                bool other = false;

                for (int i = 0; i < 6; i++)
                {
                    if (courses_other_faculty[ele][i].empty())
                        break;
                    num_prefered++;
                }


                for (int i = 0; i < num_other; i++) {
                    if (courses_other_faculty[ele][i].compare(instructor) == 0) {
                        fitness += 0.2;
                        other = true;
                        // cout << "Taught by Other Teacher" << endl;
                        break;
                    }
                }


                // check if not by pref and other

                if (!prefered && !other) {
                    fitness -= 0.1;
                    // cout<<"Not Prefered Not other" << endl;
                }

                // Classes per teacher
                int faculty_index = 0;
                for (int i = 0; i < num_faculty; i++) {
                    if (faculty[i].compare(instructor) == 0)
                        break;
                    faculty_index++;
                }
                classes_per_instructor[faculty_index] = classes_per_instructor[faculty_index] + 1;

                // Courses are apart or together
                time_slot_per_course[ele] = stoi(time_slot);


                // Getting list of room of each course 
                room_per_course[ele] = room;

                // printing
                // cout << "room = " << room << endl;
                // cout << "time_slot = " << time_slot << endl;
                // cout << "instructor = " << instructor << endl;
                // cout << "capacity = " << capacity << endl;
                // cout << "Enrollment = " << expected_enrollment << endl;
                // cout << "Fitness : " << fitness <<endl;
            }

            //  This is to check if 2 classes have same room at same time
            // cout << "\n\nClass Time Pairs: " << endl;

            int class_time_douplicates_found = 0;


            for (int i = 0; i < num_courses * 2 - 2; i += 2) {
                if (class_time_pairs[i].empty()) {
                    break;
                    cout << "Breaks Applied" << endl;
                }
                // cout << class_time_pairs[i] << endl;
                // cout << class_time_pairs[i+1] << endl;
                for (int j = i + 2; j < num_courses * 2 - 1; j += 2) {
                    if (class_time_pairs[i].compare(class_time_pairs[j]) == 0 && class_time_pairs[i + 1].compare(class_time_pairs[j + 1]) == 0)
                        class_time_douplicates_found++;
                }
            }

            // Instructor load checking
            int num_fours = 0;
            for (int i = 0; i < num_faculty; i++) {
                if (i == 7)
                    continue;
                if (classes_per_instructor[i] >= 4)
                    fitness -= 0.5;
                else if (classes_per_instructor[i] == 1 || classes_per_instructor[i] == 2)
                    fitness -= 0.4;
            }

            // Course Specific
            if (abs(time_slot_per_course[0] - time_slot_per_course[1]) > 4)
                fitness += 0.5;

            if (time_slot_per_course[0] == time_slot_per_course[1])
                fitness -= 0.5;

            if (abs(time_slot_per_course[2] - time_slot_per_course[3]) > 4)
                fitness += 0.5;

            if (time_slot_per_course[2] == time_slot_per_course[3])
                fitness -= 0.5;

            bool op1 = abs(time_slot_per_course[0] - time_slot_per_course[2]) == 1;
            bool op2 = abs(time_slot_per_course[1] - time_slot_per_course[2]) == 1;
            bool op3 = abs(time_slot_per_course[0] - time_slot_per_course[3]) == 1;
            bool op4 = abs(time_slot_per_course[1] - time_slot_per_course[3]) == 1;

            // if CS 101 and CS191 sections are Consective and are in same department  

            if (op1 || op2 || op3 || op4)
            {
                // cout << "Consective classes";
                fitness += 0.5;
                if (!(op1 && (room_per_course[0][0] == room_per_course[2][0] == 'B' || room_per_course[0][0] == room_per_course[2][0] == 'K')))
                    fitness -= 0.4;

                if (!(op2 && (room_per_course[1][0] == room_per_course[2][0] == 'B' || room_per_course[1][0] == room_per_course[2][0] == 'K')))
                    fitness -= 0.4;

                if (!(op3 && (room_per_course[0][0] == room_per_course[3][0] == 'B' || room_per_course[0][0] == room_per_course[3][0] == 'K')))
                    fitness -= 0.4;

                if (!(op4 && (room_per_course[1][0] == room_per_course[3][0] == 'B' || room_per_course[1][0] == room_per_course[3][0] == 'K')))
                    fitness -= 0.4;

            }

            if (abs(time_slot_per_course[0] - time_slot_per_course[2]) == 1 || abs(time_slot_per_course[0] - time_slot_per_course[3]) == 1 || abs(time_slot_per_course[1] - time_slot_per_course[2]) == 2 || abs(time_slot_per_course[1] - time_slot_per_course[3]) == 2)
            {
                // cout << "Consective classes";
                fitness += 0.25;
            }

            if (abs(time_slot_per_course[0] - time_slot_per_course[2]) == 0 || abs(time_slot_per_course[0] - time_slot_per_course[3]) == 0 || abs(time_slot_per_course[1] - time_slot_per_course[2]) == 0 || abs(time_slot_per_course[1] - time_slot_per_course[3]) == 0)
            {
                // cout << "Consective classes";
                fitness -= 0.25;
            }

            // Instructor same time 2 classes check
            int ins_time_douplicates_found = 0;

            for (int i = 0; i < num_faculty * 2 - 2; i += 2) {
                // if(ins_time_pairs[i].empty()){
                //     break;
                //     cout << "Breaks Applied" << endl;
                // }
                // cout << ins_time_pairs[i] << endl;
                // cout << ins_time_pairs[i+1] << endl;
                for (int j = i + 2; j < num_faculty * 2 - 1; j += 2) {
                    if (ins_time_pairs[i].compare(ins_time_pairs[j]) == 0 && ins_time_pairs[i + 1].compare(ins_time_pairs[j + 1]) == 0)
                        ins_time_douplicates_found++;
                }
            }

            if (ins_time_douplicates_found == 0)
            {
                fitness += 0.2;
                // cout<<"No Teacher has 2 classes at 1 time";
            }
            else
            {
                fitness -= 0.2;
                // cout<<"1 or more teachers has 2 classes at 1 time";
            }

            // cout << "\nFitness without classtime dups " << fitness << endl;
            fitness = fitness - 0.5 * class_time_douplicates_found;
            // cout << "douplicates_found " << class_time_douplicates_found << endl;

            // cout << "\nFitness Score for this chromosome " << fitness << endl;
            // cout<< "Fitness " << fitness << endl;
            scores[pop] = fitness;
        }

        // return scores;
        // cout << "Scores " << endl;
        // for(int i=0; i<population; i++)
        // {
        //     cout << scores[i] << endl;
        // }

        int largest_index = 0;
        float largest = scores[0];
        for (int i = 0; i < population; i++) {
            if (scores[i] > largest) {
                largest_index = i;
                largest = scores[i];
            }
        }

        int sec_largest_index = 0;
        float sec_largest = scores[0];
        for (int i = 0; i < population; i++) {
            if (scores[i] > sec_largest && scores[i] != largest) {
                sec_largest_index = i;
                sec_largest = scores[i];
            }
        }

        // cout << "\n\n\n\n Largest = " << largest << endl;
        // cout << "\n Sec Largest = " << sec_largest << "\n\n\n\n";

        string parent1[num_courses][3];
        for (int i = 0; i < num_courses; i++)
            for (int j = 0; j < 3; j++)
                parent1[i][j] = time_table[largest_index][i][j];


        string parent2[num_courses][3];
        for (int i = 0; i < num_courses; i++)
            for (int j = 0; j < 3; j++)
                parent2[i][j] = time_table[sec_largest_index][i][j];



        // cout << "\n\nbest time_table\n" <<endl;

        // string pararent1[num_courses][3];
        for (int i = 0; i < num_courses; i++)
            for (int j = 0; j < 3; j++)
                // cout << parent1[i][j] << endl;
        // cout << "Best Score is " << largest << endl;

        // cout << "\n\nSecond Best Time Table is \n" << endl;

                for (int i = 0; i < num_courses; i++)
                    for (int j = 0; j < 3; j++)
                        // cout << parent2[i][j] << endl;
                // cout << "2nd Best Score is " << sec_largest << endl;


                // Mutate to get next generation
                        srand(time(0));
        // set time_table[0] to best and time_table[1] to 2nd best

        for (int i = 0; i < num_courses; i++)
            for (int j = 0; j < 3; j++) {
                time_table[0][i][j] = parent1[i][j];
                time_table[1][i][j] = parent2[i][j];
            }

        string child1[num_courses][3];
        string child2[num_courses][3];
        for (int pop = 2; pop < population - 1; pop += 2) {
            int index_1 = rand() % num_courses;
            int index_2 = rand() % 3;
            for (int k = 0; k < num_courses; k++) {
                for (int t = 0; t < 3; t++) {
                    child1[k][t] = parent1[k][t];
                    child2[k][t] = parent2[k][t];
                }
            }
            child1[index_1][index_2] = parent2[index_1][index_2];
            child2[index_1][index_2] = parent1[index_1][index_2];

            for (int i = 0; i < num_courses; i++)
                for (int j = 0; j < 3; j++) {
                    time_table[pop][i][j] = child1[i][j];
                    time_table[pop + 1][i][j] = child2[i][j];
                }
        }



        // cout << "\n\nNew Time Table \n\n";

        // for(int pop=0; pop<population; pop++)
        //     for(int i=0; i<num_courses; i++)
        //         for(int j=0; j<3; j++)
        //             cout << time_table[pop][i][j] << endl;

        cout << "Best Score = " << largest << endl;
        cout << "Best Time Table : \n" << endl;

        for (int i = 0; i < num_courses; i++) {
            cout << "Course = " << courses_names[i] << endl;
            for (int j = 0; j < 3; j++) {
                cout << parent1[i][j] << endl;
            }
            cout << "\n";
        }

        cout << "////////////////////////////////" << endl;

    }



}



int main() {

    string faculty[10] = { "Gharibi", "Gladbach", "Hare", "Nait-Abdesselam", "Shah", "Song", "Uddin", "Xu", "Zaman", "Zein el Din" };

    string courses_names[11] = { "CS101A", "CS101B", "CS191A", "CS191B", "CS201", "CS291", "CS303", "CS304", "CS494", "CS449", "CS451" };

    int courses_expected_enrollment[11] = { 50, 50, 50, 50, 50, 50, 60, 25, 20, 60, 100 };

    string courses_prefered_faculty[11][10] = { {"Gladbach", "Gharibi", "Hare", "Zein el Din"}, { "Gladbach", "Gharibi", "Hare", "Zein el Din"}, { "Gladbach", "Gharibi", "Hare", "Zein el Din"}, { "Gladbach", "Gharibi", "Hare", "Zein el Din"}, { "Gladbach", "Hare", "Zein el Din", "Shah"}, { "Gharibi", "Hare", "Zein el Din", "Song"}, { "Gladbach", "Zein el Din", "Hare"}, { "Gladbach", "Hare", "Xu"}, {"Xu", "Song"}, {"Xu", "Song", "Shah"}, {"Xu", "Song", "Shah"} };

    string courses_other_faculty[11][10] = { { "Zaman", "Nait-Abdesselam"}, { "Zaman", "Nait-Abdesselam"}, { "Zaman", "Nait-Abdesselam"}, { "Zaman", "Nait-Abdesselam"}, { "Zaman", "Nait-Abdesselam", "Song"}, { "Zaman", "Nait-Abdesselam", "Shah", "Xu"}, { "Zaman", "Song", "Shah"}, {"Zaman", "Song", "Shah", "Nait-Abdesselam", "Uddin", "Zein el Din"}, {"Nait-Abdesselam", "Zein el Din"}, { "Zein el Din", "Uddin"}, { "Zein el Din", "Uddin", "Nait-Abdesselam", "Hare"} };

    string room_names[9] = { "Katz 003", "FH 216", "Royall 206", "Royall 201", "FH 310", "Haag 201", "Haag 301", "MNLC 325", "Bloch 119" };

    int room_capacity[9] = { 45, 30, 75, 50, 108, 60, 75, 450, 60 };

    int time_slots[6] = { 10, 11, 12, 13, 14, 15 };



    srand(time(0));
    // Write C++ code here
    int i = rand() % 10;

    // THis is the code to get length of string array
    int size = 0;
    for (string element : courses_prefered_faculty[i]) {
        if (element.empty())
            break;
        size++;
        // cout<<"elements: "<< element << endl;
    }

    // int j = rand() % size;
    // cout << "Hello Mr. "<<i << " "<< j<< endl;
    // // cout << sizeOfStrArray(courses_prefered_faculty[i]) << endl;
    // cout << courses_prefered_faculty[i][j] << endl;

    // // sizeOfStrArray(courses_prefered_faculty[i]);

    // int generations = 10;
    // int population = 2;
    // int num_courses = 11;
    // int num_faculty = 10;
    // int num_times = 6;
    // int num_rooms = 9;

    string time_table[population][num_courses][3];


    for (int pop = 0; pop < population; pop++) {
        for (int cs = 0; cs < num_courses; cs++) {
            time_table[pop][cs][0] = room_names[rand() % num_rooms];
            time_table[pop][cs][1] = to_string(time_slots[rand() % num_times]);
            time_table[pop][cs][2] = faculty[rand() % num_faculty];
        }
    }

    // Printing Time Table
    // for(int pop=0; pop<population; pop++){
    //     cout << "\n\n\nPopulation = " << pop <<endl;
    //     for(int ele=0; ele<num_courses; ele++){
    //         cout << "\nCourse = " << courses_names[ele] <<endl;
    //         for(int j=0; j<3; j++)
    //             // cout<<"ele = " << ele << endl;
    //             cout<< time_table[pop][ele][j] << endl;
    //     }
    // }

    GeneticAlgorithm(time_table, courses_names, room_names, room_capacity, courses_expected_enrollment, courses_prefered_faculty, courses_other_faculty, faculty);


    cout << generations << "Generations Completed with the population of " << population << endl;

    return 0;
}