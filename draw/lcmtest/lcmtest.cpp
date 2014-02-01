#include <lcm/lcm-cpp.hpp>
#include <iostream>
#include "imu_t.hpp"
#include <Eigen/Core>

using namespace Eigen;
using namespace std;

class LCMTest{
public:
    LCMTest();
    void run();
    void MessageHandler(const lcm::ReceiveBuffer*,
                        const string&,
                        const droidsensor::imu_t*);
    lcm::LCM * lcm_;
};

LCMTest::LCMTest(){
    lcm_ = new lcm::LCM(); // need the address?
    lcm_->subscribe("IMU_DROID", &LCMTest::MessageHandler, this);
};

void LCMTest::MessageHandler(const lcm::ReceiveBuffer* rbuf,
                     const string& channel,
                     const droidsensor::imu_t * msg){
    Vector3f acc;
    acc << msg->accel[0], msg->accel[1], msg->accel[2];
    cout << "got message!" << acc << endl;
};

void LCMTest::run(){
    cout << "running..." << endl;
    while (true) lcm_->handle();
};


int main(){
    cout << "hello world" << endl;
    LCMTest test;
    test.run();
    return 0;
}
