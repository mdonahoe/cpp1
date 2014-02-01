#include "Receiver.h"
#include <iostream>

using namespace std;
using namespace Eigen;

Receiver::Receiver(): stick() {
    stick.setZero();
    lcm_ = new lcm::LCM(); // need the address?
    lcm_->subscribe("IMU_DROID", &Receiver::MessageHandler, this);
};

void Receiver::MessageHandler(const lcm::ReceiveBuffer* rbuf,
                     const string& channel,
                     const droidsensor::imu_t * msg){
    stick << msg->accel[0], msg->accel[1], msg->accel[2];
    cout << "stick (" << msg->utime << "): "
         << stick << endl;
};

const Vector3f Receiver::GetControl(){
    return stick;
};

void Receiver::run(){
    // do this in a thread somehow?
    while (true) lcm_->handle();
};

