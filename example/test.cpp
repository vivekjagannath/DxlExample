#include <Dxl.h>
#include<unistd.h>
using namespace std;

int main()
{
	Dxl d1(1, "/dev/ttyUSB0");
    	d1.enable_torque();
    	d1.write_speed(100);
    	map<int, int> hi({{1,312}, {2,312}});
    	d1.set_goal_position(hi);
    	return 0;
}
