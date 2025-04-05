#include <kipr/wombat.h>
#include "misc.h"
#include <math.h>
#include <stdlib.h>
#include "drive.h"
void SLOW_SERVO(int servo, int goal, int step_size)
{
    set_servo_enabled(servo, 1);
    int pos=get_servo_position(servo);
    if (pos<goal)
    {
        while (pos<goal)
        {
            set_servo_position(servo, pos+step_size);
            msleep(50);
            pos=get_servo_position(servo);
        }
    }
    else
    {
        while (pos>goal)
        {
            set_servo_position(servo, pos-step_size);
            msleep(50);
            pos=get_servo_position(servo);
           
        }
    }
    set_servo_enabled(servo, 0);

}
int INT_AVG(int* arr, int length)
{
    int avg=0;
    for (int i=0; i<length; i++)
    {
        avg+=arr[i];
    }
    return avg/length;
}
float FLOAT_AVG(float* arr, int l)
{	
    float length=(float)l;
    float avg=0;
    for (int i=0; i<length; i++)
    {
        avg+=arr[i];
    }
    printf("Avg: %f, Length: %f\n", avg, length);
    return avg/length;
}
double STDV(int* arr, int l)
{
    int avg=INT_AVG(arr, l);
    double stdv=0;
    for (int i=0; i<l; i++)
    {
        stdv+=(arr[i]-avg)*(arr[i]-avg);
    }
    stdv=sqrt(stdv/l);
    return stdv;
}

int moving_calibrate(int sensor_port, int frm, int flm, int brm, int blm, int speed)
{
    int data[100];
    for (int i=0; i<100; i++)
    {
        straight(frm, flm, brm, blm, speed);
        data[i]=analog(sensor_port);
    }
    freeze(frm);
    freeze(flm);
    freeze(blm);
    freeze(brm);
    msleep(100);
    return INT_AVG(data, 100);
}
int static_calibrate( int sensor_port)
{
    int data[100];
    for (int i=0; i<100; i++)
    {
        data[i]=analog(sensor_port);
    }
    return INT_AVG(data, 100);  
}