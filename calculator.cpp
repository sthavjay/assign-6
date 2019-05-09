// Bijaya Shrestha
//  Section 2
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class digit
{
    public:
    int data;
    digit *next = nullptr;
};

// Suggested functions
digit * loadNumber(ifstream & file);
int digcmp(digit * left, digit *right);
char getOperator(ifstream & file);
void writeNumber(digit * num, ofstream & file);
void deleteNumber(digit * num);
digit * addNumbers(digit * left, digit * right);
digit * subNumbers(digit * left, digit * right);
void writeNumRecurse(digit * num, ofstream & file);
void setNeg(digit * num);
void printNum(digit * num);
void printNumrecurse(digit * num);
void subCarry(digit * head, digit * prev);

int main()
{
    digit * left, * right, * result;
    char charOperator;
    int num;
    ifstream inFile ("largeNumbers.txt");
    ofstream outFile ("output.txt");

    while (!inFile.eof())
    {
        // implement program logic here
        left = loadNumber(inFile);
        right = loadNumber(inFile);
        charOperator = getOperator(inFile);

        if(charOperator == '+')
        {
          result = addNumbers(left, right);
          writeNumber(result, outFile);
          deleteNumber(result);
          deleteNumber(left);
          deleteNumber(right);
        }
    }
    outFile.close();
    inFile.close();
    return 0;
}

// =============================================================================
/*
*  returns a number <0 || 0 || >0
*  <0 right number is larger
*  0  the numbers are equal
*  >0 left number is larger
*  only works if the number is stored in reverse order
*  CODED BY INSTRUCTOR
*/
int digcmp(digit * left, digit * right){
    int result = 0;
    do
    {
        if (left->data - right->data == 0)
        {
          // take no action
        }
        else
        {
          result = left->data - right->data;
        }
        left = left->next;
        right = right->next;

    } while (left != nullptr && right != nullptr);
    result = 0;
    if (left == nullptr && right != nullptr)
    {
        // right number is larger
        result = -1;
    }

    if (left != nullptr && right == nullptr)
    {
        // left number is larger
        result = 1;
    }
    return result;
}
// =============================================================================

// =============================================================================
// This function will read from largeNumbers.txt and load each individual
// digit into a linked list in reverse order. It will stop when the number on
// that particular line ends. It returns the head pointer pointing to the front
// of the list. i.e. original: 1234567  list: 7654321
digit * loadNumber(ifstream & file)
{
  digit *head = nullptr;
  digit *newDigit = nullptr;
  char charNum;
  int num;

  while(!file.eof())
  {
    file.get(charNum);
    if(charNum == '\n')
    {
      break;
    }
    newDigit = new digit;
    if(head == nullptr)
    {
      num = charNum - 48;
      newDigit->data = num;
      head = newDigit;
    }
    else
    {
      num = charNum - 48;
      newDigit->data = num;
      newDigit->next = head;
      head = newDigit;
    }
  }
  return head;
}
// =============================================================================

// =============================================================================
// This function reads from largeNumbers.txt and grabs the operator. It returns
// the operator it grabs.
char getOperator(ifstream & file)
{
  // hint: use get
  char op;
  string discard;

  file.get(op);
  getline(file, discard);

  return op;
}
// =============================================================================

// =============================================================================
void printNumrecurse(digit * num)
{
  return;
}
// =============================================================================

// =============================================================================
void printNum(digit * num)
{
  return;
}
// =============================================================================

// =============================================================================
void writeNumRecurse(digit * num, ofstream & file)
{
  return;
}
// =============================================================================

// =============================================================================
// This function will write the data in the linked list to output.txt.
void writeNumber(digit * num, ofstream & file)
{
  digit *writeDigit = nullptr;

  for(writeDigit = num; writeDigit != nullptr; writeDigit = writeDigit->next)
  {
    file << writeDigit->data;
  }
  file << endl;
}
// =============================================================================

// =============================================================================
// This function will delete the data in the list once it is no longer needed.
void deleteNumber(digit * num)
{
  digit *deleteDigit = nullptr;
  while(num != nullptr)
  {
    deleteDigit = num;
    num = num->next;
    delete deleteDigit;
  }
}
// =============================================================================

// =============================================================================
// This function adds the left and right numbers and returns the a pointer that
// pointing to a list containing the answer. There are three cases: if both
// numbers are the same size, if the left number is bigger than the rightm and
// if the right number is bigger than left. Based on these cases the digits will
// be added together and a node will be added to a new list. Will handle carries.
digit * addNumbers(digit * left, digit * right)
{
  digit *sum = nullptr;
  digit *head = nullptr;
  int result = 0, firstDigit = 0, secondDigit = 0;

// Case 1: Both numbers are equal or have not ended
  while(left != nullptr && right != nullptr)
  {
    sum = new digit;
    result = left->data + right->data + secondDigit;

    if(result > 9)
    {
      firstDigit = result % 10;
      secondDigit = result / 10;

      if(head == nullptr)
      {
        sum->data = firstDigit;
        head = sum;
      }
      else
      {
        sum->data = firstDigit;
        sum->next = head;
        head = sum;
      }

      if(left->next == nullptr && right->next == nullptr)
      {
        sum = new digit;
        sum->data = secondDigit;
        sum->next = head;
        head = sum;
      }
    }
    else
    {
      if(head == nullptr)
      {
        sum->data = result;
        head = sum;
      }
      else
      {
        sum->data = result;
        sum->next = head;
        head = sum;
      }
    }
    left = left->next;
    right = right->next;
  }

  // Case 2: left number is larger than right number or right number has ended
  while(left != nullptr && right == nullptr)
  {
    sum = new digit;
    result = left->data + secondDigit;

    if(result > 9)
    {
      firstDigit = result % 10;
      secondDigit = result / 10;

      if(head == nullptr)
      {
        sum->data = firstDigit;
        head = sum;
      }
      else
      {
        sum->data = firstDigit;
        sum->next = head;
        head = sum;
      }

      if(left->next == nullptr && right == nullptr)
      {
        sum = new digit;
        sum->data = secondDigit;
        sum->next = head;
        head = sum;
      }
    }
    else
    {
      if(head == nullptr)
      {
        sum->data = result;
        head = sum;
      }
      else
      {
        sum->data = result;
        sum->next = head;
        head = sum;
      }
    }
    left = left->next;
  }

  // Case 3: right number is larger than left number or left number has ended
  while(left == nullptr && right != nullptr)
  {
    sum = new digit;
    result = right->data + secondDigit;

    if(result > 9)
    {
      firstDigit = result % 10;
      secondDigit = result / 10;

      if(head == nullptr)
      {
        sum->data = firstDigit;
        head = sum;
      }
      else
      {
        sum->data = firstDigit;
        sum->next = head;
        head = sum;
      }

      if(left == nullptr && right->next == nullptr)
      {
        sum = new digit;
        sum->data = secondDigit;
        sum->next = head;
        head = sum;
      }
    }
    else
    {
      if(head == nullptr)
      {
        sum->data = result;
        head = sum;
      }
      else
      {
        sum->data = result;
        sum->next = head;
        head = sum;
      }
    }
    right = right->next;
  }

  return sum;
}
// =============================================================================

// =============================================================================
void subCarry(digit * head, digit * prev)
{
  return;
}
// =============================================================================

// =============================================================================
digit * subNumbers(digit * left, digit * right)
{
  return nullptr;
}
// =============================================================================

// =============================================================================
void setNeg(digit * num)
{
  return;
}
