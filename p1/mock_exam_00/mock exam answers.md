Q1
A Syntax Error is an Error in how the language is written and makes the program fail to compile.
A runtime error is something that makes the program fail after it was compiled, but due to something in the code the machine cant execute, for example an index that is out of range. 
A logic error doesnt make the program fail, it just produces an unexpected/undesired output. it is because the logic of the program is flawed. 

Q2
O(n) means it runs in linear time. That means for a vector with n elements, each element is checked exactly once. eg: printing a vector:
std::vector<int> v (n);
for (int i  = 0; i < v.size(); i ++) {
	std::cout << v.at(i) << " ";
}
std::endl;
>
Q3
no, since there is a number as the first character

Q4
the output is 3.0, since the operation is carried out between two integers, making it 3, and then assigned to a double, making it 3.0.

Q5
const double taxRate = 0.21;

Q6
2

Q7
F
None of the if statements are satisfied, so only the else is invoked.

Q8
i dont think we covered this, but i would guess that if i is out of the index range of the vector, then it would lead to a runtime error if the order was switched.

Q9
2 4 

Q10 
the difference is pass by value creates a local copy of the variable, pass by reference actually sees and modifies the variable that was given to the function as a parameter. If you have a very large vector, you would use pass by reference to save memory space. 

Q11
A base case is the case i which the function decides to not call itself further and return to the parent function. If a recursive function is missing a base case, it would run forever and eventually crash due to missing memory space. 

Q12
it follows the LIFO principle (Last In First Out). Two core operations would be push and pop, either adding an element to the "top" or removing the "top" element. 

