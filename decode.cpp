#include <iostream>
#include <string.h>
#include <ctype.h>

void insertionSort(std::string& encodedStr, int length);
void mergeSort(std::string& encoded, int l, int r);
std::string getLast(std::string str, int length);
int searchArr(int* arr, int index, int length);
int* getNext(std::string last, std::string first, int length);
void decodedString(std::string last, int* arr, int index, int length);
//BEGIN
int main(int argc, char *argv[])
{
  //Initializing empty string

  std::string index = "";
  std::string encodedString = "";

  //Taking input from file, line by line
  while(std::getline(std::cin, index))
  { 
    //Taking commandline input to check if insertion or merge sort will be used
     if (strcmp(argv[1], "merge") == 0)
      {
      //Casting the index to an integer for later use
      int idx = std::stoi(index);
      //Getting the line for the string
      std::getline(std::cin, encodedString);
        //If the string isn't a newline, decode it
        if (encodedString.length() != 0)
        {
          //Getting the length of the string
          int length = encodedString.length();
          //Using getLast to get the "last" column
          std::string last = getLast(encodedString, length);
          //Since the sort works in place, we make unsorted the "last" column
          //because the "last" shall become "first" 
          std::string unsorted = last;
	        //Getting the length of the now shorter string
          int lastLength = last.length();
          //Sorting last turning it into first
          mergeSort(last, 0, lastLength - 1);
          //nextArr becomes the next column
          int* nextArr = getNext(unsorted, last, lastLength);
          //Decoding and outputting the decoded string
          decodedString(unsorted, nextArr, idx, lastLength);
          //Deallocating memory
          delete[] nextArr;
        }
        //If the string is a newline, just print a newline
        else
        {
          std::cout << "\n";
        }
        
      }
     //Taking commandline input to check if insertion or merge sort will be used
     if (strcmp(argv[1], "insertion") == 0)
      {
        //Casting the index to an integer for later use
        int idx = std::stoi(index);
        //Getting the line for the string
        std::getline(std::cin, encodedString);
        if (encodedString.length() != 0)
        {
          //Getting the length of the string
          int length = encodedString.length();
          //Using getLast to get the "last" column
          std::string last = getLast(encodedString, length);
          //Since the sort works in place, we make unsorted the "last" column
          //because the "last" shall become "first"
          std::string unsorted = last;
	        //Getting the length of the now shorter string
          int lastLength = last.length();
          //Sorting last turning it into first
          insertionSort(last, lastLength);  
          //nextArr becomes the next column
          int* nextArr = getNext(unsorted, last, lastLength);
          //Decoding and outputting the decoded string
          decodedString(unsorted, nextArr, idx, lastLength);
          //Deallocating memory
          delete[] nextArr;
        }
        else
        {
          std::cout << "\n";
        }
        
      }
  }
  return 0;
}

void insertionSort(std::string& encodedStr, int length)
{
    //Initializing variables
    char temp;
    int i;
    int j;
    //Iterating through array of shifted strings
    for (i = 1; i < length; i++)
    {
        j = i;
        //Comparing two strings lexographically
        while (j > 0 && (encodedStr[j-1] > encodedStr[j]))
        {
          //Swapping using pointers
          temp = encodedStr[j];
          encodedStr[j] = encodedStr[j-1];
          encodedStr[j-1] = temp; 
          //Continuing downward
          j--;     
        }   
    }   
}

std::string getLast(std::string str, int length)
{
  //Copying the passed string
  std::string cpy = str;
  //Creating an empty string to be last
  std::string nowLast = "";
  //Initializing an empty char variable
  char tempChar = ' ';
  for (int i = 0; i < length/2; i+=2)
  {
    //Getting the size of that cluster
    int value = std::stoi(cpy);
    //Finding out how many digits the value is
    int len = std::to_string(value).length();
    //Cutting off the cluster size and space to access the character
    cpy = cpy.substr(len + 1);
    //Taking the character from the cluster
    tempChar = cpy[0];
    //Looping value times to push the correct amount of characters onto the "last" string
    for (int j = 0; j < value; j++)
    {
      nowLast = nowLast + tempChar;
    }
    //Moving to the next cluster size
    cpy = cpy.substr(2);
  }
  return nowLast;
}

//Get next takes the two strings and returns the array for the "next" column
int* getNext(std::string last, std::string first, int length)
{
  //Creating array to return
  int* arr = new int[length];
  for (int k = 0; k < length; k++)
  {
    //Filling array with negative numbers since index will never be < 0
    arr[k] = -1;
  }


  for (int i = 0; i < length; i++)
  {
    
    for (int j = 0; j < length; j++)
    {
      //searchArr checks if this index has already been used for next
      int flag = searchArr(arr, j, length);
      //if the matching characters aren't in the same index, and it hasn't been used, add to the array
      if (i != j && (first[i] == last[j]) && (flag == 0))
      {
        //Adding the index to the "next" array
        arr[i] = j;
        //Breaking from the loop
        j = length;
      }
    }
  }
  return arr;
}

//Used to make sure an index isn't being added repeatedly to the "next" array
int searchArr(int* arr, int index, int length)
{
  //Flag 0 = does not appear in array
  int flag = 0;
  for (int i = 0; i < length; i++)
  {
    if (arr[i] == index)
    {
      //Flag 1 = appears in array
      flag = 1;
    } 
  }
  return flag;
}

//Merge function used in conjuntion with mergeSort
void merge(std::string& encoded, int l, int m, int r)
{
     int i, j, k;
     int N1 = m - l + 1;
     int N2 = r - m;
      //Initializing right and left arrays
     std::string L = "";
     std::string R = "";
     L.resize(N1, ' ');
     R.resize(N2, ' ');
    
     for (i = 0; i < N1; i++)
     {
        //Adding the characters from the array to the left array
        L[i] = encoded[l + i];
     }
     
     for (j = 0; j < N2; j++)
     {
        //Adding the characters from array to the right array
        R[j] = encoded[m + 1 + j];
     }
     i = 0;
     j = 0;
     k = l;
     
  
     while (i < N1 && j < N2)
     {
        //Comparing the two strings to see if the left is less than or equal to the right
        if (L[i] <= R[j])
        {
            encoded[k] = L[i];
            i++;
        }
        else
        {
            encoded[k] = R[j];
            j++;
        }
        k++;
     }
     
     //Adding remaining right side
     while (i < N1)
     {
        encoded[k] = L[i];
        i++;
        k++;
     }
     //Adding remaining right side
     while (j < N2)
     {
        encoded[k] = R[j];
        j++;
        k++;
     }
}

//Merge Sort
void mergeSort(std::string& encoded, int l, int r)
{
     if (l < r)
     {
        int m = l + (r-l)/2;
        mergeSort(encoded, l, m);
        mergeSort(encoded, m+1, r);
        merge(encoded, l, m, r);
     }    
}

void decodedString(std::string last, int* arr, int index, int length)
{
  int start = arr[index];
  for (int i = 0; i < length; i++)
  {
    std::cout << last[start];
    start = arr[start];
  }

}

//END OF PROGRAM