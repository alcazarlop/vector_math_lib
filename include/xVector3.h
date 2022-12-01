
#ifndef __XVECTOR3_H__
#define __XVECTOR3_H__ 1

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <xmmintrin.h>

struct xVector3 {

	__forceinline xVector3() {}
	__forceinline explicit xVector3(float x, float y, float z) { xmm = _mm_setr_ps(x, y, z, 0.0f); }
	__forceinline explicit xVector3(float value) { xmm = _mm_set1_ps(value); }
	__forceinline explicit xVector3(const float* p) { xmm = _mm_setr_ps(p[0], p[1], p[2], 0.0f); }
	__forceinline explicit xVector3(__m128 m) { xmm = m; }
	__forceinline xVector3 xVector3i(int x, int y, int z) { return xVector3((float)x, (float)y, (float)z); }

	__forceinline float __vectorcall x() const { return _mm_cvtss_f32(xmm); }
	__forceinline float __vectorcall y() const { return _mm_cvtss_f32(_mm_shuffle_ps(xmm, xmm, 0b01010101)); }
	__forceinline float __vectorcall z() const { return _mm_cvtss_f32(_mm_shuffle_ps(xmm, xmm, 0b10101010)); }

	__forceinline void __vectorcall store(float* p) const { p[0] = x(); p[1] = y(); p[2] = z(); }

	__forceinline void __vectorcall setX(float x) { 
		xmm = _mm_move_ss(xmm, _mm_set_ss(x)); 
	} 
	__forceinline void __vectorcall setY(float y) {
		__m128 temp = _mm_move_ss(xmm, _mm_set_ss(y));
		temp = _mm_shuffle_ps(temp, temp, 0b11100000);
		xmm = _mm_move_ss(temp, xmm);
	}
	__forceinline void __vectorcall setZ(float z) {
		__m128 temp = _mm_move_ss(xmm, _mm_set_ss(z));
		temp = _mm_shuffle_ps(temp, temp, 0b11000100);
		xmm = _mm_move_ss(temp, xmm);
	}

	__forceinline float __vectorcall operator[] (size_t i ) const { return xmm.m128_f32[i]; }
	__forceinline float& __vectorcall operator[] (size_t i ) { return xmm.m128_f32[i]; }

	__m128 xmm;

};

xVector3 __vectorcall operator+(xVector3 a, xVector3 b){
	a.xmm = _mm_add_ps(a.xmm, b.xmm);
	return a;
}

__forceinline xVector3& __vectorcall operator+=(xVector3 a, xVector3 b){
	a = a + b;
	return a;
}

__forceinline xVector3 __vectorcall operator-(xVector3 a, xVector3 b){
	a.xmm = _mm_sub_ps(a.xmm, b.xmm);
	return a;
}

__forceinline xVector3& __vectorcall operator-=(xVector3 a, xVector3 b){
	a = a - b;
	return a;
}

__forceinline xVector3 __vectorcall operator*(xVector3 a, xVector3 b){
	a.xmm = _mm_mul_ps(a.xmm, b.xmm);
	return a;
}

__forceinline xVector3 __vectorcall operator*(xVector3 a, float b){
	a.xmm = _mm_mul_ps(a.xmm, _mm_set1_ps(b));
	return a;
}

__forceinline xVector3 __vectorcall operator*(float a, xVector3 b){
	b.xmm = _mm_mul_ps(_mm_set1_ps(a), b.xmm);
	return b;
}

__forceinline xVector3& __vectorcall operator*=(xVector3 a, xVector3 b){
	a = a * b;
	return a;
}

__forceinline xVector3& __vectorcall operator*=(xVector3 a, float b){
	a = a * b; 
	return a;
}

__forceinline xVector3 __vectorcall operator/(xVector3 a, xVector3 b){
	a.xmm = _mm_div_ps(a.xmm, b.xmm);
	return a;
}

__forceinline xVector3 __vectorcall operator/(xVector3 a, float b){
	a.xmm = _mm_div_ps(a.xmm, _mm_set1_ps(b));
	return a;
}

__forceinline xVector3 __vectorcall operator/(float a, xVector3 b){
	b.xmm = _mm_div_ps(_mm_set1_ps(a), b.xmm);
	return b;
}

__forceinline xVector3& __vectorcall operator/=(xVector3 a, xVector3 b){
	a = a / b;
	return a;
}

__forceinline xVector3& __vectorcall operator/=(xVector3 a, float b){
	a = a / b; 
	return a;
}

__forceinline xVector3 __vectorcall operator==(xVector3 a, xVector3 b){
	a.xmm = _mm_cmpeq_ps(a.xmm, b.xmm);
	return a;
}

__forceinline xVector3 __vectorcall operator!=(xVector3 a, xVector3 b){
	a.xmm = _mm_cmpneq_ps(a.xmm, b. xmm);
	return a;
}

__forceinline xVector3 __vectorcall operator>(xVector3 a, xVector3 b){
	a.xmm = _mm_cmpgt_ps(a.xmm, b.xmm);
	return a;
}

__forceinline xVector3 __vectorcall operator<(xVector3 a, xVector3 b){
	a.xmm = _mm_cmplt_ps(a.xmm, b.xmm);
	return a;
}

__forceinline xVector3 __vectorcall operator>=(xVector3 a, xVector3 b){
	a.xmm = _mm_cmpge_ps(a.xmm, b.xmm);
	return a;
}

__forceinline xVector3 __vectorcall operator<=(xVector3 a, xVector3 b){
	a.xmm = _mm_cmple_ps(a.xmm, b.xmm);
	return a;
}

__forceinline xVector3 __vectorcall operator-(xVector3 a){
	return xVector3(_mm_setzero_ps()) - a;
}

__forceinline xVector3 __vectorcall Abs(xVector3 a){
	a.xmm = _mm_andnot_ps(_mm_set_ps(0x80000000, 0x80000000, 0x80000000, 0x80000000), a.xmm);
	return a;
}

__forceinline xVector3 __vectorcall Max(xVector3 a, xVector3 b){
	a.xmm = _mm_max_ps(a.xmm, b.xmm);
	return a;
}

__forceinline xVector3 __vectorcall Min(xVector3 a, xVector3 b){
	a.xmm = _mm_min_ps(a.xmm, b.xmm);
	return a;
}

__forceinline xVector3 __vectorcall Clamp(xVector3 t, xVector3 a, xVector3 b){
	return Min(Max(t, a), b);
}

__forceinline float __vectorcall Sum(xVector3 v){
	return v.x() + v.y() + v.z();
}

__forceinline float __vectorcall DotProduct(xVector3 a, xVector3 b){
	return Sum(a * b);
}

__forceinline float __vectorcall Magnitude(xVector3 a){
	return sqrtf(DotProduct(a, a));
}

__forceinline float __vectorcall SqrMagnitude(xVector3 a){
	return DotProduct(a, a);
}

__forceinline float __vectorcall Angle(xVector3 a, xVector3 b){
	return acosf(DotProduct(a ,b) / (Magnitude(a) * Magnitude(b)));
}

__forceinline float __vectorcall Distance(xVector3 a, xVector3 b){
	return Magnitude(a - b);
} 

__forceinline xVector3 __vectorcall Normalize(xVector3 a){
	return a * (1.0f / Magnitude(a));
}

__forceinline xVector3 __vectorcall LerpUnclamped(xVector3 a, xVector3 b, float t){
	return a + (b - a) * t;
}

// __forceinline xVector3 __vectorcall Lerp(xVector3 a, xVector3 b, float t){

// }

// __forceinline xVector3 __vectorcall CrossProduct(xVector3 a, xVector3 b){

// }

__forceinline xVector3 __vectorcall Reflect(xVector3 direction, xVector3 normal){
	return (direction - normal * (DotProduct(direction, normal) * 2.0f));
}

__forceinline xVector3 __vectorcall Scale(xVector3 a){
	return xVector3(a * a);
}


void Print(xVector3* p){
	float* pointer = (float*)&p->xmm;
	printf("X[%03f] Y[%f] Z[%f] \n", pointer[0], pointer[1], pointer[2]);
}

#endif // __XVECTOR3_H__
