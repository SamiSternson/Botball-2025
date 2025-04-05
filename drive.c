#include <kipr/wombat.h>
#include <math.h>
#include <stdlib.h>
#include "drive.h"
void straight(int frm, int flm, int brm, int blm, int speed)
{
    motor(frm, speed);
    motor(flm, speed);
    motor(blm, speed);
    motor(brm, speed);
}
void sideways(int frm, int flm, int brm, int blm, int speed)
{
    motor(frm,-speed);
    motor(flm, speed);
    motor(brm, speed);
    motor(blm, -speed);
}
void diagonal_left(int frm, int flm, int brm, int blm, int speed)
{
    motor(frm,speed);
    motor(flm, 0);
    motor(brm, 0);
    motor(blm, speed);
}
void diagonal_right(int frm, int flm, int brm, int blm, int speed)
{
    motor(frm,0);
    motor(flm, speed);
    motor(brm, speed);
    motor(blm, 0);
}
void spin(int frm, int flm, int brm, int blm, int speed)
{
    motor(frm, speed);
    motor(flm, -speed);
    motor(brm, speed);
    motor(blm, -speed);
}
void turn_around_point(int frm, int flm, int brm, int blm, int rspeed, int lspeed)
{
    motor(frm, rspeed);
    motor(flm, lspeed);
    motor(brm, rspeed);
    motor(blm, lspeed);
}
void SUB_FORWARD(int frm, int flm, int brm, int blm, int speed, int rs, int ls, int thresh)
{
    int i=1;
    while (analog(rs)<thresh || analog(ls)<thresh)
    {
        if (analog(rs)<thresh && analog(ls)<thresh)
        {
            straight(frm, flm, brm, blm, speed);   
        }
        else if (analog(rs)>thresh && analog(ls)<thresh)
        {
            spin(frm, flm, brm, blm, -speed/i);  
            i+=speed/500;

        }
        else
        {
            spin(frm, flm, brm, blm, speed/i);
            i+=speed/500;
        }
    }
    freeze(blm);
    freeze(flm);
    freeze(brm);
    freeze(frm);
    msleep(100);
}
void SUW_FORWARD(int frm, int flm, int brm, int blm, int speed, int rs, int ls, int thresh)
{
    int i=1;
    while (analog(rs)>thresh || analog(ls)>thresh)
    {
        if (analog(rs)>thresh && analog(ls)>thresh)
        {
            straight(frm, flm, brm, blm, speed);   
        }
        else if (analog(rs)<thresh && analog(ls)>thresh)
        {
            spin(frm, flm, brm, blm, -speed/i);  
            i+=speed/500;

        }
        else
        {
            spin(frm, flm, brm, blm, speed/i);
            i+=speed/500;
        }
    }
    freeze(blm);
    freeze(flm);
    freeze(brm);
    freeze(frm);
    msleep(100);
}
void SUB_SIDEWAYS(int frm, int flm, int brm, int blm, int speed, int rs, int ls, int thresh)
{
    while (analog(rs)<thresh || analog(ls)<thresh)
    {
        if (analog(rs)<thresh && analog(ls)<thresh)
        {
            sideways(frm, flm, brm, blm, speed);   
        }
        else if (analog(rs)>thresh && analog(ls)<thresh)
        {
            spin(frm, flm, brm, blm, speed/abs((speed/25)));  

        }
        else
        {
            spin(frm, flm, brm, blm, -speed/abs((speed/25)));
        }
    }
    freeze(blm);
    freeze(flm);
    freeze(brm);
    freeze(frm);
    msleep(100);
}
void SUW_SIDEWAYS(int frm, int flm, int brm, int blm, int speed, int rs, int ls, int thresh)
{
    int i=1;
    while (analog(rs)>thresh || analog(ls)>thresh)
    {
        if (analog(rs)>thresh && analog(ls)>thresh)
        {
            sideways(frm, flm, brm, blm, speed);   
        }
        else if (analog(rs)<thresh && analog(ls)>thresh)
        {
            spin(frm, flm, brm, blm, speed/abs((speed/25)));
            i+=speed/500;

        }
        else
        {
            spin(frm, flm, brm, blm, -speed/abs((speed/25)));
            i+=speed/500;
        }
    }
    freeze(blm);
    freeze(flm);
    freeze(brm);
    freeze(frm);
    msleep(100);
}

void DRIVE_STRAIGHT(int frm, int flm, int brm, int blm, float frmt, float flmt, float brmt, float blmt, int speed, float distance)
{
    float fr_ticks_needed=frmt*distance;
    float fl_ticks_needed=flmt*distance;
    float br_ticks_needed=brmt*distance;
    float bl_ticks_needed=blmt*distance;
    int fr_current_ticks=0;
    int fl_current_ticks=0;
    int bl_current_ticks=0;
    int br_current_ticks=0;
    cmpc(frm);
    cmpc(flm);
    cmpc(brm);
    cmpc(blm);
    while (fr_current_ticks<fr_ticks_needed || fl_current_ticks<fl_ticks_needed||br_current_ticks<br_ticks_needed||bl_current_ticks<bl_ticks_needed)
    {
        if (fr_current_ticks<fr_ticks_needed && fl_current_ticks<fl_ticks_needed && br_current_ticks<br_ticks_needed && bl_current_ticks<bl_ticks_needed)
        {

            motor(frm, speed);
            motor(flm, speed);
            motor(brm, speed);
            motor(blm, speed);


        }
        else if ((fr_current_ticks>fr_ticks_needed || br_current_ticks>br_ticks_needed) && (bl_current_ticks<bl_ticks_needed || bl_current_ticks<bl_ticks_needed))
        {
            motor(frm, 0);
            motor(flm, speed/2);
            motor(brm, 0);
            motor(blm, speed/2);
        }
        else
        {
            motor(frm, speed/2);
            motor(flm, 0);
            motor(blm, 0);
            motor(brm,speed/2);
        }
        fr_current_ticks=abs(gmpc(frm));
        fl_current_ticks=abs(gmpc(flm));
        br_current_ticks=abs(gmpc(brm));
        bl_current_ticks=abs(gmpc(blm));
    }
    freeze(frm);
    freeze(flm);
    freeze(brm);
    freeze(blm);
    msleep(100);
}
void DRIVE_SIDEWAYS(int frm, int flm, int brm, int blm, float frmt, float flmt, float brmt, float blmt, int speed, float distance)
{
    float fr_ticks_needed=frmt*distance;
    float fl_ticks_needed=flmt*distance;
    float br_ticks_needed=brmt*distance;
    float bl_ticks_needed=blmt*distance;
    int fr_current_ticks=0;
    int fl_current_ticks=0;
    int bl_current_ticks=0;
    int br_current_ticks=0;
    while (fr_current_ticks<fr_ticks_needed || fl_current_ticks<fl_ticks_needed||br_current_ticks<br_ticks_needed||bl_current_ticks<bl_ticks_needed)
    {
        if (fr_current_ticks<fr_ticks_needed && fl_current_ticks<fl_ticks_needed && br_current_ticks<br_ticks_needed && bl_current_ticks<bl_ticks_needed)
        {

            sideways(frm,  flm, brm, blm, speed);


        }
        else if ((fr_current_ticks>fr_ticks_needed || br_current_ticks>br_ticks_needed) && (bl_current_ticks<bl_ticks_needed || bl_current_ticks<bl_ticks_needed))
        {
            turn_around_point(frm,  flm, brm, blm, 0, 25);
        }
        else
        {
            turn_around_point(frm,  flm, brm, blm, 25, 0);
        }
        fr_current_ticks=abs(gmpc(frm));
        fl_current_ticks=abs(gmpc(flm));
        br_current_ticks=abs(gmpc(brm));
        bl_current_ticks=abs(gmpc(blm));
    }
    freeze(frm);
    freeze(flm);
    freeze(brm);
    freeze(blm);
    msleep(100);
}
void LINE_FOLLOW_STRAIGHT(int frm, int flm, int brm, int blm, int speed, int turn_constant, int rs, int ls, int thresh)
{
    while (analog(rs)<thresh || analog(ls)<thresh)
    {
        if (analog(rs)<thresh && analog(ls)<thresh)
        {
            straight(frm, flm, brm, blm, speed);   
        }
        else if (analog(rs)<thresh && analog(ls)>thresh)
        {
            turn_around_point(frm, flm, brm, blm, speed, speed/turn_constant);
        }
        else
        {
            turn_around_point(frm, flm, brm, blm, speed/turn_constant, speed);
        }
    }
    freeze(frm);
    freeze(flm);
    freeze(brm);
    freeze(blm);
    msleep(100);
}
void LINE_FOLLOW_SIDEWAYS(int frm, int flm, int brm, int blm, int speed, int turn_constant, int rs, int ls, int thresh)
{
    while (analog(rs)<thresh || analog(ls)<thresh)
    {
        if (analog(rs)<thresh && analog(ls)<thresh)
        {
            sideways(frm, flm, brm, blm, speed);   
        }
        else if (analog(rs)<thresh && analog(ls)>thresh)
        {
            turn_around_point(frm, flm, brm, blm, speed, speed/turn_constant);
        }
        else
        {
            turn_around_point(frm, flm, brm, blm, speed/turn_constant, speed);
        }
    }
    freeze(frm);
    freeze(flm);
    freeze(brm);
    freeze(blm);
    msleep(100);
}