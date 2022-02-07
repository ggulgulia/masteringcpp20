#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <queue>

template<typename Coll, typename T>
void add_to_container(Coll& container, T value)
{
    /* assumptions for this function:
        1. type Cont has method push_back
        2. type of the value within container is same as value
        3. value is a copyable object
    */

    container.push_back(value);
}

template<typename T>
T add_one(const T val)
{
    /* assumptions for the generic fucntion add_one:
       val and 1 can be added
    */

    return val + 1;
}

//double* add_one(double* );


int main(){

    int one{1};
    int two{2};

    double pi{3.141};

    std::cout << "add_one(one): " << add_one(one) << "\n";
    std::cout << "add_one(pi): "  << add_one(pi) << "\n";

    int* pTwo = &two;

    std::cout << "add_one(&pi): " << add_one(&pi) << "\n";
    std::cout << "add_one(pTwo): " << add_one(pTwo) << "\n";

   
   
    std::list<char> clist;
    add_to_container(clist, 'a'); //OK

    std::vector<float> farray;
    add_to_container(farray, 0.9f); //OK
    
    //std::queue<int> iq;
    //add_to_container(iq, 1); //error since std::queue doesn't have a push_back method

    ////add_to_container(clist,221.0f); //types of objects of clist and 221.0f doesn't match

    std::vector<std::unique_ptr<int>> intPtrArray;
    std::unique_ptr<int> onePtr = std::make_unique<int>(1);
    add_to_container(intPtrArray, std::move(onePtr));

}





    //int* pTwo = &two;

    //std::cout << "add_one(&pi): " << add_one(&pi) << "\n";
    //std::cout << "add_one(pTwo): " << add_one(pTwo) << "\n";

    //std::list<char> clist;
    //add_to_container(clist, 'a'); //OK
//
    //std::vector<float> farray;
    //add_to_container(farray, 0.f); //OK
    //
    //std::queue<int> iq;
   //// add_to_container(iq, 1); //error since std::queue doesn't have a push_back method
//
    ////add_to_container(clist,221.0f); //types of objects of clist and 221.0f doesn't match
//
    //std::vector<std::unique_ptr<int>> intPtrArray;
    //std::unique_ptr<int> onePtr = std::make_unique<int>(1);
    //add_to_container(intPtrArray, std::move(onePtr));


//}
