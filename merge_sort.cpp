/*
Name: Anvesha Goydani
Roll No.: 8
PRN - F23112008
Class: SE Comp 2
Batch - P
*/

/*
Problem Statement:
Read marks of 'N' Students for the subject Data Structures. 
Sort the data and display the topper for the Subject.
*/

#include<iostream>
using namespace std;

void merge(int a[], int beg, int mid, int end)
{
    int i, j, k;
    int n1 = mid - beg + 1;
    int n2 = end - mid;
    int leftarray[n1], rightarray[n2];

    for(i=0; i<n1; i++)
    {
        leftarray[i] = a[beg + i];
    }
    for(j=0; j<n2; j++)
    {
        rightarray[j] = a[mid + 1 + j];
    }
    i = 0;
    j = 0;
    k = beg;
    while(i<n1 && j<n2)
    {
        if(leftarray[i] <= rightarray[j])
        {
            a[k] = leftarray[i];
            i++;
        }
        else
        {
            a[k] = rightarray[j];
            j++;
        }
        k++;
    }
    while(i<n1)
    {
        a[k] = leftarray[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        a[k] = rightarray[j];
        j++;
        k++;
    }
};

void mergesort(int a[], int beg, int end)
{
    if (beg < end)
    {
        int mid = (beg + end) / 2;
        mergesort(a, beg, mid);
        mergesort(a, mid + 1, end);
        merge(a, beg, mid, end);
    }
};

void printarray(int a[], int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        cout<<a[i]<<" ";
    }
};

int main()
{
    int n;
    cout<<"Enter number of students: ";
    cin>>n;
    int a[n];
    cout<<"Enter marks of students: ";
    for(int i=0; i<n; i++)
    {
        cin>>a[i];
    }
    cout<<"\nUnsorted array: ";
    printarray(a, n);
    mergesort(a, 0, n-1);
    cout<<"\nSorted array: ";
    printarray(a, n);

    cout<<"\nTop 5 marks are: ";
    for(int i=1; i<6; i++){
        cout<<a[n-i]<<" ";
    }

}

/*
OUTPUT:
Enter number of students: 10
Enter marks of students: 95
Enter marks of students: 36
Enter marks of students: 58
Enter marks of students: 72
Enter marks of students: 48
Enter marks of students: 100
Enter marks of students: 63
Enter marks of students: 77
Enter marks of students: 42
Enter marks of students: 81

Unsorted array: 95 36 58 72 48 100 63 77 42 81 
Sorted array: 36 42 48 58 63 72 77 81 95 100 
Top 5 marks are: 100 95 81 77 72
*/