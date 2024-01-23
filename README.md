# PART_1
# Goals

```
Implement a singly linked list that stores key value pairs. Nodes in the list can’t share the same key. If a
key/value pair is inserted into the list and another node in the list already has that key, that node’s value
is replaced with the new value. You need to implement all functions as described in the header file. The
comments above each function tell you what you need to do, but if you have any questions post them on
Piazza.
```
# Submission instructions

```
Upload your hash_list.h and hash_list.cpp to Gradescope. Any tests that you pass will be in green, any that
you fail will be in red, and for any failed test the output from that run (ie. everything that was printed to
the terminal) will be displayed in a box under the tests name
You may print out useful information for debugging purpose. However, when making your final submission
on Gradescope, please make sure to comment out these printing statement. You may submit multiple time
on Gradescope.
```
# Restrictions

- Your .cpp file is only allowed to include hash_list.h, no other includes are allowed.
- You may not use any standard containers.
- You aren’t allowed to delete any provided public/private functions/member variables from hash_list.h.
    You may add private or public functions/member variables if you want, but you can’t remove anything
    from hash_list.h that was there when we distributed it to you.

# Example

```
Let’s suppose we have a list with one node
list_head -> old_node(key = 1, value = 0.3)
```
We decide to insert the following node into the list

```
new_node(key = 0, value = 10)
```
We first traverse the list and find that there are no nodes that share a key with our new_node, so we’re
free to insert the new_node into our list. In this example we’re inserting at the front of the list. Your
implementation is free to insert nodes into the list wherever you want, you just need to make sure that no
two nodes share a key.
list_head -> new_node(key = 0, value = 10) -> old_node(key = 1, value =
0.3)

```
Let’s then insert another node that shares a key with the original node
duplicate_key_node(key = 1, value = 0.9)
```
```
Since the key is already shared with another node we replace the value of old_node with the value of
duplicate_key_node
list_head -> new_node(key = 0, value = 10) -> old_node(key = 1, value =
0.9)
```

# std::optional<T> discussion

```
Imagine you implement a function for your list that takes an index as an input and returns the value of the
node at that index.
int get_value_at_index(int index)
{
// return value at node index
}
```
What should you do if the user passes you an index that’s larger than the size of your list? Or they pass in a
negative value? You could return a special value, say -1, but there’s the possibility that -1 is actually stored
in your list, so a special placeholder value doesn’t work. Really what you want is to return 2 things.

1. Some indication that your function succeeded
2. A value that is only relevant if the function succeeded

```
In C you could do something like this (assuming you’ve included stdbool.h)
int get_value_at_index(int index , bool* success)
{
if (index >= size || index < 0)
{
*success = false;
return 0;
}
```
```
*success = true;
// search for value at index and return it
}
```
```
This solves the problem, but it leads to an additional problem. What happens if you call get_value_at_index
but then forget to check if it succeeded?
// assume we have a list called our_list
bool success;
int index = 10;
```
```
int ret_val = our_list.get_value_at_index(index , &success);
```
```
// forgot to check if the function succeeded , now your program might
print out garbage
```
```
std::cout << "Value at index " << index << " is " << ret_val << std::endl;
```
```
The same issue exists with null pointers. Functions that return a pointer usually indicate failure by returning
a null pointer, but the user is free to use the returned pointer without checking if it’s null. The best case
scenario here is that your program crashes immediately and you spend a few hours debugging. The worst case
is that your program doesn’t crash, you ship the code, and then your bug leads to a security vulnerability
that costs your company a lot of money.
The fundamental issue is that we want to force the caller of our function to check if our function succeeded
before they use the value we returned. And this is where optionals come into play.
Optionals are basically a struct that holds a boolean flag and a value (note: this isn’t real c++ code, but it’s
close enough to be useful)
```

```
struct Optional <T>
{
bool has_value;
T stored_value;
}
```
```
Note: That weird<T>syntax is a template, something that we’ll get to later in the course. For now all that
you need to know is that
```
1. T needs to be the type you want to store in the optional (so int ,
    float , std::string , etc)
2. When you declare an optional you need to specify that type it will
    contain. So std::optional <int > is an optional that holds an integer.

```
The reason this is so powerful is that now you can return the success flag and the value (if the function
succeeded) as one object. The code below gives an example of what this looks like
std::optional <int > get_value_at_index(int index)
{
if (index >= size)
{
return std:: nullopt; // std:: nullopt is an empty optional , could
also just return {}
}
```
```
// search for value at index and return it
}
```
```
Now the user can’t just use the optional without thinking about if it succeeded
int index = 10;
std::optional <int > ret_val = our_list.get_index (10);
```
```
std::cout << "Value at index " << index << " is " << ret_val.value () <<
std::endl; // Will crash if ret_val is empty
```
```
This might look the same but the key difference is that ifret_valdoesn’t contain a value, the call tovalue()
will fail and the program will crash. This means that even if you forget to check if the optional has a value
you won’t get silent errors like in C. Once you realize why your program crashed you’ll add a check like the
following
int index = 10;
std::optional <int > ret_val = our_list.get_index (10);
```
```
if (ret_val.has_value ()) // has_value () returns true if optional has a
value , otherwise false
{
std::cout << "Value at index " << index << " is " <<
ret_value.value () << std::endl;
}
```
```
Now we’ve forced the user to check if the function succeeded (unless you want your program to crash)*. This
makes it much less likely that you’ll end up hunting for bugs later, as the crash will happen when you try
and access the value as opposed to at some random point in your program.
```
*There is a small caveat that you could still ignore checking if your optional has a value and just get lucky
and only pass in valid indexes. This is why good testing is required; if you have a good test suite the chance


```
of using the value of an unverified optional AND never passing in invalid arguments to the functions you’re
testing is small.
If you have questions about optionals I recommend this piece of documentation. This also shows you how
to return an optional that contains a value. The above example only shows you how to return an empty
optional.
```
# Destructor discussion

```
You should pay particular attention to the implementation of the destructor for this lab. Here are a few
things to think about
```
- Why should you define an explicit destructor for this lab? [Hint: Memory leaks]
- Your destructor can’t just delete the head of the linked list. Why? What pitfalls could arise?
For questions about how destructor work I recommend looking at the following FAQ page

# Testing Locally

We have provided some example traces and amain.cppfile to help you test your code locally before submitting.
Themain.cppcontains some basic tests for both parts 1 and 2 of the lab, and the trace files are examples of
the traces we will run your program on when testing.
The providedMakefilehas targetspart1andpart2to run the default tests for parts 1 and 2 inmain.cpp.
To build and runpart1, run:
make part

```
Similarly to build and runpart2, run:
make part
```
```
There are two forms of testing: unit tests and integration tests. Unit tests verify the functionality of individual
components and will be discussed in class. We have provided five integration tests in the form of “trace”
functions that perform a series of Inserts, Gets, and Removes on your list. We are providing only a subset of
traces used on Gradescope. You must do systematic local testing on your own to increase confidence your
code would work on a more general set of traces beyond the ones we make available to you.
```

# PART_2
# Goals

Implement the copy constructor and assignment operator (ie. =) for your hash list. Implement a basic
iterator and accompanying functions for your hash_list. See hash_list.h for full details.

# Submission instructions

Upload your hash_list.h and hash_list.cpp to Gradescope. Any tests that you pass will be in green, any that
you fail will be in red, and for any failed test the output from that run (ie. everything that was printed to
the terminal) will be displayed in a box under the tests name

# Restrictions

Same as in the previous lab

# Copy constructor

Lets imagine we have a class like the following

```
class node
{
```
```
node(int elem)
{
_elem = elem;
}
```
```
int _elem;
};
```
If we have a node we want to copy we could do the following

```
node x(3);
```
```
node y(x); -> create y as a copy of x
```
The question then becomes “does this work, and if so, how?”. The answer to the first part of that question is
yes, it does work, and the answer to the second part is what the rest of this handout will explain.

This odd looking line of code invokes the copy constructor of the node class.

```
node y(x);
```
As its name implies, the copy constructor is used to copy objects. It takes an instance of an object as input
and creates a copy of that object. It turns out that the C++ compiler is very nice and will provide a built in
copy constructor if you don’t provide one. The built in implementation does a bitwise copy of each member
of the class. So in our example above we would end up with

```
x._elem = 3 -> because we set this when we called node x(3);
```
```
y._elem = 3 -> because the built in copy constructor copies x.elem
into y.elem
```
Now this seems very convenient. We wanted y to be a copy of x after all, and that’s exactly what we got.
But the built in implementation can also be very dangerous. Let’s imagine we had the following class instead


```
class dangerous_node
{
```
```
dangerous_node(int n)
{
ptr = new int;
*ptr = n;
}
```
```
~dangerous_node ()
{
delete(ptr); -> Ensures that we can't leak memory
}
```
```
int* ptr;
};
```
```
Now lets imagine we copy a dangerous_node the same way we did above
{
dangerous_node x(100);
```
```
dangerous_node y(x);
}
```
```
If you write code like this your program will probably crash. Let’s explore why.
{
dangerous_node x(100);
```
```
dangerous_node y(x); -> At this point we copy each member of x into
y. So we end up with y.ptr == x.ptr
}
```
```
Once we leave the scope that contains x and y we call their destructors
{
dangerous_node x(100);
```
```
dangerous_node y = x;
} -> At this point we call ~x() and ~y()
```
When we call ~x() all is good. We call delete() on x.ptr, so we have no memory leaks. But when we call
~y() we end up with a large problem. Remember, the built in copy constructor does a bitwise copy of each
member. So y.ptr points to the same piece of memory that x.ptr pointed do. And we already deleted that
memory when we called ~x(). So when we call ~y() and call delete() on y.ptr we’re attempting to delete
memory that’s already been deleted. That’s undefined behavior, so your program will probably crash.
So in the earlier case with the nodes class we liked what the compiler did for us, but we didn’t like what the
compiler did for us in the dangerous_node case.
The underlying reason that we need to change the implementation of the copy constructor goes back to what
we mean when we say “copy”. In the case of the dangerous_node the thing that we’ve interested in copying
isn’t x.ptr but rather the memory that x.ptr points to. The pointer is really just a way to access the memory
we’ve allocated. And because of that when we copy x we don’t want to copy the contents of x.ptr, we want
to copy the memory that x.ptr points to. This means we can’t rely on the built in copy constructor, since the


```
built in constructor isn’t aware that x.ptr points to allocated memory. In this respect what we want when we
copy x is the following
y.ptr = new int; -> Allocate a new chunk of memory
```
```
*y.ptr = *x.ptr; -> Copy data pointed to by x.ptr into memory pointed
to by y.ptr
```
By the way, when you have the situation we did above, where you have a chunk of memory and want to
“copy” it by allocating new memory and copying data from the old memory to the new memory, that’s called
a deep copy. Presumably the reason is because you’re not copying the surface level part (ie. the pointer to the
memory) but rather are going “deep” by following the pointer and copying the memory the pointer points to.
The opposite of a “deep” copy is a “shallow” copy. That’s where you just do a bitwise copy of each member,
ie. what the compiler does for you. This is fine for our node class but usually wont’t work for classes that
manage memory, such as our dangerous_node class

# Assignment operator

```
One of the werid quirks with the above examples is the way that we constructed new objects. If we had asked
you to write code that would assign x to y you probably would have done this
node y;
y = x;
```
```
Instead of
node y(x);
```
```
The reason for us choosing to use the copy constructor above is because the=operator is a little more
complicated than the copy constructor, so it’s easier to explain the copy constructor and introduce the=
operator later. Let’s illustrate why=is a more complicated with an example from our dangerous_node.
Imagine we want to implement the=operator for our dangerous_node class above. An initial implementation
might look like this
dangerous_node& operator =( const dangerous_node& other)
{
this.ptr = new int; -> Allocate new memory for the deep copy
*this.ptr = *other.ptr; -> Deep copy data
}
```
```
This code looks perfect. It avoid exactly the issues that we talked about in the copy constructor. It allocates
new memory and copies data from the old memory into the new memory. And yet this implementation will
leak memory all over the place. Here’s how
dangerous_node y(100); -> Allocate memory for integer 100 and have y
point to it
```
```
dangerous_node x(200); -> Allocate memory for integer 200 and have x
point to it
```
```
y = x; -> Call = operator for y
```
When we do y = x we end up calling the=operator code from above. And the problem is here


```
dangerous_node& operator =( const dangerous_node& other)
{
this.ptr = new int -> this.ptr already points to the memory we
allocated earlier. When we reassign this.ptr we leak that memory
and can't delete it
*this.ptr = *other.ptr;
}
```
```
And this reveals the difference between the copy constructor and the=operator. The copy constructor is
responsible for creating a new object from an existing one. That new object has no previous state to clean
up; it is simply brought into existence. But the=operator doesn’t do this. The=operator takes an existing
object and converts its contents to the contents of a different object. That means that we also need to clean
up that object’s state before we reassign it. So the=really does 2 things
```
1. Clean up the state of the object (ie. destruct it)
2. Copy state from the other object into the current object -> The copy
    constructor only does this

```
note: although I use the word destruct to describe the first step of what the destructor does you shouldn’t
call the destructor in your=operator.
So our final implementation of our dangerous_node=operator would look like this
dangerous_node& operator =( const dangerous_node& other)
{
delete(this.ptr); -> Here we're cleaning up the old state
this.ptr = new int;
*this.ptr = *other.ptr;
}
```
```
There are two last topics you should be aware of. The first is the copy and swap idiom, which is way to
use the copy constructor to implement the=operator (see how much duplicate code exists between our
copy constructor and=operator implementations?) and the second is the rule of 3, which says that if you
implement the copy constructor,=operator, or destructor, you should probably implement all 3.
```
# std::pair<K,V> explanation

If you want to return multiple values from a function in python, you can just return a tuple. In C++ you
can either use a tuple (which functions similarly to how python tuples function) or you can return a pair
(which is basically a tuple that has exactly two values).

```
For example, if you wanted your function to return an integer and a float you could do
std::pair <int , float > foo() // <int , float > tells the compiler the types
you're returning
{
int x = 3;
float y = 4;
return {3,4}; // putting the values inside of {} creates a pair
}
```
```
Two of the members of std::pair arefirstandsecond. These are how you access the values that are inside
of the pair. Using thefoo()function from above we would access x and y by
std::pair <int , float > returned_pair = foo();
```
```
int new_x = returned_pair.first; // Get x out of the pair
```

```
float new_y = returned_pair.second; // Get y out of the pair
```
# Iterator discussion

When implementing the iterator functions we left it unspecified what the iterator should point to when you
create a list. This is because we’re only defining the iterator behavior after reset_iter() is called. This means
that before we use the iterator to iterate over your lists we will call reset_iter().
An additional issue you might think of is what happens if someone is iterating over your list and calls remove()
on the node that the iterator is pointing to? We’ve decided to call this undefined behavior. If someone is
iterating over the list and they call remove(), the iterator is invalid. If they want to keep iterating over the
list after calling remove() they need to reset the iterator and start from the beginning again.

We’ve also decided it’s undefined behavior to change the value of the key using get_iter_value(). This is
because changing the key means you’re able to get around the invariant that each key in the hash_list is
unique.

We’ve given an example of how to use the iterator in main.cpp


