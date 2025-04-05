#include <kipr/wombat.h>
#include "drive.h"
#include "misc.h"
/*
V1 code for mechanum wheel robot.
Goal: Grab waterbottles and put in drink area.
Methodology: Use as little turns as possible, use sideways and forward as much as possible.
*/
//Motors
int frm=0;
int flm=1;
int brm=2;
int blm=3;
float frmt=8.10523438991; //Ticks per mm
int flmt=8.09244620454;   //Ticks per mm
float brmt=8.10399682358; //Ticks per mm
float blmt=8.09203368243; //Ticks per mm

//Sensors
int frs=0;
int fls=1;
int sfs=2;
int sbs=3;
int long_range=4;
//Servos
int up_down=0;
int left_right=1;
int up=75;
int down=1470;
int right=2047;
int left=1695;

int speed=50;
void GET_BOTTLES_V2();
int main()
{	


    GET_BOTTLES_V2();

    return 0;
}

void GET_BOTTLES_V2()
{
    SLOW_SERVO(up_down, up, 30);
    SLOW_SERVO(left_right, right, 30);
    double start_time=seconds();
    int side_thresh=moving_calibrate(sfs, frm, flm, brm, blm, -25)+1500;
    int front_thresh=moving_calibrate(frs, frm, flm, brm, blm, -25)+1500;
    SUB_SIDEWAYS(frm, flm,brm, blm, -speed*1.5, sfs, sbs, side_thresh);
    SUW_SIDEWAYS(frm, flm,brm, blm, -speed*1.5, sfs, sbs, side_thresh);
    SUB_SIDEWAYS(frm, flm,brm, blm, -speed, sfs, sbs, side_thresh);
    LINE_FOLLOW_STRAIGHT(frm, flm, brm, blm, speed*1.5, 2, frs,fls, front_thresh);
    SUB_SIDEWAYS(frm, flm,brm, blm, -speed, sfs, sbs, side_thresh);
    SUW_SIDEWAYS(frm, flm,brm, blm, -speed, sfs, sbs, side_thresh);
    SUW_FORWARD(frm, flm,brm, blm, -speed, frs, fls, front_thresh);
    spin(frm, flm, brm, blm, speed);
    msleep(2500);
    straight(frm, flm, brm, blm, speed);
    msleep(2000);
    DRIVE_STRAIGHT(frm,flm, brm, blm,  frmt, flmt,  brmt,  blmt, -speed, 50);
    int data[150];
    for (int i=0; i<150; i++)
    {
        sideways(frm, flm, brm, blm, -speed);
        data[i]=analog(long_range);
    }
    freeze(frm);
    freeze(flm);
    freeze(blm);
    freeze(brm);
    msleep(100);
    int avg=INT_AVG(data, 150);
    while (analog(long_range)<avg+1000)
    {
        sideways(frm, flm, brm, blm, -speed/2);   
    }
    sideways(frm, flm, brm, blm, -speed/2);   
    msleep(100);
    freeze(frm);
    freeze(flm);
    freeze(blm);
    freeze(brm);
    msleep(100);
    SLOW_SERVO(up_down, down, 30);
    SLOW_SERVO(left_right, left,20);
    SLOW_SERVO(up_down, up+500, 20);
    while (analog(long_range)<avg+1000)
    {
        sideways(frm, flm, brm, blm, -speed/2);   
    }
    while (analog(long_range)>avg+1000)
    {
        sideways(frm, flm, brm, blm, -speed/2);   
    }
    sideways(frm, flm, brm, blm, -speed);   
    msleep(500);
    while (analog(long_range)>avg+1000)
    {
        sideways(frm, flm, brm, blm, -speed/2);   
    }
    spin(frm, flm, brm, blm, -speed);
    msleep(5200);
    while(analog(fls)<front_thresh)
    {
        straight(frm, flm, brm, blm, speed);

    }
    SUB_FORWARD(frm, flm,brm, blm, speed, frs, fls, front_thresh);
    SUW_FORWARD(frm, flm,brm, blm, speed/2, frs, fls, front_thresh);
    SUB_FORWARD(frm, flm,brm, blm, speed, frs, fls, front_thresh);
    SLOW_SERVO(up_down, down, 50);
    SLOW_SERVO(left_right, right, 50);
    SLOW_SERVO(up_down, up+500, 50);
    sideways(frm, flm, brm, blm, -speed*2);   
    msleep(750);
    freeze(frm);
    freeze(flm);
    freeze(blm);
    freeze(brm);
    msleep(100);
    SLOW_SERVO(up_down, down, 100);
    sideways(frm, flm, brm, blm, speed);   
    msleep(1700);
    freeze(frm);
    freeze(flm);
    freeze(blm);
    freeze(brm);
    msleep(100);
    SLOW_SERVO(up_down, up, 100);
    straight(frm, flm, brm, blm, -speed);
    msleep(500);
    spin(frm, flm, brm, flm, speed);
    msleep(2500);
    SUB_SIDEWAYS(frm, flm,brm, blm, -speed, sfs, sbs, side_thresh);
    LINE_FOLLOW_STRAIGHT(frm, flm, brm, blm, speed*1.5, 2, frs,fls, front_thresh);
    SUB_SIDEWAYS(frm, flm,brm, blm, -speed, sfs, sbs, side_thresh);
    SUW_SIDEWAYS(frm, flm,brm, blm, -speed, sfs, sbs, side_thresh);
    SUW_FORWARD(frm, flm,brm, blm, -speed/2, frs, fls, front_thresh);
    spin(frm, flm, brm, blm, speed);
    msleep(2500);
    straight(frm, flm, brm, blm, speed);
    msleep(2000);
    DRIVE_STRAIGHT(frm,flm, brm, blm,  frmt, flmt,  brmt,  blmt, -speed, 50);

    for (int i=0; i<150; i++)
    {
        sideways(frm, flm, brm, blm, -speed/2);
        data[i]=analog(long_range);
    }
    freeze(frm);
    freeze(flm);
    freeze(blm);
    freeze(brm);
    msleep(100);
    avg=INT_AVG(data, 150);
    while (analog(long_range)<avg+1000)
    {
        sideways(frm, flm, brm, blm, -speed/2);   
    }
    sideways(frm, flm, brm, blm, -speed/2);   
    msleep(100);
    freeze(frm);
    freeze(flm);
    freeze(blm);
    freeze(brm);
    msleep(100);
    SLOW_SERVO(up_down, down, 30);
    SLOW_SERVO(left_right, left,20);
    SLOW_SERVO(up_down, up+500, 20);
    while (analog(long_range)<avg+1000)
    {
        sideways(frm, flm, brm, blm, -speed/2);   
    }
    while (analog(long_range)>avg+1000)
    {
        sideways(frm, flm, brm, blm, -speed/2);   
    }
    spin(frm, flm, brm, blm, -speed);
    msleep(5200);
    while(analog(fls)<front_thresh)
    {
        straight(frm, flm, brm, blm, speed);

    }
    SUB_FORWARD(frm, flm,brm, blm, speed, frs, fls, front_thresh);
    SUW_FORWARD(frm, flm,brm, blm, speed/2, frs, fls, front_thresh);
    SUB_FORWARD(frm, flm,brm, blm, speed, frs, fls, front_thresh);
    SLOW_SERVO(up_down, down, 50);
    SLOW_SERVO(left_right, right, 50);
    SLOW_SERVO(up_down, up+500, 50);
    sideways(frm, flm, brm, blm, -speed*2);   
    msleep(750);
    freeze(frm);
    freeze(flm);
    freeze(blm);
    freeze(brm);
    msleep(100);
    SLOW_SERVO(up_down, down, 100);
    sideways(frm, flm, brm, blm, speed);   
    msleep(1700);
    freeze(frm);
    freeze(flm);
    freeze(blm);
    freeze(brm);
    msleep(100);
    SLOW_SERVO(up_down, up, 100);
    straight(frm, flm, brm, blm, -speed);
    msleep(500);
    spin(frm, flm, brm, flm, speed);
    msleep(2500);
    SUB_SIDEWAYS(frm, flm,brm, blm, -speed, sfs, sbs, side_thresh);
    LINE_FOLLOW_STRAIGHT(frm, flm, brm, blm, speed*1.5, 2, frs,fls, front_thresh);
    SUB_SIDEWAYS(frm, flm,brm, blm, -speed, sfs, sbs, side_thresh);
    SUW_SIDEWAYS(frm, flm,brm, blm, -speed, sfs, sbs, side_thresh);
    SUW_FORWARD(frm, flm,brm, blm, -speed/2, frs, fls, front_thresh);
    spin(frm, flm, brm, blm, speed);
    msleep(2500);
    straight(frm, flm, brm, blm, speed);
    msleep(2000);
    DRIVE_STRAIGHT(frm,flm, brm, blm,  frmt, flmt,  brmt,  blmt, -speed, 50);

    for (int i=0; i<150; i++)
    {
        sideways(frm, flm, brm, blm, -speed/2);
        data[i]=analog(long_range);
    }
    freeze(frm);
    freeze(flm);
    freeze(blm);
    freeze(brm);
    msleep(100);
    avg=INT_AVG(data, 150);
    while (analog(long_range)<avg+1000)
    {
        sideways(frm, flm, brm, blm, -speed/2);   
    }
    sideways(frm, flm, brm, blm, -speed/2);   
    msleep(100);
    freeze(frm);
    freeze(flm);
    freeze(blm);
    freeze(brm);
    msleep(100);
    SLOW_SERVO(up_down, down, 30);
    SLOW_SERVO(left_right, left,20);
    SLOW_SERVO(up_down, up+500, 20);
    spin(frm, flm, brm, blm, -speed);
    msleep(5200);
    while(analog(fls)<front_thresh)
    {
        straight(frm, flm, brm, blm, speed);

    }   
    SUW_FORWARD(frm, flm,brm, blm, speed/2, frs, fls, front_thresh);
    SUB_FORWARD(frm, flm,brm, blm, speed, frs, fls, front_thresh);
    SLOW_SERVO(up_down, down, 50);
   SLOW_SERVO(up_down, right, 100);

    printf("\n\n%f", seconds()-start_time);
}