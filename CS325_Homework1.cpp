#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

//declare global variables
vector <int> input;
int number;
int bruteForceDifference, bruteForcePoint1, bruteForcePoint2;
int closestPairDifference, closestPairPoint1, closestPairPoint2;
int leftDistance, leftP1, leftP2;
int rightDistance, rightP1, rightP2;
int middleDistance, middleP1, middleP2;

//declare closestPair function which takes parameters passed by reference
void closestPair(vector <int> &vect, int &dist, int &point1, int &point2) {
    //declare vectors so the input vector can be split up if necessary
    vector <int> leftVector;
    vector <int> rightVector;
    vector <int> middleVector;
    //declare vector to hold the distances between points
    vector <int> distances;
    //declare maps to hold the points corresponding to the distance key value
    map <int, int> points1;
    map <int, int> points2;
    //declare map iterator
    map <int, int>::iterator it;
    
    //base case
    //if vector is 2 then the dist is the difference and the points are set
    if (vect.size() == 2) {
        dist = abs(vect[0] - vect[1]);
        point1 = vect[0];
        point2 = vect[1];
        return;
    }
    
    //base case
    //if vector is 3 then compare the first and second and second and third
    //set dist to the smallest difference and set the points to the corresponding
    if (vect.size() == 3) {
        dist = abs(vect[0] - vect[1]);
        point1 = vect[0];
        point2 = vect[1];
        if (abs(vect[1] - vect[2]) < dist) {
            dist = abs(vect[1] - vect[2]);
            point1 = vect[1];
            point2 = vect[2];
            return;
        } else {
            return;
        }
    }
    
    //take the first half of the input vector and push it into the leftVector
    for (int i = 0; i < (vect.size()/2); ++i) {
        leftVector.push_back(vect[i]);
    }
    
    //take the other half of the input vector and push it into the rightVector
    for (int i = (vect.size()/2); i < vect.size(); ++i) {
        rightVector.push_back(vect[i]);
    }
    
    //take the last element of the leftVector and the first element of rightVector and put into middleVector
    middleVector.push_back(leftVector.back());
    middleVector.push_back(rightVector[0]);
    
    //recursively call closestPair function for all vectors
    //push the smallest distance of each vector into the distances vector
    //push the corresponding points into the points maps with the distance key value
    closestPair(leftVector, leftDistance, leftP1, leftP2);
    distances.push_back(leftDistance);
    points1[leftDistance] = leftP1;
    points2[leftDistance] = leftP2;
    
    closestPair(rightVector, rightDistance, rightP1, rightP2);
    distances.push_back(rightDistance);
    points1[rightDistance] = rightP1;
    points2[rightDistance] = rightP2;

    closestPair(middleVector, middleDistance, middleP1, middleP2);
    distances.push_back(middleDistance);
    points1[middleDistance] = middleP1;
    points2[middleDistance] = middleP2;
    
    //sort the distances vector
    sort(distances.begin(), distances.end());
    //the first value at index 0 is the smallest distance after sorted
    dist = distances[0];
    
    //use the iterator to find the corresponding left and right point to the dist key value
    it = points1.find(distances[0]);
    if (it != points1.end()) {
        point1 = points1.find(distances[0])->second;
    }
    it = points2.find(distances[0]);
    if (it != points2.end()) {
        point2 = points2.find(distances[0])->second;
    }
}

int main()
{
    //continuously read in input and push into input vector
    while (cin >> number) {
        input.push_back(number);
    }
    
    //if input size is less than 2 then prompt show error
    if (input.size() < 2) {
        cerr << "You must input at least 2 integers" << endl;
        exit(1);
    }
    
    //sort the input vector
    sort(input.begin(), input.end());

    //brute force
    //instantiate the difference as the difference between the first 2 integers
    bruteForceDifference = abs(input[0] - input[1]);
    //instantiate the points at the first 2 integers
    bruteForcePoint1 = input[0];
    bruteForcePoint2 = input[1];
    //set index i to the first element and increment it until the size of the vector minus 1
    for (int i =0; i < input.size()-1; ++i) {
        //set index j to the second element and increment it until the end of the vector
        for (int j = i+1; j < input.size(); ++j) {
            //if the difference of the comparison is less than the difference being held
            if (abs(input[i] - input[j]) < bruteForceDifference) {
                //set the the difference to the new smaller difference
                bruteForceDifference = abs(input[i] - input[j]);
                //set the points corresponding to the new difference
                bruteForcePoint1 = input[i];
                bruteForcePoint2 = input[j];
            }
        }
    }

    //print out the brute force closest pair
    printf("Brute force closest pair: (%i%c%i%c\n", bruteForcePoint1, ',' , bruteForcePoint2, ')');
    
    //recursive divide and conquer algorithm
    //call closestPair function on input vector
    closestPair(input, closestPairDifference, closestPairPoint1, closestPairPoint2);
    //print the recursive divide and conquer closest pair
    printf("Recursive divide and conquer closest pair: (%i%c%i%c\n", closestPairPoint1, ',' , closestPairPoint2, ')');
}

