#include "Camera.h"

Camera::Camera() {

	position.set(50.0f, 10.0f, 50.0f);
	forward.set(0.0f, 0.0f, 0.0f);
	up.set(0.0f, 1.0f, 0.0f);

	Pitch = 0, Yaw = 1, Roll = 0;
	sinR = 0, sinP = 0, sinY = 0;
	cosR = 0, cosP = 0, cosY = 0;

	
}

void Camera::UpdateCamera() {

	// Only want to calculate these values once, when rotation changes, not every frame.
	cosY = cosf(Yaw * 3.1415 / 180);
	cosP = cosf(Pitch * 3.1415 / 180);
	cosR = cosf(Roll * 3.1415 / 180);
	sinY = sinf(Yaw * 3.1415 / 180);
	sinP = sinf(Pitch * 3.1415 / 180);
	sinR = sinf(Roll * 3.1415 / 180);

	// Direciton camera is looking //CANT BE MORE OR LESS THAN +1/-1
	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	// Look At Point
	// To calculate add Forward Vector to Camera position.
	lookAt = position + forward;

	// Side Vector (right)
	// this is a cross product between the forward and up vector.
	right = forward.cross(up);

	// Up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;
}

void Camera::SetCameraPosition(float x, float y, float z) {
	position.set(x, y, z);
}

void Camera::SetCameraPositionX(float x) {
	position.setX(position.x + x);
}
void Camera::SetCameraPositionY(float y) {
	position.setY(position.y + y);
}
void Camera::SetCameraPositionZ(float z) {
	position.setZ(position.z + z);
}

Vector3 Camera::GetCameraPosition() {
	return position;
}

//////////////////////////////////////////

void Camera::SetLookAt(float x, float y, float z) {
	forward.set(x, y, z);
}

void Camera::SetLookAtX(float x) {
	forward.setX(forward.x + x);
}
void Camera::SetLookAtY(float y) {
	forward.setY(forward.y + y);
}
void Camera::SetLookAtZ(float z) {
	forward.setZ(forward.z + z);
}

Vector3 Camera::GetLookAt() {
	return lookAt;
}

////////////////////////////////////////////////////////////////////

void Camera::SetUpVector(float x, float y, float z) {
	up.set(x, y, z);
}

void Camera::SetUpVectorX(float x) {
	up.setX(up.x + x);
}
void Camera::SetUpVectorY(float y) {
	up.setY(up.y + y);
}
void Camera::SetUpVectorZ(float z) {
	up.setZ(up.z + z);
}

Vector3 Camera::GetUpVector() {
	return up;
}

/////////////////////////////////////////////////////////////////

void Camera::SetPitch(float x) {

	Pitch += x;
	if (Pitch > 450) {
		Pitch = 450;
	}
	else if (Pitch < 270) {
		Pitch = 270;
	}
}

void Camera::SetHelicopterPitch(float x) {
	Pitch = x;
}
void Camera::SetHelicopterYaw(float y) {
	Yaw = y;
}

void Camera::SetYaw(float y) {
	Yaw += y;
}

void Camera::SetRoll(float z) {
	Roll += z;
}

float Camera::GetPitch() {
	return Pitch;
}

float Camera::GetYaw() {
	return Yaw;
}

float Camera::GetRoll() {
	return Roll;
}

void Camera::moveForward(float dt)
{
	forward.scale(dt * speed);
	position = position + forward;
}

void Camera::moveBackwards(float dt)
{
	forward.scale(dt * speed);
	position = position - forward;
}

void Camera::moveLeft(float dt) {
	right.scale(dt * speed);
	position = position - right;
}

void Camera::moveRight(float dt) {
	right.scale(dt * speed);
	position = position + right;
}

void Camera::SetForward(float x, float y, float z) {
	forward.x = x;
	forward.y = y;
	forward.z = z;
}

Vector3 Camera::GetForward() {
	return forward;
}