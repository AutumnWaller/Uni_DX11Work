#include "Camera.h"




Camera::Camera(XMVECTOR _Eye, XMVECTOR _At, XMVECTOR _Up)
{
	XMStoreFloat4x4(_pEye, _Eye);
	XMStoreFloat4x4(_pAt, _At);
	XMStoreFloat4x4(_pUp, _Up);


	XMStoreFloat4x4(&view, XMMatrixLookAtLH(_Eye, _At, _Up));

	// Initialize the projection matrix
	XMStoreFloat4x4(&projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _WindowWidth / (FLOAT)_WindowHeight, 0.01f, 100.0f));

}


Camera::~Camera()
{
}
