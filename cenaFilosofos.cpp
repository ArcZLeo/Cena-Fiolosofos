#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
int comer = 2000;
int comida=20;

class Chopstics{
  public:
    Chopstics(){}
    mutex mu;
};

class timer{
  public:
  int time;
  auto endT(float timed){}
};

int main()
{
  int num_filosfos;
  cout<<"Ingrese la cantidad de filosofos"<<endl;
  cin>> num_filosfos;

  timer clock;

  clock.time=comer;
  while (comida!=0){
    int ms = clock.time;
    auto start = chrono::high_resolution_clock::now();
    auto eat = [ms](Chopstics &left_chopstics, Chopstics &right_chopstics, int philosopher_number) {

      unique_lock<mutex> llock(left_chopstics.mu);
      unique_lock<mutex> rlock(right_chopstics.mu);

      cout << "El filosofo " << philosopher_number << " esta comiendo"<<endl;

      chrono::milliseconds timeout(ms);
      this_thread::sleep_for(timeout);

      cout << "El filosofo " << philosopher_number << " termino de comer"<<endl;
    };

    Chopstics chp[num_filosfos];
    thread philosopher[num_filosfos];

    cout << "El filosofo 1 esta pensando"<<endl;
    philosopher[0] = thread(eat, ref(chp[0]), ref(chp[num_filosfos-1]), 1);

    for(int i = 1; i < num_filosfos; ++i) {
        cout << "El filosofo " << (i+1) << " esta pensando"<<endl;
        //filosofos disminuyendo energia
        philosopher[i] = thread(eat, ref(chp[i]), ref(chp[i-1]), (i+1));
        comida=comida-1;
    }

    for(auto &ph: philosopher) {
        ph.join();
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration <float> duration = end - start;
    clock.endT(duration.count());
  }
  cout<<"Ya no hay mas comida, la cena termino"<<endl;
}