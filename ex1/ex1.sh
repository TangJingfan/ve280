#!/bin/bash
mkdir Coursework
cd ./Coursework
mkdir assignments reports
cd ./assignments
touch assignment1.txt assignment2.txt
echo "This is assignment 1." >assignment1.txt
echo "This is assignment 2." >assignment2.txt
cp assignment1.txt ../reports
mv assignment2.txt renamed_assignment.txt
mv renamed_assignment.txt ../reports
cd ..
mkdir exams
touch exams/exam1.txt exams/exam2.txt
cp -r exams ./reports
cp -r exams ./assignments
rm -r exams
ls -l >directory_info.txt
diff ./assignments/assignment1.txt ./reports/renamed_assignment.txt >content_comparison.txt
