#include <iostream>
#include <string.h>

//Defining created functions
char** toArray(std::string s, int size);
void insertionSort(char** array, int length);
void merge(char** array, int l, int m, int r);
void mergeSort(char** array, int l, int r);
void indexGen(char** array, int length, std::string s);
void clusterGen(char** array, int length);

//BEGIN
int main(int argc, char *argv[])
{
  //Initializing empty string
  std::string init_String = "";
  //Taking input from file, line by line
  while(std::getline(std::cin, init_String))
  { 
    //If statement searching for an empty line
    if (init_String.length() != 0)
    {
          //Taking the string size
          int string_size = init_String.length();
          //Creating array variable and calling toArray to fill/shift array
          char** arr = new char*[string_size];
          arr = toArray(init_String, string_size);
          //If user has entered "insertion", program runs using insertion sort
          if (strcmp(argv[1], "insertion") == 0)
          {
            //Calling function to perform insertion sort
            insertionSort(arr, string_size);
            //Calling function to calculate the index
            indexGen(arr, string_size, init_String);
            //Calling function to calculate the correct char clusters
            clusterGen(arr, string_size);
          }
        
          if (strcmp(argv[1], "merge") == 0)
          {
            //Calling function to perform merge sort
            mergeSort(arr, 0, string_size-1);
            //Calling function to calculate the index
            indexGen(arr, string_size, init_String);
            //Calling function to calculate the correct char clusters
            clusterGen(arr, string_size);
          }
        
          //Deallocating
          for (int i = 0; i < string_size; i++)
          {
              delete[] arr[i];    
          }
          delete[] arr;  
     
      }
      else
      {
       std::cout << 0 << "\n\n"; 
      }
    }
    
      
  //Ending main
  return 0;
}

//Function that takes original string and pushes it into a array of pointers that points to an array of chars
char** toArray(std::string s, int size)
{
  //Creating array of pointers
  char** array = new char*[size];
  //Looping through pointer array to create a new array for each pointer
  for (int i = 0; i < size; i++)
  {
      array[i] = new char[size]; 
  }
  //Filling the array with chars from the string 
  for (int i = 0; i < size; i++)
  {
      for (int j = 0; j < size; j++)
      {
          array[i][j] = s[j];
      }
      //Shifting the string one to the left
      s = s.substr(1,size) + s.substr(0,1);
  }
  //Ending function
  return array;
}

//Insertion Sort
void insertionSort(char** array, int length)
{
    //Initializing variables
    char* temp;
    int i;
    int j;
    
    //Iterating through array of shifted strings
    for (i = 1; i < length; i++)
    {
        j = i;
        //Comparing two strings lexographically
        while (j > 0 && (strcmp(array[j-1], array[j]) > 0))
        {
          //Swapping using pointers
          temp = array[j];
          array[j] = array[j-1];
          array[j-1] = temp; 
          //Continuing downward
          j--;     
        }   
    }   
}
//Merging function
void merge(char** array, int l, int m, int r)
{
     int i, j, k;
     int N1 = m - l + 1;
     int N2 = r - m;
      //Initializing right and left arrays
     char* L[N1];
     char* R[N2];
    
     for (i = 0; i < N1; i++)
     {
        //Adding the characters from the array to the left array
        L[i] = array[l + i];
     }
     
     for (j = 0; j < N2; j++)
     {
        //Adding the characters from array to the right array
        R[j] = array[m + 1 + j];
     }
     i = 0;
     j = 0;
     k = l;
     
  
     while (i < N1 && j < N2)
     {
        //Comparing the two strings to see if the left is less than or equal to the right
        if ((strcmp(L[i], R[j]) <= 0))
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
     }
     
     //Adding remaining right side
     while (i < N1)
     {
        array[k] = L[i];
        i++;
        k++;
     }
     //Adding remaining right side
     while (j < N2)
     {
        array[k] = R[j];
        j++;
        k++;
     }
}
//Merge Sort
void mergeSort(char** array, int l, int r)
{
     if (l < r)
     {
        int m = l + (r-l)/2;
        mergeSort(array, l, m);
        mergeSort(array, m+1, r);
        merge(array, l, m, r);
     }    
}

//Function to generate the index assuming the 2D array has already been sorted
void indexGen(char** array, int length, std::string s)
{
  //Initializing
  int index;
  //Making the original string a char array for later comparison
  const char* string_arr = s.c_str();
  //Outer loop through array
  for (int i = 0; i < length; i++)
  {
    //Inner loop through array
    for (int j = 0; j < length; j++)
    {
        //Comparing each letter of the string with the array
        //If there is any incongruence inner for loop breaks and it moves to the next index
        if (string_arr[j] != array[i][j])
        {
          break; 
        }
        //If the inner for loop hasn't broken, and the final character in the strings match, return that index
        if ((string_arr[j] == array[i][j]) && (j == length - 1))
        {
          index = i;
          //Writing out to the stdout
          std::cout << index << "\n";
        }
    }
  } 
}

//Function to generate the encoding clusters 
void clusterGen(char** array, int length)
{
  //Creating a 1D array that is comprised of the final characters of every index
  char* arrayOut = new char[length];
  //Filling said array
  for (int i = 0; i < length; i++)
  {
    arrayOut[i] = array[i][length-1]; 
  }
  
  //Initializing count, starting at one because there is always at least one char
  int count = 1;
  //Iterating through array
  for (int j = 0; j < length; j++)
  {
    //If the next matches this index, add to the count
    if (arrayOut[j] == arrayOut[j+1])
    {
      count++; 
    }
    //If the next doesn't match, just output the current count, and the char in question
    if (arrayOut[j] != arrayOut[j+1])
    {
      std::cout << count << ' ' << arrayOut[j] << ' ';
      //Reset the count back to one before the for loop restarts
      count = 1;
    }
  }
  //Formatting
  std::cout << "\n";
  //Deallocating memory
  delete[] arrayOut;
}
//END OF PROGRAM
