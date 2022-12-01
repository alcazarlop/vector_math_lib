
#include <stdio.h>
#include <chrono>
#include "xVector3.h"
#include "vector_3.h"

const unsigned int kRepetitions = 100;

void MeasureVector3(){

	xVector3 v1 = xVector3(1.0f, 2.0f, 3.0f);
	xVector3 v2 = xVector3(3.0f, 2.0f, 1.0f);
	xVector3 res;

	xVector3 vecA = xVector3(12.0f, 27.0f, 50.0f);
	xVector3 vecB = xVector3(8.0f, 95.0f, 12.0f);

	float f_res = 0.0f;

	std::chrono::time_point<std::chrono::high_resolution_clock> start_point, end_point;
	start_point = std::chrono::high_resolution_clock::now();

		for(unsigned int i = 0; i < kRepetitions; ++i){
			res = res + v2;
			f_res = DotProduct(vecA, vecB);
			f_res = Magnitude(vecA);
			f_res = SqrMagnitude(vecA);
			f_res = Angle(vecA, vecB);
			f_res = Distance(vecA, vecB);
		}

	end_point = std::chrono::high_resolution_clock::now();
	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_point).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_point).time_since_epoch().count();

	printf("ASM Time: %lld\n",(end - start));
	float* pointer = (float*)&res.xmm;
	printf("X[%03f] Y[%f] Z[%f] \n", pointer[0], pointer[1], pointer[2]);
}

void MeasureVec3(){

	Vec3 v1 = Vec3(1.0f, 2.0f, 3.0f);
	Vec3 v2 = Vec3(5.0f, 4.0f, 3.0f);
	Vec3 res = Vec3();

	std::chrono::time_point<std::chrono::high_resolution_clock> start_point, end_point;
	start_point = std::chrono::high_resolution_clock::now();

	for(unsigned int i = 0; i < kRepetitions; ++i){
		res = v1 + v2;
	}

	end_point = std::chrono::high_resolution_clock::now();
	auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_point).time_since_epoch().count();
	auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_point).time_since_epoch().count();
	
	printf("C++ Time: %lld\n",(end - start));
}

void CheckVectorOperations(){

	xVector3 vecA = xVector3(12.0f, 27.0f, 50.0f);
	xVector3 vecB = xVector3(8.0f, 95.0f, 12.0f);
	xVector3 res = xVector3();

	float f_res = 0.0f;

	// float scalar = 10.0f;
	// res = vecA + vecB;
	// Print(&res);

	// res = vecA - vecB;
	// Print(&res); 

	// res = vecA * scalar;
	// Print(&res);

	f_res = DotProduct(vecA, vecB);
	printf("Resultado DotProduct: %f\n", f_res);

	f_res = Magnitude(vecA);
	printf("Resultado Magnitude: %f\n", f_res);

	f_res = SqrMagnitude(vecA);
	printf("Resultado SqrMagnitude: %f\n", f_res);

	f_res = Angle(vecA, vecB);
	printf("Resultado Angle: %f\n", f_res);

	f_res = Distance(vecA, vecB);
	printf("Resultado Distance: %f\n", f_res);

	res = Normalize(vecB);
	Print(&res);

	res = Scale(vecB);
	Print(&res);

	res = Reflect(vecB, vecA);
	Print(&res);

}

int main(int argc, char** argv){
	argc = 0;
	argv = NULL;

	MeasureVec3();
	system("pause");
	MeasureVector3();
	// CheckVectorOperations();

	return 0;
}