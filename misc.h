void SLOW_SERVO(int servo, int goal, int step_size);
int INT_AVG(int* arr, int length);
float FLOAT_AVG(float* arr, int l);
double STDV(int*arr, int l);
int moving_calibrate(int sensor_port, int frm, int flm, int brm, int blm, int speed);
int static_calibrate( int sensor_port);