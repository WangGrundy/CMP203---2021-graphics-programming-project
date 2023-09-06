#pragma once
#include "Vector3.h"
#include <math.h>

class Camera
{
public:
	Camera();

	void UpdateCamera();

	void SetCameraPosition(float, float, float);
	void SetCameraPositionX(float);
	void SetCameraPositionY(float);
	void SetCameraPositionZ(float);
	Vector3 GetCameraPosition();

	void SetLookAt(float, float, float);
	void SetLookAtX(float);
	void SetLookAtY(float);
	void SetLookAtZ(float);
	Vector3 GetLookAt();

	void SetUpVector(float, float, float);
	void SetUpVectorX(float);
	void SetUpVectorY(float);
	void SetUpVectorZ(float);
	Vector3 GetUpVector();

	void SetPitch(float);
	void SetYaw(float);
	void SetRoll(float);
	float GetPitch();
	float GetYaw();
	float GetRoll();

	void moveForward(float dt);
	void moveBackwards(float dt);
	void moveLeft(float dt);
	void moveRight(float dt);

	void SetForward(float,float,float);
	Vector3 GetForward();

	//extra
	void SetHelicopterPitch(float);
	void SetHelicopterYaw(float);


private:

	Vector3 position; //XYZ POS
	Vector3 forward; //FORWARD DIRECTION
	Vector3 up; //up
	Vector3 lookAt; // POINT IN SPACE WE ARE LOOKING AT
	Vector3 right; //TILT RIGHT

	float cosR, cosP, cosY;
	float sinR, sinP, sinY;
	float Pitch, Yaw, Roll;

	float speed = 10;

};