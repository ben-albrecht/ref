// const.cpp
//
// not compilable at this time, just some snippets
//
// const pointers 

char greeting[] = "Hello";

char *p = greeting; // non-const pointer, non-const data

const char *p = greeting; // non-const pointer, const data

char const *p = greeting; // const pointer, non-const data 

const char * const p = greeting;  // const point, const data


// order before or after type does _not_ matter however:
class Widget; 
(
 Widget()
 ~Widget();
);

const Widget *pw // pointer to constant Widget object

Widget const *pw // pointer to constant Widget object



