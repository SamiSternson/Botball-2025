void straight(int frm, int flm, int brm, int blm, int speed);
void sideways(int frm, int flm, int brm, int blm, int speed);
void diagonal_right(int frm, int flm, int brm, int blm, int speed);
void diagonal_left(int frm, int flm, int brm, int blm, int speed);
void spin(int frm, int flm, int brm, int blm, int speed);
void turn_around_point(int frm, int flm, int brm, int blm, int rspeed, int lspeed);
void SUB_FORWARD(int frm, int flm, int brm, int blm, int speed, int rs, int ls, int thresh);
void SUW_FORWARD(int frm, int flm, int brm, int blm, int speed, int rs, int ls, int thresh);
void DRIVE_STRAIGHT(int frm, int flm, int brm, int blm, float frmt, float flmt, float brmt, float blmt, int speed, float distance);
void DRIVE_SIDEWAYS(int frm, int flm, int brm, int blm, float frmt, float flmt, float brmt, float blmt, int speed, float distance);
void SUB_SIDEWAYS(int frm, int flm, int brm, int blm, int speed, int rs, int ls, int thresh);
void SUW_SIDEWAYS(int frm, int flm, int brm, int blm, int speed, int rs, int ls, int thresh);
void LINE_FOLLOW_STRAIGHT(int frm, int flm, int brm, int blm, int speed, int turn_constant, int rs, int ls, int thresh);
void LINE_FOLLOW_SIDEWAYS(int frm, int flm, int brm, int blm, int speed, int turn_constant, int rs, int ls, int thresh);