# Name: Anvesha Goydani
# Roll No.: 8
# PRN - F23112008
# Class: SE Comp 2
# Batch - P

"""
Problem Statement: 
Write a Python program to store marks scored in subject “Fundamental of Data Structure” by N students in the class. Write functions to compute following:
a) The average score of class
b) Highest score and lowest score of class
c) Count of students who were absent for the test
d) Display mark with highest frequency
"""

def accept(A):
    n = int(input("Enter the number of students: "))
    for i in range(n):
        mark = input("Enter the marks of student (or -1 for absent): ")
        try:
            A.append(int(mark))  # Convert to int for calculations
        except ValueError:
            print("Invalid input, setting to -1 (absent)")
            A.append(-1)  # Set as -1 if invalid input
    return A

def display(A):
    for mark in A:
        print(mark)
    return A

def average(A):
    total = 0.0
    count = 0
    for mark in A:
        if mark != -1:
            total += mark
            count += 1
    if count == 0:
        return 0  # Avoid division by zero if no valid marks
    avg = total / count
    return avg

def absent(A):
    count = A.count(-1)
    print(count)
    return count

def minimum(A):
    valid_marks = [mark for mark in A if mark != -1]
    if not valid_marks:
        return None  # Return None if no valid marks
    return min(valid_marks)

def maximum(A):
    valid_marks = [mark for mark in A if mark != -1]
    if not valid_marks:
        return None  # Return None if no valid marks
    return max(valid_marks)

def highest_freq(A):
    from collections import Counter
    marks = [mark for mark in A if mark != -1]
    if not marks:
        print("No valid marks to find frequency.")
        return None, 0
    freq_count = Counter(marks)
    most_common = freq_count.most_common(1)[0]
    mark, freq = most_common
    print(f"Marks with highest frequency is {mark} ({freq} times)")
    return mark, freq

def main():
    marks_list = []
    
    while True:
        print("\t1: Accept the information")
        print("\t2: Average marks of the students")
        print("\t3: Number of students absent")
        print("\t4: Maximum and minimum marks")
        print("\t5: Highest frequency marks scored")
        print("\t6: Exit the program")

        ch = int(input("Enter your choice: "))

        if ch == 6:
            print("End of program")
            break

        elif ch == 1:
            accept(marks_list)
            print("The marks of students are: ")
            display(marks_list)

        elif ch == 2:
            print("The average marks of students are: ")
            avg = average(marks_list)
            print(avg)

        elif ch == 3:
            print("The number of students absent are: ")
            absent(marks_list)

        elif ch == 4:
            min_mark = minimum(marks_list)
            max_mark = maximum(marks_list)
            print(f"Minimum mark is: {min_mark}")
            print(f"Maximum mark is: {max_mark}")
        
        elif ch == 5:
            highest_freq(marks_list)

main()

"""
OUTPUT:
	1: Accept the information
	2: Average marks of the students
	3: Number of students absent
	4: Maximum and minimum marks
	5: Highest frequency marks scored
	6: Exit the program
Enter your choice: 1
Enter the number of students: 10
Enter the marks of student (or -1 for absent): 55
Enter the marks of student (or -1 for absent): -1
Enter the marks of student (or -1 for absent): 99
Enter the marks of student (or -1 for absent): 36
Enter the marks of student (or -1 for absent): 70
Enter the marks of student (or -1 for absent): 85
Enter the marks of student (or -1 for absent): 55
Enter the marks of student (or -1 for absent): 37
Enter the marks of student (or -1 for absent): -1
Enter the marks of student (or -1 for absent): 88
The marks of students are: 
55
-1
99
36
70
85
55
37
-1
88
	1: Accept the information
	2: Average marks of the students
	3: Number of students absent
	4: Maximum and minimum marks
	5: Highest frequency marks scored
	6: Exit the program
Enter your choice: 2
The average marks of students are: 
64.0
	1: Accept the information
	2: Average marks of the students
	3: Number of students absent
	4: Maximum and minimum marks
	5: Highest frequency marks scored
	6: Exit the program
Enter your choice: 3
The number of students absent are: 
2
	1: Accept the information
	2: Average marks of the students
	3: Number of students absent
	4: Maximum and minimum marks
	5: Highest frequency marks scored
	6: Exit the program
Enter your choice: 4
Minimum mark is: 36
Maximum mark is: 99
	1: Accept the information
	2: Average marks of the students
	3: Number of students absent
	4: Maximum and minimum marks
	5: Highest frequency marks scored
	6: Exit the program
Enter your choice: 5
Marks with highest frequency is 55 (2 times)
	1: Accept the information
	2: Average marks of the students
	3: Number of students absent
	4: Maximum and minimum marks
	5: Highest frequency marks scored
	6: Exit the program
Enter your choice: 6
End of program

"""