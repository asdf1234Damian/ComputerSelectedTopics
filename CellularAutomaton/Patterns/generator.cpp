// C++ program to generate n-bit Gray codes
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> generateGrayarr(int n){
    std::vector<std::string> arr;
    arr.push_back("0");
    arr.push_back("1");
    for (size_t i = 2; i < (1<<n); i = i<<1){
        for (size_t j = i-1 ; j >= 0 ; j--)
            arr.push_back(arr[j]);
        for (size_t j = 0 ; j < i ; j++)
            arr[j] = "0" + arr[j];
        for (size_t j = i ; j < 2*i ; j++)
            arr[j] = "1" + arr[j];
    }
    std::cout << "something" << '\n';
    //return arr;
}

int main(int argc, char const *argv[]) {
  //freopen("nextState","w+",stdout);//Output file
  std::vector<std::string> v= generateGrayarr(2);
  return 0;
}
