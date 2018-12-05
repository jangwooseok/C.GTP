#pragma once
#include <GL/freeglut.h>
//#include "../../import/GL/glut.h"
#include <cmath>
#include "float3.h"


#define WWIDTH 800
#define WHEIGHT 600
#define DEPTH 400

template<typename Vector3>
float Length(Vector3&& vec) { return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z); }
#define PI 3.14
template<typename Vector3>
Vector3 Normalize(Vector3&& vec)
{
	float fLength = Length(vec);
	if (fLength == 0) return Vector3{ 0, 0, 0 };
	return Vector3{ vec.x / fLength, vec.y / fLength, vec.z / fLength };
}

template<typename Vector3>
class Camera
{
	Vector3 m_at{ 0.f, 0.f, 0.f };
	Vector3 m_up{ 0.f, 1.f, 0.f };

	float m_distance{ 0 };

	float m_vertical{ PI*0.5f };
	float m_horizontal{ 0 };

	float m_aspect{ 0 };
	float m_near{ 0.f };
	float m_far{ 1.f };
	float m_fovy{ 0 };

public:
	Camera()
		// 카메라 생성 시 최초 1회는 aspect를 자동으로 설정한다.
		: m_aspect{ glutGet(GLUT_WINDOW_WIDTH) / static_cast<float>(glutGet(GLUT_WINDOW_HEIGHT)) }
	{
	}
	Camera(float aspect)
		// 카메라 생성 시 최초 1회는 aspect를 자동으로 설정한다.
		: m_aspect{ aspect }
	{
	}

	~Camera() = default;

	void Initialize(const Vector3 & pos, float distance, float zNear, float zFar, float fov)
	{
		m_fovy = fov;
		m_near = zNear;
		m_far = zFar;
		m_distance = distance;
		m_at = pos;
	}

	void SetAspect(float aspect) { m_aspect = aspect; }
	Vector3 GetPosition()   const { return m_at; }

	void SetAt(const Vector3& pos) { m_at = pos; LookAt(); }
	//void SetAt(Vector3&& pos)   noexcept { m_at = std::move(pos); LookAt(); }
	void Move(const Vector3& pos)   noexcept { SetAt(m_at + pos); }
	//void Move(Vector3&& pos)      noexcept { SetPosition(m_at + std::move(pos)); }

	void SetDistance(const float& d) { m_distance = fmax(d, m_near); }
	float GetDistance() const { return m_distance; }

	void zoom(float per) {m_distance = m_distance * per; }

	void Rotate(float v, float h)
	{
		m_vertical += v;
		if (-PI * 0.5f <= m_horizontal + h && m_horizontal + h <= PI * 0.5f)
			m_horizontal += h;
	}

	void LookAt() const
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		Vector3 vEye{ eye() };

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluPerspective(m_fovy, m_aspect, m_near, m_far);

		gluLookAt(
			vEye.x, vEye.y, vEye.z,      //카메라의 위치
			m_at.x, m_at.y, m_at.z,   //(촛점)바라보는곳
			m_up.x, m_up.y, m_up.z      //업벡터
		);
	}

	void LookAtOrtho() const
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		Vector3 vEye{ eye() };
		
		// 윈도우 사이즈에 맞춰서 임의로 바꿈
		glOrtho(-WWIDTH / 2, WWIDTH/2, -WHEIGHT/2, WHEIGHT/2, 5, 6000);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		gluLookAt(
			vEye.x, vEye.y, vEye.z,      //카메라의 위치
			m_at.x, m_at.y, m_at.z,		//바라보는곳
			m_up.x, m_up.y, m_up.z      //업벡터
		);

	}

	Vector3 GetLookVector() const
	{
		return Normalize(Vector3
			{
			   cos(m_horizontal) * cos(m_vertical),
			   sin(m_horizontal),
			   cos(m_horizontal) * sin(m_vertical)
			});
	}

	Vector3 eye() const { return GetPosition() - GetLookVector() * m_distance; }
};