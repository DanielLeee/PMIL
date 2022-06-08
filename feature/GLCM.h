#pragma once

#include "config.h"

typedef struct glcmFeature 
{
	double    dCorrelation;        
	double    dEnergy;            
	double    dEntropy;            
	double    dInertiaQuadrature;    
	double    dLocalCalm;                
} glcmFeature;

/*
typedef struct glcmFeatureVar 
{
	double    dAveCorrelation;    
	double    dAveEnergy;    
	double    dAveEntropy;    
	double    dAveInertiaQuadrature;
	double    dAveLocalCalm;    
	double    dVarCorrelation;    
	double    dVarEnergy;        
	double    dVarEntropy;        
	double    dVarInertiaQuadrature;
	double    dVarLocalCalm;        
} glcmFeatureVar;
*/

class ZBGLCM
{
public:    
	ZBGLCM();    
	~ZBGLCM();
     
	void ComputeMatrix(BYTE **LocalImage, int LocalImageWidth);      
	void ComputeFeature(double&FeatureEnergy, double&FeatureEntropy, 
	double&FeatureInertiaQuadrature, double&FeatureCorrelation, 
	double&FeatureLocalCalm, int** pMatrix, int dim);
	glcmFeature pGLCMF;
	//glcmFeatureVar pGLCMFVar;
	glcmFeature GLCMFeature(const Mat& gray,int FilterWindowWidth,int dir);    
	//glcmFeatureVar GLCMFeatureVar(BYTE* ImageArray,long ImageWidth,long ImageHeight,int FilterWindowWidth);
     
public:    
	double FeatureLocalCalmRD;    
	double FeatureLocalCalmLD;    
	double FeatureLocalCalmV;    
	double FeatureLocalCalmH;
	double FeatureCorrelationRD;
	double FeatureCorrelationLD;
	double FeatureCorrelationV;    
	double FeatureCorrelationH;    
	double FeatureInertiaQuadratureRD;
	double FeatureInertiaQuadratureLD;
	double FeatureInertiaQuadratureV;
	double FeatureInertiaQuadratureH;
	double FeatureEntropyRD;
	double FeatureEntropyLD;
	double FeatureEntropyV;    
	double FeatureEntropyH;    
	double FeatureEnergyRD;    
	double FeatureEnergyLD;    
	double FeatureEnergyV;    
	double FeatureEnergyH;    
 	
	int distance;    
	int GrayLayerNum;	
	int** PMatrixRD;
	int** PMatrixLD;    
	int** PMatrixV;    
	int** PMatrixH;    
};
