/** Header of Pointers.cpp
*
*
*
*/

class Vehicle {
    public:
        Vehicle(int, int, double);
        //~Vehicle();
        int get_passengers();
        void set_passengers(int);

    private:
        int wheels;
        int passengers;
        double max_speed;
};

int add(int, int);
int add_deref(int *, int *); // (*+)
int add_ref(int &, int &); // (&+)
//int operation (int, int, int (*functocall)(int,int))
