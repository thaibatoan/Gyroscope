#if !defined (_MY_CAMERA_CLASS)
#define _MY_CAMERA_CLASS
#define CAN2 1.41421356
#define PI 3.14159265

class MyCamera {
	public:
		float angle;
		float height;
		float distance;
		float positionX, positionY, positionZ;
		float lookAt_X, lookAt_Y, lookAt_Z;
	public:
		MyCamera() {
			angle = 45;
			height = 6;
			distance = 8 * CAN2;
			lookAt_X = lookAt_Z = 0; lookAt_Y = 3;
			Calculate();
		}
		void Calculate() {
			if (distance <= 0.2) {
				distance = 0.2;
			}
			positionX = distance*sin(angle*PI / 180);
			positionY = height;
			positionZ = distance*cos(angle*PI / 180);
		}
};
#endif
