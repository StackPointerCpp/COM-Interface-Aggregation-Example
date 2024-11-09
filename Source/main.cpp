#include "main.h"

int main()
{
	// Declare IFace interface
	IFace* pFace = NULL;

	// Retrieve IFace pointer
	GetFace(NULL, IID_PPV_ARGS(&pFace));

	// Call IFace methods
	pFace->FirstSampleMethod(1);
	pFace->SecondSampleMethod(2);
	pFace->ThirdSampleMethod(3);

	// ReleasepFace pointer
	pFace->Release();

	// Return
	return 0;
}